#if !defined(AFX_DLGENTERCASH_H__A15FD14D_ADE3_4000_9A32_9803537AB1AF__INCLUDED_)
#define AFX_DLGENTERCASH_H__A15FD14D_ADE3_4000_9A32_9803537AB1AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnterCash.h : header file
//
#include "Label.h"
#include "WntRetEdit.h"
#include "CheckDoc.h"
#include "UserThreadsView.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgEnterCash dialog

class CDlgEnterCash : public CDialog
{
// Construction
public:
	CDlgEnterCash(CWnd* pParent = NULL);   // standard constructor
	int DoModal();
// Dialog Data
	//{{AFX_DATA(CDlgEnterCash)
	enum { IDD = IDD_DLGCHANGE };
	CEdit	m_wndEdit;
	CLabel	m_lblWnd;
	CLabel	m_lblChange;
	float	m_flCash;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnterCash)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEnterCash)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeCash();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CCheckDoc* pDoc;
	CFont m_Font;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENTERCASH_H__A15FD14D_ADE3_4000_9A32_9803537AB1AF__INCLUDED_)
