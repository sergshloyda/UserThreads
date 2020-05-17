#if !defined(AFX_COMPORTDLG_H__7AAD6391_78A3_4514_B46D_FF0F5FD075E4__INCLUDED_)
#define AFX_COMPORTDLG_H__7AAD6391_78A3_4514_B46D_FF0F5FD075E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComPortDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComPortDlg dialog

class CComPortDlg : public CDialog
{
// Construction
public:
	CComPortDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComPortDlg)
	enum { IDD = IDD_DLGCOMPORT };
	CString	m_strComPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComPortDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComPortDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPORTDLG_H__7AAD6391_78A3_4514_B46D_FF0F5FD075E4__INCLUDED_)
