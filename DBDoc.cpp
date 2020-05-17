// DBDoc.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "DBDoc.h"
#include "CashDoc.h"
#include "InfoFrame.h"
#include "InfoConsole.h"
#include "MainDocument.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBDoc
static TCHAR szSection[]     = _T("Font2");
static TCHAR szFontName[]    = _T("Font Name");
static TCHAR szFontSize[]    = _T("Font Size");


static TCHAR szPeriodSection[]     = _T("Period");
static TCHAR szStart[]       = _T("Start");
static TCHAR szEnd[]         = _T("End");

static TCHAR szFormat[]      = _T("%d/%d/%d");
static TCHAR szComPortSection[] =_T("ComPort");
static TCHAR szComPort[]=_T("ComPort");

static BOOL ReadDateTime(TCHAR* szSubSection,COleDateTime& time)
{
	CString strBuffer = AfxGetApp()->GetProfileString(szPeriodSection, szSubSection);
	if (strBuffer.IsEmpty())
		return FALSE;
	int nDay,nMonth,nYear;
	nDay=0;
	nMonth=0;
	nYear=0;
	
	//int nRead = _stscanf(strBuffer, szFormat,
	//	&nYear, &nMonth,&nDay);
	COleDateTime tm(nYear,nMonth,nDay,0,0,0);
	time=tm;
	return TRUE;
}

static void WriteDateTime(TCHAR* szSubSection,COleDateTime& time)
	// write a window placement to settings section of app's ini file
{
	TCHAR szBuffer[sizeof("10/10/2010")+1];
	memset(&szBuffer,0,sizeof(szBuffer));
	wsprintf(szBuffer, szFormat,
		time.GetYear(), time.GetMonth(),
	time.GetDay());
	AfxGetApp()->WriteProfileString(szPeriodSection, szSubSection, szBuffer);
}
static BOOL stReadComPort(int &nComPort)
{

   nComPort = AfxGetApp()->GetProfileInt(szComPortSection, szComPort, 0);
	return TRUE;
}
static void WriteComPort(int nComPort)
{
   	AfxGetApp()->WriteProfileInt(szComPortSection, szComPort, nComPort);
}



IMPLEMENT_DYNCREATE(CDBDoc, CDocument)

CDBDoc::CDBDoc()
{
	ReadFont();
	ReadPeriod();
	ReadComPort ();

}

BOOL CDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
		
		//strSQL=strSQL+buff+" And PartId<>" +buff;
	return TRUE;
}

CDBDoc::~CDBDoc()
{
}


BEGIN_MESSAGE_MAP(CDBDoc, CDocument)
	//{{AFX_MSG_MAP(CDBDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBDoc diagnostics

#ifdef _DEBUG
void CDBDoc::AssertValid() const
{
	//CDocument::AssertValid();
}

void CDBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBDoc serialization

void CDBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDBDoc commands

void CDBDoc::SetPointFont(CString szName, int nSize)
{
	if ((HFONT)m_font) 
	{
		// first time init: create font
		m_font.DeleteObject ();
	}
	m_font.CreatePointFont (nSize*10,szName);
	m_nFontSize=nSize;
	m_szFontName=szName;
}

void CDBDoc::ReadFont()
{
	CInfoFrame* pFrame=static_cast<CInfoFrame*>(AfxGetMainWnd());

	m_szFontName=AfxGetApp()->GetProfileString (szSection,szFontName,_T("Arial"));
	m_nFontSize=AfxGetApp()->GetProfileInt(szSection,szFontSize,10);

	pFrame->m_wndFontTB.SetupToolBar (m_szFontName,m_nFontSize);

	//pFrame->m_wndFontTB.EnableDocking(CBRS_ALIGN_ANY);
	//pFrame->EnableDocking(CBRS_ALIGN_ANY);
	//pFrame->DockControlBarLeftOf (&pFrame->m_wndFontTB ,&pFrame->m_wndToolBar );
	TRACE(_T("CDBDoc::ReadFont\n"));
	SetPointFont(m_szFontName,m_nFontSize);
}

void CDBDoc::SaveFont()
{
	CString szBuffer="Arial";
 	CInfoFrame* pFrame=static_cast<CInfoFrame*>(AfxGetMainWnd());
	szBuffer=pFrame->m_wndFontTB.GetFontName ();

	int nSize=10;
  
	nSize=pFrame->m_wndFontTB.GetFontSize ();

	AfxGetApp()->WriteProfileString(szSection, szFontName, szBuffer);
	AfxGetApp()->WriteProfileInt (szSection,szFontSize,nSize);
}

void CDBDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	SaveFont();
	SavePeriod();
	SaveComPort();
	CDocument::OnCloseDocument();
}





CFont& CDBDoc::GetFont()
{
	return m_font;

}

void CDBDoc::ReadPeriod()
{
	// TODO: Add extra initialization here
	COleDateTime tmStart,tmEnd;
	
	if(!ReadDateTime(szStart,m_dtStart))
		m_dtStart=COleDateTime::GetCurrentTime ();
	if(!ReadDateTime(szEnd,m_dtEnd))
		m_dtEnd=COleDateTime::GetCurrentTime ();



}

void CDBDoc::SavePeriod()
{
	WriteDateTime (szStart,m_dtStart);
	WriteDateTime (szEnd,m_dtEnd);
}



void CDBDoc::ReadComPort()
{
	int nComPort=0;
	if(stReadComPort(nComPort))
	 m_nComPort=nComPort;
 
}

void CDBDoc::SaveComPort()
{
	WriteComPort(m_nComPort);
}

BOOL CDBDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	return TRUE;
}
BOOL CDBDoc::UpdateCashMove()
{
	_RecordsetPtr pRst=NULL;
	CString strSQL="Select docid,cashid,pointid,summa,cash2id,point2id,docdate,doctime"
		" from HCAMOEXP where docid not in (select docid from dhcashmv) order by docdate,doctime";
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CMainDocument* pMainDoc=pApp->GetDocument<CMainDocument>();
	try
	{
		
		
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		CInfoConsole* pInfo=(CInfoConsole*)AfxGetThread();
		ASSERT((CWinThread*)pInfo!=(CWinThread*)pApp);
		HRESULT hr=pRst->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pInfo->pConn),
			adOpenKeyset, adLockBatchOptimistic, adCmdText);
		if (hr!=S_OK)
		{
			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
			return FALSE;
		}
		long lRecordsCount=pRst->GetRecordCount ();
		if (lRecordsCount>0)
		{
			//pRst->MoveLast ();
			//pRst->MoveFirst ();
	
		
		
			
			pMainDoc->m_blIsDirty =TRUE;
		}
		else
			AfxMessageBox(_T("Нет новых документов для добавления."),MB_ICONINFORMATION|MB_OK);
		TESTHR(pRst->Close());
		return TRUE;
	}
	catch (_com_error &e)
	{
		// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
		_variant_t vtConnect = pRst->GetActiveConnection();
		
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
			MessageBoxHelper::ShowError(_T("Errors occured."));
			break;
		}
		return FALSE;
	}

}