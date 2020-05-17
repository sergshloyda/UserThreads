// UserThreads.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "UserThreads.h"

#include "MainFrm.h"
#include "MainChildFrame.h"
#include "ChildFrm.h"
//#include "UserThreadsDoc.h"
#include "UserThreadsView.h"
#include "InfoConsole.h"
#include "NaklForm.h"
#include "EmptyView.h"
#include "MainDocument.h"
#include "FindView.h"
#include <initguid.h>
#include "UserThreads_i.c"
#include "BarCodeReader.h"
#include "DlgLogin.h"
#include "ReturnDoc.h"
#include "ReturnView.h"
#include "CheckDoc.h"
#include "CashDoc.h"
#include "Salarydoc.h"
#include "Repository.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "LimitSingleInstance.H"
#include <Objbase.h>
// The one and only CLimitSingleInstance object
CLimitSingleInstance g_SingleInstanceObj(TEXT("{56C48194-3AE5-481c-A70B-9827E4680A00}"));
HANDLE g_hEventCloseComm;
/////////////////////////////////////////////////////////////////////////////
// CUserThreadsApp

BEGIN_MESSAGE_MAP(CUserThreadsApp, CWinApp)
	//{{AFX_MSG_MAP(CUserThreadsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_REFRESH_CATALOG, OnRefreshCatalog)
	
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)

END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CUserThreadsApp, CWinApp)
 //DISP_FUNCTION_ID(CMainDocument,"AfterTransactDocument",0x1,OnAfterTransactDocument,VT_I4,VTS_BSTR)
END_DISPATCH_MAP( )
BEGIN_INTERFACE_MAP(CUserThreadsApp, CWinApp)
//INTERFACE_PART(CUserThreadsApp, DIID__IDir1CServEvents, Dispatch)
END_INTERFACE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUserThreadsApp construction

CUserThreadsApp::CUserThreadsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
		m_pInfoConsoleThread=NULL;
		pConn=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUserThreadsApp object

CUserThreadsApp theApp; 


/////////////////////////////////////////////////////////////////////////////
// CUserThreadsApp initialization

BOOL CUserThreadsApp::InitInstance()

{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
//*******************************************************
if (g_SingleInstanceObj.IsAnotherInstanceRunning())
       return FALSE; 
	
	// Get current flag
		int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
	
	// Turn on leak-checking bit.
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF|_CRTDBG_ALLOC_MEM_DF|_CRTDBG_DELAY_FREE_MEM_DF|_CRTDBG_CHECK_ALWAYS_DF;
	
	// Turn off CRT block checking bit.
	tmpFlag &= ~_CRTDBG_CHECK_CRT_DF;
	
	// Set flag to the new value.
	_CrtSetDbgFlag( tmpFlag );
//********************************************************
::CoInitialize (NULL);


	HRESULT hr = CoInitializeSecurity(
          NULL,                        //Points to security descriptor
            -1,                          //Count of entries in asAuthSvc
            NULL,                        //Array of names to register
            NULL,                        //Reserved for future use
            RPC_C_AUTHN_LEVEL_NONE,      //The default authentication
                                         //level for proxies
            RPC_C_IMP_LEVEL_IMPERSONATE, //The default impersonation
                                         //level for proxies
            NULL,                        //Reserved; must be set to NULL
            EOAC_NONE,                   //Additional client or
                                         //server-side capabilities
            NULL                         //Reserved for future use
            );

	/*******************************************
	//***********************************************/

	AfxEnableControlContainer();
//_CrtSetBreakAlloc(11674);
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
//			oldMemState.Checkpoint();

#ifdef _AFXDLL
	//Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	//CSplash *pSplash=new CSplash(IDB_SPLASH,50000,0,&pSplash);

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("RUSLAN"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	////////////////////////////////



	
		CMultiDocTemplate* pDocTemplate;
	pDocTemplate =new CMultiDocTemplate(
		IDR_MDIUSERTH,
		RUNTIME_CLASS(CCheckDoc),
		RUNTIME_CLASS(CMainChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CUserThreadsView));
	//pDocTemplate->m_bAutoDelete=TRUE;
		AddDocTemplate(pDocTemplate);
		/*
Здесь происходит утечка видимо из-за присвоения
	m_pMyDocTemplate=pDocTemplate;
  */
//	m_pMyDocTemplate=pDocTemplate;
	




// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	
	CString strConn/*=_T("File Name=C:\\VisualCStudy\\UserThreads\\data\\connstring.udl")*/;
	strConn.LoadString(IDS_CONNSTRING);
	

	if (!ConnectBase (strConn))
		return FALSE;

	

		g_hEventFocus=::CreateEvent(NULL,TRUE,FALSE,_T("WindowFocus"));
		g_hEventBaseOccupied =::CreateEvent(NULL,TRUE,FALSE,_T("BaseOccupied"));
		g_hCommPortOpen=::CreateEvent(NULL,TRUE,FALSE,NULL);
	/*CSplash **/
	// Parse command line for standard shell commands, DDE, file open

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
		//if(cmdInfo.m_nShellCommand ==CCommandLineInfo::FileNew)
	//cmdInfo.m_nShellCommand =CCommandLineInfo::FileNothing;
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	if(pSplash)
		pSplash->Kill();//все загружено 





	/***********************************/
	TRACE0("User Successfully registered\n");
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_MAXIMIZE);
	//pMainFrame->m_MDIClient.RestoreMainFrameState(m_nCmdShow);
	pMainFrame->UpdateWindow();

//	delete pDocTemplate;
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	virtual void OnOK()
	{
	
	}

	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CUserThreadsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CUserThreadsApp message handlers


void CUserThreadsApp::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	::CoUninitialize();

	CWinApp::OnFinalRelease();
}



void CUserThreadsApp::GetExePath(LPTSTR strPath)
{
	TCHAR strBuff[_MAX_PATH];
	_tcscpy(strBuff,m_pszHelpFilePath );
	int len=_tcslen(strBuff);
	len--;
	TCHAR* ptr=strBuff+len;
	while(*ptr)
	{
		
		if((int)*ptr==92) 
			break;
		*ptr='\0';
		ptr--;
	}
	_tcscpy(strPath,strBuff);
}

	

int CUserThreadsApp::ExitInstance()
{

	


	::ResetEvent (g_hEventBaseOccupied );
	
	::CloseHandle(g_hCommPortOpen);
	::CloseHandle(g_hEventBaseOccupied);
	::CloseHandle(g_hEventFocus);


	
	int ret=CWinApp::ExitInstance();

	
	return ret;

	
}


BOOL CUserThreadsApp::ConnectBase(CString &strConnString)
{
	try
    {
	
		
		TCHAR buffer[MAX_PATH];
		GetModuleFileName(AfxGetInstanceHandle (),buffer,MAX_PATH);
		CString strPath=buffer;
		strPath.MakeLower();
		CString str;
		int nFindIdx = 0;
		int nFirst = 0;
		CStringList strList;
		while(nFindIdx >= 0)
		{
			nFindIdx = strPath.Find('\\', nFindIdx + 1);
			if ((nFindIdx < 0) && (nFirst > 0))
				str = strPath.Mid(nFirst, strPath.GetLength() - nFirst);
			else
				str = strPath.Mid(nFirst, nFindIdx - nFirst);
			strList.AddTail (str);
			nFirst = nFindIdx + 1;
		}
		CString strHead=_T("File Name=");
		CString strTail=_T("\\data\\connstringSQL.udl");
		strList.RemoveTail();
		strList.RemoveTail ();
		CString strConn=strHead;
		POSITION pos;
		pos=strList.GetHeadPosition ();
		while(pos != NULL )
		{
			strConn+=strList.GetNext (pos);
			strConn+='\\';
		}
		CString strSQLConn=strConn;
		strSQLConn+=strTail;
	/*	
		DbContext dbCtxt(
			L"File Name=C:\\ModernC\\Repository\\Product.udl");
		
		
		pConn->Open ((_bstr_t)strSQLConn,"User1C","vjkjltxyj",adConnectUnspecified);
		pConn->CursorLocation = adUseClient;*/
		if(!CreateDbContext((strSQLConn.AllocSysString()),L"",L""))
			return FALSE;
		::SetEvent(	g_hEventBaseOccupied );
		AfxMessageBox(_T("CUserThreadsApp Connection success\n"),MB_ICONINFORMATION|MB_TOPMOST);
		
		EnableAutomation();
		
		//::CoInitializeSecurity(NULL, -1, NULL, NULL,RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY ,	NULL, EOAC_NONE, NULL);
		return TRUE;

	}
	catch(_com_error &e)
    {
		USES_CONVERSION;
		// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
        MessageBoxHelper::ShowError(e.Description ());
		return FALSE;
    }
return TRUE;	
}



void CUserThreadsApp::OnFileNew() 
{

	RegisterDocument<CMainDocument>();
	RegisterDocument<CCashDoc>();
	RegisterDocument<CSalaryDoc>();
	RegisterDocument<Repository>();
	// #Sample_GetDocument
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	pMainDoc->SetEnvironmentPoint();
	CDlgLogin dlgLogin(pMainDoc);//кто пользователь?
	int ret =dlgLogin.DoModal();
	if (ret==IDCANCEL)
	{
		if(::IsWindow (m_pMainWnd->m_hWnd ))
		m_pMainWnd->PostMessage(WM_CLOSE,0L,0L);
		return;
	}
	
	pSplash=new CSplash(IDB_SPLASH,8000,0,&pSplash);
	WaitForSingleObject (pSplash->g_hEvent  ,INFINITE);//подождем пока поток создаст окно
#ifndef _DEBUG
	//pMainDoc->RefreshRecordsetList ();
#endif
	pSplash->SetText1 (_T("Откроем таблицы"));
	
	
	//pMainDoc->LoadCategoryTree ();



	if (m_pDocManager != NULL)
		m_pDocManager->OnFileNew();
	odslog(L"Load AllDocs");

}



BOOL CUserThreadsApp::DisconnectBase()
{

	
	
	::ResetEvent (g_hEventBaseOccupied );
	return TRUE;
}



/*long CUserThreadsApp::NomenclatureChanged()
{
CMainFrame* pFrm=(CMainFrame*)AfxGetMainWnd();
CView* pCurView=pFrm->GetActiveView ();
pCurView->EnableWindow (FALSE);
 CMainDocument *pMainDoc=GetDocument<CMainDocument> ();

 pMainDoc->RefreshRecordsetList ();
 pCurView->EnableWindow (TRUE);
 return 0L;
}*/


void CUserThreadsApp::OnRefreshCatalog() 
{
//CWaitCursor cur;
//	try
//	{
//	
//		_CommandPtr pcmdRefreshCatalog = NULL;
//	
//		TESTHR(pcmdRefreshCatalog.CreateInstance(__uuidof(Command)));
//		pcmdRefreshCatalog->CommandText = "sp_refresh_catalog";
//		pcmdRefreshCatalog->CommandType = adCmdStoredProc;
//		
//	
//		
//	
//		
//		// Create Recordset by executing the command
//		pcmdRefreshCatalog->ActiveConnection = pConn ;
//		_variant_t recordsAffected = long(0);
//		pcmdRefreshCatalog->Execute(&recordsAffected, 0, adOptionUnspecified);
//		
//		
//	
//	}
//	catch(_com_error &ce)
//	{	// Notify the user of errors if any.
//		CString adoStr,msgStr,tempStr;
//		
//		
//		// Trace COM error information.
//		// 
//		adoStr=_T("");
//		TRACE0( "\nCom Exception Information\n-----------------------------------------------\n" );
//		TRACE1( "Description : %s\n",   (char*) ce.Description()  );
//		TRACE1( "Message     : %s\n",   (char*) ce.ErrorMessage() );
//		TRACE1( "HResult     : 0x%08x\n", ce.Error() );
//		// 
//		// Trace ADO exception information only if connection is not null.
//		// 
//		if ( NULL != pConn )
//		{
//			TRACE0( "\nADO Exception Information\n-----------------------------------------------\n" );
//			ErrorPtr err;
//			for ( long i=0; i<pConn->Errors->Count; i++ ) 
//			{
//				tempStr=_T("");
//				err = pConn->Errors->Item[i];
//				TRACE1( "Number      : 0x%08x\n", err->Number );
//				TRACE1( "Description : %s\n",	  (char*) err->Description );
//				TRACE1( "SQLState    : %s\n",     (char*) err->SQLState );
//				TRACE1( "Source      : %s\n\n",   (char*) err->Source );
//				tempStr.Format(_T("Ado Exception :\n===============\nDescription : %s\nSource : %s\n"),(char*) err->Description,(char*) err->Source);  
//				adoStr += tempStr;
//			} 
//		}
//		msgStr.Format(_T("Com Exception :\n===============\nDescription : %s\nMessage     : %s\n%s"),(char*) ce.Description(),(char*) ce.ErrorMessage(), (LPCTSTR) adoStr);  
//		MessageBox(::GetDesktopWindow(),msgStr,_T("Error Message"), MB_OK|MB_TOPMOST);
//	}
	
	
}

 bool CUserThreadsApp::CreateDbContext(std::wstring const& connString,std::wstring const& user,std::wstring const& passw){
	dbCtxt_=boost::shared_ptr<DbContext>(new DbContext(connString,user,passw));
	return(dbCtxt_!=NULL);
}





