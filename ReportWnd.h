#if !defined(AFX_REPORTWND_H__B510B0E2_4B13_461C_A7B5_AE8D5FB3E726__INCLUDED_)
#define AFX_REPORTWND_H__B510B0E2_4B13_461C_A7B5_AE8D5FB3E726__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportWnd window

class CReportWnd : public CWnd
{
// Construction
public:
	CReportWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReportWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTWND_H__B510B0E2_4B13_461C_A7B5_AE8D5FB3E726__INCLUDED_)
