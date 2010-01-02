.>c:.>o

# SPIM needs a DPMI server when compiled with DJGPP.
# PMODE/DJ can be found at:
#   ftp://ftp.simtel.net/pub/simtelnet/gnu/djgpp/v2misc/pmode11b.zip
PMODESTUB = c:\djgpp\bin\pmodstub.exe

CC = gcc
IFLAGS =
CL_FLAG =
CFLAGS = -g $(IFLAGS) $(CL_FLAG)
LDFLAGS = -lm

all: spimsfx.exe builder spiminst
	strip spiminst
	copy /b $(PMODESTUB)+spiminst spiminst.exe
	djp spiminst
	builder

spimsfx.exe:
	cd build
	lha a -rx1 ..\spimsfx *.*
	cd ..
	lha s -x1 spimsfx

builder: builder.o
	$(CC) -g builder.o $(LDFLAGS) -o builder
	
spiminst: spiminst.o
	$(CC) -g spiminst.o $(LDFLAGS) -o spiminst

clean:
	rm -f spimdos.exe builder.exe builder spiminst.exe spiminst *.o \
		  spimsfx.*
