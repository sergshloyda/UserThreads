#if !defined(AFX_DIALOGVIEW_H__A2EC97E6_C608_4B73_912A_28039753B47A__INCLUDED_)
#define AFX_DIALOGVIEW_H__A2EC97E6_C608_4B73_912A_28039753B47A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogView.h : header file
//
//#include "UserThreadsDoc.h"
#include "DBDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogView form view
#define IDD_DICT_DLG 132
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "GoodsGrid.h"	// Added by ClassView

class CDialogView : public CFormView
{
protected:
	CDialogView(); 
	// protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDialogView)
// Form Data
public:
	//{{AFX_DATA(CDialogView)
	enum { IDD = IDD_DICT_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

	CGoodsGrid m_GridGoods;
	CDBDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL m_blItemHasChilren;
	virtual ~CDialogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDialogView)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnAfterDataRefresh() ;
	afx_msg void OnDblClickGrid();
	
	DECLARE_MESSAGE_MAP()
	
private:
	COLORREF m_crDefaultGridColor;
	BOOL m_blFillCategory;
	const int m_constGridBorder;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGVIEW_H__A2EC97E6_C608_4B73_912A_28039753B47A__INCLUDED_)
