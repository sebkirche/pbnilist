// My.h : header file for PBNI class
#ifndef CPBNILIST_H
#define CPBNILIST_H

#include <pbext.h>
#include <list>

using namespace std;

class PbniList : public IPBX_NonVisualObject
{
public:
	// construction/destruction
	PbniList();
	PbniList( IPB_Session * pSession );
	virtual ~PbniList();

	// IPBX_UserObject methods
	PBXRESULT Invoke
	(
		IPB_Session * session,
		pbobject obj,
		pbmethodID mid,
		PBCallInfo * ci
	);

   void Destroy();

	// PowerBuilder method wrappers
	enum Function_Entrys
	{
		mid_Hello = 0,
		mid_Size,
		mid_MaxSize,
		mid_Purge,
		mid_Append,
		mid_Get,
		mid_GetAt,
		mid_Set,
		mid_SetAt,
		mid_Remove,
		mid_RemoveAt,
		mid_Next,
		mid_Previous,
		mid_Rewind,
		mid_First,
		mid_Last,
		mid_Prepend,
		mid_Insert,
		mid_InsertBefore,
		mid_InsertAfter,
		NO_MORE_METHODS
	};


protected:
 	// methods callable from PowerBuilder
	PBXRESULT Hello( PBCallInfo * ci );
	PBXRESULT Size(PBCallInfo * ci);
	PBXRESULT MaxSize(PBCallInfo * ci);
	PBXRESULT Purge(PBCallInfo * ci);
	void DoPurge();
	PBXRESULT Append(PBCallInfo * ci);
	PBXRESULT Get(PBCallInfo * ci);
	PBXRESULT GetAt(PBCallInfo * ci);
	PBXRESULT Set(PBCallInfo * ci);
	PBXRESULT SetAt(PBCallInfo * ci);
	PBXRESULT Remove(PBCallInfo * ci);
	PBXRESULT RemoveAt(PBCallInfo * ci);
	PBXRESULT Next(PBCallInfo * ci);
	PBXRESULT Previous(PBCallInfo * ci);
	PBXRESULT Rewind(PBCallInfo * ci);
	PBXRESULT First(PBCallInfo * ci);
	PBXRESULT Last(PBCallInfo * ci);
	PBXRESULT Prepend(PBCallInfo * ci);
	PBXRESULT Insert(PBCallInfo * ci);
	PBXRESULT InsertBefore(PBCallInfo * ci);
	PBXRESULT InsertAfter(PBCallInfo * ci);

protected:
    // member variables
    IPB_Session * m_pSession;
	list<IPB_Value *> m_list;
	list<IPB_Value *>::iterator m_cursor;
 };

#endif	// !defined(CPBNILIST_H)