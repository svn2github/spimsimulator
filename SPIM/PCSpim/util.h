#ifndef _UTIL_H_
#define _UTIL_H_

#define COPYCHAR(d, s) *(d) = *(s), ++d, ++s
#define APPENDCHAR(d, ch) *(d) = ch, ++d

LPTSTR MakeCRLFValid(LPCTSTR strBuf);
int UTIL_GetOSType();

#endif
