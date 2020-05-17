#if !defined(AFX_NAKLFORM_H__58A98D0D_EDF4_4FF8_9561_DE470A4CFA93__INCLUDED_)
#define AFX_NAKLFORM_H__58A98D0D_EDF4_4FF8_9561_DE470A4CFA93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NaklForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNaklForm form view
#include "DBDoc.h"
#include "GoodsGrid.h"
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CNaklForm : public CFormView
{
protected:
	CNaklForm();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CNaklForm)

// Form Data
public:
	//{{AFX_DATA(CNaklForm)
	enum { IDD = IDD_NAKL_DLG };
	CStatic	m_wndToolBarHolder;
	//}}AFX_DATA

// Attributes
public:
	CGoodsGrid m_wndGrid;
private:
	const int m_constGridBorder;
	IVSFlexGridPtr pGrid;
// Operations
public:
	COleDateTime m_tmEndInterval;
	COleDateTime m_tmStartInterval;
	CToolBar m_wndToolBar;
	void RepositionControls();
	CDBDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNaklForm)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetupGrid();
	void LoadToolbar();
	virtual ~CNaklForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CNaklForm)
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPreviewDoc();
	afx_msg void OnUpdatePreviewDoc(CCmdUI* pCmdUI);
	afx_msg void OnSetinterval();
	afx_msg void OnUpdateSetinterval(CCmdUI* pCmdUI);
	afx_msg void OnFinddoc();
	afx_msg void OnUpdateFinddoc(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_EVENTSINK_MAP()

	afx_msg void OnAfterDataRefresh() ;
	afx_msg void OnDblClickGrid();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAKLFORM_H__58A98D0D_EDF4_4FF8_9561_DE470A4CFA93__INCLUDED_)
