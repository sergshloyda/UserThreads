// About.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "About.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog


CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbout)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
	//{{AFX_MSG_MAP(CAbout)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbout message handlers

void CAbout::OnOk() 
{
}

void CAbout::OnButton1() 
{

			_ConnectionPtr pConn=NULL;
	CString strConn=_T("File Name=C:\\VisualCStudy1\\UserThreads\\data\\connstring.udl");
	//strConn.LoadString(IDS_CONNSTRING);
	
	HRESULT hr=pConn.CreateInstance (__uuidof(Connection));
	if(hr!=S_OK) 
	{
		TRACE("Error Connect1\n");
		return ;
	}
	//pConn->Mode = adModeShareExclusive;
	//pConn->IsolationLevel = adXactIsolated;
	
	hr=pConn->Open ((_bstr_t)strConn,"sa","vjkjltxyj",adConnectUnspecified);
		if(hr!=S_OK) 
	{
		AfxMessageBox("Error Connect2");
		return ;
	}
	pConn->CursorLocation =adUseClient;
	_RecordsetPtr pRst=NULL;
	pRst.CreateInstance(__uuidof(Recordset));
	pRst->CursorLocation = adUseClient;
	
	hr=pRst->Open(_bstr_t("catalog"),_variant_t((IDispatch*)pConn), 
		adOpenKeyset, adLockOptimistic,adCmdTable);
		if(hr!=S_OK) 
	{
		AfxMessageBox("Error Connect3");
		return ;
	}
}
