// Vector.cpp : PBNI class
#define _CRT_SECURE_NO_DEPRECATE

#include "main.h"
#include "Vector.h"
#include <algorithm>

#ifdef _DEBUG
#define	VERSION_STR	_T(" (Debug version - ") _T(__DATE__) _T(" ") _T(__TIME__) _T(")")
#else
#define	VERSION_STR	_T(" (Release version - ") _T(__DATE__) _T(" ") _T(__TIME__) _T(")")
#endif

// default constructor
Vector::Vector()
{
}

Vector::Vector( IPB_Session * pSession )
:m_pSession( pSession )
{
	m_cursor = 0;
}

// destructor
Vector::~Vector()
{
	DoPurge();
}

// method called by PowerBuilder to invoke PBNI class methods
PBXRESULT Vector::Invoke
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
		case mid_Reserve:
			pbxr = this->Reserve(ci);
			break;
		case mid_Resize:
			pbxr = this->Resize(ci);
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


void Vector::Destroy() 
{
   delete this;
}

// Method callable from PowerBuilder
PBXRESULT Vector::Hello( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;

	// return value
	ci->returnValue->SetString( _T("Hello from Vector") VERSION_STR );

	return pbxr;
}

//Append some data to the vector
PBXRESULT Vector::Append( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	bool bFirstAdd;

	bFirstAdd = m_vector.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	m_vector.push_back(data);
	if(bFirstAdd){
		//m_begin = m_vector.begin(); // if we insert the first item, move the cursor to the first item
		m_cursor = 0;
	}
	return pbxr;
}

//Insert some data at the begining of the vector PERFORMANCE WARNING !!!
PBXRESULT Vector::Prepend( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	bool bFirstAdd;

	bFirstAdd = m_vector.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	m_vector.insert(m_vector.begin(),data);
	if(bFirstAdd)
		m_cursor = 0;
		//m_begin = m_vector.begin(); // if we insert the first item, move the cursor to the first item
	else
		m_cursor++;
	return pbxr;
}

//Insert some data at the current cursor position PERFORMANCE WARNING !!!
PBXRESULT Vector::Insert( PBCallInfo * ci )
{
	PBXRESULT	pbxr = PBX_OK;
	bool bFirstAdd;

	bFirstAdd = m_vector.empty();
	IPB_Value *data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	if(bFirstAdd)
		m_vector.insert(m_vector.begin(), data); // if we insert the first item, move the cursor to the first item
		//m_cursor = 0;
	else
		m_vector.insert(m_vector.begin()+m_cursor, data);
	return pbxr;
}

//Return the data at the current cursor pos or null
PBXRESULT Vector::Get(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(!m_vector.empty())
		m_pSession->SetValue(ci->returnValue, m_vector[m_cursor]);
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Assign the data at the current cursor pos
PBXRESULT Vector::Set(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(0));
	if(m_cursor != m_vector.size()){
		m_pSession->ReleaseValue(m_vector[m_cursor]);
		m_vector[m_cursor] = data;
	}
	else
		m_vector.push_back(data);
	return pbxr;
}

//Return the data at the given cursor pos
PBXRESULT Vector::GetAt(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	unsigned long pos;

	if ( ci->pArgs->GetAt(0)->IsNull()){
		// if any of the passed arguments is null, return the null value
		ci->returnValue->SetToNull();
	}
	else{
		pos = ci->pArgs->GetAt(0)->GetUlong();
		if((pos < 1) || (pos > m_vector.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
		else{
			m_pSession->SetValue(ci->returnValue, *(m_vector.begin()+pos-1));
		}
	}
	return pbxr;
}

//Assign the data at the given cursor pos
PBXRESULT Vector::SetAt(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	unsigned long pos;
	vector<IPB_Value *>::iterator it;
	
	pos = ci->pArgs->GetAt(0)->GetUlong();
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(1));
	if(pos > m_vector.size())
		m_vector.push_back(data);
	else{
		if(pos > 0){
			it = m_vector.begin()+(pos-1);
			m_pSession->ReleaseValue(*it);
			*it = data;
		}
		else
			pbxr = PBX_E_INVALID_ARGUMENT;
	}
	return pbxr;
}

//Insert the data before the given cursor pos
PBXRESULT Vector::InsertBefore(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	vector<IPB_Value *>::iterator it;
	IPB_Value *data;
	unsigned long pos;
	
	pos = ci->pArgs->GetAt(0)->GetUlong();
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(1));
	if((pos < 1) || (pos > m_vector.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
	else{
		it = m_vector.begin()+(pos-1);
		m_vector.insert(it, data);
		if(pos-1 <= m_cursor)
			m_cursor++;
	}
	return pbxr;
}

//Insert the data after the given cursor pos
PBXRESULT Vector::InsertAfter(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	vector<IPB_Value *>::iterator it;
	IPB_Value *data;
	unsigned long pos;
	
	pos = ci->pArgs->GetAt(0)->GetUlong();
	data = m_pSession->AcquireValue(ci->pArgs->GetAt(1));
	if((pos < 1) || (pos > m_vector.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
	else{
		it = m_vector.begin()+pos;
		m_vector.insert(it, data);
		if(pos <= m_cursor)
			m_cursor++;
	}
	return pbxr;
}

//Remove the data at the current cursor pos
PBXRESULT Vector::Remove(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	vector<IPB_Value *>::iterator it;
	
	if(m_cursor != m_vector.size()){
		it = m_vector.begin()+m_cursor;
		m_pSession->ReleaseValue(*it);
		m_vector.erase(it);
		//m_cursor--;
	}
	return pbxr;
}

//Remove the data at the current cursor pos
PBXRESULT Vector::RemoveAt(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	vector<IPB_Value *>::iterator it;
	unsigned long pos;
	
	if ( ci->pArgs->GetAt(0)->IsNull()){
		pbxr = PBX_E_INVALID_ARGUMENT;
	}
	else{
		pos = ci->pArgs->GetAt(0)->GetUlong();
		if((pos < 1) || (pos > m_vector.size()))
			pbxr = PBX_E_INVALID_ARGUMENT;
		else{
			it = m_vector.begin() + pos - 1;
			m_pSession->ReleaseValue(*it);
			m_vector.erase(it);
			if(pos - 1 <= m_cursor)
				m_cursor--;
		}
	}
	return pbxr;
}

//Return the current vector size (elements count, not capacity)
PBXRESULT Vector::Size(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = m_vector.size();
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

//Return the current position
PBXRESULT Vector::Position(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = m_cursor + 1;
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

//tells if the cursor is not yet on the last element
PBXRESULT Vector::HasNext(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbboolean bHasNext = (m_cursor != m_vector.size() - 1);
	ci->returnValue->SetBool(bHasNext);

	return pbxr;
}

//Return the maximum list size (system dependent)
PBXRESULT Vector::MaxSize(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbulong ulRet = m_vector.max_size();
	ci->returnValue->SetUlong(ulRet);

	return pbxr;
}

//pre-allocate a size for the vector
PBXRESULT Vector::Reserve(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	unsigned long size;
	
	if ( ci->pArgs->GetAt(0)->IsNull()){
		pbxr = PBX_E_INVALID_ARGUMENT;
	}
	else{
		size = ci->pArgs->GetAt(0)->GetUlong();
		try{
			m_vector.reserve(size);
			ci->returnValue->SetBool(true);
		}
		catch(length_error &le){
			ci->returnValue->SetBool(false);
		}
	}
	return pbxr;
}

//pre-allocate a size for the vector
PBXRESULT Vector::Resize(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	unsigned long size;
	
	if ( ci->pArgs->GetAt(0)->IsNull()){
		pbxr = PBX_E_INVALID_ARGUMENT;
	}
	else{
		size = ci->pArgs->GetAt(0)->GetUlong();
		try{
			m_vector.resize(size);
			ci->returnValue->SetBool(true);
		}
		catch(bad_alloc  &ba){
			ci->returnValue->SetBool(false);
		}
	}
	return pbxr;
}

PBXRESULT Vector::Purge(PBCallInfo *ci)
{
	PBXRESULT pbxr = PBX_OK;

	DoPurge();
	return pbxr;
}
 
void Vector::DoPurge()
{
	size_t i;

	/*release the data*/
	for(i=0; i<m_vector.size(); i++){
		m_pSession->ReleaseValue(m_vector[i]);
	}
	m_vector.clear();
	//m_begin = m_list.begin();
	m_cursor = 0;
}

//Return the next data after the current pos
PBXRESULT Vector::GetNext(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(m_cursor < m_vector.size() - 1){
		m_cursor++;
		m_pSession->SetValue(ci->returnValue, m_vector[m_cursor]);
	}
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Return the next data after the current pos
PBXRESULT Vector::GetAndNext(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(m_cursor < m_vector.size() - 1){
		m_pSession->SetValue(ci->returnValue, m_vector[m_cursor++]);
	}
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Return the previous data before the current pos
PBXRESULT Vector::GetPrevious(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(m_cursor > 0){
		m_cursor--;
		m_pSession->SetValue(ci->returnValue, m_vector[m_cursor]);
	}
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//rewind the cursor to the begining
PBXRESULT Vector::Rewind(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	m_cursor = 0;

	return pbxr;
}

//Return the first item or null if empty
PBXRESULT Vector::GetFirst(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(!m_vector.empty())
		m_pSession->SetValue(ci->returnValue, m_vector[0]);
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Return the last item or null if empty
PBXRESULT Vector::GetLast(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	IPB_Value *data;
	
	if(!m_vector.empty())
		m_pSession->SetValue(ci->returnValue, m_vector[m_vector.size()-1]);
	else
		ci->returnValue->SetToNull();
	return pbxr;
}

//Sort the vector
PBXRESULT Vector::Sort(PBCallInfo *ci)
{
	PBXRESULT	pbxr = PBX_OK;
	pbobject pbCompObj;
	pbclass pbCompClass;
	pbmethodID pbCompMID;

	if ( ci->pArgs->GetAt(0)->IsNull() || !ci->pArgs->GetAt(0)->IsObject()){
		pbxr = PBX_E_INVALID_ARGUMENT;
	}
	else{
		pbCompObj = ci->pArgs->GetAt(0)->GetObjectW();
		//check for object compliance : must implement the function int list_compare(any, any)
		pbCompClass = m_pSession->GetClass(pbCompObj);
		if (!pbCompClass)
			return PBX_E_INVALID_ARGUMENT;

		//Debug
		//LPCTSTR test = m_pSession->GetClassNameW(m_pbCompClass);
		//m_pSession->ReleaseString(test);

		pbCompMID = m_pSession->GetMethodID(pbCompClass, L"list_compare", PBRT_FUNCTION, L"IAA", false);
		//m_pbCompMID = m_pSession->FindMatchingFunction(m_pbCompClass, L"list_compare", PBRT_FUNCTION, L"any, any");
		if (pbCompMID == kUndefinedMethodID)
			return PBX_E_INVALID_ARGUMENT;

		std::sort(m_vector.begin(), m_vector.end(),VectorComparator(m_vector, m_pSession, pbCompObj, pbCompClass, pbCompMID));
	}

	return pbxr;
}

bool VectorComparator::operator()(IPB_Value *first, IPB_Value *second) const
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

