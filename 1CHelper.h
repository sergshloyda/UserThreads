// 1CHelper.h: interface for the C1CHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_1CHELPER_H__E3EBBCBB_08AE_4DD4_9EDD_754F2F1700A3__INCLUDED_)
#define AFX_1CHELPER_H__E3EBBCBB_08AE_4DD4_9EDD_754F2F1700A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CMainDocument;
class C1CHelper
{ 
	friend class CMainDocument;
public:
	BOOL SaveCheckIn1C(const CString& strPointName,const CString& strUser,int nCheckNum,VARIANT* vtArray);
	BOOL SaveZReportIn1C(const CString& strNumDoc,  const COleDateTime& tmTimeDoc,
						 const CString& strNumPoint,const CString& strEmpl,
						 const CString& strCust,    VARIANT* vtArray);
	BOOL Open1CEx(const CString& strPath,const CString& strUser,const CString& strPassword);
	BOOL Open1C(BSTR bstrParam);
	BOOL SetPropertyValue(IDispatch *pDisp,BSTR strPropertyName, VARIANT vtValue);
	C1CHelper();
	virtual ~C1CHelper();

private:
	  COleDispatchDriver drvApp;
};

#endif // !defined(AFX_1CHELPER_H__E3EBBCBB_08AE_4DD4_9EDD_754F2F1700A3__INCLUDED_)
