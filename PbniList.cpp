// PbniList.cpp : PBNI class
#define _CRT_SECURE_NO_DEPRECATE

#include "PbniList.h"

#ifdef _DEBUG
#define	VERSION_STR	_T(" (Debug version - ") _T(__DATE__) _T(" ") _T(__TIME__) _T(")")
#else
#define	VERSION_STR	_T(" (Release version - ") _T(__DATE__) _T(" ") _T(__TIME__) _T(")")
#endif

// default constructor
PbniList::PbniList()
{
}

PbniList::PbniList( IPB_Session * pSession )
:m_pSession( pSession )
{
	m_cursor = m_list.begin();
}

// destructor
PbniList::~PbniList()
{
	DoPurge();
}

// method called by PowerBuilder to invoke PBNI class methods
PBXRESULT PbniList::Invoke
(
	IPB_Session * session,
	pbobject obj,
	pbmethodID mid,
	PBCallInfo * ci
)
{
   PBXRESULT pbxr = PBX_OK;

	switch ( mid )
	{
		case mid_Hello:
			pbxr = this->Hello( ci );
			break;
		case mid_Size:
			pbxr = this->Size(ci);
			break;
		case mid_MaxSize:
			pbxr = this->MaxSize(ci);
			break;
		case mid_Append:
			pbxr = this->Append(ci);
			break;
		case mid_Get:
			pbxr = this->Get(ci);
			break;
		case mid_GetAt:
			pbxr = this->GetAt(ci);
			break;
		case mid_Set:
			pbxr = this->Set(ci);
			break;
		case mid_SetAt:
			pbxr = this->SetAt(ci);
			break;
		case mid_Remove:
			pbxr = this->Remove(ci);
			break;
		case mid_RemoveAt:
			pbxr = this->RemoveAt(ci);
			break;
		case mid_Purge:
			pbxr = this->Purge(ci);
			break;
		case mid_Next:
			pbxr = this->Next(ci);
			break;
		case mid_Previous:
			pbxr = this->Previous(ci);
			break;
		case mid_Rewind:
			pbxr = this->Rewind(ci);
			break;
		case mid_First:
			pbxr = this->First(ci);
			break;
		case mid_Last:
			pbxr = this->Last(ci);
			break;
		case mid_Prepend:
			pbxr = this->Prepend(ci);
			break;
		case mid_Insert:
			pbxr = this->Insert(ci);
			break;
		case mid_InsertBefore:
			pbxr = this->InsertBefore(ci);
			break;
		case mid_InsertAfter:
			pbxr = this->InsertAfter(ci);
			break;
		default:
			pbxr = PBX_E_INVOKE_METHOD_AMBIGUOUS;
	}

	return pbxr;
}


void PbniList::Destroy() 
{
   delete this;
}

// Method callable from PowerBuilder
PBXRESULT PbniList::Hello( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;

	// return value
	ci->returnValue->SetString( _T("Hello from PbniList") VERSION_STR );

	return pbxr;
}

//Append some data to the list
PBXRESULT PbniList::Append( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	int keyLen;
	bool bFirstAdd;

	bFirstAdd = m_list.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	m_list.push_back(data);
	if(bFirstAdd)
		m_cursor = m_list.begin(); // if we insert the first item, move the cursor to the first item
	return pbxr;
}

//Insert some data at the begining of the list
PBXRESULT PbniList::Prepend( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	int keyLen;
	bool bFirstAdd;

	bFirstAdd = m_list.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	m_list.push_front(data);
	if(bFirstAdd)
		m_cursor = m_list.begin(); // if we insert the first item, move the cursor to the first item
	return pbxr;
}

//Insert some data at the current cursor position
PBXRESULT PbniList::Insert( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	int keyLen;
	bool bFirstAdd;

	bFirstAdd = m_list.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	if(bFirstAdd)
		m_cursor = m_list.insert(m_list.begin(), data); // if we insert the first item, move the cursor to the first item
	else
		m_cursor = m_list.insert(m_cursor, data);
	return pbxr;
}

//Return the data at the current cursor pos or null
PBXRESULT PbniList::Get(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(m_cursor != m_list.end())
		m_pSession->SetValue(ci->returnValue, *m_cursor);
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Assign the data at the current cursor pos
PBXRESULT PbniList::Set(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	if(m_cursor != m_list.end()){
		m_pSession->ReleaseValue(*m_cursor);
		*m_cursor = data;
	}
	else
		m_list.insert(m_cursor, data);
	return pbxr;
}

//Return the data at the given cursor pos
PBXRESULT PbniList::GetAt(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	unsigned long pos;
	list<IPB_Value *>::iterator i;

	if ( ci->pArgs->GetAt(0)->IsNull()){
		// if any of the passed arguments is null, return the null value
		ci->returnValue->SetToNull();
	}
	else{
		pos = ci->pArgs->GetAt(0)->GetUlong();
		if((pos < 1) || (pos > m_list.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
		else{
			i = m_list.begin();
			advance(i, pos - 1);
			m_pSession->SetValue(ci->returnValue, *i);
		}
	}
	return pbxr;
}

//Assign the data at the given cursor pos
PBXRESULT PbniList::SetAt(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	list<IPB_Value *>::iterator i;
	IPB_Value *data;
	unsigned long pos;
	
	pos = ci->pArgs->GetAt(0)->GetUlong();
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(1));
	if(pos > m_list.size())
		m_list.push_back(data);
	else{
		i = m_list.begin();
		advance(i, pos - 1);
		m_pSession->ReleaseValue(*i);
		*i = data;
	}
	return pbxr;
}

//Insert the data before the given cursor pos
PBXRESULT PbniList::InsertBefore(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	list<IPB_Value *>::iterator i;
	IPB_Value *data;
	unsigned long pos;
	
	pos = ci->pArgs->GetAt(0)->GetUlong();
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(1));
	if((pos < 1) || (pos > m_list.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
	else{
		i = m_list.begin();
		advance(i, pos - 1);
		m_list.insert(i, data);
	}
	return pbxr;
}

//Insert the data after the given cursor pos
PBXRESULT PbniList::InsertAfter(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	list<IPB_Value *>::iterator i;
	IPB_Value *data;
	unsigned long pos;
	
	pos = ci->pArgs->GetAt(0)->GetUlong();
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(1));
	if((pos < 1) || (pos > m_list.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
	else{
		i = m_list.begin();
		advance(i, pos);
		m_list.insert(i, data);
	}
	return pbxr;
}

//Remove the data at the current cursor pos
PBXRESULT PbniList::Remove(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	list<IPB_Value *>::iterator i;
	
	if(m_cursor != m_list.end()){
		i = m_cursor++;
		m_pSession->ReleaseValue(*i);
		m_list.erase(i);
	}
	return pbxr;
}

//Remove the data at the current cursor pos
PBXRESULT PbniList::RemoveAt(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	list<IPB_Value *>::iterator i;
	unsigned long pos;
	
	if ( ci->pArgs->GetAt(0)->IsNull()){
		pbxr = PBX_E_INVALID_ARGUMENT;
	}
	else{
		pos = ci->pArgs->GetAt(0)->GetUlong();
		if((pos < 1) || (pos > m_list.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
		else{
			i = m_list.begin();
			advance(i, pos - 1);
			if(i == m_cursor)
				m_cursor++;
			m_pSession->ReleaseValue(*i);
			m_list.erase(i);
		}
	}
	return pbxr;
}

//Return the current list size
PBXRESULT PbniList::Size(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = m_list.size();
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

//Return the maximum list size (system dependent)
PBXRESULT PbniList::MaxSize(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = m_list.max_size();
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

PBXRESULT PbniList::Purge(PBCallInfo *ci)
{
	PBXRESULT pbxr = PBX_OK;

	DoPurge();
	return pbxr;
}
 
void PbniList::DoPurge()
{
	list<IPB_Value *>::iterator it;

	/*release the data*/
	for(it=m_list.begin(); it!=m_list.end(); it++){
		m_pSession->ReleaseValue(*it);
	}
	m_list.clear();
	m_cursor = m_list.begin();
}

//Return the next data after the current pos
PBXRESULT PbniList::Next(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(m_cursor != m_list.end()){
		m_cursor++;
		if(m_cursor != m_list.end())
			m_pSession->SetValue(ci->returnValue, *m_cursor);
		else
			ci->returnValue->SetToNull();
	}
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Return the previous data before the current pos
PBXRESULT PbniList::Previous(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(m_cursor != m_list.begin()){
		m_cursor--;
		m_pSession->SetValue(ci->returnValue, *m_cursor);
	}
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//rewind the cursor to the begining
PBXRESULT PbniList::Rewind(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	m_cursor = m_list.begin();

	return pbxr;
}

//Return the first item or null if empty
PBXRESULT PbniList::First(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	list<IPB_Value *>::iterator i;
	
	i = m_list.begin();
	if(i != m_list.end())
		m_pSession->SetValue(ci->returnValue, *i);
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Return the last item or null if empty
PBXRESULT PbniList::Last(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	list<IPB_Value *>::reverse_iterator i;
	
	i = m_list.rbegin();
	if(i != m_list.rend())
		m_pSession->SetValue(ci->returnValue, *i);
	else
		ci->returnValue->SetToNull();
	return pbxr;
}
