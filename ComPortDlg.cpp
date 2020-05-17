// ComPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ComPortDlg.h"
#include "DBDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComPortDlg dialog


CComPortDlg::CComPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComPortDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComPortDlg)
	m_strComPort = _T("");
	//}}AFX_DATA_INIT
}


void CComPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComPortDlg)
	DDX_CBString(pDX, IDC_COMPORTLIST, m_strComPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComPortDlg, CDialog)
	//{{AFX_MSG_MAP(CComPortDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComPortDlg message handlers

BOOL CComPortDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox* pCombo=(CComboBox*)GetDlgItem (IDC_COMPORTLIST);
	for(int i=1;i<20;i++)
	{
		CString strComPort=_T("COM");
		TCHAR buff[20];
		_itot(i,buff,10);
		strComPort+=buff;
		pCombo->AddString (strComPort);
	}
	CFrameWnd* pFrame=(CFrameWnd*)AfxGetMainWnd();
	CDBDoc* pDoc=(CDBDoc*)pFrame->GetActiveDocument();
	pCombo->SetCurSel (pDoc->m_nComPort -1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CComPortDlg::OnOK() 
{
	CFrameWnd* pFrame=(CFrameWnd*)AfxGetMainWnd();
	CDBDoc* pDoc=(CDBDoc*)pFrame->GetActiveDocument();
	CComboBox* pCombo=(CComboBox*)GetDlgItem (IDC_COMPORTLIST);	// TODO: Add extra validation here
	CString str;
	pCombo->GetLBText (pCombo->GetCurSel (),str);
	str=str.Mid (3);
	pDoc->m_nComPort =_ttoi(str);
	CDialog::OnOK();
}
