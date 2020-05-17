#if !defined(AFX_CHECKBUTTON_H__5622241F_4759_4F44_B23A_AE1BF9ABD392__INCLUDED_)
#define AFX_CHECKBUTTON_H__5622241F_4759_4F44_B23A_AE1BF9ABD392__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckButton window

class CCheckButton : public CButton
{
// Construction
public:
	CCheckButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCheckButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKBUTTON_H__5622241F_4759_4F44_B23A_AE1BF9ABD392__INCLUDED_)
