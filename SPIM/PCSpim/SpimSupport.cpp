#include "stdafx.h"

#include "PCSpim.h"

#include "PCSpimView.h"
#include "ConsoleWnd.h"

// Necessary SPIM globals
int bare_machine;                /* Non-zero => simulate bare machine */
int accept_pseudo_insts;	 /* Non-Zero => parse pseudo instructions  */
int delayed_branches;		 /* Non-zero => simulate delayed branches */
int delayed_loads;		 /* Non-zero => simulate delayed loads */
int quiet;			 /* Non-zero => no warning messages */
int source_file;		 /* Non-zero => program is source, not binary */
char * trap_file = NULL;	 /* The path from which to load the trap handler, if desired */
port message_out, console_out;
int mapped_io;			 /* Non-zero => activate memory-mapped IO */


int console_input_available()
{
  if (mapped_io)
    {
      ((CPCSpimApp *)AfxGetApp())->RunMessageLoop();

      return g_pView->GetConsole()->AreKeysAvailable();
    }
  else
    return 0;
}


void control_c_seen(int arg)
{
  g_pView->SendMessage(WM_COMMAND, MAKEWPARAM(ID_SIMULATOR_BREAK, 0), 0);
}


#define IO_BUFFSIZE 10000
void error(char *fmt, ...)
{
  va_list args;
  char io_buffer [IO_BUFFSIZE];

  va_start (args, fmt);
  vsprintf (io_buffer, fmt, args);
  va_end (args);

  write_output(message_out, io_buffer);
}


void fatal_error(char *fmt, ...)
{
  CString strMsg, strErrText;

  va_list args;
  va_start(args, fmt);

  // Get the error message.
  _vsnprintf(strErrText.GetBuffer(2048), 2048, fmt, args);
  strErrText.ReleaseBuffer();
  strErrText.TrimLeft();
  strErrText.TrimRight();

  // Create the message box contents.
  strMsg.Format(
		"A fatal error has occurred within the SPIM simulator.\n"
		"The error message is:\n"
		"\n"
		"%s\n"
		"\n"
		"Would you like to attempt to continue?", strErrText);

  // Prompt the user.
  if (IDYES == MessageBox(NULL, strMsg, NULL, MB_YESNO | MB_ICONEXCLAMATION))
    return;
  else
    exit(-1);
}


char get_console_char()
{
  g_pView->BringConsoleToTop();
  CPCSpimApp *pApp = (CPCSpimApp *)AfxGetApp();

  // Loop until the user presses a key.
  while (!force_break)
    {
      pApp->RunMessageLoop();
      if (g_pView->GetConsole()->AreKeysAvailable())
	return g_pView->GetConsole()->GetKeyPress();
    }

  return 0;
}


void put_console_char(char c)
{
  char buf[4];

  buf[0] = c;
  buf[1] = '\0';

  write_output(console_out, buf);
}


void read_input(char *str, int str_size)
{
  char ch;

  // We assume that get_console_char will "do the right thing" wrt the msg
  // pump, etc.
  while ((1 < str_size) && (!force_break))
    {
      ch = get_console_char();
      *str = ch;
      ++str;
      --str_size;
      put_console_char(ch);

      // Read just one line.
      if (ch == '\n')
	break;
    }

  if (0 < str_size)
    *str = '\0';
}


int* run_error (char *fmt, ...)
{
  va_list args;
  char io_buffer [IO_BUFFSIZE];

  va_start (args, fmt);
  vsprintf (io_buffer, fmt, args);
  va_end (args);

  write_output(message_out, io_buffer);

  // Force a break;
  force_break = 1;

  return 0;
}


void write_output (port fp, char *fmt, ...)
{
  CString strBuf;
  va_list args;

  va_start(args, fmt);
  _vsnprintf(strBuf.GetBuffer(IO_BUFFSIZE), IO_BUFFSIZE, fmt, args);
  strBuf.ReleaseBuffer();
  va_end(args);

  if (fp.i == message_out.i)
    g_pView->WriteToMessage(strBuf);
  else if (fp.i == console_out.i)
    {
      g_pView->MakeConsoleVisible();
      g_pView->WriteToConsole(strBuf);
    }
  else
    error("Internal error in calling write_output!");
}
