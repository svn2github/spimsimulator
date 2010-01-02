#include <stdio.h>
#include <stdlib.h>

#include "spiminst.h"

long fsize(FILE *f);
void fcat(FILE *fDest, char *szSrc);

void main()
{
	FILE *f;
	unsigned char rgbKey[] = FILEIDKEY;

	f = fopen("spimdos.exe", "wb");
	fcat(f, "spiminst.exe");
	fwrite(rgbKey, sizeof(rgbKey), 1, f);
	fcat(f, "spimsfx.exe");

	fclose(f);
}


long fsize(FILE *f)
{
	fseek(f, 0, SEEK_END);
	return ftell(f);
}


void fcat(FILE *fDest, char *szSrc)
{
	FILE *fSrc;
	long cbFile;
	char *rgbBuf;

	fSrc = fopen(szSrc, "rb");
	cbFile = fsize(fSrc);
	fseek(fSrc, 0, SEEK_SET);
	rgbBuf = malloc(cbFile);
	if (1 != fread(rgbBuf, cbFile, 1, fSrc))
	{
		printf("Could not read %s!\n", szSrc);
		exit(1);
	}
	fwrite(rgbBuf, cbFile, 1, fDest);
	free(rgbBuf);
	fclose(fSrc);
}

