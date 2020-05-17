#if !defined(AFX_GOODSGRID_H__28EA51AD_2684_4BE3_A513_69DDDD52D51D__INCLUDED_)
#define AFX_GOODSGRID_H__28EA51AD_2684_4BE3_A513_69DDDD52D51D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoodsGrid.h : header file
//
//#define IDC_GRID 1
/////////////////////////////////////////////////////////////////////////////
// CGoodsGrid window
#include "vsflexgrid.h"
#include "puptext.h"
class CGoodsGrid : public CVSFlexGrid
{
// Construction
public:
	CGoodsGrid();
	enum { MinColWidth=1000 };

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//enum { IDD = IDC_GRID };
// Attributes
public:
	//static CPopupText g_wndTip;	
	BOOL	m_bCapture;
	static UINT g_nTipTimeMsec;	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoodsGrid)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShrinkColumn(long numColumn)
	{
		IVSFlexGridPtr spGrid=GetControlUnknown();
		long remainWidth=0;
		for(long i=0;i<spGrid->Cols-1;i++)
		{
			if (i==numColumn) continue;
			remainWidth+=spGrid->GetColWidth(i);
		}
		spGrid->put_ColWidth (numColumn,spGrid->ClientWidth -remainWidth);/* */
	}
	void LoadGridPlacement(CWinApp* pApp,LPCTSTR szGrid);
	void SaveGridPlacement(CWinApp* pApp,LPCTSTR szGrid);
	VARIANT GetGridArray();
	UINT nID;
	int GetCountHiddenRows();
	BOOL LoadRecordset(LPUNKNOWN pRst);
	UINT TwipsPerPixelY();
	UINT TwipsPerPixelX();
	double GetSumColumn(long lCol);
	int FindInColumn(const CString& strFind,long lCol,long lRowBegin=0);
	UINT TwipsToPixelY(long lTwips);
	UINT TwipsToPixelX(long lTwips);
	BOOL CreateFromStatic(UINT nId,CWnd* pParent);
	virtual ~CGoodsGrid();
	virtual BOOL IsRectCompletelyVisible(const CRect& rc,long Row,long Col);
	virtual int OnGetItemInfo(CPoint p, CRect& rc, CString& s,long& Row,long& Col);
	// Generated message map functions
protected:
	//{{AFX_MSG(CGoodsGrid)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
	int m_nCurItem;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOODSGRID_H__28EA51AD_2684_4BE3_A513_69DDDD52D51D__INCLUDED_)
