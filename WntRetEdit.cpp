+
	// WntRetEdit.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "WntRetEdit.h"

#ifdef _DEBUG

#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWntRetEdit

CWntRetEdit::CWntRetEdit()
{
}

CWntRetEdit::~CWntRetEdit()
{
}


BEGIN_MESSAGE_MAP(CWntRetEdit, CEdit)
	//{{AFX_MSG_MAP(CWntRetEdit)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWntRetEdit message handlers

UINT CWntRetEdit::OnGetDlgCode() 
{
	// TODO: Add your message handler code here and/or call default
	
	return DLGC_WANTALLKEYS;
}

void CWntRetEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_RETURN)
	{
		NMRETURN nm;
		nm.hwndFrom = m_hWnd;
		nm.idFrom = GetDlgCtrlID();
		nm.code = NM_RETURN;
		CString strText;
		GetWindowText(strText);
		nm.pszText=strText.GetBuffer (255);
		strText.ReleaseBuffer ();
		CWnd* pParent=GetParent();
		pParent->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}


