// ReturnEdit.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ReturnEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReturnEdit

CReturnEdit::CReturnEdit()
{
}

CReturnEdit::~CReturnEdit()
{
}


BEGIN_MESSAGE_MAP(CReturnEdit, CEdit)
	//{{AFX_MSG_MAP(CReturnEdit)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReturnEdit message handlers



void CReturnEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
