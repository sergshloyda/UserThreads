#if !defined(AFX_FINDVIEW_H__86C6F542_D0DE_4EC2_BCC2_824FA94D5A69__INCLUDED_)
#define AFX_FINDVIEW_H__86C6F542_D0DE_4EC2_BCC2_824FA94D5A69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "SuperTree.h"
#include "DBDoc.h"
#include "FindEdit.h"
class CFindView : public CFormView
{
protected:
	CFindView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFindView)

// Form Data
public:
	//{{AFX_DATA(CFindView)
	enum { IDD = IDD_FIND_DLG1 };
	CStatic	m_wndStaticEx;
	CFindEdit	m_wndEdit;
	int		m_radio;
	CString	m_strName;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void Find();
	CDBDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFindView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFindView)
	afx_msg void OnRadioCustom();
	afx_msg void OnRadioAll();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeComboex();
	afx_msg void OnFindbtn();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CStringList m_lstPredicates;
	void EnumerateChildNodes(CTreeNode* root,int*);
	CString m_strSQL;
	CImageList m_il;

	CString m_strExplorer;
	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	void InitComboBoxEx();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDVIEW_H__86C6F542_D0DE_4EC2_BCC2_824FA94D5A69__INCLUDED_)
