#if !defined(AFX_MULTBUTTON_H__2F8025C9_D4E6_447B_A1B4_A8F5993DA651__INCLUDED_)
#define AFX_MULTBUTTON_H__2F8025C9_D4E6_447B_A1B4_A8F5993DA651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultButton window

class CMultButton : public CButton
{
// Construction
public:
	CMultButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTBUTTON_H__2F8025C9_D4E6_447B_A1B4_A8F5993DA651__INCLUDED_)
