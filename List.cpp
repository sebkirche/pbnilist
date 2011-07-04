// List.cpp : PBNI class
#define _CRT_SECURE_NO_DEPRECATE

#include "main.h"
#include "List.h"

#ifdef _DEBUG
#define	VERSION_STR	_T(PBX_VERSION) _T(" (Debug version - ") _T(__DATE__) _T(" ") _T(__TIME__) _T(")")
#else
#define	VERSION_STR	_T(PBX_VERSION) _T(" (Release version - ") _T(__DATE__) _T(" ") _T(__TIME__) _T(")")
#endif

// default constructor
List::List()
{
}

List::List( IPB_Session * pSession )
:m_pSession( pSession )
{
	m_cursor = m_list.begin();
}

// destructor
List::~List()
{
	DoPurge();
}

// method called by PowerBuilder to invoke PBNI class methods
PBXRESULT List::Invoke(IPB_Session *session, pbobject obj, pbmethodID mid, PBCallInfo *ci)
{
   PBXRESULT pbxr = PBX_OK;

	switch ( mid )
	{
	case mid_GetVersion:
			pbxr = this->GetVersion( ci );
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
		case mid_GetNext:
			pbxr = this->GetNext(ci);
			break;
		case mid_GetAndNext:
			pbxr = this->GetAndNext(ci);
			break;
		case mid_GetPrevious:
			pbxr = this->GetPrevious(ci);
			break;
		case mid_Rewind:
			pbxr = this->Rewind(ci);
			break;
		case mid_GetFirst:
			pbxr = this->GetFirst(ci);
			break;
		case mid_GetLast:
			pbxr = this->GetLast(ci);
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
		case mid_HasNext:
			pbxr = this->HasNext(ci);
			break;
		case mid_Position:
			pbxr = this->Position(ci);
			break;
		case mid_Sort:
			pbxr = this->Sort(ci);
			break;
		default:
			pbxr = PBX_E_INVOKE_METHOD_AMBIGUOUS;
	}

	return pbxr;
}


void List::Destroy() 
{
   delete this;
}

// Method callable from PowerBuilder
PBXRESULT List::GetVersion( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;

	// return value
	ci->returnValue->SetString( VERSION_STR );

	return pbxr;
}

//Append some data to the list
PBXRESULT List::Append( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	bool bFirstAdd;

	bFirstAdd = m_list.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	m_list.push_back(data);
	if(bFirstAdd)
		m_cursor = m_list.begin(); // if we insert the first item, move the cursor to the first item
	return pbxr;
}

//Insert some data at the begining of the list
PBXRESULT List::Prepend( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	bool bFirstAdd;

	bFirstAdd = m_list.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	m_list.push_front(data);
	if(bFirstAdd)
		m_cursor = m_list.begin(); // if we insert the first item, move the cursor to the first item
	return pbxr;
}

//Insert some data at the current cursor position
PBXRESULT List::Insert( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
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
PBXRESULT List::Get(PBCallInfo *ci)
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
PBXRESULT List::Set(PBCallInfo *ci)
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
PBXRESULT List::GetAt(PBCallInfo *ci)
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
		if(pos > 0){
				i = m_list.begin();
				advance(i, pos - 1);
				m_pSession->SetValue(ci->returnValue, *i);
		}
		else
			pbxr = PBX_E_INVALID_ARGUMENT;
		}
	}
	return pbxr;
}

//Assign the data at the given cursor pos
PBXRESULT List::SetAt(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	list<IPB_Value *>::iterator i;
	IPB_Value *data;
	unsigned long pos;
	bool bFirstAdd;

	bFirstAdd = m_list.empty();
	pos = ci->pArgs->GetAt(0)->GetUlong();
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(1));
	if(pos > m_list.size())
		m_list.push_back(data);
	else{
		if(pos > 0){
			i = m_list.begin();
			advance(i, pos - 1);
			m_pSession->ReleaseValue(*i);
			*i = data;
		}
		else
			pbxr = PBX_E_INVALID_ARGUMENT;
	}
	if (bFirstAdd)
		m_cursor = m_list.begin();
	return pbxr;
}

//Insert the data before the given cursor pos
PBXRESULT List::InsertBefore(PBCallInfo *ci)
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
PBXRESULT List::InsertAfter(PBCallInfo *ci)
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
PBXRESULT List::Remove(PBCallInfo *ci)
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
PBXRESULT List::RemoveAt(PBCallInfo *ci)
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
PBXRESULT List::Size(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = m_list.size();
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

//Return the current cursor position
PBXRESULT List::Position(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = distance(m_list.begin(), m_cursor) + 1;
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

//tells if the cursor is not yet on the last element
PBXRESULT List::HasNext(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbboolean bHasNext = !m_list.empty() && (*m_cursor != m_list.back());
	ci->returnValue->SetBool(bHasNext);

	return pbxr;
}

//Return the maximum list size (system dependent)
PBXRESULT List::MaxSize(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = m_list.max_size();
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

PBXRESULT List::Purge(PBCallInfo *ci)
{
	PBXRESULT pbxr = PBX_OK;

	DoPurge();
	return pbxr;
}
 
void List::DoPurge()
{
	list<IPB_Value *>::iterator it;

	/*release the data*/
	for(it=m_list.begin(); it!=m_list.end(); it++){
		m_pSession->ReleaseValue(*it);
	}
	m_list.clear();
	m_cursor = m_list.begin();
}

//Return the current data then increase cursor
PBXRESULT List::GetAndNext(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(m_cursor != m_list.end()){
		m_pSession->SetValue(ci->returnValue, *m_cursor++);
	}
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Return the next data after the current pos
PBXRESULT List::GetNext(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(*m_cursor != m_list.back()){
		m_cursor++;
		m_pSession->SetValue(ci->returnValue, *m_cursor);
	}
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Return the previous data before the current pos
PBXRESULT List::GetPrevious(PBCallInfo *ci)
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
PBXRESULT List::Rewind(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	m_cursor = m_list.begin();

	return pbxr;
}

//Return the first item or null if empty
PBXRESULT List::GetFirst(PBCallInfo *ci)
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
PBXRESULT List::GetLast(PBCallInfo *ci)
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

//Sort the list
PBXRESULT List::Sort(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbobject pbCompObj;
	pbclass pbCompClass;
	pbmethodID pbCompMID;
	pbstring pbCmpFunc;
	LPCTSTR cmpFuncName;

	if ( ci->pArgs->GetAt(0)->IsNull() || !ci->pArgs->GetAt(0)->IsObject() || ci->pArgs->GetAt(1)->IsNull()){
		pbxr = PBX_E_INVALID_ARGUMENT;
	}
	else{
#if defined (PBVER) && (PBVER < 100)
		pbCompObj = ci->pArgs->GetAt(0)->GetObjectA();
#else
		pbCompObj = ci->pArgs->GetAt(0)->GetObjectW();
#endif
		//check for object compliance : must implement the function int list_compare(any, any)
		pbCompClass = m_pSession->GetClass(pbCompObj);
		if (!pbCompClass)
			return PBX_E_INVALID_ARGUMENT;

		//Debug
		//LPCTSTR test = m_pSession->GetClassNameW(m_pbCompClass);
		//m_pSession->ReleaseString(test);

		pbCmpFunc = ci->pArgs->GetAt(1)->GetString();
		cmpFuncName = m_pSession->GetString(pbCmpFunc);
		pbCompMID = m_pSession->GetMethodID(pbCompClass, cmpFuncName, PBRT_FUNCTION, STR("IAA"), false);
		//m_pbCompMID = m_pSession->FindMatchingFunction(m_pbCompClass, L"list_compare", PBRT_FUNCTION, L"any, any");
		if (pbCompMID == kUndefinedMethodID)
			return PBX_E_INVALID_ARGUMENT;

		m_list.sort(ListComparator(m_list, m_pSession, pbCompObj, pbCompClass, pbCompMID));
	}

	return pbxr;
}

bool ListComparator::operator()(IPB_Value *first, IPB_Value *second) const
{
	PBCallInfo comp_ci;
	m_pSession->InitCallInfo(m_pbCompClass, m_pbCompMID, &comp_ci);

	SetCorrectPBValue(comp_ci.pArgs->GetAt(0), first);
	SetCorrectPBValue(comp_ci.pArgs->GetAt(1), second);
	
	m_pSession->InvokeObjectFunction(m_pbCompObj, m_pbCompMID, &comp_ci);

	if (m_pSession->HasExceptionThrown())
		m_pSession->ClearException();
	pbint compRet = comp_ci.returnValue->GetInt();
	m_pSession->FreeCallInfo(&comp_ci);

	return compRet < 0;
}

// SetCorrectPBValue : assign correct type to IPB_Value* from another IPB_Value*
void SetCorrectPBValue(IPB_Value *dest, IPB_Value *src)
{
	if(src->IsNull()){
		dest->SetToNull();
		return;
	}
	if(src->IsEnum()){
		dest->SetInt( src->GetInt() );
		return;
	}
	if(src->IsArray()){
		dest->SetArray( src->GetArray() );
		return;
	}
	if(src->IsObject()){
#if defined (PBVER) && (PBVER < 100)
		dest->SetObject( src->GetObjectA() );
#else
		dest->SetObject( src->GetObjectW() );
#endif
		return;
	}

	switch(src->GetType()){
		case pbvalue_any:
			//objects, structs goes here ? NO !!!
			break;
		case pbvalue_blob:
			dest->SetBlob(src->GetBlob());
			break;
		case pbvalue_boolean:
			dest->SetBool(src->GetBool());
			break;
#if defined (PBVER) && (PBVER >= 105)
		case pbvalue_byte:
			dest->SetByte(src->GetByte());
			break;
#endif
		case pbvalue_char:
			dest->SetChar(src->GetChar());
			break;
		case pbvalue_date:
			dest->SetDate(src->GetDate());
			break;
		case pbvalue_datetime:
			dest->SetDateTime(src->GetDateTime());
			break;
		case pbvalue_dec:
			dest->SetDecimal(src->GetDecimal());
			break;
		case pbvalue_double:
			dest->SetDouble(src->GetDouble());
			break;
		case pbvalue_int:
			dest->SetInt(src->GetInt());
			break;
		case pbvalue_long:
			dest->SetLong(src->GetLong());
			break;
		case pbvalue_longlong:
			dest->SetLongLong(src->GetLongLong());
			break;
		case pbvalue_real:
			dest->SetReal(src->GetReal());
			break;
		case pbvalue_string:
			dest->SetPBString(src->GetString());
			break;
		case pbvalue_time:
			dest->SetTime(src->GetTime());
			break;
		case pbvalue_uint:
			dest->SetUint(src->GetUint());
			break;
		case pbvalue_ulong:
			dest->SetUlong(src->GetUlong());
			break;
		//case pbvalue_notype: //and dummy* case pbvalue_type:
	}
}