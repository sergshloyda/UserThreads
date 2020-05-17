// GoodsGrid.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "GoodsGrid.h"
#include"Font.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "InfoFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CGoodsGrid

//CPopupText CGoodsGrid::g_wndTip;

UINT CGoodsGrid::g_nTipTimeMsec = 1000; // .1 sec

CGoodsGrid::CGoodsGrid()
{


	m_nCurItem=-1;
	m_bCapture = FALSE;
}

BOOL CGoodsGrid::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_MOUSEWHEEL)
	{
		//long cur=get_Row();
		short zDelta=GET_WHEEL_DELTA_WPARAM(pMsg->wParam);
		if(zDelta>0){
			SendMessage(WM_KEYDOWN,VK_UP,0);
			//OutputDebugString(_T("Mouse_Wheel Up\n"));
			return TRUE;

		}
		else
		{
			SendMessage(WM_KEYDOWN,VK_DOWN,0);
			//OutputDebugString(_T("Mouse_Wheel Down\n"));
			return TRUE;
			//put_TopRow(cur++);
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

CGoodsGrid::~CGoodsGrid()
{
}


BEGIN_MESSAGE_MAP(CGoodsGrid, CWnd)
	//{{AFX_MSG_MAP(CGoodsGrid)
	ON_WM_CREATE()
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGoodsGrid message handlers

BOOL CGoodsGrid::CreateFromStatic(UINT nID, CWnd *pParent)
{
	CStatic wndStatic;
	if(!wndStatic.SubclassDlgItem (nID,pParent))
		return FALSE;
	CRect rc;
	DWORD dwStyle=wndStatic.GetStyle ();
	wndStatic.GetWindowRect (&rc);
	pParent->ScreenToClient (&rc);
	
	//this->nID =nID;
	
	Create(NULL ,dwStyle,CRect(rc),pParent,nID);
	wndStatic.DestroyWindow ();
	return TRUE;
}



int CGoodsGrid::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CVSFlexGrid::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	return 0;
}

//DEL void CGoodsGrid::OnMouseMove(UINT nFlags, CPoint point) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	//check to cursor location into grid
//DEL 	if (CGoodsGrid::g_wndTip.m_hWnd !=NULL)
//DEL 	{
//DEL 		try{
//DEL 			//TRACE("Enter\n");
//DEL 			long lCol = GetMouseCol();
//DEL 			long lRow;
//DEL 			long lGridHeight=0;
//DEL 			for(long r=0;r<GetRows();r++)
//DEL 				lGridHeight+=GetRowHeight(r);
//DEL 			long lClientHeight=GetClientHeight();
//DEL 			if (lGridHeight<lClientHeight)
//DEL 			{
//DEL 				int nGridHeight=TwipsToPixelY (lGridHeight);
//DEL 				if (point.y>nGridHeight)
//DEL 					lRow=-1;
//DEL 				else
//DEL 					lRow=GetMouseRow();
//DEL 			}
//DEL 			else
//DEL 				lRow=GetMouseRow();
//DEL 			if((lRow<=0)||(lCol<=0)) return;
//DEL 			//TRACE("Row=%d,Col=%d\n",lRow,lCol);
//DEL 			
//DEL 			// Get text and text rectangle for item under mouse
//DEL 			CString sText;	// item text
//DEL 			CRect rcText;	// item text rect
//DEL 			
//DEL 			int nItem = OnGetItemInfo(point, rcText, sText,lRow,lCol);
//DEL 			//		TRACE("OnGetItemInfo\n");
//DEL 			if(lRow==0)nItem=-1;
//DEL 			if (nItem==-1 || nItem!=m_nCurItem) {
//DEL 				g_wndTip.Cancel(); // new item, or no item: cancel popup text
//DEL 				
//DEL 				if (nItem>=0 && !IsRectCompletelyVisible(rcText,lRow,lCol)) {
//DEL 					// new item, and not wholly visible: prepare popup tip
//DEL 					CRect rc = rcText;
//DEL 					ClientToScreen(&rc);	// text rect in screen coords
//DEL 					g_wndTip.SetWindowText(sText);
//DEL 					
//DEL 					CFont font;
//DEL 					font.CreatePointFont ((int)(GetFontSize()*10),GetFontName());
//DEL 					LOGFONT lf;
//DEL 					font.GetLogFont(&lf);
//DEL 					g_wndTip.SetLogFont(&lf);
//DEL 					// move tip window over list text
//DEL 					ClientToScreen(&point);
//DEL 					//ScreenToClient(&point);
//DEL 					g_wndTip.SetWindowPos(NULL, point.x/*-rc.Width()/2*/, /*rc.top*/point.y , rc.Width(),
//DEL 						rc.Height(), SWP_NOZORDER|SWP_NOACTIVATE);
//DEL 					
//DEL 					g_wndTip.ShowDelayed(g_nTipTimeMsec); // show popup text delayed
//DEL 				}
//DEL 			}
//DEL 			m_nCurItem = nItem;
//DEL 			
//DEL 			if (nItem==-1) {
//DEL 				::ReleaseCapture();
//DEL 				m_bCapture=FALSE;
//DEL 			}
//DEL 			
//DEL 			ClientToScreen(&point);	
//DEL 		}catch (...)
//DEL 		{
//DEL 			
//DEL 			AfxMessageBox("Error From MouseMove",MB_ICONSTOP);
//DEL 		}
//DEL 		
//DEL 		/*	CInfoFrame* pFrame=static_cast<CInfoFrame*>(AfxGetMainWnd());
//DEL 		if(pFrame->IsKindOf (RUNTIME_CLASS(CInfoFrame))&&::IsWindow(pFrame->m_hWnd ))
//DEL 		{
//DEL 		CString strStatusBarGridInfo;
//DEL 		
//DEL 		  strStatusBarGridInfo.Format ("R=%d,C=%d",lRow,lCol);
//DEL 		  pFrame->m_strStatusBarInfoGrid =strStatusBarGridInfo;
//DEL 		  
//DEL 	}*/
//DEL 	}
//DEL 	CVSFlexGrid::OnMouseMove(nFlags, point);
//DEL }
int CGoodsGrid::OnGetItemInfo (CPoint p,CRect& rc,CString& s,long& Row,long& Col)
{

	
	BOOL bOutside=FALSE;

	if((Col<=0)||(Row<=0))bOutside=TRUE;
	s.Empty();
	if (!bOutside) {
		//SetRow(Row);
		//SetCol(Col);
		s=GetTextMatrix(Row,Col);
		s.TrimRight ();
		s+="  ";
		long lLeft,lTop,lWidth,lHeight;
		
		lLeft=0;
		for(long cl=GetLeftCol()-1;cl<Col;cl++)
			lLeft+=GetColWidth (cl);
		lTop=0;
		for(long rw=GetTopRow()-1;rw<Row;rw++)
			lTop+=GetRowHeight (rw);
		lWidth=GetColWidth(Col);
		lHeight=GetRowHeight(Row);
		CRect rcCell;
		rcCell.SetRect(TwipsToPixelX(lLeft),TwipsToPixelY(lTop),TwipsToPixelX(lLeft)+TwipsToPixelX(lWidth),TwipsToPixelY(lTop)+TwipsToPixelY(lHeight));
	
		CFont* pFont=new CFont;
		
		pFont->CreatePointFont ((int)(GetFontSize ()*10) ,GetFontName ());
		CClientDC dc(this);
		CFont* pOldFont = dc.SelectObject(pFont);
		CRect rcAdjust=rcCell;
		dc.DrawText(s,&rcAdjust,DT_CALCRECT);
		rc.SetRect(rcCell.left,rcCell.top ,rcCell.left+rcAdjust.Width (),rcCell.bottom );
		
		dc.SelectObject(pOldFont);
		delete pFont;
		return Col*Row;
	}
	return -1;


}


BOOL CGoodsGrid::IsRectCompletelyVisible(const CRect& rc,long Row,long Col)
{
	//TRACE("IsRectCompletelyVisible1\n");
	long lCellWidth=TwipsToPixelX(GetColWidth (Col));
	//TRACE("IsRectCompletelyVisible2\n");
	return rc.Width ()<lCellWidth;
}

UINT CGoodsGrid::TwipsToPixelX(long lTwips)
{
	CClientDC dc(this);


	long lTwPerPixel=1440/dc.GetDeviceCaps (LOGPIXELSX);
	return lTwips/lTwPerPixel;
}

UINT CGoodsGrid::TwipsToPixelY(long lTwips)
{

	CClientDC dc(this);

	long lTwPerPixel =1440/dc.GetDeviceCaps (LOGPIXELSY);
	return lTwips/lTwPerPixel;
}

void CGoodsGrid::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	CWnd::PreSubclassWindow();
}



//DEL void CGoodsGrid::InitToolTip()
//DEL {
//DEL 				if (!g_wndTip) {
//DEL 		// create scroll tip window
//DEL 		g_wndTip.Create(CPoint(0,0), NULL, 0);
//DEL 	}
//DEL 			
//DEL }



int CGoodsGrid::FindInColumn(const CString &strFind, long lCol,long lRowBegin)
{

	long lRows=GetRows();
	long lCols=GetCols();
	ASSERT(lCol<=lCols);
	long lFindRow=-1;
	for(long r=lRowBegin;r<lRows;r++)
	{
		if (GetRowHidden(r))continue;
		CString str=GetTextMatrix(r,lCol);
		if(strFind.Compare (str)==0)
		{
		
			lFindRow=r;
			break;
		
		}
	}
	
	return lFindRow;
		
}

double CGoodsGrid::GetSumColumn(long lCol)
{
	long lRows=GetRows();
	long lCols=GetCols();
	ASSERT(lCol<=lCols);
	double dbSumma=0;
	for(long r=1;r<lRows;r++)
	{
		if (GetRowHidden(r)) continue;
		CString str=GetTextMatrix(r,lCol);
		float tmp=0.0;
		::VarR4FromStr (str.AllocSysString (),MAKELCID(LANG_ENGLISH,SORT_DEFAULT),LOCALE_NOUSEROVERRIDE,&tmp);
		dbSumma+=tmp;
	}
	return
		dbSumma;

}

UINT CGoodsGrid::TwipsPerPixelX()
{
	CClientDC dc(this);


	return 1440/dc.GetDeviceCaps (LOGPIXELSX);
	//return lTwips/lTwPerPixel;
}

UINT CGoodsGrid::TwipsPerPixelY()
{
	CClientDC dc(this);
	return 1440/dc.GetDeviceCaps (LOGPIXELSY);
}

BOOL CGoodsGrid::LoadRecordset(LPUNKNOWN pRst)
{
	SetEditable(flexEDNone);
	SetDataMode(0 /*flexDMFree*/);
	SetRedraw(FALSE);
	SetRefDataSource(pRst);
	
	// check binding
	if (GetDataSource() == NULL)
	{
		TRACE0("Failed to bind grid to recordset");
		return FALSE;
	}
	if (GetDataMode() != 1 /*flexDMBound*/)
	{
		TRACE0("Got recordset data, but can't update it "
			"(check recordset parameters)");
		SetEditable(0 /*flexEDNone*/);
	}
	SetRedraw(TRUE);
	return TRUE;
}

//DEL BOOL CGoodsGrid::CancelToolTip()
//DEL {
//DEL 	BOOL ret=FALSE;
//DEL 	if (g_wndTip)
//DEL 		ret=g_wndTip.DestroyWindow ();
//DEL 	return ret;
//DEL }

BOOL CGoodsGrid::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	CancelToolTip();
	return CWnd::DestroyWindow();
}

UINT CGoodsGrid::OnGetDlgCode() 
{
	// TODO: Add your message handler code here and/or call default
	
	return DLGC_WANTALLKEYS|DLGC_WANTARROWS;
}

int CGoodsGrid::GetCountHiddenRows()
{
	int nCount=0;
	for(int r=0;r<GetRows();r++)
		if(GetRowHidden(r)) nCount++;

	return nCount;

}




VARIANT CGoodsGrid::GetGridArray()
{
	COleSafeArray saRet; 
	long lNumRows=GetRows()-GetFixedRows();
	long lNumCols=GetCols()-GetFixedCols();        
	DWORD numElements[] = {lNumRows, lNumCols}; 
	
	// Create the 2 dimensional safe-array of type VT_VARIANT
	saRet.Create(VT_VARIANT, 2, numElements);
	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	// Initialize safearray  with values...
	long index[2];
	for(index[0]=0; index[0]<lNumRows; index[0]++)
	{
		for(index[1]=0; index[1]<lNumCols; index[1]++)
		{
			long r=GetFixedRows()+index[0];
			long c=GetFixedCols()+index[1];
			VARIANT val=GetCell (flexcpText,_variant_t(r),_variant_t(c),v,v);
			//populate the safearray elements with variant values
			saRet.PutElement(index, &val);
		}
	}
	// Return the safe-array encapsulated in a VARIANT...
	return saRet.Detach();
	
}

void CGoodsGrid::SaveGridPlacement(CWinApp *pApp, LPCTSTR szGrid)
{
   CString strSection       = szGrid;
   for(long c=0;c<GetCols();c++)
   {
	   CString strIntItem;
	   strIntItem.Format (_T("Col%d"),c);
	   pApp->WriteProfileInt(strSection, strIntItem, GetColWidth(c));
   }
 
}

void CGoodsGrid::LoadGridPlacement(CWinApp *pApp, LPCTSTR szGrid)
{
	CString strSection       = szGrid;
	for(long c=0;c<GetCols();c++)
	{
		CString strIntItem;
		strIntItem.Format (_T("Col%d"),c);
		int nColWidth;
		
		nColWidth = pApp->GetProfileInt(strSection, strIntItem, 100);
		SetColWidth (c,nColWidth);
	}
	
	
}

BOOL CGoodsGrid::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	long lTopRow=GetTopRow ();
	if(zDelta<0)
		SetTopRow (++lTopRow);
	else
		SetTopRow (--lTopRow);
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
