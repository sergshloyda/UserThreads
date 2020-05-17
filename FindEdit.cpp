// FindEdit.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "FindEdit.h"
#include "FindView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindEdit

CFindEdit::CFindEdit()
{
}

CFindEdit::~CFindEdit()
{
}


BEGIN_MESSAGE_MAP(CFindEdit, CEdit)
	//{{AFX_MSG_MAP(CFindEdit)
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_COMMAND(IDC_ARCHIVE, OnArchive)
	ON_UPDATE_COMMAND_UI(IDC_ARCHIVE, OnUpdateArchive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindEdit message handlers

void CFindEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
 if (nChar == VK_RETURN)
 {
	 CFindView* pView=static_cast<CFindView*>(GetParent());
	 pView->Find();

 }
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

UINT CFindEdit::OnGetDlgCode() 
{
return DLGC_WANTARROWS|DLGC_WANTALLKEYS|DLGC_WANTCHARS;	
	//return CEdit::OnGetDlgCode();
}

void CFindEdit::OnArchive() 
{
	// TODO: Add your command handler code here
	
}

void CFindEdit::OnUpdateArchive(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
