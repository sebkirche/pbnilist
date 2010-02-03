// PbniHash.cpp : defines the entry point for the PBNI DLL.
//Global: 0
//Unicode: -1
#include "PbniList.h"
#include "Main.h"


BOOL APIENTRY DllMain
(
   HANDLE hModule,
   DWORD ul_reason_for_all,
   LPVOID lpReserved
)
{	
		
	switch(ul_reason_for_all)
	{	
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:		
	case DLL_PROCESS_DETACH:
		break;
	}
			
	return TRUE;
}

// The description returned from PBX_GetDescription is used by
// the PBX2PBD tool to create pb groups for the PBNI class.
//
// + The description can contain more than one class definition.
// + A class definition can reference any class definition that
//   appears before it in the description.
// + The PBNI class must inherit from a class that inherits from
//   NonVisualObject, such as Transaction or Exception

PBXEXPORT LPCTSTR PBXCALL PBX_GetDescription()
{
   // combined class description
   static const TCHAR classDesc[] = {
      /* PbniList */
	_T("class uo_list from nonvisualobject\n") \
    _T("   function string hello()\n") \
	_T("   function ulong size()\n") \
	_T("   function ulong maxsize()\n") \
	_T("   subroutine purge()\n") \
    _T("   subroutine append(any value)\n") \
	_T("   function any get()\n") \
	_T("   function any getat(ulong index)\n") \
	_T("   subroutine set(any value)\n") 
	_T("   subroutine setat(ulong index, any value)\n") 
	_T("   subroutine remove()\n") \
	_T("   subroutine removeat(ulong index)\n") \
	_T("   function any next()\n") \
	_T("   function any previous()\n") \
	_T("   subroutine rewind()\n") \
	_T("   function any first()\n") \
	_T("   function any last()\n") \
	_T("   subroutine prepend(any value)\n") \
	_T("   subroutine insert(any value)\n") \
	_T("   subroutine insertbefore(ulong index, any value)\n") \
	_T("   subroutine insertafter(ulong index, any value)\n") \
    _T("end class\n")
   
	};

   return (LPCTSTR)classDesc;
}

// PBX_CreateNonVisualObject is called by PowerBuilder to create a C++ class
// that corresponds to the PBNI class created by PowerBuilder.
PBXEXPORT PBXRESULT PBXCALL PBX_CreateNonVisualObject
(
   IPB_Session * session,
   pbobject obj,
   LPCTSTR className,
   IPBX_NonVisualObject ** nvobj
)
{
   // The name must not contain upper case
   if (_tcscmp(className, _T("uo_list")) == 0)
      *nvobj = new PbniList(session);

   return PBX_OK;
}

