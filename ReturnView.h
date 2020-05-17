#if !defined(AFX_RETURNVIEW_H__F5F87E24_3F13_46C8_A60F_0603826EF8A4__INCLUDED_)
#define AFX_RETURNVIEW_H__F5F87E24_3F13_46C8_A60F_0603826EF8A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReturnView.h : header file
//
#include "ReturnDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CReturnView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "GoodsGrid.h"	// Added by ClassView
#include "Label.h"	// Added by ClassView
class CReturnDoc;
class CReturnView : public CFormView
{  
 
public:
	CReturnView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReturnView)

// Form Data
public:
	//{{AFX_DATA(CReturnView)
	enum { IDD = IDD_RETURN };
		// NOTE: the ClassWizard will add data members here
		CStatic	m_wndToolBarHolder;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

	
	BOOL m_blSelectCheck;
	static CReturnView* GetView();
	CGoodsGrid m_wndGridGoods;
	void SetupGrids();  
	void RepositionControls(int nGridDocHeight=-1);
	void SetTitle(LPCTSTR strNewTitle);
	CReturnDoc* GetDocument();
	CGoodsGrid m_wndGridSelGoods;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReturnView)
	public:
	virtual BOOL DestroyWindow();
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint=NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int ReadDocsGridPlacement();
	void WriteGridPlacement();
	void ShowInfoOnPanel(BOOL blErase=TRUE);
	CFont m_fntLabel;
	CLabel m_lblInfoSumma;
	CLabel m_lblInfoNumUnits;
	CLabel m_lblInfoNumPos;
	CLabel m_lblInfoBaseDoc;
	CLabel m_lblInfoDocNum;
	COleSafeArray varArrRetGood;
	COleSafeArray varArrEntryDoc;
	CString m_strSelDocId;
	void DrawResizeBar(CRect *rc);
	void LoadToolbar();
	CGoodsGrid m_wndGridDocs;
	CString m_strReceivingBarCode;

 	CToolBar m_wndSelGoodToolBar;
	CRect m_rcResizeArea;
	int m_nDocsGridHeight;
	virtual ~CReturnView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CReturnView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnexec();
	afx_msg void OnExecreturn();
	afx_msg void OnSelgood();
	afx_msg void OnUpdateSelgood(CCmdUI* pCmdUI);
	afx_msg void OnDateselect();
	afx_msg void OnUpdateDateselect(CCmdUI* pCmdUI);
	afx_msg void OnSelsaledoc();
	afx_msg void OnUpdateSelsaledoc(CCmdUI* pCmdUI);
	afx_msg void OnSel1good();
	afx_msg void OnSelallgoods();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateSel1good(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelallgoods(CCmdUI* pCmdUI);
	afx_msg void OnUndoAllGoods();
	afx_msg void OnUpdateUndoAllGoods(CCmdUI* pCmdUI);
	afx_msg void OnBtnpodbor();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg void OnUpdateExecReturn(CCmdUI* pCmdUI);
	 void OnGridDocsAfterDataRefresh() ;
     void OnGridDocsDblClickGrid();
	 void OnGridDocsEnterCell();
	 void OnGridDocsLeaveCell();
	 void OnGridGoodsAfterDataRefresh();
	 void OnReturnAfterDataRefresh();
	 void OnGridGoodsAfterResizeColumn(int row,int col);
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
private:
	void CheckReturn(LPCTSTR strNomId,LPCTSTR strDocId);
	COLORREF m_clrForeColorSel;
	COLORREF m_clrBackColorSel;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RETURNVIEW_H__F5F87E24_3F13_46C8_A60F_0603826EF8A4__INCLUDED_)
