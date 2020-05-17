#if !defined(AFX_FONTTOOLBAR_H__6AC85FB2_D218_495D_B7D4_E1FCD9F087EE__INCLUDED_)
#define AFX_FONTTOOLBAR_H__6AC85FB2_D218_495D_B7D4_E1FCD9F087EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontToolBar.h : header file
//
#include "FontCombo.h"
/////////////////////////////////////////////////////////////////////////////
// CFontToolBar window

class CFontToolBar : public CMFCToolBar
{
// Construction
public:
	CFontToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetFontSize();
	void GetFontName(LPTSTR szFontName);
	
	BOOL SetupToolBar(CString szFontName,int nFontSize);
	virtual ~CFontToolBar();
public:
	CString GetFontName();

protected:
	CFontCombo m_wndFontNameCB;
	CFontCombo m_wndFontSizeCB;
	// Generated message map functions
protected:
	BOOL ReadFont(CString szFontName,CString szFontSize);
	
	//{{AFX_MSG(CFontToolBar)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTTOOLBAR_H__6AC85FB2_D218_495D_B7D4_E1FCD9F087EE__INCLUDED_)
