// MainChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "MainChildFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainChildFrame
const int NBUTTONS = 4;

// This table is used to load the buttons
// One table is worth a thousand lines of code (well, a lot, anyway)
// Use tables!!!
//
static struct {
	UINT id;										 // command ID
	UINT style;									 // button style
	UINT iImage;								 // index of image in normal/hot bitmaps

} Buttons[NBUTTONS] = {

	// command ID					button style						image index
	{ ID_SELSALEDOC,	TBSTYLE_BUTTON,							0 },
	{ ID_DATESELECT,	TBSTYLE_BUTTON,							1 },
	{ ID_SELGOOD,	    TBSTYLE_BUTTON,							2 },
	{ ID_EXECRETURN,	TBSTYLE_BUTTON,							3 }
};
IMPLEMENT_DYNCREATE(CMainChildFrame, CMDIChildWnd)

CMainChildFrame::CMainChildFrame()
{
}

CMainChildFrame::~CMainChildFrame()
{
}


BEGIN_MESSAGE_MAP(CMainChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMainChildFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainChildFrame message handlers
BOOL CMainChildFrame::ReplaceView(CRuntimeClass * pViewClass)

{
	CCreateContext context;
	CView * pCurrentView;
	
	// If no active view for the frame, return FALSE because
	// thisfunction retrieves the current document from the active
	// view.
	if ((pCurrentView=GetActiveView())==NULL)
		return FALSE;
	DWORD dwStyle=pCurrentView->GetStyle ();
	// If we're already displaying this kind of view, no need
	// to go further.
	if ((pCurrentView->IsKindOf(pViewClass))==TRUE)
		return TRUE;
	::SetWindowLong(pCurrentView->m_hWnd, GWL_ID, 0);
	// Get pointer to CDocument object so that it can be used
	// in the creation process of the new view.
	CDocument * pDoc= pCurrentView->GetDocument();
	
	// Set flag so that document will not be deleted when
	// view is destroyed.
	BOOL bAutoDelete=pDoc->m_bAutoDelete;
	pDoc->m_bAutoDelete=FALSE;
	// Delete existing view
	pCurrentView->DestroyWindow();
	// restore flag
	pDoc->m_bAutoDelete=bAutoDelete;
	
	// Create new view and redraw.
	context.m_pNewViewClass=pViewClass;
	context.m_pCurrentDoc=pDoc;
	context.m_pNewDocTemplate=NULL;
	context.m_pLastView=NULL;
	context.m_pCurrentFrame=this;
	//pDoc->SetTitle (pViewClass->m_lpszClassName );
	
	CView * pNewView = (CView *) pViewClass->CreateObject();
	
	if (pNewView == NULL)
	{
		TRACE1("Warning: Dynamic create of view type %Fs failed\n", pViewClass->m_lpszClassName);
			return FALSE;
	}
	
	if (!pNewView->Create(NULL, NULL, dwStyle,
		CRect(0,0,0,0), this, AFX_IDW_PANE_FIRST,
		&context))
	{
		TRACE0("Warning: couldn't create view for frame\n");
		return FALSE; // Programmer can assume FALSE return value
		// from this function means that there
		// isn't a view.
	}
	
	
	// WM_INITIALUPDATE is define in AFXPRIV.H.
	pNewView->SendMessage(WM_INITIALUPDATE, 0, 0);
	
	RecalcLayout();
	
	pNewView->UpdateWindow();
	
	SetActiveView(pNewView);
	
	return TRUE;
} 

BOOL CMainChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	 CMDIChildWnd::OnCreateClient(lpcs, pContext);
	  MDIMaximize ();
	return TRUE;
}

int CMainChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	
 if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
           return -1;

       // Create a toolbar window.  IDR_CHILDFRAME is the resource name
       // of the toolbar to be loaded.
    	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT|TBSTYLE_LIST, WS_CHILD | WS_VISIBLE | CBRS_TOP
	| CBRS_TOOLTIPS | CBRS_FLYBY  ) )
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if(!m_wndToolBar.LoadToolBar(IDR_RETURN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	TRACE0("1 create toolbar\n");
	CSize szImage(16,16);
	CSize szMargin(83,7);//for button labels
	CImageList il;
	VERIFY(il.Create (szImage.cx ,szImage.cy ,ILC_COLOR8|ILC_MASK,4,szMargin.cx ));
	il.SetBkColor (TRANSPARENT);

	HICON hIcon[NBUTTONS+1];
	int n;
	hIcon[0]=AfxGetApp()->LoadIcon (IDI_SELSALEDOC);
	hIcon[1]=AfxGetApp()->LoadIcon (IDI_CALENDAR);
	hIcon[2]=AfxGetApp()->LoadIcon (IDI_SELGOOD);
	hIcon[3]=AfxGetApp()->LoadIcon (IDI_OK);
	hIcon[4]=AfxGetApp()->LoadIcon (IDI_GOOD_TB);
	for(n=0;n<NBUTTONS+1;n++)
		il.Add (hIcon[n]);
	
	m_wndToolBar.SetSizes (szImage+szMargin,szImage);

	m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)il.Detach());

	m_wndToolBar.SetButtons(NULL, NBUTTONS);
	for (int i=0; i<NBUTTONS; i++) {
		m_wndToolBar.SetButtonInfo(i,
			Buttons[i].id,						 // command id
			Buttons[i].style,					 // buttons style
			Buttons[i].iImage);	                 // index of image in bitmap
			m_wndToolBar.SetButtonText (i,_T(" "));//set text later in OnUpdateViewInfoconsole
	}
	
	

       // TODO: Delete these three lines if you don't want the toolbar
       // to be dockable
       //m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
       //EnableDocking(CBRS_ALIGN_ANY);
       //DockControlBar(&m_wndToolBar);

       return 0;	

}

CToolBar* CMainChildFrame::GetToolBar(UINT nID)
{
	
	if (nID == 0)
		return NULL;
	POSITION pos = m_listControlBars.GetHeadPosition();
	while (pos != NULL)
	{
		CControlBar* pBar = (CControlBar*)m_listControlBars.GetNext(pos);
		ASSERT(pBar != NULL);
		int id=::GetDlgCtrlID(pBar->m_hWnd );
		if (id == (int)nID)
		{
			ASSERT_KINDOF(CControlBar, pBar);
			return (CToolBar*)pBar;
		}
	}
	//return NULL;
	return  &m_wndToolBar;
}

void CMainChildFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CMDIChildWnd::OnClose();
}

BOOL CMainChildFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	if(cs.hMenu!=NULL)
	{
		::DestroyMenu(cs.hMenu);      // delete menu if loaded
		cs.hMenu = NULL;              // no menu for this window
	}
	
	cs.style&=~(LONG)FWS_ADDTOTITLE;
	return CMDIChildWnd::PreCreateWindow(cs);
}




