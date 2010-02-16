// PbniHash.h : include file for standard system include files,
//  or project specific include files that are used frequently,
//  are changed infrequently
//

#ifndef MAIN_H
#define MAIN_H

#define WIN32_LEAN_AND_MEAN			// Exclude rarely-used stuff from Windows headers

// Insert your headers here
#include <windows.h>
#include <pbext.h>

extern void SetCorrectPBValue(IPB_Value *dest, IPB_Value *src);

#endif // !defined(MAIN_H)
