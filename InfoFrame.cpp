// InfoFrame.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "InfoFrame.h"
//#include "UserThreadsDoc.h"
#include "InfoConsole.h"
#include "NaklForm.h"
#include "MDIChild.h"
#include "MainFrm.h"
#include "DBDoc.h"
#include "DlgSetPeriod.h"
#include "FileDialog2K.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "ComPortDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CInfoFrame

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_ROWS,
	ID_INDICATOR_LANG,

};

IMPLEMENT_DYNCREATE(CInfoFrame, CMDIFrameWnd)

CInfoFrame::CInfoFrame()
{

}

CInfoFrame::~CInfoFrame()
{
}


BEGIN_MESSAGE_MAP(CInfoFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CInfoFrame)
	ON_COMMAND(ID_FILE_DICTIONARY, OnFileDictionary)
	ON_UPDATE_COMMAND_UI(ID_FILE_DICTIONARY, OnUpdateFileDictionary)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_NAKLAD, OnFileNaklad)
	ON_UPDATE_COMMAND_UI(ID_FILE_NAKLAD, OnUpdateFileNaklad)
	ON_WM_CLOSE()
	ON_COMMAND(ID_SET_PERIOD, OnSetPeriod)
	ON_UPDATE_COMMAND_UI(ID_SET_PERIOD, OnUpdateSetPeriod)
	ON_COMMAND(IDC_ARCHIVE, OnArchive)
	ON_UPDATE_COMMAND_UI(IDC_ARCHIVE, OnUpdateArchive)
	ON_COMMAND(ID_DEARCHIVE,OnDearchive)
	ON_UPDATE_COMMAND_UI(ID_DEARCHIVE, OnUpdateDearchive)
	ON_COMMAND(ID_CUSTOMIZE, OnCustomize)
	ON_UPDATE_COMMAND_UI(ID_CUSTOMIZE, OnUpdateCustomize)
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_FONT_CHANGED,OnFontChanged)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ROWS, OnUpdateRows)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_LANG, OnUpdateLanguage)
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnToolbarDropDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoFrame message hted(

void CInfoFrame::OnFileDictionary() 
{
	ASSERT(AfxGetApp()!=AfxGetThread());
//	CInfoConsole* pInfoConsoleThread=static_cast<CInfoConsole*>(AfxGetThread());
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	m_wndFontTB.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP);
	//DockControlBarLeftOf(&m_wndToolBar,&m_wndFontTB);
//	DockControlBarLeftOf(&m_wndFontTB,&m_wndToolBar);
	//LoadBarState(AfxGetApp()->m_pszProfileName);
	ShowForm("DictionaryForm");
//m_wndToolBar.ShowWindow (SW_HIDE);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
/**/
//	::SendMessage(hwndForm,WM_INITIALUPDATE,0,0);

}

void CInfoFrame::OnUpdateFileDictionary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
POSITION pos = m_lsForms.GetHeadPosition();
while( pos != NULL )
	{
		CString szCmp = static_cast<CString>(m_lsForms.GetNext( pos ));
		
		if (szCmp == _T("DictionaryForm")) //...Is there a view anyway?
		{
			//if(pActiveView->IsKindOf (CView))
				pCmdUI->Enable (FALSE);
		}
	}	
}

BOOL CInfoFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CMDIFrameWnd::OnCreateClient(lpcs,pContext);

	return TRUE;
}



void CInfoFrame::ShowForm(CString szName)
{
//	char *lpszPathName=NULL;
	BOOL bMakeVisible=TRUE;
	CWinApp* pApp=AfxGetApp();
	POSITION curTmplPos=pApp->GetFirstDocTemplatePosition ();
	
	while(curTmplPos)
	{
		CDocTemplate* curTemplate=pApp->GetNextDocTemplate (curTmplPos);
		CString str;
		curTemplate->GetDocString (str,CDocTemplate::docName);
		
		if(str==szName)
			
		{
			
			CDocument* pDocument=NULL;
			
			POSITION curDocPos=curTemplate->GetFirstDocPosition ();
			if(curDocPos!=NULL)
				
				pDocument = curTemplate->GetNextDoc (curDocPos);
			else
				pDocument=curTemplate->CreateNewDocument ();
			if (pDocument == NULL)
			{
				TRACE0("CDocTemplate::CreateNewDocument returned NULL.\n");
				AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
				return ;
			}
			ASSERT_VALID(pDocument);
			
			m_wndMDIClient.SetViewManager (this);
			
			BOOL bAutoDelete = pDocument->m_bAutoDelete;
			pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
			
			CMDIChild* pFrame = (CMDIChild*)curTemplate->CreateNewFrame(pDocument/*NULL*/, this);
			pDocument->m_bAutoDelete = bAutoDelete;
			//pFrame->SubclassWindow(pFrame->GetSafeHwnd());
			
			
			if (pFrame == NULL)
			{
				AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
				delete pDocument;       // explicit delete on error
				return ;
			}
			ASSERT_VALID(pFrame);
			
			m_lsForms.AddTail (szName);
			//	if (lpszPathName == NULL)
			//	{
			// create a new document - with default document name
			//		SetDefaultTitle(pDocument);
			
			// avoid creating temporary compound file when starting up invisible
			//	if (!bMakeVisible)
			//	pDocument->m_bEmbedded = TRUE;
			
			
			
			// it worked, now bump untitled count
			//	m_nUntitledCount++;
			//}
			//else
			//	{
			// open an existing document
			//	CWaitCursor wait;
			//	if (!pDocument->OnOpenDocument(lpszPathName))
			//{
			// user has be alerted to what failed in OnOpenDocument
			//	TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
			//pFrame->DestroyWindow();
			//return ;
			//}
			//	pDocument->SetPathName(lpszPathName);
			//}
			
			//pFrame->SetTitle (GetFormCaption(szName));
			pDocument->SetTitle (GetFormCaption(szName));
			curTemplate->InitialUpdateFrame(pFrame, pDocument/*NULL*/, bMakeVisible);
			
		}
	}
	// Must temporarily remove the doc so MFC won't have a conniption
	
}

int CInfoFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	TRACE0("CInfoFrame::OnCreate\n");
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | /*CBRS_SIZE_DYNAMIC|*/ CBRS_FLOAT_MULTI) ||
		!m_wndToolBar.LoadToolBar(IDR_INFO_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//Set Archive Button on ToolBar DropDown style
		m_wndToolBar.SendMessage(TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_DRAWDDARROWS);
		m_wndToolBar.SetButtonStyle (3,	TBSTYLE_BUTTON | TBSTYLE_DROPDOWN);

	VERIFY(m_wndMDIClient.SubclassMDIClient(this));
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);



	if (!m_wndFontTB.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | /*WS_VISIBLE |*/ CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_FLOAT_MULTI ) )
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndFontTB.LoadToolBar (IDR_FONTTBAR);
/*	if(!m_wndFontTB.SetupToolBar ())
	DockControlBar(&m_wndMainBar,AFX_IDW_DOCKBAR_TOP);
	DockControlBarLeftOf(&m_wndEditBar,&m_wndMainBar);
	}*/
	
	//m_wndFontTB.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP);
	//DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_BOTTOM);
	//DockControlBar(&m_wndFontTB,AFX_IDW_DOCKBAR_TOP);
	//DockControlBarLeftOf(&m_wndFontTB,&m_wndToolBar);
	
	/*if(!m_wndFontTB.SetupToolBar ())
	{
		TRACE0("Failed to create Font Toolbar\n");
		return -1;
	}
	*/
	//m_wndFontTB.EnableDocking(CBRS_ALIGN_ANY);

	//DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP);
/*/Docking FontToolBar left of main ToolBar
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	m_wndToolBar.GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=m_wndToolBar.GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(&m_wndToolBar,n,&rect);*/
	//DockControlBar(&m_wndFontTB,AFX_IDW_DOCKBAR_TOP);

	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	//m_wndStatusBar.SetPaneInfo(4,ID_INDICATOR_ROWS,m_wndStatusBar.GetStyle(),100);
	UINT nID, nStyle;
	int cxWidth;
	
	m_wndStatusBar.GetPaneInfo(4, nID, nStyle, cxWidth);
	m_wndStatusBar.SetPaneInfo(4, nID, nStyle ,
		cxWidth+100);//set enough width for information about rows count
//LoadBarState(AfxGetApp()->m_pszProfileName);
	InitHashTable();
	return 0;
}

void CInfoFrame::OnFileNaklad() 
{
	// TODO: Add your command handler code here
ShowForm("NaklForm");	
}

void CInfoFrame::OnUpdateFileNaklad(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
POSITION pos = m_lsForms.GetHeadPosition();
while( pos != NULL )
	{
		CString szCmp = static_cast<CString>(m_lsForms.GetNext( pos ));
		
		if (szCmp == _T("NaklForm")) //...Is there a view anyway?
		{
			//if(pActiveView->IsKindOf (CView))
				pCmdUI->Enable (FALSE);
		}
	}
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


void CInfoFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CUserThreadsApp* pApp = static_cast<CUserThreadsApp*>(AfxGetApp());
	ASSERT(pApp);
	if(pApp->hwndInfoWnd)
		pApp->hwndInfoWnd=NULL;
	//m_wndToolBar.SetSizes (CSize(0,0),CSize(0,0));
	m_wndMDIClient.SaveMainFrameState ();
	
	while (!m_lsForms.IsEmpty())
		m_lsForms.RemoveHead();
	//Send Message WM_CLOSE For All MDIChild Windows
	::EnumChildWindows(m_wndMDIClient.GetSafeHwnd (), SendMDIChildToClose, 0);
	CMDIFrameWnd::OnClose();
}

void CInfoFrame::InitHashTable()
{
	m_mpFormCaption.InitHashTable ((UINT)10);
	m_mpFormCaption.SetAt (_T("DictionaryForm"),_T("Товары и остатки"));
	m_mpFormCaption.SetAt (_T("NaklForm"),_T("Общий журнал документов"));
}

CString CInfoFrame::GetFormCaption(CString& strKey)
{
	CString strRet;
	m_mpFormCaption.Lookup (strKey,strRet);
	return strRet;
}

BOOL CInfoFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	//cs.style &= ~FWS_ADDTOTITLE;
	return CMDIFrameWnd::PreCreateWindow(cs);
}


void CInfoFrame::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CUserThreadsApp* pApp = static_cast<CUserThreadsApp*>(AfxGetApp());
	ASSERT(pApp);
	
	pApp->GetMainWnd ()->PostMessage (WM_KILL_THREAD);
	CMDIFrameWnd::PostNcDestroy();
}

LRESULT CInfoFrame::OnFontChanged (WPARAM,LPARAM)
{

	// Get the active MDI child window.

	// Get the active MDI child window.
	CMDIChildWnd* pChild = static_cast<CMDIChildWnd*>(GetActiveFrame());
	// Get the active view attached to the active MDI child window.
	CView* pActiveView = reinterpret_cast<CView*>(pChild->GetActiveView());

	ASSERT(pActiveView!=NULL);
	CDBDoc* pDoc=static_cast<CDBDoc*>(pActiveView->GetDocument ());
	ASSERT(pDoc!=NULL);
	TCHAR szBuff[MAX_PATH];
	m_wndFontTB.GetFontName (szBuff);
	int nFontSize=m_wndFontTB.GetFontSize ();
	pDoc->SetPointFont(szBuff,nFontSize);
	pDoc->UpdateAllViews (NULL);
	return 0L;
}




CDocument* CInfoFrame::GetActiveDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CMDIChildWnd* pChild = static_cast<CMDIChildWnd*>(GetActiveFrame());
	// Get the active view attached to the active MDI child window.
	
	CView* pActiveView = reinterpret_cast<CView*>(pChild->GetActiveView());
	CDocument* pDoc=NULL;
	if(pActiveView)
	 pDoc=pActiveView->GetDocument ();
	else
	 pDoc=CMDIFrameWnd::GetActiveDocument();
	
	return pDoc;
}

void CInfoFrame::OnSetPeriod() 
{
	// TODO: Add your command handler code here
	CDlgSetPeriod dlgSetPeriod;
	dlgSetPeriod.DoModal ();	
}

void CInfoFrame::OnUpdateSetPeriod(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable (MDIGetActive()!=NULL);
	
}
void CInfoFrame::OnUpdateRows(CCmdUI *pCmdUI)
{
    pCmdUI->Enable();
	CString strPage;
    strPage.Format( _T("Page %d"), 5 ); 

    pCmdUI->SetText( m_strStatusBarInfoGrid  );
}

void CInfoFrame::OnUpdateLanguage(CCmdUI *pCmdUI)
{
    pCmdUI->Enable();
	//CString strPage;
    
    pCmdUI->SetText( m_strStatusBarInfoLang );
}


void CInfoFrame::OnArchive() 
{
	Open1C(NULL);
}

void CInfoFrame::OnUpdateArchive(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void CInfoFrame::OnToolbarDropDown(NMHDR* pnmhdr, LRESULT *plr)
{
	// load and display popup menu
	CMenu menu;
	menu.LoadMenu(IDR_POPUP);
	CMenu* pPopup = menu.GetSubMenu(0);

	ASSERT(pPopup);

	CRect rc;
	NMTOOLBAR* pnmtb=reinterpret_cast<NMTOOLBAR*>(pnmhdr);
	m_wndToolBar.SendMessage(TB_GETRECT, pnmtb->iItem, (LPARAM)&rc);
	m_wndToolBar.ClientToScreen(&rc);
	//TRACE("\n\npnmtb->iItem=%d\n",pnmtb->iItem);
	switch(pnmtb->iItem)
	{ case IDC_ARCHIVE:

	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,
		rc.left, rc.bottom, this, &rc);
	break;
	}
}

void CInfoFrame::OnDearchive()
{
	
	CString szFilter = "Archive Files (*.rar;*.zip)|*.rar; *.rar|All Files (*.*)|*.*||";
	//( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL );
//	DWORD dwVersion = GetVersion();
// BOOL bIsW2K=FALSE;
// Get theK Windows version.

//DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
//DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));

// Get the build number.


 CFileDialog2K dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,NULL);  





	if(dlg.DoModal ()==IDOK)
	{
		PROCESS_INFORMATION piProcInfo; 
		STARTUPINFO siStartInfo={sizeof(siStartInfo)}; 
		
		// Set up members of the PROCESS_INFORMATION structure. 
		
		ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
		
		// Set up members of the STARTUPINFO structure. 
		
		ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
		siStartInfo.cb = sizeof(STARTUPINFO); 
		
		// Create the child process. 
		CString strCommandLine;
		CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		TCHAR szAppPath[MAX_PATH];
		pApp->GetExePath (szAppPath);
		int len=_tcslen(szAppPath);
		len-=2;
		TCHAR* ptr=szAppPath+len;
		while(*ptr)
		{
			
			if((int)*ptr==92) //symbol '\'
				break;
			*ptr='\0';
			ptr--;
		}
		
		ASSERT(AfxGetApp()!=AfxGetThread());
		//CUserThreadsApp* pApp=AfxGetApp();
		CInfoConsole* pInfoConsoleThread=static_cast<CInfoConsole*>(AfxGetThread());
		try
		{
			CComBSTR connString;
			TESTHR(pInfoConsoleThread->pConn ->get_ConnectionString (&connString));
			TESTHR(pInfoConsoleThread->pConn->Close ());
			while(pInfoConsoleThread->pConn->State ==adStateOpen)
			{

			::Sleep(500);
			}
			//::Sleep(1500);

	//::Sleep(1500);
			//TESTHR(pApp->pConn->Close ());
			CString strDataCatalog=szAppPath;
			strDataCatalog+="Data";
			strCommandLine.Format(_T("%c%s%c e -y -ilog %c%s%c %c%s%c"),34,_T("C:\\Program Files\\WinRAR\\rar.exe"),34,34,dlg.GetPathName (),34,34,strDataCatalog,34);
			BOOL fSuccess=::CreateProcess(NULL, 
				strCommandLine.GetBuffer (MAX_PATH),       // command line 
				NULL,          // process security attributes 
				NULL,          // primary thread security attributes 
				TRUE,          // handles are inherited 
				0,             // creation flags 
				NULL,          // use parent's environment 
				NULL,          // use parent's current directory 
				&siStartInfo,  // STARTUPINFO pointer 
				&piProcInfo);  // receives PROCESS_INFORMATION 
			strCommandLine.ReleaseBuffer ();
			DWORD dwExitCode;
			if(fSuccess){
				::CloseHandle(piProcInfo.hThread );
//********************************************************************************
//********************************************************************************
/***************/::WaitForSingleObject (piProcInfo.hProcess ,INFINITE);/********/
                 //caution WAIT ENDING RAR.EXE PROCESS
//Ах если бы я знал!!!! неделя бессонных ночей
//********************************************************************************
				
				::GetExitCodeProcess(piProcInfo.hProcess ,&dwExitCode);
				::CloseHandle (piProcInfo.hProcess );
			}
			//::SendMessage(::FindWindow("_CheckWindow_",NULL),WM_CONNECTBASE,0,0);

			//::Sleep(1500);
			TESTHR(pInfoConsoleThread->pConn->Open ((_bstr_t)connString,"","",adConnectUnspecified));
		CDBDoc* pDoc=(CDBDoc*)GetActiveDocument ();
		if(!pDoc->UpdateCashMove ())
			AfxMessageBox(_T("При разархивировании возникли проблемы!!!\nПроверьте правильность данных!!!"));
			::SysFreeString (connString);
		}
		
		catch (_com_error &e)
		{
			// Pass a connection pointer accessed from the Recordset.
			_variant_t vtConnect = (IDispatch*)pInfoConsoleThread->pConn;
			
			// GetActiveConnection returns connect string if connection
			// is not open, else returns Connection object.
			switch(vtConnect.vt)
			{
			case VT_BSTR:
				PrintComError(e);
				break;
			case VT_DISPATCH:
				PrintProviderError(vtConnect);
				break;
			default:
				TRACE0("Errors occured.");
				break;
			}
		}
		
	}
	
}
void CInfoFrame::OnUpdateDearchive(CCmdUI* pCmdUI)
{
	
}

void CInfoFrame::OnCustomize() 
{
	// TODO: Add your command handler code here
CComPortDlg dlg;
dlg.DoModal ();	
}

void CInfoFrame::OnUpdateCustomize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CDocument* pDoc=GetActiveDocument ();
pCmdUI->Enable (pDoc!=NULL);
}
void CInfoFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;
	TRACE0("CInfoFrame::DockControlBarLeftOf\n");
	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
	//RecalcLayout();
}





void CInfoFrame::OnActivateApp(BOOL bActive, DWORD dwThreadId) 
{
	CMDIFrameWnd::OnActivateApp(bActive, dwThreadId);
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	HANDLE hMutex=pApp->g_hEventFocus ;
	
	if(bActive)
	{
		if(::WaitForSingleObject (hMutex,0)==WAIT_OBJECT_0)
		{
			::SendMessage(::FindWindow(_T("_CheckWindow_"),NULL),WM_DISCONNECTBASE,0,0);
			while(::WaitForSingleObject (pApp->g_hEventBaseOccupied ,100)==WAIT_OBJECT_0);
			ASSERT(AfxGetApp()!=AfxGetThread());
			CString strConn/*=_T("File Name=C:\\VisualCStudy\\UserThreads\\data\\connstring.udl")*/;
			strConn.LoadString(IDS_CONNSTRING);
			CInfoConsole* pInfoConsoleThread=static_cast<CInfoConsole*>(AfxGetThread());
			
			pInfoConsoleThread->ConnectBase(strConn);
			::ResetEvent (hMutex);
		}
		
	}
	
}



BOOL CInfoFrame::Open1C(BSTR param)
{
	CWaitCursor wait;
	Help1C.Open1CEx("C:\\TS\\DistrDB","Администратор","vjkjltxyj");
	HICON hIcon=(HICON)::LoadImage(  AfxGetApp()->m_hInstance ,
               MAKEINTRESOURCE(IDI_1C),
               IMAGE_ICON,
               16,
               16,
               0); 
	m_wndStatusBar.GetStatusBarCtrl().SetIcon (0,hIcon);
	return TRUE;
}
