// TableValue1.cpp : implementation file
//

#include "stdafx.h"
#include "TableValue1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableValue
IMPLEMENT_DYNCREATE(CField, CObject)

CField::CField()
{
	//::VariantInit (&varValue);
}

CField::~CField()
{
	TRACE(_T("Delete CField\n"));
//	::VariantClear (&varValue);
}




/////////////////////////////////////////////////////////////////////////////
// CField message handlers

HRESULT CField::SetValue(const VARIANT* val)
{
	return m_varValue.Copy (val);
}

HRESULT  CField::GetValue(VARIANT* val)
{
	val->vt=VT_EMPTY;
	return m_varValue.Detach (val);
}
IMPLEMENT_DYNCREATE(CTableValue, CObject)

CTableValue::CTableValue()
{
}

CTableValue::~CTableValue()
{
	
	POSITION pos = m_listRows.GetHeadPosition();
	
	while( pos != NULL )
	{
		CRow* pRow=(CRow*)m_listRows.GetNext( pos );
		POSITION posMap=pRow->GetStartPosition ();
			while( posMap != NULL )
			{
				CField* pField;
				CString string;
				// Gets key (string) and value (pField)
				pRow->GetNextAssoc( posMap, string, (CObject*&)pField );
				delete pField;
			}
		pRow->RemoveAll ();
		delete pRow;

	}
	m_listRows.RemoveAll();
	
	
}








void CTableValue::AddField(LPCTSTR strNField)
{
	m_vecFNames.Add (strNField);
}

void CTableValue::AddNewLine()
{
	CRow* pmapFields=new CRow(20);
	for(int i=0;i<m_vecFNames.GetSize ();i++){
		CField* pField=new CField();
		COleVariant vtVal;
		pField->SetValue (vtVal);
		CString strKey=m_vecFNames[i];
		pmapFields->SetAt (strKey,pField);//set copy now we  must delete pField
		delete pField;
	}
	m_curRowPos=m_listRows.AddTail (pmapFields);
	
}

BOOL CTableValue::SetFieldValue(LPCTSTR strFName, const VARIANT* pval)
{
	BOOL bRes=FALSE;
	for(int i=0;i<m_vecFNames.GetSize ();i++){
		CString strCurFName=m_vecFNames.GetAt(i);
		if(strCurFName==strFName){
			bRes=TRUE;
			break;
		}
	}
	if(!bRes){
		CString strMsg;
		strMsg.Format (_T("Поля с именем %s в таблице не существует"),strFName);
		throw CTableValue::CTableValueError(strMsg);
	}
	ASSERT(m_curRowPos!=NULL);
	CRow* pmapFields=(CRow*)m_listRows.GetAt (m_curRowPos);
	ASSERT_VALID(pmapFields);
	CField* pField=new CField();
	ASSERT_VALID(pField);
	pField->SetValue (pval);
	pmapFields->SetAt (strFName,pField);
	return TRUE;
	
}

BOOL CTableValue::GetFieldValue(LPCTSTR strFName, VARIANT *pval)
{
	BOOL bRes=FALSE;

	
	ASSERT(m_curRowPos!=NULL);
	CRow* mapFields=(CRow*)m_listRows.GetAt (m_curRowPos);
	CField* pField;
	bRes=mapFields->Lookup(strFName,(CObject*&)pField);
	if(!bRes){
		CString strMsg;
		strMsg.Format (_T("Поля с именем %s в таблице не существует"),strFName);
		throw CTableValue::CTableValueError(strMsg);
	}
	pField->GetValue (pval);
	
	return TRUE;
}

POSITION CTableValue::LoadRows()
{
	m_curRowPos=m_listRows.GetHeadPosition ();
return m_curRowPos;
}

POSITION CTableValue::GetRow()
{ 
	POSITION pos;
	pos=m_curRowPos;
	if(pos==NULL)
		return pos;
	
	m_listRows.GetNext (pos);
	if(pos!=NULL)
		m_curRowPos=pos;
	return pos;   
}

BOOL CTableValue::GetColumnName(int index, CString &strColName)
{
	BOOL bRes=FALSE;
	if(index>m_vecFNames.GetSize ()){
		CString strMsg;
		strMsg.Format (_T("Таблица содержит %d колонок"),m_vecFNames.GetSize ());
		throw CTableValue::CTableValueError(strMsg);
	}
	strColName=m_vecFNames[index];

return TRUE;
}

int CTableValue::GetColumnCount()
{
 return m_vecFNames.GetSize ();
}
