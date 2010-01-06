		  README FILE FOR SPIM, XSPIM, and PCSPIM
		  =======================================

This directory contains SPIM--an assembly language MIPS R2000/R3000
simulator. SPIM is covered by a BSD license.

Copyright (c) 1990-2010, James R. Larus.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

Neither the name of the James R. Larus nor the names of its contributors may be
used to endorse or promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



			       BUILDING SPIM
			       =============

These instructions explain how to compile and install spim and xspim.

It is not necessary to compile PCSpim (the Microsoft Windows version), as
the spim web site contains a precompiled version.

To build spim (the terminal version) or xspim (the X-windows and Mac
version):

1. Change to the directory "spim" to build spim. Change to the directory
"xspim" to build xspim

2. If necessary, edit the first few non-comment lines of the Makefile (or
the Imakefile if you are building xspim) to set the pathnames for your
system:

	EXCEPTION_DIR -- The full pathname of the directory in which to
			 install the SPIM exception handler.

	BIN_DIR -- The full pathname of the directory in which spim and
		   xspim should be installed.

	MAN_DIR -- The full pathname of the directory in which the manual
		   pages for spim and xspim should be installed.

In general, the remaining parameters need not be changed.


3. If you are building spim type:

	% make


4. If you are building xspim, type:

	% xmkmf
	% make

5. To run spim or xspim, the exception handler code must be installed in the
directory specified by the variable EXCEPTION_DIR in the Makefile.  If the
file "exceptions."s is not installed, spim and xspim fail with a message
before they start running.  You can either install this file by hand or by
typing

	% make install

which also installs spim, xspim, and the manual pages in the directories
that you set (above). If you use the default paths, then you will need root
permissions to install the files, so instead type:

	% sudo make install

This will prompt you for the root password.


6. To test that spim builds correctly, in the "spim" directory type

	% make test

and examine the output of the test.  (Note: the exception handler must be
installed before running the test.)


		     BUILDING SPIM ON MICROSOFT WINDOWS
		     ==================================

spim (the terminal version) works well on Microsoft Windows.  You can easily
build it using the Cygwin port of the GNU tools (see www.cygwin.com).

The Microsoft Windows version of spim is called PCSpim and is built using
Microsoft Visual Studio. You can get the files separately from
www.cs.wisc.edu/~larus/spim.html



			 NEW VERSIONS OF SPIM
			 ===================

I generally release new version of SPIM once a year, before a semester
boundary (late August or early January).  The new version are available on:

		www.cs.wisc.edu/~larus/spim.html



This directory contains several files and subdirectories:

README	This file.

VERSION
	Version number of system.

ChangeLog
	Record of changes to spim code.

Documentation/TeX
	TeX document that describes SPIM.

Documentation/H_P_AppendixA
	Copy of Appendix A from Hennessey & Patterson's book "Computer
Organization and Design". This more up-to-date than the TeX documentation.

PCSpim
	Microsoft Windows interface to SPIM

Setup
	Installer code for PCSpim.

spim
	Terminal interfaces to spim (Microsoft Windows, Unix, and Mac).

Tests
	Subdirectory contain torture tests to verify that SPIM works.

xspim
	X-Windows interface to spim (Unix and Mac).



		  WHAT ABOUT SPIM ON SYSTEM XYZ?
		  ==============================

SPIM should run without many changes on many Unix systems.  Obviously,
I have not tested SPIM on many system, nor can I port SPIM to systems
that I don't have.  However, I would like to hear about the changes
necessary to run SPIM on your favorite system.

James Larus
Microsoft Research
(larus@microsoft.com)
