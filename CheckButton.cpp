// CheckButton.cpp : implementation file
//

#include "stdafx.h"
#include "CheckButton.h"
#include "UserThreads.h"
#include "MainDocument.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckButton

CCheckButton::CCheckButton()
{


	
}

CCheckButton::~CCheckButton()
{
}


BEGIN_MESSAGE_MAP(CCheckButton, CButton)
	//{{AFX_MSG_MAP(CCheckButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckButton message handlers

void CCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rc;
	rc=lpDrawItemStruct->rcItem;
	dc.FillSolidRect(rc,::GetSysColor(COLOR_BTNFACE));
	UINT state=lpDrawItemStruct->itemState;
	if(lpDrawItemStruct->CtlID==IDC_TRANSACT)
	{
		dc.SetTextColor(RGB(255,0,0));
	}
	else
	{
		dc.SetTextColor(RGB(50,50,200));
	}
	
	if((state&ODS_SELECTED))
	{
		dc.DrawEdge(rc,EDGE_SUNKEN,BF_RECT);
	}
	else if((state&ODS_DISABLED))
	{
		dc.DrawEdge(rc,EDGE_RAISED,BF_FLAT);
		dc.SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
	}
	else
	{
		dc.DrawEdge(rc,EDGE_RAISED,BF_RECT);
	}
	
	CString strTemp;
	GetWindowText(strTemp);
	dc.DrawText(strTemp,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	if(state&ODS_FOCUS)
	{
		rc.InflateRect(CSize(-3,-3));
		rc.NormalizeRect();
		dc.DrawFocusRect(rc);
	}
	dc.Detach();
}
