// BarcodeEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "userthreads.h"
#include "BarcodeEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarcodeEdit

CBarcodeEdit::CBarcodeEdit()
{
}

CBarcodeEdit::~CBarcodeEdit()
{
}


BEGIN_MESSAGE_MAP(CBarcodeEdit, CEdit)
	//{{AFX_MSG_MAP(CBarcodeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarcodeEdit message handlers



//DEL void CBarcodeEdit::OnUpdate() 
//DEL {
//DEL 	// TODO: If this is a RICHEDIT control, the control will not
//DEL 	// send this notification unless you override the CEdit::OnInitDialog()
//DEL 	// function to send the EM_SETEVENTMASK message to the control
//DEL 
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }

//DEL void CBarcodeEdit::OnMaxtext() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }

//DEL int CBarcodeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//DEL {
//DEL 	if (CEdit::OnCreate(lpCreateStruct) == -1)
//DEL 		return -1;
//DEL 	
//DEL 	// TODO: Add your specialized creation code here
//DEL 	SendMessage(EM_LIMITTEXT,(WPARAM)13,0);
//DEL 	return 0;
//DEL }

//DEL void CBarcodeEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	//SendMessage(EM_SETSEL, 0, MAKELONG(0xffff, 0xffff) );
//DEL 	//CEdit::OnChar(nChar, nRepCnt, nFlags);
//DEL }




