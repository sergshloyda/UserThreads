#if !defined(AFX_ZREPORTVIEW_H__B8776BA2_7111_49E5_ABA0_BFCBDCD811ED__INCLUDED_)
#define AFX_ZREPORTVIEW_H__B8776BA2_7111_49E5_ABA0_BFCBDCD811ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZReportView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZReportView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "GoodsGrid.h"
#include "statlink.h"
#include "UpFolderTabCtrl.h"
class CZReportDoc;
#define NAME_COL 2
class CZReportView : public CFormView
{ 
protected:   

	CZReportView();                  // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CZReportView)

// Form Data
public:
	//{{AFX_DATA(CZReportView)
	enum { IDD = IDD_ZREPORT };
	CLabel	m_lblCurTotal;
	CLabel	m_lblOstatok;
	CStaticLink	m_lblSumReturn;
	CLabel	m_lblSumSale;
	CLabel	m_lblCaption;
	//}}AFX_DATA     
	CUpFolderTabCtrl m_wndFolderTab;	
// Attributes
public:
 _variant_t vtArray;
// Operations
public:
	BOOL LoadReturns();
	void RepositionControls();
	CGoodsGrid m_wndGrid;
	IVSFlexGridPtr  m_spGrid;
	CZReportDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZReportView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg LRESULT OnShowReturn(WPARAM wParam,LPARAM lParam);
	afx_msg void OnChangedTab(NMHDR* nmtab, LRESULT* pRes);
	virtual ~CZReportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CZReportView)
	afx_msg void OnOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	//}}AFX_MSG
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnAfterDataRefresh() ;
	DECLARE_MESSAGE_MAP()
private:
	BOOL LoadZReportTable();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZREPORTVIEW_H__B8776BA2_7111_49E5_ABA0_BFCBDCD811ED__INCLUDED_)
