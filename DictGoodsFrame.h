#if !defined(AFX_DICTGOODSFRAME_H__01182C4B_14C4_4154_A01C_DC7FE91CD513__INCLUDED_)
#define AFX_DICTGOODSFRAME_H__01182C4B_14C4_4154_A01C_DC7FE91CD513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DictGoodsFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDictGoodsFrame frame
#include "MultiSplitterView.h"
#include "MDIChild.h"
class CDictGoodsFrame : public CMDIChild
{
	DECLARE_DYNCREATE(CDictGoodsFrame)
protected:
	CDictGoodsFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	CMultiSplitterView m_wndSplitter;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDictGoodsFrame)
	public:
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_uCurrentButton;
	BOOL LoadToolBar(UINT IDD,CWnd *parentWnd);
	CToolBar m_wndToolBar;

	virtual ~CDictGoodsFrame();

	// Generated message map functions
	//{{AFX_MSG(CDictGoodsFrame)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFolderViewShow();
	afx_msg void OnUpdateFolderViewShow(CCmdUI* pCmdUI);
	afx_msg void OnFindViewShow();
	afx_msg void OnUpdateFindViewShow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DICTGOODSFRAME_H__01182C4B_14C4_4154_A01C_DC7FE91CD513__INCLUDED_)
