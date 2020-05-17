#if !defined(AFX_DLGSETQUANTITY_H__AF64DE3D_59C5_4444_A8BD_A20179A6DA4E__INCLUDED_)
#define AFX_DLGSETQUANTITY_H__AF64DE3D_59C5_4444_A8BD_A20179A6DA4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetQuantity.h : header file
//
//#include "UserThreadsDoc.h"
/////////////////////////////////////////////////////////////////////////////
#pragma warning( push )
#pragma warning( disable : 4018 )
#include <vector>
#include <string>
#pragma warning( pop )
class CDlgSetQuantity : public CDialog
{
// Construction
public:
	CString m_strHolder;

	CDlgSetQuantity(CWnd* pParent = NULL);   // standard constructor
	CDlgSetQuantity(LPCTSTR strCaption,CWnd* pParent = NULL);   // standard constructor
	CDlgSetQuantity(BOOL blPass,CWnd* pParent = NULL);   
// Dialog Data
	//{{AFX_DATA(CDlgSetQuantity)
	enum { IDD = IDD_SETQTY };
	CEdit	m_wndEdit;
	int		m_nQty;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetQuantity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetQuantity)
	virtual BOOL OnInitDialog();
	afx_msg void On1num();
	afx_msg void On2num();
	afx_msg void On3num();
	afx_msg void OnClear();
	afx_msg void On0num();
	afx_msg void OnBackspc();
	afx_msg void On4num();
	afx_msg void On5num();
	afx_msg void On6num();
	afx_msg void On7num();
	afx_msg void On8num();
	afx_msg void On9num();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMainDocument* pDoc;
	CFont m_Font;
	CString m_strCaption;
	BOOL m_blPass;
	std::vector<char> charStack;
	std::vector<char>::iterator myVectorIterator;
	
	virtual void OnCancel();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETQUANTITY_H__AF64DE3D_59C5_4444_A8BD_A20179A6DA4E__INCLUDED_)
