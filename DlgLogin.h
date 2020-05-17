#if !defined(AFX_DLGLOGIN_H__5D229003_C497_4795_86C8_4F4493E72092__INCLUDED_)
#define AFX_DLGLOGIN_H__5D229003_C497_4795_86C8_4F4493E72092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//
#include "MainDocument.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog
class ItemData
{
public:
	ItemData(const CString& szId,const CString&  szName,const CString&  szPassword,const CString& szNick)
	{
		id=szId;
		name=szName;
		password=szPassword;
		Nick=szNick;
	}
	CString  id       ;
	CString  name     ;
	CString  password  ;
	CString Nick;
};

class CDlgLogin : public CDialog
{
// Construction
public:
	CDlgLogin(CDocument* pDoc,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_LOGIN };
	CComboBox	m_cbUsers;
	CString	m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCbusers();
	afx_msg void OnOk();
	afx_msg void OnGetdigit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strCompare;
	CPtrList m_lsItems;
	CMainDocument* m_pMainDoc;
//	CMainDocument* pDoc;
//	CString m_strCashID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__5D229003_C497_4795_86C8_4F4493E72092__INCLUDED_)
