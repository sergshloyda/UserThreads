// InfoConsole.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "InfoConsole.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "InfoFrame.h"
#include "DBDoc.h"
//#include "UserThreadsDoc.h"
#include "DialogView.h"
#include "NaklForm.h"
#include "MDIChild.h"
#include "DictGoodsFrame.h"
#include "ZReportWizard.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CZReportWizard *pWizard;
/////////////////////////////////////////////////////////////////////////////
// CInfoConsole
//inline void TESTHR(HRESULT x){if FAILED(x) _com_issue_error(x);};
void PrintProviderError(_ConnectionPtr pConn)
{
    // Print Provider Errors from Connection object.
    
    // pErr is a record object in the Connection's Error collection.
 

   CString adoStr,msgStr,tempStr;
		
		
		// Trace COM error information.
		// 
		adoStr=_T("");
	
		// 
		// Trace ADO exception information only if connection is not null.
		// 
		if ( NULL != pConn )
		{
			TRACE0( "\nADO Exception Information\n-----------------------------------------------\n" );
			ErrorPtr err;
			for ( long i=0; i<pConn->Errors->Count; i++ ) 
			{
				tempStr=_T("");
				err = pConn->Errors->Item[i];
				TRACE1( "Number      : 0x%08x\n", err->Number );
				TRACE1( "Description : %s\n",	  (char*) err->Description );
				TRACE1( "SQLState    : %s\n",     (char*) err->SQLState );
				TRACE1( "Source      : %s\n\n",   (char*) err->Source );
				tempStr.Format(_T("Ado Exception :\n===============\nDescription : %s\nSource : %s\n"),(char*) err->Description,(char*) err->Source);  
				adoStr += tempStr;
			} 
		}
		msgStr.Format(_T("%s"), (LPCTSTR) adoStr);  
		MessageBox(::GetDesktopWindow(),msgStr,_T("Error Message"), MB_OK|MB_TOPMOST);
}

//////////////////////////////////////
//      PrintComError Function      //
//////////////////////////////////////

void PrintComError(_com_error &e)
{
    _bstr_t bstrSource(e.Source());
    _bstr_t bstrDescription(e.Description());
    
    // Print Com errors.
    CString msg1("Error\n");
	CString msg2;
    msg2.Format (_T("\tCode = %08lx\n"), e.Error());
	CString msg3;
    msg3.Format(_T("\tCode meaning = %s\n"), e.ErrorMessage());
	CString msg4;
    msg4.Format(_T("\tSource = %s\n"), (LPCSTR) bstrSource);
	CString msg5;
    msg5.Format(_T("\tDescription = %s\n"), (LPCSTR) bstrDescription);
	AfxMessageBox(msg1+msg2+msg3+msg4+msg5);
	CString msg6;
	msg6.Format(_T("HRESULT=%x"),e.Error ());
		AfxMessageBox(msg1+msg2+msg3+msg4+msg5+msg6,MB_ICONSTOP|MB_SETFOREGROUND);
}
IMPLEMENT_DYNCREATE(CInfoConsole, CWinThread)

CInfoConsole::CInfoConsole(HWND hwndView,HWND hwndFrame):m_hwndView(hwndView)
{

	m_pFrame=CWnd::FromHandlePermanent (hwndFrame);
	m_bConnOpen=FALSE;

}

CInfoConsole::~CInfoConsole()
{
//	delete pMainFrame;
}

BOOL CInfoConsole::InitInstance()
{
	::CoInitialize (NULL);
	BOOL bTemplateIsLoaded=FALSE;
	CString strConn/*=_T("File Name=C:\\VisualCStudy\\UserThreads\\data\\connstring.udl")*/;
	strConn.LoadString(IDS_CONNSTRING);
	if(!ConnectBase(strConn))return FALSE;
	CUserThreadsApp* pApp = static_cast<CUserThreadsApp*>(AfxGetApp());
	ASSERT(pApp);
	POSITION curTmplPos=pApp->GetFirstDocTemplatePosition ();
	while(curTmplPos)
	{
		CDocTemplate* curTemplate=pApp->GetNextDocTemplate (curTmplPos);
		CString str;
		curTemplate->GetDocString (str,CDocTemplate::docName);
		
		if(str==_T("NaklForm")||str==_T("DictionaryForm"))
		{
			
			bTemplateIsLoaded=TRUE;
		
			break;
		}
	}
	
	if(!bTemplateIsLoaded)
	{
	
		{
			CMultiDocTemplate* pDocTemplate;
			pDocTemplate = new CMultiDocTemplate(
				IDR_DICTFORM_TMPL,
				RUNTIME_CLASS(CDBDoc),
				RUNTIME_CLASS(CDictGoodsFrame), // custom MDI child frame
				RUNTIME_CLASS(CDialogView));
				TRACE0("Loaded Template DictionaryForm!!!\n");
			pApp->AddDocTemplate(pDocTemplate);
		
		}
		
		
		{	
			CMultiDocTemplate* pNewDocTemplate = new CMultiDocTemplate(
				IDR_NAKLFORM_TMPL,
				RUNTIME_CLASS(CDBDoc),		// document class
				RUNTIME_CLASS(CMDIChild),		// frame class
				RUNTIME_CLASS(CNaklForm));
				TRACE0("Loaded Template NaklForm!!!\n");// view class
			pApp->AddDocTemplate(pNewDocTemplate);
			
		}
	
	}
	// create main MDI Frame window
	

	pMainFrame = new CInfoFrame;
	if (!pMainFrame->LoadFrame(IDR_INFOFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	

	
	pMainFrame->m_wndMDIClient.RestoreMainFrameState(SW_SHOWNORMAL);
	pMainFrame->UpdateWindow();
	pApp->hwndInfoWnd=m_pMainWnd->GetSafeHwnd ();
	pMainFrame->hwndForm =m_hwndView ;
	return TRUE;

}

int CInfoConsole::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
		CUserThreadsApp* pApp = static_cast<CUserThreadsApp*>(AfxGetApp());
		ASSERT(pApp);
		//

	DisconnectBase ();
	pApp->m_pInfoConsoleThread =NULL;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CInfoConsole, CWinThread)
	//{{AFX_MSG_MAP(CInfoConsole)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoConsole message handlers

CInfoConsole::CInfoConsole()
{
m_bConnOpen=FALSE;
}



void CInfoConsole::SetDocument(CDocument *pDoc)
{
m_pDocument=(CMainDocument*)pDoc;
}

void CInfoConsole::CloseAll()
{
if (m_pMainWnd)
		m_pMainWnd->PostMessage(WM_CLOSE);
}

void CInfoConsole::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
		::CoUninitialize();

	CWinThread::OnFinalRelease();
}

BOOL CInfoConsole::ConnectBase(CString strConn)
{
	if(!m_bConnOpen)
	{
		try
		{
			
			TESTHR(pConn.CreateInstance (__uuidof(Connection)));
			TESTHR(pConn->Open ((_bstr_t)strConn,"","",adConnectUnspecified));
			TRACE0("Info Connect Base\n");
			m_bConnOpen=TRUE;
			return TRUE;
		}
		
		catch (_com_error &e)
		{
			// Pass a connection pointer accessed from the Recordset.
			_variant_t vtConnect = (IDispatch*)pConn;
			
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
			return FALSE;
		}
		  }
	return TRUE;
	
}

BOOL CInfoConsole::DisconnectBase()
{
	if(!m_bConnOpen)
		return TRUE;
	try
			{if(pConn->State ==adStateOpen)
			  TESTHR(pConn->Close ()); 
		m_bConnOpen=FALSE;
		TRACE0("Info DisconnectBase\n");
			  return TRUE;
			 }
		  
		  catch (_com_error &e)
		  {
		  // Pass a connection pointer accessed from the Recordset.
			  _variant_t vtConnect = (IDispatch*)pConn;
			  
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
			  return FALSE;
		  }
		 
}
