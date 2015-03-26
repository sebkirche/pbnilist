// My.h : header file for PBNI class
#ifndef CVECTOR_H
#define CVECTOR_H

#include "main.h"
#include <vector>
#include <functional>

using namespace std;

class Vector : public IPBX_NonVisualObject
{
public:
	// construction/destruction
	Vector();
	Vector( IPB_Session * pSession );
	virtual ~Vector();

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
		mid_GetVersion = 0,
		mid_Size,
		mid_MaxSize,
		mid_Reserve,
		mid_Resize,
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
		mid_InsertHere,
		mid_InsertBefore,
		mid_InsertAfter,
		mid_HasNext,
		mid_Position,
		mid_Sort,
		NO_MORE_METHODS
	};


protected:
 	// methods callable from PowerBuilder
	PBXRESULT GetVersion( PBCallInfo * ci );
	PBXRESULT Size(PBCallInfo * ci);
	PBXRESULT MaxSize(PBCallInfo * ci);
	PBXRESULT Reserve(PBCallInfo * ci);
	PBXRESULT Resize(PBCallInfo * ci);
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
	PBXRESULT InsertHere(PBCallInfo * ci);
	PBXRESULT InsertBefore(PBCallInfo * ci);
	PBXRESULT InsertAfter(PBCallInfo * ci);
	PBXRESULT HasNext(PBCallInfo * ci);
	PBXRESULT Position(PBCallInfo * ci);
	PBXRESULT Sort(PBCallInfo * ci);

protected:
    // member variables
    IPB_Session * m_pSession;
	vector<IPB_Value *> m_vector;
	size_t m_cursor;
	pbobject comparator;
};

/*
	VectorComparator functor used to sort the Vector
	a functor is a class that can be called like a function.
	It is needed for the sorting process
*/
class VectorComparator : public binary_function<IPB_Value *, IPB_Value *, bool>
{
	const vector<IPB_Value *> &m_vector;
    IPB_Session *m_pSession;
	pbobject m_pbCompObj;
	pbclass m_pbCompClass;
	pbmethodID m_pbCompMID;
public:
	VectorComparator(const vector<IPB_Value *> &vector, 
									IPB_Session *session, 
									pbobject compObj,
									pbclass compClass, 
									pbmethodID compMID) 
									: m_vector(vector), m_pSession(session), m_pbCompObj(compObj), m_pbCompClass(compClass), m_pbCompMID(compMID) {}
	bool operator()(IPB_Value *first, IPB_Value *second) const;
};


#endif	// !defined(CVECTOR_H)