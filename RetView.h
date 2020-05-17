#if !defined(AFX_RETVIEW_H__C1D93F55_E38E_4C0E_8213_6A344B08E7A1__INCLUDED_)
#define AFX_RETVIEW_H__C1D93F55_E38E_4C0E_8213_6A344B08E7A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RetView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRetView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRetView : public CFormView
{
protected:
	CRetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRetView)

// Form Data
public:
	//{{AFX_DATA(CRetView)
	enum { IDD = IDD_RETURN };
	CStatic	m_wndToolBarHolder;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRetView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRetView)
	afx_msg void OnBtnexec();
	afx_msg void OnBtnseldoc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RETVIEW_H__C1D93F55_E38E_4C0E_8213_6A344B08E7A1__INCLUDED_)
