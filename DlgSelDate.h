#if !defined(AFX_DLGSELDATE_H__D0E2D1C3_0363_4DCE_A34F_C54DAA96D48E__INCLUDED_)
#define AFX_DLGSELDATE_H__D0E2D1C3_0363_4DCE_A34F_C54DAA96D48E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelDate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelDate dialog

class CDlgSelDate : public CDialog
{
// Construction
public:
	CDlgSelDate(CWnd* pParent = NULL);   // standard constructor
CDlgSelDate(CString *pDate, BOOL *pbOK, int x, int y, CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDlgSelDate)
	enum { IDD = IDD_DLGSELDATE };
	CMonthCalCtrl	m_ctrlCalendar;
	COleDateTime	m_tmDate;
	//}}AFX_DATA
	CString	*m_pDate;
	BOOL	*m_pbOK;
	BOOL	m_bFirstTime;
	int		m_x;
	int		m_y;
	BOOL	m_bOk; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelDate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
CView* m_pParentView;
	// Generated message map functions
	//{{AFX_MSG(CDlgSelDate)
	afx_msg void OnSelectMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnWindowPosChanging(WINDOWPOS * lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELDATE_H__D0E2D1C3_0363_4DCE_A34F_C54DAA96D48E__INCLUDED_)
