// UpFolderTabCtrl.cpp: implementation of the CUpFolderTabCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "userthreads.h"
#include "UpFolderTabCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const int CXOFFSET = 8;		// defined pitch of trapezoid slant
const int CXMARGIN = 2;		// left/right text margin
const int CYMARGIN = 1;		// top/bottom text margin
const int CYBORDER = 1;		// top border thickness  
CUpFolderTabCtrl::CUpFolderTabCtrl()
{

}

CUpFolderTabCtrl::~CUpFolderTabCtrl()
{

}

void CUpFolderTabCtrl::DrawTabs(CDC &dc, const CRect &rc)
{
	CFolderTab* pCurTab = NULL;
	CPen blackPen(PS_SOLID, 1, RGB(0,0,0));	// black
	CPen shadowPen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
	CPen darkShadowPen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));
	CPen redPen(PS_SOLID,1,RGB(255,0,0));
	int n = GetItemCount();
	
	////////////////////////////////////////////////////////////////////
    
	CRect		rect;			// bounding rect
	GetClientRect(&rect);
	int x=0;
	CRgn rgn;
				// polygon region to fill (trapezoid)
	BOOL bSelected;
	CPoint selPoints[4] ;
	CRect selRect;
	for (int i=0; i<n; i++) 
	{
		CFolderTab* pTab = GetTab(i);
		ASSERT(pTab);
		if (i==m_iCurItem)
		{
			bSelected =TRUE;
			pCurTab=pTab;
			
		}
		else
			bSelected=FALSE;
		COLORREF bgColor = GetSysColor(COLOR_3DFACE);
		COLORREF fgColor = GetSysColor( COLOR_BTNTEXT);
		
		CBrush brush(bgColor);					 // background brush
		dc.SetBkColor(bgColor);					 // text background
		dc.SetTextColor(fgColor);				 // text color = fg color
		
		
		
		
		
		CRect rc;// = rect;
		rc.SetRectEmpty();
		dc.DrawText(pTab->GetText(), &rc, DT_CALCRECT);
		rc.right  += 2*CXOFFSET + 2*CXMARGIN;						// add margins
		rc.bottom = rc.top + GetSystemMetrics(SM_CYHSCROLL);	// ht = scrollbar ht
		rc += CPoint(x,0);
		// create trapezoid region
		CPoint pts[4];
		pts[0] = CPoint(rc.left + CXOFFSET,rc.top);
		pts[1] = CPoint(rc.left ,   rc.bottom);
		pts[2] = CPoint(rc.right -1, rc.bottom);
		pts[3] = CPoint(rc.right- CXOFFSET-1, rc.top);
		if(bSelected)
		{
			selPoints[0]=pts[0];
			selPoints[1]=pts[1];
			selPoints[2]=pts[2];
			selPoints[3]=pts[3];
			selRect=rc;
		}
		
		rgn.DeleteObject();
		
		
		
		rgn.CreatePolygonRgn(pts, 4, WINDING);
		
		if (pTab) 
			x += pTab->ComputeRgn(dc, x) - CXOFFSET;
		
		CPen* pOldPen = dc.SelectObject(&blackPen);
		dc.FillRgn(&rgn, &brush);
		
		
		
		pts[1].y--;			// correction #1: true bottom edge y-coord
		pts[2].y--;			// ...ditto
		//pts[3].y--;			// correction #2:	extend final LineTo
		dc.MoveTo(pts[0]);						// upper left
		dc.LineTo(pts[1]);						// bottom left
		// bottom line is shadow color
		//
		// line is inside trapezoid bottom
		// ...
		dc.SelectObject(&blackPen);			// upstroke is black
		
		dc.MoveTo(pts[2]);
		dc.LineTo(pts[3]);
		
		dc.LineTo(pts[0]);
		// y-1 to include endpoint
		
		// if not highlighted, upstroke has a 3D shadow, one pixel inside
		pts[2].x--;		// offset left one pixel
		pts[3].x--;		// ...ditto
		dc.SelectObject(&shadowPen);
		dc.MoveTo(pts[2]);
		dc.LineTo(pts[3]);
		dc.MoveTo(pts[3]);
		dc.LineTo(pts[0]);
		
		dc.SelectObject(pOldPen);
		
		// draw text
		rc.DeflateRect(CXOFFSET + CXMARGIN, CYMARGIN);
		CFont font;
		LOGFONT lf;
		
		m_fontNormal.GetLogFont (&lf);
		
		
		font.CreateFontIndirect (&lf);
		
		CFont* pOldFont = dc.SelectObject(&font);
		dc.DrawText(pTab->GetText(), &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		dc.SelectObject(pOldFont);
		
		if(rc.right >rect.right )break;
		
	}
	
	
	////////////////////////////рисуем выделенную закладку//////////////////////////////////////////////////////////////////
	{
		rgn.DeleteObject ();
		rgn.CreatePolygonRgn(selPoints, 4, WINDING);
		COLORREF bgSelColor = GetSysColor(COLOR_INFOBK);
		COLORREF fgSelColor = GetSysColor( COLOR_INFOTEXT);
		
		CBrush selBrush(bgSelColor);					 // background brush
		dc.SetBkColor(bgSelColor);					 // text background
		dc.SetTextColor(fgSelColor);				 // text color = fg color	
		
		
		CPen* pOldPen = dc.SelectObject(&blackPen);
		dc.FillRgn(&rgn, &selBrush);
		
		
		
		selPoints[1].y--;			// correction #1: true bottom edge y-coord
		selPoints[2].y--;			// ...ditto
		//pts[3].y--;			// correction #2:	extend final LineTo
		dc.MoveTo(selPoints[0]);						// upper left
		dc.LineTo(selPoints[1]);						// bottom left
		// bottom line is shadow color
		//
		// line is inside trapezoid bottom
		// ...
		dc.SelectObject(&blackPen);			// upstroke is black
		
		dc.MoveTo(selPoints[2]);
		dc.LineTo(selPoints[3]);
		
		dc.LineTo(selPoints[0]);
		// y-1 to include endpoint
		
		dc.SelectObject(pOldPen);
		
		// draw text
		selRect.DeflateRect(CXOFFSET + CXMARGIN, CYMARGIN);
		
		
		
		
		
		CFont* pOldFont = dc.SelectObject(&m_fontSelected);
		dc.DrawText(pCurTab->GetText(), &selRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		dc.SelectObject(pOldFont);
		
	}
	// draw border: line along the top edge, excluding seleted tab
	CRect rcCurTab(0,0,0,0);
	if (pCurTab)
		rcCurTab = pCurTab->GetRect();
	
	
	CPen* pOldPen = dc.SelectObject(&darkShadowPen);
	dc.MoveTo(rcCurTab.right, rcCurTab.bottom-1);
	dc.LineTo(rect.right, rect.bottom-1);
	if (m_dwFtabStyle & FTS_FULLBORDER) {
		dc.MoveTo(rc.right-1, rc.top);
		dc.LineTo(rc.right-1, rc.bottom-1);
		dc.LineTo(rc.left,  rc.bottom-1);
		dc.LineTo(rc.left,  rc.top);
	} else {
		dc.MoveTo(rect.left, rect.bottom-1);
	}
	dc.LineTo(rcCurTab.left,rcCurTab.bottom -1);

	pOldPen = dc.SelectObject(&shadowPen);
	dc.MoveTo(rcCurTab.right, rcCurTab.bottom-2);
	dc.LineTo(rect.right, rect.bottom-2);
	if (m_dwFtabStyle & FTS_FULLBORDER) {
		dc.MoveTo(rc.right-1, rc.top);
		dc.LineTo(rc.right-1, rc.bottom-1);
		dc.LineTo(rc.left,  rc.bottom-1);
		dc.LineTo(rc.left,  rc.top);
	} else {
		dc.MoveTo(rect.left, rect.bottom-2);
	}
	dc.LineTo(rcCurTab.left,rcCurTab.bottom -2);

	dc.SelectObject(pOldPen);
	
}
