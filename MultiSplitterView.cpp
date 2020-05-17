// MultiSplitterView.cpp: implementation of the CMultiSplitterView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MultiSplitterView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMultiSplitterView::CMultiSplitterView()
{

}

CMultiSplitterView::~CMultiSplitterView()
{

}

/*
*******************************************************************************/
bool CMultiSplitterView::AddSwitchableView(UINT id, CRuntimeClass * pView,
								 CCreateContext* pContext,
								 const CRect & size, bool isFirstView, UINT altId)
{
   CWnd* pWin;
   DWORD style;

   pWin  = (CWnd*) pView->CreateObject();
   style = WS_CHILD ;
   
   if (isFirstView) 
   {
	   style |=  WS_VISIBLE ;
   }

   pWin->Create(NULL, NULL, style, size , this, id, pContext);

   if (isFirstView) // id provided is usally diff. so use alternate
   {
	   views[pWin] =altId ;
   }
   else 
   {
	   views[pWin] = id;
   }

   return true;
}


/*
* Description:  Hides one view and shows another
*
*******************************************************************************/
bool CMultiSplitterView::SwitchView(UINT id, int paneRow, int paneCol)
{
	
	CView* pOldView = (CView*) GetPane(paneRow, paneCol); // get current view
	
	if (pOldView == NULL) // serious prob
	{

	   MessageBoxHelper::ShowError(_T("Invalid OLD view ptrs !! Cant switch views "));

	   return false;
	}

   CView* pNewView = (CView*) GetDlgItem(id); // get new view

   if(pNewView == NULL ) // bad view id or this is already the view we requested
   {

	   MessageBoxHelper::ShowError(_T("Invalid view ptrs !! Cant switch views "));

      return false;
   }

   //CFrameWnd * mainWnd = (CFrameWnd *)AfxGetMainWnd();this for SDI
	CMDIFrameWnd* pMainWnd = (CMDIFrameWnd*)AfxGetMainWnd();

   // Get the active MDI child window.
   CMDIChildWnd* mainWnd = (CMDIChildWnd*)pMainWnd->MDIGetActive();

   // Get the active view attached to the active MDI child window.
  

   if (mainWnd == NULL) // serious prob
   {
	   ASSERT(false);
	   return false;
   }
	/*
		CMDIFrameWnd* pMainWnd = (CMDIFrameWnd*)AfxGetMainWnd();

   // Get the active MDI child window.
   CMDIChildWnd* pChild = (CMDIChildWnd*)pMainWnd->MDIGetActive();

   // Get the active view attached to the active MDI child window.
   CView* pOldActiveView = pChild->GetActiveView();
  */
   if(mainWnd->GetActiveView() == pOldView)
		mainWnd->SetActiveView(pNewView);
	
   pNewView->ShowWindow(SW_SHOW);
   pOldView->ShowWindow(SW_HIDE);

   pNewView->SetDlgCtrlID(  IdFromRowCol(paneRow, paneCol));

   CWnd * bCwnd =(CWnd *)pOldView; // upcast to CWnd ptr

  if (views.find(bCwnd) == views.end()) // search for CWnd ptr
  {

	MessageBoxHelper::ShowError(_T("Failed to find old view ptr !!!"));

	return false;
  }

   UINT oldId = views[bCwnd]; // get id of this view for future lookup

   pOldView->SetDlgCtrlID(oldId); // reset view id, so we can look it up

   RecalcLayout();

   pOldView->Invalidate();
   pNewView->Invalidate();

   return true;
}

/*
* Description:  Gets a base class CWnd ptr 
*
*******************************************************************************/
CWnd * CMultiSplitterView::GetViewPtr(UINT id, int paneRow, int paneCol)
{
	map<CWnd *, UINT>::iterator It, Iend = views.end();

	for (It = views.begin(); It != Iend; It++)
	{
		if ((*It).second == id)
		{
			return (*It).first;
		}
	}

	return NULL;
}
