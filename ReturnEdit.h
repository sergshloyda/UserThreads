#if !defined(AFX_RETURNEDIT_H__C13E285F_5A31_45A7_8AFF_60A94BDBC9C5__INCLUDED_)
#define AFX_RETURNEDIT_H__C13E285F_5A31_45A7_8AFF_60A94BDBC9C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReturnEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReturnEdit window

class CReturnEdit : public CEdit
{
// Construction
public:
	CReturnEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReturnEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReturnEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReturnEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RETURNEDIT_H__C13E285F_5A31_45A7_8AFF_60A94BDBC9C5__INCLUDED_)
