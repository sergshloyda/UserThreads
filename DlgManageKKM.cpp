// DlgManageKKM.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgManageKKM.h"
#include "drvfr.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgManageKKM dialog


CDlgManageKKM::CDlgManageKKM()
	: CPropertyPage(CDlgManageKKM::IDD)
{
	//{{AFX_DATA_INIT(CDlgManageKKM)
	//m_KKMOnLine = FALSE;
	m_strNameKKM = _T("");
	m_strCOMPortKKM = _T("");
	m_strStatusKKM=_T("");
	//}}AFX_DATA_INIT
}


void CDlgManageKKM::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManageKKM)
	//DDX_Check(pDX, IDC_CHECK_KKMON, m_KKMOnLine);
	DDX_Text(pDX, IDC_KKM_INFO, m_strNameKKM);
	DDX_Text(pDX, IDC_COM_KKM, m_strCOMPortKKM);
	DDX_Text(pDX, IDC_STATUS_KKM,m_strStatusKKM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgManageKKM, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgManageKKM)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgManageKKM message handlers

void CDlgManageKKM::OnOk() 
{
	CShtrihFRK Driver;
   
    Driver.ShowProperties();
	
}


BOOL CDlgManageKKM::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CString sName=_T("Name"),sComNumber=_T("ComNumber");
	long lResult=0;
	HKEY hKey;
	DWORD dwBuffLen;
	TCHAR buffer[MAX_PATH];
	DWORD dwComNumber=0;
	lResult=RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\ShtrihM\\DrvFR\\Logical Devices\\0"),0,
		KEY_READ,&hKey);
	if (lResult==ERROR_SUCCESS)
	{
		dwBuffLen=MAX_PATH;
		DWORD type=REG_SZ;
		lResult=RegQueryValueEx(hKey,sName,NULL,&type,(BYTE*)buffer,&dwBuffLen);
		if (lResult==ERROR_SUCCESS)
		{
			m_strNameKKM=buffer;
		}
		dwBuffLen=sizeof(DWORD);
		type=REG_DWORD;
		lResult=RegQueryValueEx(hKey,sComNumber,NULL,&type,(BYTE*)&dwComNumber,&dwBuffLen);
		if (lResult==ERROR_SUCCESS)
		{
			CString strCom;
			strCom.Format(_T("COM%d"),dwComNumber);
			m_strCOMPortKKM=strCom;
		}
		RegCloseKey(hKey);
	}
	
	CShtrihFRK drv;
	long res_code=drv.ConnectFR(30);
	CString descr=drv.GetResultCodeDescription();
	m_strStatusKKM=descr;
	//res_code=drv.GetECRStatus();
	//res_code=drv.GetResultCode();
	drv.DisconnectFR();
	//m_strNameKKM=drv.GetNameCashReg();
	UpdateData(FALSE);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
