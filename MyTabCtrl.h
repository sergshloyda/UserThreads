#if !defined(AFX_MYTABCTRL_H__43CF3E23_7EF8_4F26_9F0C_CDC1774C08D4__INCLUDED_)
#define AFX_MYTABCTRL_H__43CF3E23_7EF8_4F26_9F0C_CDC1774C08D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl window

class CMyTabCtrl : public CTabCtrl
{
// Construction
public:
	CMyTabCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetFont(int nSize,LPCTSTR chFontName);
	virtual ~CMyTabCtrl();

	// Generated message map functions
protected:
	CFont m_font;
	//{{AFX_MSG(CMyTabCtrl)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
public:
	


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTABCTRL_H__43CF3E23_7EF8_4F26_9F0C_CDC1774C08D4__INCLUDED_)
