// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "UserThreads.h"
#include "UserThreadsView.h"
#include "MainFrm.h"
//#include "UserThreadsDoc.h"
#include "ReturnView.h"
#include "ReciclingView.h"
#include "ReturnDoc.h"
#include "MainChildFrame.h"
#include "CheckDoc.h"
#include "CashDoc.h"
#include "ZReportView.h"
#include "ZReportDoc.h"
#include "DlgLogin.h"
#include "DlgManageKKM.h"
#include "MultButtonEx.h"
#include "PointSettings.h"
#include "FontDlgPage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ID_FONT_CB 1
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_VIEW_INFOCONSOLE, OnUpdateViewInfoconsole)
	ON_COMMAND(ID_CHECK, OnCheckView)
	ON_UPDATE_COMMAND_UI(ID_CHECK, OnUpdateCheckView)
	ON_COMMAND(ID_ZREPORT, OnZReport)
	ON_UPDATE_COMMAND_UI(ID_ZREPORT, OnUpdateZReport)
	ON_COMMAND(ID_RECIC, OnRecicling)
	ON_UPDATE_COMMAND_UI(ID_RECIC, OnUpdateRecicling)
	ON_COMMAND(ID_TOOL, OnSetup)
	ON_UPDATE_COMMAND_UI(ID_TOOL, OnUpdateSetup)
	ON_COMMAND(ID_RETURN, OnReturn)
	ON_UPDATE_COMMAND_UI(ID_RETURN, OnUpdateReturn)
	
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI ( ID_PANE_COMPORT, OnUpdatePaneComPort )
	ON_UPDATE_COMMAND_UI ( ID_PANE_PA, OnUpdatePointActual )
	ON_UPDATE_COMMAND_UI ( ID_PANE_KKM,OnUpdatePaneKKM     )
	ON_UPDATE_COMMAND_UI ( ID_PANE_KKM_ERROR,OnUpdatePaneKKMError     )
	ON_COMMAND(ID_VIEW_INFOCONSOLE, OnInfoConsole)
	ON_MESSAGE(WM_KILL_THREAD,OnKillThread)
	ON_MESSAGE(WM_FONT_CHANGED,OnFontChanged)
	ON_MESSAGE(WM_DISCONNECTBASE,OnDisconnectBase)
	ON_MESSAGE(WM_CONNECTBASE,OnConnectBase)
	ON_MESSAGE(WM_CHANGE_MULTIPLICATOR, OnChangeMultiplicator)
	ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &CMainFrame::OnResetToolbar)
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	// status line indicator
	ID_PANE_KKM_ERROR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_PANE_PA,
	ID_PANE_COMPORT,
	ID_PANE_KKM,


};



const int NBUTTONS = 8;

// This table is used to load the buttons
// One table is worth a thousand lines of code (well, a lot, anyway)
// Use tables!!!
//
const int MULTBUT_WIDTH=90;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
LPCTSTR CMainFrame::s_winClassName = NULL;
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bActive = -1; // invalid
	m_rcQtyView.SetRectEmpty ();
	m_bUserActivated=FALSE;
	m_nQtyMultiplicator=0;
	m_strErrorMsg=_T("Ждем соединения с кассовым аппаратом");
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
	
if(!CreateMainToolBar ())
 return -1;
if (!m_wndMultToolBar.Create(this, WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|
	CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC| CBRS_GRIPPER | CBRS_BORDER_3D, IDR_MULTTOOLBAR) ||
	!m_wndMultToolBar.LoadToolBar(IDR_MULTTOOLBAR))
{
	TRACE0("Failed to create build toolbar\n");
	return FALSE;      // fail to create
}

//EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);	
	
	//EnableDocking(CBRS_ALIGN_TOP);


	//if (!m_wndFontTB.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_FLOAT_MULTI ) )
	//{
	//	TRACE0("Failed to create toolbar\n");
	//	return -1;      // fail to create
	//}
	//m_wndFontTB.LoadToolBar (IDR_FONTTBAR);
/*	if(!m_wndFontTB.SetupToolBar ())
	DockControlBar(&m_wndMainBar,AFX_IDW_DOCKBAR_TOP);
	DockControlBarLeftOf(&m_wndEditBar,&m_wndMainBar);
	}*/
	//if (!m_wndOutput.Create(_T("Output"), this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, 
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM| CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("Failed to create Output window\n");
	//	return FALSE; // failed to create
	//}
	//m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndOutput);
	//DockControlBarLeftOf(&m_wndFontTB,&m_wndToolBar);
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndFontTB.EnableDocking(CBRS_ALIGN_ANY);

	m_wndMultToolBar.EnableDocking(CBRS_ALIGN_ANY);


	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	DockPane(&m_wndToolBar);
	DockPane(&m_wndMultToolBar);
	DockPaneLeftOf(&m_wndToolBar, &m_wndMultToolBar);
	CString strOutputWndCaption;
	strOutputWndCaption.LoadString(ID_VIEW_OUTPUTWND);
	if (!m_wndOutput.Create(strOutputWndCaption, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, 
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Output window\n");
		return FALSE; // failed to create
	}
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	/*CRect rcToolBar;
	m_wndToolBar.GetWindowRect (&rcToolBar);
	CRect rcQtyView(rcToolBar.right+11,rcToolBar.top+11 ,rcToolBar.right +70,rcToolBar.bottom );
	m_rcQtyView=rcQtyView ;
	DockPane(&m_wndFontTB);*/



	m_hAccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)); 
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	//m_wndStatusBar.EnableDocking(CBRS_ALIGN_BOTTOM);
	//DockPane(&m_wndStatusBar);
	
	return 0;
	
	


}

static LPCTSTR RegisterSimilarClass(LPCTSTR lpszNewClassName,
	LPCTSTR lpszOldClassName, UINT nIDResource)
{
	// Get class info for old class.
	//
	HINSTANCE hInst = AfxGetInstanceHandle();
	WNDCLASS wc;
	if (!::GetClassInfo(hInst, lpszOldClassName, &wc)) {
		TRACE1("Can't find window class %s\n", lpszOldClassName);
		return NULL;
	}

	// Register new class with same info, but different name and icon.
	//
	wc.lpszClassName = lpszNewClassName;
	wc.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(nIDResource));
	if (!AfxRegisterClass(&wc)) {
		TRACE1("Unable to register window class%s\n", lpszNewClassName);
		return NULL;
	}
	return lpszNewClassName;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
//cs.lpszClass = _T("MyNewClass");

          // Change the following line to call.
          // CFrameWnd::PreCreateWindow(cs) if this is an SDI application.
          //return CMDIFrameWnd::PreCreateWindow(cs);
	

	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if (s_winClassName==NULL) {	
		// One-time initialization: register the class
		//
		s_winClassName = RegisterSimilarClass(_T("_CheckWindow_"), 
			(LPTSTR)cs.lpszClass, IDR_FINDVIEW_TMPL);
		if (!s_winClassName)
			return FALSE;
	}
	cs.lpszClass = s_winClassName;
	//cs.hMenu =NULL;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnInfoConsole()
{
	//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
	//CMainDocument* pMainDocument=pApp->GetDocument<CMainDocument> ();
	//
	//
	//// Get the active MDI child window.
	//CMDIChildWnd* pChild = (CMDIChildWnd*)MDIGetActive();
	//
	//// Get the active view attached to the active MDI child window.
	//CView* pView = pChild->GetActiveView();
	////pView->DestroyWindow ();
	//if(pApp->m_pInfoConsoleThread ==NULL)
	//pApp->m_pInfoConsoleThread=new CInfoConsole(pView->GetSafeHwnd (),GetSafeHwnd ());
	//pApp->m_pInfoConsoleThread->CreateThread ();
	//
	//pApp->m_pInfoConsoleThread->SetDocument (pMainDocument);


}


static BOOL CALLBACK SendMDIChildToClose(HWND hWnd, LPARAM)
{
	CWnd* pWnd = CWnd::FromHandlePermanent(hWnd);
	if (pWnd != NULL)
	{
		pWnd->SendMessage(WM_CLOSE);

	}
	return TRUE;
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CUserThreadsApp* pApp = static_cast<CUserThreadsApp*>(AfxGetApp());
	ASSERT(pApp);
	if((pApp->hwndInfoWnd)&&(::IsWindow (pApp->hwndInfoWnd)))
	
		::SendMessage(pApp->hwndInfoWnd ,WM_CLOSE,0,0);

	::EnumChildWindows(m_hWndMDIClient, SendMDIChildToClose, 0);

	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnUpdateViewInfoconsole(CCmdUI* pCmdUI) 
{

	//m_wndToolBar.SetToolBarBtnText (5,_T("Информация(F6)"),FALSE,TRUE);
	//m_wndToolBar.SetToolBarBtnText (6,_T("О программе(F1)"),FALSE,TRUE);	
}
LRESULT CMainFrame::OnKillThread (WPARAM,LPARAM)
{
	CUserThreadsApp* pApp = static_cast<CUserThreadsApp*>(AfxGetApp());
	ASSERT(pApp);
	
if(pApp->m_pInfoConsoleThread)
	::WaitForSingleObject (pApp->m_pInfoConsoleThread ->m_hThread ,INFINITE);
//	delete pApp->m_pInfoConsoleThread ;
	return 0L;
}
LRESULT CMainFrame::OnFontChanged (WPARAM,LPARAM)
{
        
	
	// Get the active MDI child window.
	CMDIChildWnd* pChild = static_cast<CMDIChildWnd*>(GetActiveFrame());
	// Get the active view attached to the active MDI child window.
	CView* pActiveView = reinterpret_cast<CView*>(pChild->GetActiveView());

	ASSERT(pActiveView!=NULL);
	//CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	ASSERT(pMainDoc->IsKindOf(RUNTIME_CLASS(CMainDocument)));
//	TCHAR szBuff[MAX_PATH];
//	m_wndFontTB.GetFontName (szBuff);
//	int nFontSize=m_wndFontTB.GetFontSize ();
//	pMainDoc->SetPointFont(szBuff,nFontSize);
	CCheckDoc* pDoc=(CCheckDoc*)pActiveView->GetDocument ();
	pDoc->UpdateAllViews (NULL);
	return 0L;
}
void CMainFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf)
{
	
}

//DEL CDocument* CMainFrame::GetActiveDocument() 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL CMDIChildWnd* pChild = static_cast<CMDIChildWnd*>(GetActiveFrame());
//DEL 	// Get the active view attached to the active MDI child window.
//DEL 	CView* pActiveView = reinterpret_cast<CView*>(pChild->GetActiveView());
//DEL CUserThreadsDoc* pDoc=NULL;
//DEL 	if(pActiveView!=NULL)
//DEL 	pDoc=static_cast<CUserThreadsDoc*>(pActiveView->GetDocument ());
//DEL 	return pDoc;
//DEL }



BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message >= WM_KEYFIRST) && 
		(pMsg->message <= WM_KEYLAST) ){
			switch (pMsg->wParam)
			{
			case VK_F10:
				OnZReport();   
				break;
			case VK_F4:
				OnReturn();
				break;
			default:
				return CMDIFrameWnd::PreTranslateMessage(pMsg);
				break;
			}
			return TRUE;
		
	}else
	//		CWnd* pWnd=CWnd::FromHandle(pMsg->hwnd);
	//		OutputDebugString(_T("one"));
	//		CWnd* pParent=pWnd->GetParentFrame();
	//		if(pParent->IsKindOf(RUNTIME_CLASS(CMainChildFrame)))
	//		{
	//			OutputDebugString(_T("two"));
	//			CView* pView=NULL;
	//			CMainChildFrame* pChild = static_cast<CMainChildFrame*>(pParent);
	//			if(pChild){
	//			 pView=pChild->GetActiveView();
	//			if(pView)    
	//				{
	//					OutputDebugString(_T("!!!!!"));
	//					return pView->PreTranslateMessage(pMsg);
	//					
	//					
	//				}
	//			}
	//		 }
	//}
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnCheckView() 
{
	// TODO: Add your command handler code here
	//CMainChildFrame* pChild = static_cast<CMainChildFrame*>(GetActiveFrame());
	//pChild->ReplaceView (RUNTIME_CLASS(CUserThreadsView));
		m_nCurView=CHECK;
			SwitchView (RUNTIME_CLASS(CUserThreadsView));

}

void CMainFrame::OnUpdateCheckView(CCmdUI* pCmdUI) 
	
{
	
		pCmdUI->SetRadio (m_nCurView==CHECK);
	//m_wndToolBar.SetToolBarBtnText (0,_T("Чек(F2)"),FALSE,TRUE);

}
void CMainFrame::OnZReport() 
{
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	CDlgLogin dlgLogin(pMainDoc);//кто пользователь?
	int ret =dlgLogin.DoModal();
	if (ret==IDCANCEL)
	{
		return;
	}
	m_nCurView=ZREPORT;
	SwitchView (RUNTIME_CLASS(CZReportView));
}
	

void CMainFrame::OnUpdateZReport(CCmdUI* pCmdUI) 
	
{
	//// TODO: Add your command update UI handler code here
//#ifdef OutputDebugString_ENABLED
//	OutputDebugString(_T("CMainFrame::OnUpdateZReport\n"));
//#endif
		pCmdUI->SetRadio (m_nCurView==ZREPORT);
	//m_wndToolBar.SetToolBarBtnText (1,_T("Z-Отчет(F10)"),TRUE,TRUE);
	//CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	//if(pMainDoc)
	//pCmdUI->Enable(TRUE ); 



}
void CMainFrame::OnRecicling() 
{
keybd_event(VK_DELETE, 0, 0 ,0);
keybd_event(VK_DELETE, 0, KEYEVENTF_KEYUP,0);

}

void CMainFrame::OnUpdateRecicling(CCmdUI* pCmdUI) 

{


	BOOL blEnable=FALSE;
	CCheckDoc* pCheckDoc=CUserThreadsApp::GetDocument<CCheckDoc>();
	if(pCheckDoc!=NULL)
	{
		std::size_t size=pCheckDoc->GetSalesLineItems().size();

		blEnable=(m_nCurView==CHECK)&&(size>0);
		
	}
	pCmdUI->Enable(blEnable);
}
void CMainFrame::OnSetup() 
{
	// TODO: Add your command handler code here
	CDlgManageKKM dlgKKM;
	CFontDlgPage dlgFonts;
	//dlg.DoModal ();
	//CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	//pMainDoc->m_blKKMOnLine =dlg.m_KKMOnLine ;
	CPointSettings dlg(_T("Настройка оборудования"),this,0);
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	dlg.AddPage(&dlgKKM);
	dlg.AddPage(&dlgFonts);
	dlg.DoModal();
}

void CMainFrame::OnUpdateSetup(CCmdUI* pCmdUI) 
	
{
	// TODO: Add your command update UI handler code here
	//m_wndToolBar.SetToolBarBtnText (4,_T("Настройка(F5)"),FALSE,TRUE);	
}
void CMainFrame::OnReturn() 
{
	// TODO: Add your command handler code here
	/*
	Получаем список шаблонов документов
	  находим наш основной шаблон(UserThreads)
		проверяем есть ли в списке документов ReturnDoc
		если есть получаем на него ссылку
		 добавляем вид
		 и показываем его в фрейме
		 если нет создаем и показываем фрейм*/
	//CMainChildFrame* pChild = static_cast<CMainChildFrame*>(GetActiveFrame());
	//pChild->ReplaceView (RUNTIME_CLASS(CReturnView));
		m_nCurView=RETURN;
	SwitchView (RUNTIME_CLASS(CReturnView));
}

void CMainFrame::OnUpdateReturn(CCmdUI* pCmdUI) 
	
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetRadio (m_nCurView==RETURN);
	/*m_wndToolBar.SetToolBarBtnText (3,_T("Возврат(F4)"),FALSE,TRUE);*/	
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CView* pView = GetActiveView();
     if (pView != NULL && pView->OnCmdMsg( nID,  nCode,  pExtra,  pHandlerInfo))
     return TRUE;

	return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

LRESULT CMainFrame::OnDisconnectBase (WPARAM,LPARAM)
{
	

	return 0L;
}
LRESULT CMainFrame::OnConnectBase (WPARAM,LPARAM)
{

		return 0L;
}

BOOL CMainFrame::SwitchView(CRuntimeClass* pNewViewClass)
{
	CMainChildFrame* pChild = static_cast<CMainChildFrame*>(GetActiveFrame());
	CView* pOldActiveView = pChild->GetActiveView();
	DWORD dwStyle=pOldActiveView->GetStyle ();
	// If we're already displaying this kind of view, no need to go further.
	if (pOldActiveView->IsKindOf(pNewViewClass))
		return TRUE;
	
	// Set the child window ID of the active vi ew to AFX_IDW_PANE_FIRST.
	// This is necessary so that CFrameWnd::RecalcLayout will allocate
	// this "first pane" to that portion of the frame window's client
	// area not allocated to control bars.  Set the child ID of
	// the previously active view to some other ID.
	
	::SetWindowLong(pOldActiveView->m_hWnd, GWL_ID, 0);
	
	// create the new document depending from associated view
	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;
	if (!strcmp(pNewViewClass->m_lpszClassName,"CReturnView"))
	{
		CRuntimeClass* pNewDocClass;
		pNewDocClass = RUNTIME_CLASS(CReturnDoc);
		CReturnDoc* pDoc=static_cast <CReturnDoc*>(pNewDocClass->CreateObject ());
		pDoc->OnNewDocument ();
		context.m_pCurrentDoc = pDoc;
    }
	else if(!strcmp(pNewViewClass->m_lpszClassName,"CUserThreadsView"))
	{
		CRuntimeClass* pNewDocClass;
		pNewDocClass = RUNTIME_CLASS(CCheckDoc);
		CCheckDoc* pDoc=static_cast <CCheckDoc*>(pNewDocClass->CreateObject ());
		pDoc->OnNewDocument ();
		context.m_pCurrentDoc = pDoc;
		//context.m_pCurrentDoc = this;
	}
	else if(!strcmp(pNewViewClass->m_lpszClassName,"CZReportView"))
	{
		CRuntimeClass* pNewDocClass;
		pNewDocClass = RUNTIME_CLASS(CZReportDoc);
		CZReportDoc* pDoc=static_cast <CZReportDoc*>(pNewDocClass->CreateObject ());
		pDoc->OnNewDocument ();
		context.m_pCurrentDoc = pDoc;
		//context.m_pCurrentDoc = this;
	}
	//create new viewrr
	CRect rc(0,0,0,0);
	CView* pNewView = (CView*)pNewViewClass->CreateObject();
	ASSERT(pNewView);
	if (!pNewView->Create(NULL, NULL, dwStyle, rc, pChild, AFX_IDW_PANE_FIRST, &context))
		return FALSE;
	
	if (pNewView != NULL)
	{
		// the new view is there, but invisible and not active...
		pNewView->ShowWindow(SW_SHOW);
		pNewView->OnInitialUpdate();
		
		pChild->SetActiveView(pNewView);
		pChild->RecalcLayout();
		
		// destroy the old view...
		pOldActiveView->DestroyWindow();
		return TRUE;
	}
	
	return FALSE;
}
void	CMainFrame::OnUpdatePaneComPort(CCmdUI* pCmdUI)
{
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	pCmdUI->Enable(pDoc!=NULL);
	if(pDoc)
	
		pCmdUI->SetText (pDoc->GetComPort ());
	
}



void CMainFrame::OnActivateApp(BOOL bActive, DWORD dwTID) 
{
	//CMDIFrameWnd::OnActivateApp(bActive, dwTID);
	//CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//HANDLE hMutex=pApp->g_hEventFocus ;

	//
	//

	//if(bActive)
	//{
	//	if(::WaitForSingleObject (hMutex,0)!=WAIT_OBJECT_0)
	//	{
	//		if(pApp->m_pInfoConsoleThread!=NULL)
	//		{
	//	
	//			
	//		//	pApp->m_pInfoConsoleThread->DisconnectBase();
	//		while(::WaitForSingleObject (pApp->g_hEventBaseOccupied ,100)==WAIT_OBJECT_0);
	//			
	//			CString strConn/*=_T("File Name=C:\\VisualCStudy\\UserThreads\\data\\connstring.udl")*/;
	//			strConn.LoadString(IDS_CONNSTRING);
	//			
	//			
	//			//pApp->ConnectBase(strConn);
	//				
	//			CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	//			pMainDoc->SetEnvironmentPoint();
	//			if(pMainDoc->m_blIsDirty)
	//			{
	//				CRuntimeClass* pNewDocClass;
	//			pNewDocClass = RUNTIME_CLASS(CCashDoc);
	//			CCashDoc* pCashDoc=static_cast <CCashDoc*>(pNewDocClass->CreateObject ());
	//			pCashDoc->OnNewDocument ();
	//			//pCashDoc->UpdateCashMove();
	//			}
	//		}
	//		
	//		::SetEvent(hMutex);
	//	}
	//}
	//else
	//{
	///*	CMDIChildWnd* pChild = (CMDIChildWnd*)MDIGetActive();
	//			if(::IsWindow (pChild->GetSafeHwnd ()))
	//			{	
	//			// Get the active view attached to the active MDI child window.
	//			CView* pView = pChild->GetActiveView();
	//			if(pView->IsKindOf (RUNTIME_CLASS(CUserThreadsView)))
	//				((CUserThreadsView*)pView)->CloseCommPort( );
	//		//	::WaitForSingleObject (pApp->g_hCommPortOpen ,INFINITE);
	//			}
	//			*/
	//	SendMessage(WM_NCPAINT);
	//}
	
}
void	CMainFrame::OnUpdatePointActual(CCmdUI* pCmdUI)
{
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	pCmdUI->Enable(pDoc!=NULL);
	if(pDoc)
	{
		CString strPA;
		strPA.Format (_T("ТА:%.2d/%.2d/%d  %.2d:%.2d:%.2d"),
			pDoc->m_tmPointActual.GetDay(),
			pDoc->m_tmPointActual.GetMonth(),
			pDoc->m_tmPointActual.GetYear(),
			pDoc->m_tmPointActual.GetHour(),
			pDoc->m_tmPointActual.GetMinute(),
			pDoc->m_tmPointActual.GetSecond());




		pCmdUI->SetText (strPA);
	}
	
}

void	CMainFrame::OnUpdatePaneKKM(CCmdUI* pCmdUI)
{
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	if(pDoc)
	{
		CString msg1=_T("KKM OnLine");
		CString msg2=_T("KKM OffLine");
		if(pDoc->m_blKKMOnLine )
			
			pCmdUI->SetText (_T("KKM OnLine"));
		else
			pCmdUI->SetText (_T("KKM OffLine"));
	}
}

//DEL void CMainFrame::OnNcPaint() 
//DEL {
//DEL 	// TODO: Add your message handler code here
//DEL 	CFrameWnd::OnNcPaint();
//DEL 	HDC  hdc = ::GetWindowDC(m_hWnd);
//DEL 	CDC dc;
//DEL 	dc.Attach (hdc);
//DEL 
//DEL 	HPEN hPen = ::CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
//DEL 	HPEN OldPen = (HPEN)::SelectObject((HDC)dc, (HPEN)hPen);
//DEL 	HBRUSH OldBrush = (HBRUSH)::SelectObject(dc, GetStockObject(NULL_BRUSH));
//DEL 	::Rectangle(dc, 2,2, 25, 15);
//DEL 	::SelectObject(dc, OldBrush);
//DEL 	::SelectObject(dc, OldPen);
//DEL 	::DeleteObject(hPen);
//DEL /**/
//DEL 	//Default();
//DEL 	// Do not call CMDIFrameWnd::OnNcPaint() for painting messages
//DEL }








LRESULT CMainFrame::OnChangeMultiplicator(WPARAM wParam, LPARAM lParam)
{
	// Turn WS_VISIBLE style off before calling Windows to
	// set the text, then turn it back on again after.
	//

	//CMainDocument *pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
 ////pMainDoc->pRstCatalog ->Requery (adCmdUnknown);
	//m_nQtyMultiplicator=(int)lParam;


 //CString str;
 //str.Format (_T("x%d"),m_nQtyMultiplicator);
 //m_wndMultButton.SetWindowText (str);
	m_wndMultToolBar.RedrawWindow();
							 // ..and paint it
	return 0;
}



BOOL CMainFrame::CreateMainToolBar()
{
	DWORD dwCtrlStyle=TBSTYLE_FLAT|TBSTYLE_TOOLTIPS|CBRS_SIZE_DYNAMIC;
	DWORD dwStyle=AFX_DEFAULT_TOOLBAR_STYLE;
	CMFCToolBarInfo tbi;
	const CRect r1(1,1,1,1);
	if(!m_wndToolBar.CreateEx(this,dwCtrlStyle,dwStyle,r1,IDR_MAINFRAME)||
		!m_wndToolBar.LoadToolBarEx(IDR_MAINFRAME,tbi,TRUE))
	{
		return FALSE;
	}
CSize szImg=m_wndToolBar.GetImageSize();
CSize szButton(szImg.cx+6,szImg.cy+6);
m_wndToolBar.SetMenuSizes(szButton,szImg);
dwStyle=CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC;
m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle()|dwStyle);
m_wndToolBar.InsertSeparator(4);
m_wndToolBar.InsertSeparator(8);



/*CImageList il;
VERIFY(il.Create (szImage.cx ,szImage.cy ,ILC_COLOR8|ILC_MASK,4,szMargin.cx ));
il.SetBkColor (TRANSPARENT);

HICON hIcon[NBUTTONS];
int n;
hIcon[0]=AfxGetApp()->LoadIcon (ID_INSERT);
hIcon[1]=AfxGetApp()->LoadIcon (IDI_ARCHIVE);
hIcon[2]=AfxGetApp()->LoadIcon (ID_DELETE);
hIcon[3]=AfxGetApp()->LoadIcon (ID_RETURN);
hIcon[4]=AfxGetApp()->LoadIcon (ID_TOOL);
hIcon[5]=AfxGetApp()->LoadIcon (IDR_INFOFRAME);
hIcon[6]=AfxGetApp()->LoadIcon (IDI_QUEST);
for(n=0;n<NBUTTONS-1;n++)
il.Add (hIcon[n]);
*/
	//m_wndToolBar.SetSizes (szImage+szMargin,szImage);

	//m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)il.Detach());
	//CMFCToolBarImages img;
	
	//m_wndToolBar.GetImages()->Load(IDB_TOOLBAR1_32);
	//m_wndToolBar.GetImages()->CreateFromImageList(il);
	//m_wndToolBar.EnableLargeIcons(TRUE);
	//m_wndToolBar.EnableTextLabels(TRUE);
	//m_wndToolBar.SetLargeIcons(TRUE);

	//m_wndToolBar.SetButtons(NULL, NBUTTONS);
	//m_wndToolBar.RemoveAllButtons();
	//for (int i=0; i<NBUTTONS; i++) {
	//	//m_wndToolBar.SetButtonInfo(i,
	//	//	Buttons[i].id,						 // command id
	//	//	Buttons[i].style,					 // buttons style
	//	//	Buttons[i].iImage);	                 // index of image in bitmap
	//	//	m_wndToolBar.SetButtonText (i,_T(" "));//set text later in OnUpdateViewInfoconsole
	//		m_wndToolBar.InsertButton(CMFCToolBarButton(Buttons[i].id,Buttons[i].iImage,_T("")));

	//}
	//m_wndToolBar.AdjustLayout();
	//m_wndToolBar.OnUpdateCmdUI(this,TRUE);
	//получим прямоугольник последней кнопки
//	CRect rcButton;
//	m_wndToolBar.GetItemRect (NBUTTONS-1,&rcButton);
//	//ScreenToClient(&rcButton);
//	rcButton.DeflateRect (1,0);
//	
//	m_wndMultButton.Create (_T("x1"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_OWNERDRAW, rcButton, &m_wndToolBar,
//        ID_MULTBUT_HOLDER);
//	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
//	if(pMainDoc)
//	{
//	if(!(HFONT)m_NCFont)
//	m_NCFont.CreatePointFont (pMainDoc->GetFontSize ()*20,pMainDoc->GetFontName ());
//	
//	}
//	else
//		m_NCFont.CreatePointFont (240,_T("Arial"));
//m_wndMultButton.SendMessage(WM_SETFONT,
//        (WPARAM)HFONT(m_NCFont), TRUE);
	return TRUE;
}

void	CMainFrame::OnUpdatePaneKKMError(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
	pCmdUI->SetText (m_strErrorMsg);	
}


afx_msg LRESULT CMainFrame::OnResetToolbar(WPARAM wParam, LPARAM lParam)
{
	
	UINT uiToolBarId = (UINT) wParam;

	switch (uiToolBarId)
	{
	case IDR_MULTTOOLBAR:
		{
			ASSERT(m_wndToolBar.GetSafeHwnd() != NULL);

			// Replace dropdown resources button:
			CMenu menu;
			menu.LoadMenuA(IDR_POPUP);
			m_wndMultToolBar.ReplaceButton(ID_MULTBUT_HOLDER,MultButtonEx(ID_MULTBUT_HOLDER,_T(" x1"),menu.GetSafeHmenu()));
			/*	m_wndToolBar.InsertSeparator(8);
			m_wndToolBar.ReplaceButton(ID_FONT_BOLD,CMFCToolBarComboBoxButton());*/
			

		
		}
		break;

	
	
	}

	
	return 0;
}


//void CMainFrame::OnMultbutHolder()
//{

//	// TODO: Add your command handler code here
//}
//
//
//void CMainFrame::OnUpdateMultbutHolder(CCmdUI *pCmdUI)
//{
//	// TODO: Add your command update UI handler code here	

//}
