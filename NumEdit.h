#if !defined(AFX_NUMEDIT_H__1D443ACC_CA76_46FC_AB57_C16EAA87281A__INCLUDED_)
#define AFX_NUMEDIT_H__1D443ACC_CA76_46FC_AB57_C16EAA87281A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumEdit window

class CNumEdit : public CEdit
{
// Construction
public:
	CNumEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumEdit)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	CFont m_Font;
	virtual ~CNumEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMEDIT_H__1D443ACC_CA76_46FC_AB57_C16EAA87281A__INCLUDED_)
