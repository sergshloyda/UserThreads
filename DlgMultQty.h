#if !defined(AFX_DLGMULTQTY_H__D764BC3A_8E4D_4E14_973D_E9A5F81AD230__INCLUDED_)
#define AFX_DLGMULTQTY_H__D764BC3A_8E4D_4E14_973D_E9A5F81AD230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMultQty.h : header file
//
#include "NumEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgMultQty dialog

class CDlgMultQty : public CDialog
{
// Construction
public:
	CDlgMultQty(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMultQty)
	enum { IDD = IDD_MULQTY };
//	CEdit	m_wndEdit;
	int		m_nQty;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMultQty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMultQty)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_Font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMULTQTY_H__D764BC3A_8E4D_4E14_973D_E9A5F81AD230__INCLUDED_)
