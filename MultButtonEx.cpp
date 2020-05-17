// MultButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "MultButtonEx.h"


// MultButtonEx
IMPLEMENT_SERIAL(MultButtonEx,CMFCToolBarMenuButton,1)
MultButtonEx::MultButtonEx(UINT nID,LPCTSTR lpszText,HMENU hMenu):CMFCToolBarMenuButton(nID,hMenu,-1,lpszText,FALSE)
{
	if(lpszText!=NULL)
		m_strText=lpszText;
	m_bText=TRUE;
	m_nID=nID;
	m_iImage=-1;
	
	
	
}



void MultButtonEx::OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz /*= TRUE*/, BOOL bCustomizeMode /*= FALSE*/, BOOL bHighlight /*= FALSE*/, BOOL bDrawBorder /*= TRUE*/, BOOL bGrayDisabledButtons /*= TRUE*/)
{
	UINT nStyle=m_nStyle;
	m_nStyle&=~TBBS_DISABLED;
	CFont font;
	font.CreatePointFont (200,_T("Arial"));
	CFont* pOldFont=pDC->SelectObject(&font);
	pDC->DrawText( m_strText,(LPRECT)&rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	pDC->SelectObject(pOldFont);
	CMFCToolBarButton::OnDraw(pDC,rect,nullptr,bHorz,FALSE,FALSE,TRUE,TRUE);
	//OutputDebugString(_T("MultButtonEx::OnDraw\n"));
	m_bText=FALSE;
	m_nStyle=nStyle;
}

void MultButtonEx::OnGlobalFontsChanged()
{
OutputDebugString(_T("MultButtonEx::OnGlobalFontsChanged\n"));	
}

// MultButtonEx member functions
