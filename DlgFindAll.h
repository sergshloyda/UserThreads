#if !defined(AFX_DLGFINDALL_H__A89B0500_B808_4934_A959_D2DAFA935222__INCLUDED_)
#define AFX_DLGFINDALL_H__A89B0500_B808_4934_A959_D2DAFA935222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFindAll.h : header file
//
#include "GoodsGrid.h"
//#include "UserThreadsDoc.h"
#include "UserThreadsView.h"
#include "WntRetEdit.h"
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgFindAll dialog

class CDlgFindAll : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgFindAll)

// Construction
public:
	CDlgFindAll(CView* pParent);
	CDlgFindAll();
	~CDlgFindAll();

// Dialog Data
	//{{AFX_DATA(CDlgFindAll)
	enum { IDD = IDD_FINDALL };
	
	CString	m_strFind;
	//}}AFX_DATA
protected:
	CGoodsGrid m_Grid;
	CWntRetEdit	m_wndEdit;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgFindAll)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgFindAll)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnEditReturnPressed(NMHDR * pNotifyStruct, LRESULT* pRes);
	afx_msg void OnBnClickedButton();
	void OnEnterCell();
	void OnGridKeyDown(short* KeyCode,short Shift);
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

private:
	void UpdateLayout();
	void SetupGrid();
	void LoadSelectedProducts(const std::wstring& filter);
	void LoadItemsInGrid(long begin_row=0);
	void AfterScroll(long OldTopRow,long OldLeftCol,long NewTopRow,	long NewLeftCol);
	//CMainDocument* pDoc;
	CFont m_Font;
	typedef boost::tuple<std::wstring,std::wstring,std::wstring> GridLine;
	std::vector<GridLine> SelectedProducts;
	//_RecordsetPtr pRst;
	//CUserThreadsView* pView;
	CButton m_btnFind;
	bool blGridIsLoaded;
public:
	

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFINDALL_H__A89B0500_B808_4934_A959_D2DAFA935222__INCLUDED_)
