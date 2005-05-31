Creating the distribution file for PCSpim for Windows requires two
tools.  WinZip, and WinZip self extractor.  These can be purchased
over the web for a total cost of approximately $78.

All you should have to do is use WinZip to create a zip file
with the contents of the files directory (just the files, not
the directory tree itself).

Then, run the spimsfx.bat.  You may have to modify the path
referenced in the batch file if you did not accept the default
installatin location for the WinZip self extractor.

Files that should be in the "files" directory:

setup.exe
setup32.exe
Mfc40.dll
Msvc4032.dll		Gets renamed to msvcrt40.dll
Msvc4095.dll		Gets renamed to msvcrt40.dll
trap.han		Gets renamed to trap.handler on long filename systems
PCSpim.exe
PCSpim.cnt
PCSPIM.HLP

