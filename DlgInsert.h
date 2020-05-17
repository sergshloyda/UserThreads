#if !defined(AFX_DLGINSERT_H__902E3DC7_4A00_4286_AB69_E738A9EC99AC__INCLUDED_)
#define AFX_DLGINSERT_H__902E3DC7_4A00_4286_AB69_E738A9EC99AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInsert.h : header file
//
#include "BarcodeEdit.h"
#include "GoodsGrid.h"
//#include"UserThreadsDoc.h"
#include "UserThreadsView.h"
#include "WntRetEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgInsert dialog

class CDlgInsert : public CPropertyPage
{
// Construction
	static int stnLen;
public:
	
	CGoodsGrid m_Grid;
	CDlgInsert(CView* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInsert)
	enum { IDD = IDD_DLGINSERT };
	CButton	m_btnBarCodeFind;
	CWntRetEdit	m_wndEdit;
	CString	m_strBarCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInsert)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnEnterCell();

	// Generated message map functions
	//{{AFX_MSG(CDlgInsert)
	afx_msg void OnChangeEdit();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	void OnGridKeyDown(short* KeyCode,short Shift);
	afx_msg LRESULT OnSetFocusToGrid(WPARAM,LPARAM);
	afx_msg void OnEditReturnPressed(NMHDR * pNotifyStruct, LRESULT* pRes);
	void LoadSelectedProducts(const std::wstring& filter);
	void LoadItemsInGrid(long begin_row=0);
	void AfterScroll(long OldTopRow,long OldLeftCol,long NewTopRow,	long NewLeftCol);
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
private:
	CFont m_Font;
	typedef boost::tuple<std::wstring,std::wstring,std::wstring,std::wstring> GridLine;
	std::vector<GridLine> SelectedProducts;
	void UpdateLayout();
	void SetupGrid();
	bool blGridIsLoaded;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINSERT_H__902E3DC7_4A00_4286_AB69_E738A9EC99AC__INCLUDED_)
