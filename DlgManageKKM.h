#if !defined(AFX_DLGMANAGEKKM_H__0987F7FB_B9DC_4D8B_B318_79B760B37E58__INCLUDED_)
#define AFX_DLGMANAGEKKM_H__0987F7FB_B9DC_4D8B_B318_79B760B37E58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgManageKKM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgManageKKM dialog

class CDlgManageKKM : public CPropertyPage
{
// Construction
public:
	CDlgManageKKM();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgManageKKM)
	enum { IDD = IDD_DLGKKM };
	BOOL	m_KKMOnLine;
	CString	m_strNameKKM;
	CString	m_strCOMPortKKM;
	CString m_strStatusKKM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManageKKM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManageKKM)
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANAGEKKM_H__0987F7FB_B9DC_4D8B_B318_79B760B37E58__INCLUDED_)
