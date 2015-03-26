// PbniHash.h : include file for standard system include files,
//  or project specific include files that are used frequently,
//  are changed infrequently

#ifndef MAIN_H
#define MAIN_H

#define WIN32_LEAN_AND_MEAN			// Exclude rarely-used stuff from Windows headers

// Insert your headers here
#include <windows.h>

#define PBX_VERSION "0.4.2"
#define PBX_VERSION_RC 0,4,2,0

#ifdef PB9
#define STR(x) x
#else
#define STR(x) _T(x)
#endif

#ifndef RC_INVOKED
#include <pbext.h>

extern void SetCorrectPBValue(IPB_Value *dest, IPB_Value *src);
#endif //RC_INVOKED
#endif // !defined(MAIN_H)
