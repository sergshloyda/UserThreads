// FirstStepPage.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "FirstStepPage.h"
#include "ZReportWizard.h"
#include "SalaryDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CZReportWizard *pWizard;
/////////////////////////////////////////////////////////////////////////////
// CFirstStepPage property page

IMPLEMENT_DYNCREATE(CFirstStepPage, CPropertyPage)

CFirstStepPage::CFirstStepPage() : CPropertyPage(CFirstStepPage::IDD)
{
	//{{AFX_DATA_INIT(CFirstStepPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFirstStepPage::~CFirstStepPage()
{
}

void CFirstStepPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirstStepPage)
	DDX_Control(pDX, IDC_FSKASSA, m_lblCash);
	DDX_Control(pDX, IDC_FSITOGO, m_lblItogo);
	DDX_Control(pDX, IDC_FSPREMIA, m_lblPremia);
	DDX_Control(pDX, IDC_FSOKLAD, m_lblKassa);
	DDX_Control(pDX, IDC_FSENDAMOUNT, m_lblEndAmount);
	DDX_Control(pDX, IDC_FSBEGAMOUNT, m_lblBegAmount);
	DDX_Control(pDX, IDC_FSEMPLOYER, m_lblSaler);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFirstStepPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFirstStepPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstStepPage message handlers

BOOL CFirstStepPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization ;here
	m_lblSaler.SetColor (RGB(255,0,0));
	m_lblSaler.SetText ("Продавец:Сивун Петр Юрьевич");
	m_lblSaler.SetLabelFont (_T("Arial"),14);
	m_lblBegAmount.SetColor (RGB(255,150,0));
	m_lblBegAmount.SetText ("Начало дня:100000");
	m_lblBegAmount.SetLabelFont (_T("Arial"),14);
	m_lblEndAmount.SetColor (RGB(255,150,0));
	m_lblEndAmount.SetText ("Конец дня:100000");
	m_lblEndAmount.SetLabelFont (_T("Arial"),14);
	m_lblKassa.SetColor (RGB(0,150,0));
	m_lblKassa.SetText ("Оклад:100 0");
	m_lblKassa.SetLabelFont (_T("Arial"),14);
	m_lblCash.SetColor (RGB(0,0,150));
	m_lblCash.SetText ("Касса:100000");
	m_lblCash.SetLabelFont (_T("Arial"),14);
	m_lblPremia.SetColor (RGB(0,150,0));
	m_lblPremia.SetText ("Премия 5% : 100000");
	m_lblPremia.SetLabelFont (_T("Arial"),14);
	m_lblItogo.SetColor (RGB(0,0,0));
	m_lblItogo.SetText ("Итого зарплата:100000");
	m_lblItogo.SetLabelFont (_T("Arial"),14);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFirstStepPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	pWizard->SetWizardButtons (PSWIZB_NEXT);
	CString strProlog=_T("Данный мастер позволит рассчитать сумму начисленной зарплаты и,соответственно,\nвычислить сумму для сдачи в кассу");
	SetDlgItemText(IDC_STATICFP,strProlog);

	if(!LoadSalerInfo())return FALSE;
	if(!LoadCashInfo())return FALSE;
	return CPropertyPage::OnSetActive();
}

BOOL CFirstStepPage::LoadSalerInfo()
{
	CString strLabelName="Продавец:";
	CString strFilter;
	CString strName;
//	float flSalary=0.0;

	strFilter.Format(_T("emplid='%s'"),pWizard->m_strSalerId );
//	CSalaryDoc* pSalaryDoc=CSalaryDoc::GetSalaryDoc ();
	/*try
    {
		CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		_RecordsetPtr pRst=NULL;
		_RecordsetPtr pRstFilter=NULL;

		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		TESTHR(pRstFilter.CreateInstance(__uuidof(Recordset)));
		HRESULT hResult=pRst->Open(_bstr_t("employee"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenStatic, adLockReadOnly,adCmdTable);
		if(hResult!=S_OK)return FALSE;

		if(pRst->GetRecordCount ()<0) return FALSE;
		pRst->Filter=(_bstr_t)strFilter;
		if(pRst->GetRecordCount ()<=0) return FALSE;
		pRst->MoveFirst();
		strName=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem ("emplname")->Value) ;
		strName.TrimRight ();
		strName.TrimLeft ();
		pWizard->m_strSalerName =strName;
	
	
		pRst->Close ();
		
	}
	catch(_com_error &e)
	{ 
		AfxMessageBox(e.Description() );
		return FALSE ;
	}*/
	
	strLabelName+=strName ;
	m_lblSaler.SetText (strLabelName);
	CString strSalary;
	strSalary.Format (_T("Оклад:%.2f"),pWizard->m_flSalary);
	m_lblKassa.SetText (strSalary);
	return TRUE;
}

 BOOL CFirstStepPage::LoadCashInfo()
{
	CString strBegAmount;
	strBegAmount.Format(_T("Начало:%.2f"),pWizard->pZReportDoc->m_flOstatok-pWizard->pZReportDoc ->m_flCurSummSale );
	m_lblBegAmount.SetText(strBegAmount);
	 
	CString strEndAmount;
	strEndAmount.Format (_T("Конец дня:%.2f"),pWizard->pZReportDoc->m_flOstatok  );
	m_lblEndAmount.SetText(strEndAmount);

	CString strCash;
	strCash.Format (_T("Касса:%.2f"),pWizard->pZReportDoc ->m_flCurSummSale );
	m_lblCash.SetText(strCash);

	CString strPremia;
	strPremia.Format(_T("Премия %.2f %% :%.2f"),(pWizard->m_flPremia/pWizard->pZReportDoc ->m_flCurSummSale)*100 , pWizard->m_flPremia );
	m_lblPremia.SetText(strPremia);

	CString strItogo;
	pWizard->m_flItogo =pWizard->m_flSalary +pWizard->m_flPremia ;
	strItogo.Format(_T("Итого зарплата:%.2f"),pWizard->m_flItogo );
	m_lblItogo.SetText (strItogo);
	return TRUE;
}
