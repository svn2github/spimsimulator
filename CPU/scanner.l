%{
/* SPIM S20 MIPS simulator.
   Lexical scanner.

   Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu).
   ALL RIGHTS RESERVED.

   SPIM is distributed under the following conditions:

     You may make copies of SPIM for your own use and modify those copies.

     All copies of SPIM must retain my name and copyright notice.

     You may not sell SPIM or distributed SPIM in conjunction with a
     commerical product or service without the expressed written consent of
     James Larus.

   THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE. */


/* $Header: $
*/


#include "spim.h"
#include "string-stream.h"
#include "spim-utils.h"
#include "inst.h"
#include "reg.h"
#include "sym-tbl.h"
#include "parser.h"
#include "scanner.h"
#include "y.tab.h"

#ifndef YY_CHAR
#define YY_CHAR char
#endif


/* Exported Variables: */

int only_id;
int line_no;		/* Line number in input file*/


/* Local Variables: */

/* Track which line we are reading and where it began in the buffer. */
static int current_line_no = 0;

static YY_CHAR *current_line = NULL;


static double scan_float;	/* Where FP values are kept */

static int line_returned = 0;	/* Returned current line yet? */

static int eof_returned = 0;	/* Return EOF token yet? */


/* Local functions: */

static int check_keyword (YY_CHAR *id, int allow_pseudo_ops);
static YY_CHAR *copy_str (YY_CHAR *str, int chop);
static YY_CHAR scan_escape (YY_CHAR **str);


#undef yywrap

%}

%%

[ \t]		       {
		        if (current_line == NULL)
			  {
			    current_line_no = line_no;
			    current_line = yytext;
			  }
		       }


[\n]			{
			 line_no += 1;
			 return (Y_NL);
			}

[\r]			{ /* Ignore carrage returns */ }

[;]			{
			 return (Y_NL);
			}


[\001]		{	/* Marker character inserted to allow scanner to
				   return Y_EOF before returning hard EOF. */
			  return (Y_EOF);
			}

"#".*		{
				/* Ignore comments */
			}


(-[0-9]+)|([0-9]+)	{
			 if (current_line == NULL)
			   {
			     current_line_no = line_no;
			     current_line = yytext;
			   }
			 yylval.i = atoi (yytext);
			 return (Y_INT);
			}


((0x)|(-0x))[0-9A-Fa-f]+ {
			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }
			  if (*yytext == '-')
			    {
			      sscanf(yytext+3, "%x", &(yylval.i));
			      yylval.i = -yylval.i;
			    }
			  else
			    {
			      sscanf(yytext+2, "%x", &(yylval.i));
			    }
			  return (Y_INT);
			}


(\+|\-)?[0-9]+\.[0-9]*(e)?(\+|\-)?[0-9]* {
			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }
			  scan_float = atof (yytext);
			  yylval.p = (double*) &scan_float;
			  return (Y_FP);
			}


[a-zA-Z_\.][a-zA-Z0-9_\.]* {
			  int token = check_keyword (yytext,
						     !bare_machine
						     && accept_pseudo_insts);
			  label *l;

			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }

			  if (!only_id && token != 0)
			    {
			      /* Keyword */
			      yylval.i = token;
			      current_line = yytext;
			      return (token);
			    }

			  if (only_id && token != 0)
			    yyerror ("Cannot use opcodes as labels");

			  if ((l = label_is_defined (yytext)) != NULL
			      && l->const_flag)
			    {
			      /* Defined label */
			      yylval.i = (int) l->addr;
			      return (Y_INT);
			    }
			  else
			    {
			      /* Not-yet defined label */
			      yylval.p = (char*) str_copy (yytext);
			      return (Y_ID);
			    }
			}


\$[a-zA-Z0-9_\.$]+	{
			  int reg_no = register_name_to_number (yytext + 1);

			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }

			  if (reg_no != -1
			      && *(yytext + 1) == 'f'
			      && *(yytext + 2) != 'p')
			    {
			      /* Floating point register ($f0) */
			      yylval.i = reg_no;
			      return (Y_FP_REG);
			    }

			  if (0 <= reg_no && reg_no < R_LENGTH)
			    {
			      /* Register ($r0) */
			      yylval.i = reg_no;
			      return (Y_REG);
			    }
			  else
			    {
			      /* Otherwise, an integer or identifier */
			      label *l = label_is_defined (yytext);

			      if (l != NULL && l->const_flag)
				{
				  yylval.i = (int) l->addr;
				  return (Y_INT);
				}
			      else
				{
				  yylval.p = (char*) str_copy (yytext);
				  return (Y_ID);
				}
			    }
			}


[:()+-]|">"|"="		{
			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }
			  return (*yytext);
			}


","			{
			 if (current_line == NULL)
			   {
			     current_line_no = line_no;
			     current_line = yytext;
			   }
			 /* Skip commas */
		        }

"?"			{
			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }
			  yylval.p = (char*) str_copy (yytext);
			  /* For top level */
			  return (Y_ID);
			}


\"(([^""])|(\\\"))*\"	{
			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }
			  yylval.p = (char*) copy_str (yytext + 1, 1);
			  return (Y_STR);
			}

\'(([^''])|(\\[^'']))\'	{
			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }

			    if (*(yytext + 1) == '\\')
			      {
				YY_CHAR *escape = yytext + 1;
				yylval.i = (int) scan_escape (&escape);
			      }
			    else
			      {
				yylval.i = (int) *(yytext + 1);
				return (Y_INT);
			      }
			}

.			{
			  if (current_line == NULL)
			    {
			      current_line_no = line_no;
			      current_line = yytext;
			    }
			  yyerror ("Unknown character");
			}


%%



void
initialize_scanner (FILE *in_file)
{
  yyin = in_file;
#ifdef FLEX_SCANNER
  yyrestart(in_file);
#if (YY_FLEX_MAJOR_VERSION==2 && YY_FLEX_MINOR_VERSION==5 && YY_FLEX_SUBMINOR_VERSION==33)
  /* flex 2.5.33 flips the polarity of this flag (sigh) */
  yy_init = 0;
#else
  yy_init = 1;
#endif
#endif
  line_no = 1;
  current_line = NULL;
  line_returned = 0;
  eof_returned = 0;
}


void
scanner_start_line ()
{
  current_line = NULL;
  line_returned = 0;
}


/* This is a work-around for a bug in flex v 2.5.31 (but not earlier or
   later versions such as 2.5.4) that left this symbol undefined. */

#ifndef yytext_ptr
#define yytext_ptr yytext
#endif


/* Use yywrap to insert a marker character, which causes the
   scanner to return Y_EOF, before return a hard EOF.  This
   wouldn't be necessary, except that bison does not allow
   the parser to use EOF (= 0) as a non-terminal */

int yywrap()
{
	if (eof_returned)
		return (1);
	else
	{
		unput ('\001');
		eof_returned = 1;
#ifdef FLEX_SCANNER
		yy_did_buffer_switch_on_eof = 1;
#endif
		return (0);
	}
}


/* A backslash has just been read, return the character designated by *STR.  */

static YY_CHAR
scan_escape (YY_CHAR **str)
{
  YY_CHAR first = **str;
  *str += 1;
  switch (first)
    {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case '\\': return '\\';
    case '"': return '"';
    case '\'': return '\'';

    case 'x':
    case 'X':
      {
	YY_CHAR c1 = **str, c2 = *(*str + 1);
	int b = 0;

	if ('0' <= c1 && c1 <= '9') b = c1 - '0';
	else if ('A' <= c1 && c1 <= 'F') b = c1 - 'A' + 10;
	else if ('a' <= c1 && c1 <= 'f') b = c1 - 'a' + 10;
	else yyerror ("Bad character in \\X construct in string");

	b <<= 4;
	if ('0' <= c2 && c2 <= '9') b += c2 - '0';
	else if ('A' <= c2 && c2 <= 'F') b += c2 - 'A' + 10;
	else if ('a' <= c2 && c2 <= 'f') b += c2 - 'a' + 10;
	else yyerror ("Bad character in \\X construct in string");

	*str += 2;
	return (YY_CHAR) b;
      }

    default:
      {
	char message[] = "Bad character \\X";
	message[strlen (message) - 1] = first;
	yyerror (message);
	return '\0';
      }
    }
}


/* Return a freshly-allocated copy of STRING with the last CHOP
   characters removed. */

static YY_CHAR *
copy_str (YY_CHAR *str, int chop)
{
  int new_len = strlen (str) - chop;
  YY_CHAR *new_str = (YY_CHAR *) xmalloc (new_len + 1), *n;

  for (n = new_str; *str != '\0' && new_len > 0; new_len -= 1)
    if (*str == '\\')
      switch (*(str + 1))
	{
	case 'n':
	  {
	    *n ++ = '\n';
	    str += 2;
	    new_len -= 1;
	    continue;
	  }
	case 't':
	  {
	    *n ++ = '\t';
	    str += 2;
	    new_len -= 1;
	    continue;
	  }
	case '"':
	  {
	    *n ++ = '"';
	    str += 2;
	    new_len -= 1;
	    continue;
	  }
	case '0':		/* \nnn */
	case '1':
	case '2':
	case '3':
	  {
	    YY_CHAR c2 = *(str + 2), c3 = *(str + 3);
	    int b = (*(str + 1) - '0') << 3;

	    if ('0' <= c2 && c2 <= '7')
	      b = (c2 - '0') << 3;
	    else
	      yyerror ("Bad character in \\ooo construct in string");

	    if ('0' <= c3 && c3 <= '7')
	      b += c3 - '0';
	    else
	      yyerror ("Bad character in \\ooo construct in string");

	    *n ++ = (YY_CHAR) b;
	    str += 4;
	    new_len -= 3;
	    continue;
	  }
	case 'X':
	  {
	    YY_CHAR c2 = *(str + 2), c3 = *(str + 3);
	    int b = 0;

	    if ('0' <= c2 && c2 <= '9')
	      b = c2 - '0';
	    else if ('A' <= c2 && c2 <= 'F')
	      b = c2 - 'A' + 10;
	    else
	      yyerror ("Bad character in \\X construct in string");

	    b <<= 4;
	    if ('0' <= c3 && c3 <= '9')
	      b += c3 - '0';
	    else if ('A' <= c3 && c3 <= 'F')
	      b += c3 - 'A' + 10;
	    else
	      yyerror ("Bad character in \\X construct in string");

	    *n ++ = (YY_CHAR) b;
	    str += 4;
	    new_len -= 3;
	    continue;
	  }
	default:
	  {
	    *n ++ = *str ++;
	    continue;
	  }
	}
    else
      *n ++ = *str ++;

  *n = '\0';
  return (new_str);
}


/* On a parse error, write out the current line and print a caret (^)
   below the point at which the error occured.	Also, reset the input
   stream to the begining of the next line. */

void
print_erroneous_line ()
{
  int prefix_length = yytext - current_line;
  int i, c;
  YY_CHAR buffer[1024], *bp = buffer;

  if (current_line == NULL) return;

  /* Print part of line that has been consumed. */
  if (0 <= prefix_length)
    {
      /* yytext and current_line point to same line */
      error ("	  ");
      c = *(current_line + prefix_length);
      *(current_line + prefix_length) = '\0';
      error ("%s", current_line);
      *(current_line + prefix_length) = (char)c;
      error ("%s", yytext);
    }
  else
    {
      /* yytext and current_line point to different lines */
      error ("	  ");
      error ("%s", current_line);
      prefix_length = strlen(current_line);
    }

  /* Flush the rest of the line (not consumed) from lex input. */
  if (*yytext != '\n')
    {
      while ((c = input ()) != '\n' && c != EOF && c != 1)
	*bp ++ = (char)c;
      *bp = '\0';
      error ("%s\n", buffer);
      if (c == '\n') unput ('\n');
      current_line = NULL;
    }

  /* Print marker to point at which consumption stopped. */
  if (1024 <= prefix_length) return;
  error ("	  ");
  for (i = 0; i < prefix_length; i ++) buffer[i] = ' ';
  buffer[i] = '\0';
  error ("%s^\n", buffer);
}


static name_val_val keyword_tbl [] = {
#undef OP
#define OP(NAME, OPCODE, TYPE, R_OPCODE) {NAME, OPCODE, TYPE},
#include "op.h"
};


static int
check_keyword (YY_CHAR *id, int allow_pseudo_ops)
{
  name_val_val *entry =
    map_string_to_name_val_val (keyword_tbl,
			     sizeof(keyword_tbl) / sizeof (name_val_val),
			     id);
  if (entry == NULL)
    return (0);
  else if (!allow_pseudo_ops && entry->value2 == PSEUDO_OP)
    return (0);
  else
    return (entry->value1);
}


static name_val_val register_tbl [] = {
  {"a0", 4, 0},
  {"a1", 5, 0},
  {"a2", 6, 0},
  {"a3", 7, 0},
  {"at", 1, 0},
  {"fp", 30, 0},
  {"gp", 28, 0},
  {"k0", 26, 0},
  {"k1", 27, 0},
  {"kt0", 26, 0},
  {"kt1", 27, 0},
  {"ra", 31, 0},
  {"s0", 16, 0},
  {"s1", 17, 0},
  {"s2", 18, 0},
  {"s3", 19, 0},
  {"s4", 20, 0},
  {"s5", 21, 0},
  {"s6", 22, 0},
  {"s7", 23, 0},
  {"s8", 30, 0},
  {"sp", 29, 0},
  {"t0", 8, 0},
  {"t1", 9, 0},
  {"t2", 10, 0},
  {"t3", 11, 0},
  {"t4", 12, 0},
  {"t5", 13, 0},
  {"t6", 14, 0},
  {"t7", 15, 0},
  {"t8", 24, 0},
  {"t9", 25, 0},
  {"v0", 2, 0},
  {"v1", 3, 0},
  {"zero", 0, 0}
};

int
register_name_to_number (char *name)
{
  int c1 = *name, c2 = *(name + 1);

  if ('0' <= c1 && c1 <= '9'
      && (c2 == '\0' || (('0' <= c2 && c2 <= '9') && *(name + 2) == '\0')))
    return (atoi (name));
  else if (c1 == 'f' && c2 >= '0' && c2 <= '9')
    return atoi (name + 1);
  else
    {
      name_val_val *entry =
	map_string_to_name_val_val (register_tbl,
				 sizeof (register_tbl) / sizeof (name_val_val),
				 name);
      if (entry == NULL)
	return (-1);
      else
	return (entry->value1);
    }
}


/* Exactly once, return the current source line, as a printable string
   with a line number.  Subsequent calls receive NULL instead of the
   line. */

char *
source_line ()
{
  if (line_returned)
    return (NULL);
  else if (current_line == NULL)	/* Error on line */
    return (NULL);
  else
    {
      YY_CHAR *eol1, c1;
      YY_CHAR *null1 = NULL;
      char *r;

      /* Find end of line: */
      for (eol1 = current_line; *eol1 != '\0' && *eol1 != '\n'; ) eol1 += 1;

#ifdef FLEX_SCANNER
      /* Ran into null byte, inserted by yylex. In necessary, look further
	 for newline. (This only works for scanners produced by flex. Other
         versions of lex need similar code, or source code lines will end
         early. */
      if (*eol1 == '\0' && yy_hold_char != '\n')
	{
	  null1 = eol1;
	  *eol1 = yy_hold_char;
	  for ( ; *eol1 != '\0' && *eol1 != '\n'; )
	    eol1 += 1;
	}
#endif

      /* Save end-of-line character and null terminate string so it can
	 be printed. */
      c1 = *eol1;
      *eol1 = '\0';

      r = (char *) xmalloc (eol1 - current_line + 10);
      sprintf (r, "%d: %s", current_line_no, current_line);

      /* Restore end-of-line character and, if necessary, yylex's null byte. */
      *eol1 = c1;
      if (null1 != NULL)
	{
	  *null1 = '\0';
	}
      line_returned = 1;
      return ((char *) r);
    }
}
