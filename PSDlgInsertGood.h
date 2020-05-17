#if !defined(AFX_PSDLGINSERTGOOD_H__B6DFFCA6_AB30_42B6_B606_B3A41E6747C9__INCLUDED_)
#define AFX_PSDLGINSERTGOOD_H__B6DFFCA6_AB30_42B6_B606_B3A41E6747C9__INCLUDED_

#include "MyTabCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSDlgInsertGood.h : header file
//
#include "DlgInsert.h"
#include "DlgSelectGood.h"
#include "DlgFindAll.h"
#include "MyTabCtrl.h"
#include "Label.h"
/////////////////////////////////////////////////////////////////////////////
// CPSDlgInsertGood

class CPSDlgInsertGood : public CPropertySheet
{
	DECLARE_DYNAMIC(CPSDlgInsertGood)

// Construction
public:
	CPSDlgInsertGood(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSDlgInsertGood(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDlgInsert* m_pgSelBarCode;
	CDlgSelectGood* m_pgSelGood;
	CString m_strSelectProduct;
private:
	CImageList m_ImageList;
	CRect m_PageRect;
	static  TCHAR s_profileRect[];
	static  TCHAR s_profilePage[];
	static  TCHAR s_profileHeading[];
	BOOL m_bFirstTime;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSDlgInsertGood)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetTipText(LPCTSTR strText);
	void OnSelectGood(const CString& strBarCode);
	CMyTabCtrl m_myTabCtrl;
	//CView* pParent;
	BOOL SetPageIcon(int nTab,int nIcon);
	void SetPageTitle(int nTab,LPTSTR pszText);
	virtual ~CPSDlgInsertGood();

	// Generated message map functions
protected:
	void RestorePropertyPage();
	BOOL   m_bNeedInit;
	CRect  m_rCrt;
	int    m_nMinCX;
	int    m_nMinCY;
	CLabel m_wndTip;
	BOOL CreateTipWindow(UINT nID,CWnd*pParent);
	

    

	//{{AFX_MSG(CPSDlgInsertGood)
	virtual BOOL OnInitDialog();
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
    afx_msg void OnApplyNow();
	//}}AFX_MSG
	afx_msg LRESULT OnResizePage(WPARAM wParam, LPARAM lParam);
	static int CALLBACK XmnPropSheetCallback(HWND hWnd,UINT message, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
 #define WM_RESIZEPAGE WM_USER + 111
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSDLGINSERTGOOD_H__B6DFFCA6_AB30_42B6_B606_B3A41E6747C9__INCLUDED_)
