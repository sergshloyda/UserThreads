// MDIChild.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "MDIChild.h"
#include "InfoFrame.h"
#include "InfoConsole.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIChild

IMPLEMENT_DYNCREATE(CMDIChild, CMDIChildWnd)

CMDIChild::CMDIChild()
{
	
}

CMDIChild::~CMDIChild()
{
}


BEGIN_MESSAGE_MAP(CMDIChild, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMDIChild)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIChild message handlers

BOOL CMDIChild::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	 
	CMDIChildWnd::OnCreateClient(lpcs, pContext);


	return TRUE;
}

void CMDIChild::OnClose() 
{
	CView* pView=GetActiveView();
	pView->SendMessage (WM_CLOSE);
	CMDIChildWnd::OnClose();
}







BOOL CMDIChild::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(nCode==CN_COMMAND)
	{
		switch(nID & 0xFFF0)
		{
		case SC_MAXIMIZE:MDIMaximize();break;
		case SC_RESTORE:MDIRestore();break;
		case SC_NEXTWINDOW:
			GetParent()->SendMessage(WM_MDINEXT,(WPARAM)GetSafeHwnd(),(LPARAM)0);
			break;
		case SC_MINIMIZE:ShowWindow(SW_MINIMIZE);break;
		case SC_CLOSE:PostMessage(WM_CLOSE);break;
		}
	}	
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMDIChild::SetTitle(LPCTSTR strTitle)
{
 AfxSetWindowText(m_hWnd,strTitle);
}
