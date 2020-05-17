#if !defined(AFX_WNTRETEDIT_H__ECB4A2BA_6683_4DD0_8459_B6C163F0DE55__INCLUDED_)
#define AFX_WNTRETEDIT_H__ECB4A2BA_6683_4DD0_8459_B6C163F0DE55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WntRetEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWntRetEdit window
struct NMRETURN : public NMHDR {		 // notification struct
										 // item index
	LPCTSTR pszText; 					 // ptr to data, if any
};
class CWntRetEdit : public CEdit
{
// Construction
public:
	CWntRetEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWntRetEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWntRetEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWntRetEdit)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNTRETEDIT_H__ECB4A2BA_6683_4DD0_8459_B6C163F0DE55__INCLUDED_)
