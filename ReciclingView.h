#if !defined(AFX_RECICLINGVIEW_H__F9294071_3A58_4E90_84A9_E46BE4147992__INCLUDED_)
#define AFX_RECICLINGVIEW_H__F9294071_3A58_4E90_84A9_E46BE4147992__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReciclingView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReciclingView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "label.h"
class CReciclingView : public CFormView
{
protected:
          // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReciclingView)

// Form Data
public:
	//{{AFX_DATA(CReciclingView)
	enum { IDD = IDD_RECICLING };
	CLabel	m_Label;
	//}}AFX_DATA

// Attributes
public:
	CReciclingView(); 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReciclingView)
	public:
	virtual BOOL DestroyWindow();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CReciclingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CReciclingView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CAnimateCtrl cAnimCtrl;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECICLINGVIEW_H__F9294071_3A58_4E90_84A9_E46BE4147992__INCLUDED_)
