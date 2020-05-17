#if !defined(AFX_FINDEDIT_H__6550A760_82D9_4F2B_B371_79CB56A2C875__INCLUDED_)
#define AFX_FINDEDIT_H__6550A760_82D9_4F2B_B371_79CB56A2C875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindEdit window

class CFindEdit : public CEdit
{
// Construction
public:
	CFindEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFindEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFindEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnArchive();
	afx_msg void OnUpdateArchive(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDEDIT_H__6550A760_82D9_4F2B_B371_79CB56A2C875__INCLUDED_)
