// UserThreadsView.h : interface of the CUserThreadsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERTHREADSVIEW_H__E59BE59A_AC70_46C2_B339_8B1B835C5237__INCLUDED_)
#define AFX_USERTHREADSVIEW_H__E59BE59A_AC70_46C2_B339_8B1B835C5237__INCLUDED_
#include "Barcode.h"
#include "GoodsGrid.h"
#include "Label.h"
#include "StatLink.h"
#include "MainDocument.h"
#include "resource.h"
#include "font.h"	// Added by ClassView
#include "CheckButton.h"
#include "WntRetComboBox.h"
#include "atlwin.h"
#include "afxwin.h"
#include <afxpriv.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCheckDoc;
class CMercury;

class CUserThreadsView : public CFormView
{
	friend class CCheckDoc;
protected: // create from serialization only
 
	DECLARE_DYNCREATE(CUserThreadsView)  

public:
	//{{AFX_DATA(CUserThreadsView)
	enum{ IDD = IDD_USERTHREADS_FORM };
	enum{IDC_COMBO_NUM=10001};
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	

	// Attributes
public:
	CCheckDoc* GetDocument();
	CUserThreadsView();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserThreadsView)
	public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:

	CLabel m_wndLblClient;
	CLabel m_wndLblNumPos;
	CLabel m_wndLblNumDoc;
	CLabel m_wndLblSumma;
	CGoodsGrid m_wndGrid;
	CFont m_LabelFont;

	CBarcode* m_pBarCodeReader;
	virtual ~CUserThreadsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void TransactCheck();
	//{{AFX_MSG(CUserThreadsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnInsert();
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);

	afx_msg void OnCheckButton();
	afx_msg void OnUpdateCheckButton(CCmdUI* pCmdUI);
	afx_msg void OnKillfocusCombo();
	//}}AFX_MSG
	afx_msg void OnIdleUpdateCmdUI();
	afx_msg LRESULT OnViewClientInfo(WPARAM,LPARAM);
	afx_msg void OnComboBoxReturnPressed(NMHDR* pNMHDR, LRESULT* pResult);
	void OnAfterEditGrid(long Row,long Col);
	void OnGridKeyDown(short* KeyCode,short Shift);
	void OnClick();
	void OnEnterCell();


	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:

	
	CString m_strReceivingBarCode;
	int m_nQtyMultiplicator;
	BOOL CloseCommPort();
	BOOL OpenCommPort(LPCTSTR strCommPort);
	void PrintCheck(float flCash=0.0);
	void SetTitle(LPCTSTR strNewTitle);
	BOOL RepositionControls();
private:
	void ShowKKMError();
	void DeleteRow();
	void ShowInfoOnPanel();
	void SetFontSetting();
	CMainDocument* m_pMainDoc;
	HACCEL  m_hAccelTable;
public:
	CCheckButton m_btnPrintCheck;
	CCheckButton m_btnFindDlg;
	WntRetComboBox m_wndCombo;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSelectProductDlg();
	afx_msg void OnTransactBtnClck();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

/*#ifndef _DEBUG  // debug version in UserThreadsView.cpp
inline CUserThreadsDoc* CUserThreadsView::GetDocument()
   { return (CUserThreadsDoc*)m_pDocument; }
#endif*/

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERTHREADSVIEW_H__E59BE59A_AC70_46C2_B339_8B1B835C5237__INCLUDED_)
