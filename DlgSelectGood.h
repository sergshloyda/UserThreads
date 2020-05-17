#if !defined(AFX_DLGSELECTGOOD_H__C72C2436_73EA_4888_B1A2_4202D6F31439__INCLUDED_)
#define AFX_DLGSELECTGOOD_H__C72C2436_73EA_4888_B1A2_4202D6F31439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectGood.h : header file
//
#include "SuperTree.h"
//#include "UserThreadsDoc.h"
#include "GoodsGrid.h"	// Added by ClassView
#include <string>
#include <map>
#include "Repository.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgSelectGood dialog

class CDlgSelectGood : public CPropertyPage
{
	CGoodsGrid m_Grid;
	IVSFlexGridPtr m_spGoodsGrid;
	CSuperTree	m_TreeCtrl;
	std::map<CString,CAdapt<CComPtr<IDispatch>>> icons;
	CSize m_szTwPerPixel;
	CSize m_szPict;
	CFont m_Font;
	CRect m_rcResizeArea;
	std::wstring curProdFolderCode;	
	typedef boost::tuple<int,std::wstring,std::wstring,std::wstring> GridLine;
	std::vector<GridLine> SelectedProducts;
	typedef std::vector<GridLine>::const_iterator const_iter;
	bool blGridIsLoaded;
	Repository::ReferenceItem root;
// Construction
public:
	void InitGrid(const std::wstring& parent);
	

	struct TypeIcons{
		  static const CString CloseFolder() 
		  {
			  return "close_folder";
		  }
		  static const CString Goods() 
		  {
			  return "good";
		  }
		  static const CString OpenFolder() 
		  {
			  return "open_folder";
		  }
	};

	


	
	CDlgSelectGood();   // standard constructor
	DECLARE_DYNCREATE(CDlgSelectGood)
// Dialog Data
	//{{AFX_DATA(CDlgSelectGood)
	enum { IDD = IDD_SELGOOD };
	
	//}}AFX_DATA



	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);




	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectGood)

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnDblClick();
	void OnEnterCell();
	void OnGridKeyDown(short* KeyCode,short Shift);
	void AfterScroll(long OldTopRow,long OldLeftCol,long NewTopRow,	long NewLeftCol);

	

	void DrawResizeBar(LPRECT rc);
	void UpdateLayout(int iTreeWidth = -1);



	// Generated message map functions
	//{{AFX_MSG(CDlgSelectGood)
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	/*afx_msg LRESULT OnGetInfoFromNode(WPARAM,LPARAM);
	afx_msg LRESULT OnSetFocusToGrid(WPARAM,LPARAM);*/
	afx_msg void OnFolderDblClk(NMHDR* pNMHDR, LRESULT* pResult);
	
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	int  LoadPrice();
	void LoadIcons();
	void SetupGrid();
	void OnUpLevel();
	void OnDownLevel();
	void OnReturnPressed(long row=-1);
	void LoadItemsInGrid(long row=0);
	void LoadsSelectedProducts(const std::wstring& parent);
	void LoadHierarchy(const std::wstring& root);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTGOOD_H__C72C2436_73EA_4888_B1A2_4202D6F31439__INCLUDED_)
