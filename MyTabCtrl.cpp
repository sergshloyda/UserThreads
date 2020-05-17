// MyTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "MyTabCtrl.h"
#include "PSDlgInsertGood.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define CX_BORDER  1
#define CY_BORDER  0
/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl

CMyTabCtrl::CMyTabCtrl()
{
}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTabCtrl)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	
	

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl message handlers
void CMyTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(IsWindow(m_hWnd));
	
	CRect rcTab   =  CRect(&(lpDrawItemStruct->rcItem));
	int nTabIndex = lpDrawItemStruct->itemID;
	if (nTabIndex < 0 || nTabIndex >= GetItemCount())
		return;
	
	BOOL bSelected = (nTabIndex == GetCurSel());
	
	TCHAR szLabel[_MAX_PATH];
	TCITEM tci;
	tci.mask       = TCIF_TEXT | TCIF_IMAGE ;
	tci.pszText    = szLabel;     
	tci.cchTextMax = _MAX_PATH - 1;    	
	if (!GetItem(nTabIndex, &tci)) 
		return;
	
	CDC dc;
	if (lpDrawItemStruct->hDC == NULL)
		return;
	
	if (!dc.Attach(lpDrawItemStruct->hDC)) 
		return;
	
	DWORD dwStyle = GetStyle();
    rcTab.NormalizeRect();
	if ((dwStyle & TCS_BOTTOM) == 0)
	{
		rcTab.DeflateRect(CX_BORDER, CY_BORDER);
		rcTab.top += ::GetSystemMetrics(SM_CYEDGE);
	}
	
	dc.SetBkMode(TRANSPARENT);
	dc.FillSolidRect(rcTab, ::GetSysColor(COLOR_WINDOW));
	
	
	CImageList*   pImageList = GetImageList();
	//CMDIChildWnd* pViewFrame = reinterpret_cast<CMDIChildWnd*>(tci.lParam);
	//HICON hIcon = reinterpret_cast<HICON>(GetClassLong(pViewFrame->m_hWnd, GCL_HICONSM));
	//pImageList->Replace(tci.iImage/*nTabIndex*/, hIcon);  // nTabIndex
	
	if (pImageList && tci.iImage >= 0) 
	{
		rcTab.left += 4;//TODO--dc.GetTextExtent(_T(" ")).cx;		// Set a little margin
		
		// Get the height of image 
		IMAGEINFO info;
		pImageList->GetImageInfo(tci.iImage, &info);
		CRect ImageRect(info.rcImage);
		
		int nYpos;
		if ((dwStyle & TCS_BOTTOM) != 0)
			nYpos= rcTab.top + ::GetSystemMetrics(SM_CYEDGE);
		else
			nYpos= rcTab.top - ::GetSystemMetrics(SM_CYEDGE);
		
		pImageList->Draw(&dc, tci.iImage, CPoint(rcTab.left, nYpos), ILD_TRANSPARENT);
		rcTab.left += ImageRect.Width();
	}
	//	}
	CFont* poldFont=dc.SelectObject(&m_font);
	if (bSelected) 
	{
		dc.SetTextColor(RGB(255,0,0));
		//	dc.SelectObject(&m_SelFont);
		//	rcTab.top -= ::GetSystemMetrics(SM_CYEDGE);
	} 
	else 
	{
		dc.SetTextColor(RGB(0,0,0));	
		
	}
	
	dc.DrawText(szLabel, rcTab, DT_SINGLELINE | DT_VCENTER | DT_LEFT|DT_END_ELLIPSIS);
	dc.SelectObject (poldFont);
	dc.Detach();
} 




BOOL CMyTabCtrl::SetFont(int nSize, LPCTSTR chFontName)
{
	m_font.CreatePointFont (nSize*10,chFontName);
	return TRUE;
}







HBRUSH CMyTabCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CTabCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return (HBRUSH)GetStockObject (WHITE_BRUSH);
}

BOOL CMyTabCtrl::OnEraseBkgnd(CDC* pDC) 
{

   CRect rc;
   GetClientRect(&rc);
   pDC->FillSolidRect(rc, ::GetSysColor(COLOR_WINDOW));
   return TRUE;

}








