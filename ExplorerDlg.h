#if !defined(AFX_EXPLORERDLG_H__5D3D627B_7C20_423C_8C1F_32465698AB55__INCLUDED_)
#define AFX_EXPLORERDLG_H__5D3D627B_7C20_423C_8C1F_32465698AB55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExplorerDlg.h : header file
//
#include "SuperTree.h"
/////////////////////////////////////////////////////////////////////////////
// CExplorerDlg dialog

class CExplorerDlg : public CDialog
{
// Construction
public:
	CTreeNode* m_pNode;

	CExplorerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExplorerDlg)
	enum { IDD = IDD_EXPL_DLG };

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExplorerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExplorerDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnGetInfoFromNode(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CWnd* pAssocView;
	CSuperTree	m_STreeCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLORERDLG_H__5D3D627B_7C20_423C_8C1F_32465698AB55__INCLUDED_)
