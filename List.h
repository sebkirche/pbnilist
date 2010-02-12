// My.h : header file for PBNI class
#ifndef CLIST_H
#define CLIST_H

#include <pbext.h>
#include <list>

using namespace std;

class List : public IPBX_NonVisualObject
{
public:
	// construction/destruction
	List();
	List( IPB_Session * pSession );
	virtual ~List();

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
		mid_GetNext,
		mid_GetPrevious,
		mid_GetAndNext,
		mid_Rewind,
		mid_GetFirst,
		mid_GetLast,
		mid_Prepend,
		mid_Insert,
		mid_InsertBefore,
		mid_InsertAfter,
		mid_HasNext,
		mid_Position,
		//mid_Sort,
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
	PBXRESULT GetNext(PBCallInfo * ci);
	PBXRESULT GetPrevious(PBCallInfo * ci);
	PBXRESULT GetAndNext(PBCallInfo * ci);
	PBXRESULT Rewind(PBCallInfo * ci);
	PBXRESULT GetFirst(PBCallInfo * ci);
	PBXRESULT GetLast(PBCallInfo * ci);
	PBXRESULT Prepend(PBCallInfo * ci);
	PBXRESULT Insert(PBCallInfo * ci);
	PBXRESULT InsertBefore(PBCallInfo * ci);
	PBXRESULT InsertAfter(PBCallInfo * ci);
	PBXRESULT HasNext(PBCallInfo * ci);
	PBXRESULT Position(PBCallInfo * ci);
	//PBXRESULT Sort(PBCallInfo * ci);

protected:
    // member variables
    IPB_Session * m_pSession;
	list<IPB_Value *> m_list;
	list<IPB_Value *>::iterator m_cursor;
	pbobject comparator;
 };

#endif	// !defined(CLIST_H)