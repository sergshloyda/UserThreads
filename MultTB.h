#if !defined(AFX_MULTTB_H__E1B54354_EDB4_4CDA_B528_C461502456E8__INCLUDED_)
#define AFX_MULTTB_H__E1B54354_EDB4_4CDA_B528_C461502456E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultTB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultTB window

class CMultTB : public CToolBar
{
// Construction
public:
	CMultTB();

// Attributes
public:
CButton m_wndMulButton;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultTB)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultTB();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultTB)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTTB_H__E1B54354_EDB4_4CDA_B528_C461502456E8__INCLUDED_)
