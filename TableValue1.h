#ifndef _TABLEVALUE_H_
#define _TABLEVALUE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableValue1.h : header file
//
#include "afxcoll.h"
#include <stdexcept>
class CField : public CObject
{
	DECLARE_DYNCREATE(CField)
public:
	CField();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	HRESULT  GetValue(VARIANT* val);
	HRESULT  SetValue(const VARIANT* val);



// Implementation
public:
	virtual ~CField();



private:
	CComVariant m_varValue;
};

typedef CMapStringToOb CRow;
/////////////////////////////////////////////////////////////////////////////
// CTableValue command target

class CTableValue : public CObject
{
	DECLARE_DYNCREATE(CTableValue)
public:
	CTableValue();           // protected constructor used by dynamic creation

// Attributes
public:
	CStringArray m_vecFNames;
	CObList  m_listRows;
	class CTableValueError:public std::runtime_error

	{

	public:
		CTableValueError(const char *msg):std::runtime_error(msg){
			#ifdef OutputDebugString_ENABLED
			OutputDebugString(msg);
			#endif
			
		}
		
	};

private:
	POSITION m_curRowPos;

// Operations
public:
	int GetColumnCount();
	BOOL GetColumnName(int index,CString& strColName);
	POSITION GetRow();
	POSITION LoadRows();
	BOOL GetFieldValue(LPCTSTR strFName,VARIANT* val);
	BOOL SetFieldValue(LPCTSTR strFName,const VARIANT* val);
	void AddNewLine();
	void AddField(LPCTSTR strNField);


// Implementation
 ~CTableValue();

};
	



#endif // !defined _TABLEVALUE_H_
