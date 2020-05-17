// FontToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "FontToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontToolBar





CFontToolBar::CFontToolBar()
{
}

CFontToolBar::~CFontToolBar()
{
}


BEGIN_MESSAGE_MAP(CFontToolBar, CMFCToolBar)
	//{{AFX_MSG_MAP(CFontToolBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontToolBar message handlers







BOOL CFontToolBar::SetupToolBar(CString szFontName,int nFontSize)
{
	if(!IsWindowVisible ())
		ShowWindow(SW_SHOW);

	if(m_wndFontNameCB.GetSafeHwnd ()==NULL){
	CRect rect;
	SetButtonInfo (0,IDC_FONTNAME_CB,TBBS_SEPARATOR,550);
	GetItemRect (0,&rect);
	rect.bottom =rect.top+250;
	if(!m_wndFontNameCB.Create (WS_CHILD|CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_VSCROLL|CBS_HASSTRINGS,
		rect,this,IDC_FONTNAME_CB))
	{
		return FALSE;
	}
	m_wndFontNameCB.ShowWindow (SW_SHOW);
	m_wndFontNameCB.PopulateFont ();

	////////////////////////////////////////////////////////////////////////;
	SetButtonInfo (1,IDC_FONTSIZE_CB,TBBS_SEPARATOR,44);
	GetItemRect (1,&rect);
	rect.bottom =rect.top+150;
	if(!m_wndFontSizeCB.Create (WS_CHILD|CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_VSCROLL|CBS_HASSTRINGS,
		rect,this,IDC_FONTSIZE_CB))
	{
		return FALSE;
	}
	m_wndFontSizeCB.ShowWindow (SW_SHOW);
	m_wndFontSizeCB.PopulFontSize ();
	TCHAR buff[MAX_PATH];
	_itot(nFontSize,buff,10);
	return ReadFont(szFontName,buff);
	}
	else
		return FALSE;
}

BOOL CFontToolBar::ReadFont(CString szFontName,CString szFontSize)
{

	int nIndex = 0;
	if ((nIndex=m_wndFontNameCB.FindString(nIndex, szFontName)) != LB_ERR)
		m_wndFontNameCB.SetCurSel (nIndex);
	else
		m_wndFontNameCB.SetCurSel (0);

		if ((nIndex=m_wndFontSizeCB.FindString(nIndex, szFontSize)) != LB_ERR)
		m_wndFontSizeCB.SetCurSel (nIndex);
	else
		m_wndFontSizeCB.SetCurSel (0);
		return TRUE;
}







void CFontToolBar::GetFontName(LPTSTR szBuffer)
{
	int nIndex=m_wndFontNameCB.GetCurSel();
	m_wndFontNameCB.GetLBText (nIndex,szBuffer);

}

int CFontToolBar::GetFontSize()
{
	CString szSizeBuff;
    int nIndex=m_wndFontSizeCB.GetCurSel();
	m_wndFontSizeCB.GetLBText (nIndex,szSizeBuff);
	return _ttoi(szSizeBuff);
}

CString CFontToolBar::GetFontName()
{
	CString szBuffer;
	int nIndex=m_wndFontNameCB.GetCurSel();
	m_wndFontNameCB.GetLBText (nIndex,szBuffer);
	return szBuffer;
}


