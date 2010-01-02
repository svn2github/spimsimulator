#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <dirent.h>
#include <fcntl.h>

#include "spiminst.h"

#define FALSE 	(1 != 1)
#define TRUE	!FALSE

/* Function decl's */
void corrupt();
void Welcome();
int DirExists(const char *szDir);
const char * AskDir();
int CreateAndGoToDir(const char * szDestDir);
const char * MakeTempSFX(const char * argv0);


int main(int argc, char **argv)
{
	FILE * f;
	const char *szTempSFX;
	const char *szDestDir;

	Welcome();
	szDestDir = AskDir();
	if (!CreateAndGoToDir(szDestDir))
		goto l_Exit;

	szTempSFX = MakeTempSFX(argv[0]);
	if (szTempSFX == NULL)
		goto l_Exit;

	/* Execute the SFX */
	spawnl(P_WAIT, szTempSFX, szTempSFX, 0);

	/* Informative message to the user */
	printf("\n\n");
	printf("For more information about PC SPIM for DOS:\n");
	printf("\tSPIMMAN.TXT -- The SPIM 'man' page\n");
	printf("\tBUILDING.TXT -- How to build PC SPIM from source code\n");
	printf("\tHTMLDOCS\\SPIM.HTM -- The SPIM manual in HTML\n");
	printf("\n");

	/* Cleanup */
l_Exit:
	/* Remove the temporary file */
	unlink(szTempSFX);

	/* Eat up any pending key presses (to prevent unintended commands) */
	while (kbhit())
		getkey();

	return 0;
}


void corrupt()
{
	printf("This archive file is corrupted.  Please obtain a new copy.\n");
}


void Welcome()
{
	printf("Welcome to the PCSPIM for DOS Installation!\n");
}


int DirExists(const char *szDir)
{
	DIR *d;
	d = opendir(szDir);
	if (d == NULL)
		return FALSE;
	else
	{
		closedir(d);
		return TRUE;
	}
}


const char * MakeTempSFX(const char *argv0)
{
	FILE *f, *fTmp;
	unsigned char *rgbBuf = NULL;
	unsigned char rgbKey[] = FILEIDKEY;
	int i, iChar, cbFile, cbTmpFile;
	const char *szFilename;

	f = fopen(argv0, "rb");

	/* Get the file size */
	fseek(f, 0, SEEK_END);
	cbFile = ftell(f);

	/* Go back to the beginning, and read the file in */
	fseek(f, 0, SEEK_SET);
	rgbBuf = malloc(cbFile);
	if (1 != fread(rgbBuf, cbFile, 1, f))
	{
		corrupt();
		return NULL;
	}
	fclose(f);

	/* Scan through the file, looking for the ID key */
	iChar = 0;
	for (i = 0; i < cbFile; i++)
	{
		if (rgbKey[iChar] == rgbBuf[i])
			++iChar;
		else
			iChar = 0;

		if (iChar == sizeof(rgbKey))
		{
			i++;
			break;
		}
	}

	if (iChar != sizeof(rgbKey))	/* Did not find the key */
	{
		corrupt();
		return NULL;
	}

	/* Find the size of the sfx */
	cbTmpFile = cbFile - i;

	/* Pull the sfx off our tail, and place it in a temp file */
	szFilename = tmpnam(NULL);
	fTmp = fopen(szFilename, "wb");
	fwrite(&rgbBuf[i], cbTmpFile, 1, fTmp);
	
	fclose(fTmp);
	free(rgbBuf);

	return szFilename;
}


int IsValidFileName(char * szFile)
{
	char szShort[64];	/* Just some extra space */
	return (stricmp(_lfn_gen_short_fname(szFile, szShort), szFile) == 0);
}


int IsValidPath(char *szPath)
{
	char *szTemp = NULL;
	char *szPiece = NULL;

	/* We'll assume that most LFN paths are valid. */
	if (_USE_LFN)
		return TRUE;
	
	szTemp = (char*)strdup(szPath);
	szPiece = (char*)strtok(szTemp, "\\");
	while (szPiece != NULL)
	{
		if (!IsValidFileName(szPiece))
			return FALSE;

		szPiece = strtok(NULL, "\\");
	}
	free(szTemp);

	return TRUE;
}


const char * AskDir()
{
	static char szDestDir[2048] = {0};
	int cbDir;

	while (1)
	{
		/* Ask the user for the destination directory */
		printf("\nDestination directory: ");
		fgets(szDestDir, 2047, stdin);

		/* Remove the trailing CRLF */
		cbDir = strlen(szDestDir);
		if ((cbDir > 0) && (szDestDir[cbDir - 1] == '\n'))
			szDestDir[cbDir - 1] = NULL;

		if ((szDestDir[0] == NULL) || (!IsValidPath(szDestDir)))
		{
			printf("\"%s\" is not a valid filename.  Try again.\n", szDestDir);
			fflush(stdout);
		}
		else if (DirExists(szDestDir))
		{
			char chYesNo;

			printf("\"s\" already exists.  Are you sure? ", szDestDir);
			fflush(stdout);
			while (1)
			{
			  chYesNo = toupper(getkey());
			  if ((chYesNo == 'Y') || (chYesNo == 'N'))
				  break;
			}
			printf("%c\n", chYesNo);
			fflush(stdout);

			if (chYesNo == 'Y')
				break;
		}
		else
		{
			while (kbhit())		/* Flush the KBD buffer */
				getkey();
			printf("\nPCSpim for DOS will be installed to \"%s\"\n"
				"Press any key to finish installation.",
				szDestDir);
			fflush(stdout);
			while (!kbhit());	/* Wait for a keypress */
			break;
		}
	}

	return szDestDir;
}


int CreateAndGoToDir(const char * szDestDir)
{
	/* Try to create the destination dir, and go there */
	if (!DirExists(szDestDir) && (0 != mkdir(szDestDir, 0)))
	{
		printf("Could not create destination directory.");
		return FALSE;
	}
	chdir(szDestDir);

	return TRUE;
}


