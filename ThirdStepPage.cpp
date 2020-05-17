// ThirdStepPage.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ThirdStepPage.h"
#include "ZReportWizard.h"
#include "CashDoc.h"
#include "SalaryDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CZReportWizard* pWizard;
/////////////////////////////////////////////////////////////////////////////
// CThirdStepPage property page

IMPLEMENT_DYNCREATE(CThirdStepPage, CPropertyPage)

CThirdStepPage::CThirdStepPage() : CPropertyPage(CThirdStepPage::IDD)
{
	//{{AFX_DATA_INIT(CThirdStepPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CThirdStepPage::~CThirdStepPage()
{
}

void CThirdStepPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThirdStepPage)
	DDX_Control(pDX, IDC_SALER, m_lblSaler);
	DDX_Control(pDX, IDC_OSTATOK, m_lblOstatok);
	DDX_Control(pDX, IDC_SDANO, m_lblSdano);
	DDX_Control(pDX, IDC_ZABRAL, m_lblZabral);
	DDX_Control(pDX, IDC_SALARY, m_lblSalary);
	DDX_Control(pDX, IDC_CASHVAL, m_lblCashValue);
	DDX_Control(pDX, IDC_ENDAMOUNT, m_lblEndAmount);
	DDX_Control(pDX, IDC_BEGAMOUNT, m_lblBegAmount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThirdStepPage, CPropertyPage)
	//{{AFX_MSG_MAP(CThirdStepPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThirdStepPage message handlers

BOOL CThirdStepPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_lblSaler.SetColor (RGB(255,0,0));
	m_lblSaler.SetText (_T("Продавец:Сивун Петр Юрьевич"));
	m_lblSaler.SetLabelFont (_T("Arial"),14);
	m_lblBegAmount.SetColor (RGB(255,150,0));
	m_lblBegAmount.SetText (_T("Начало дня:100000"));
	m_lblBegAmount.SetLabelFont (_T("Arial"),14);
	m_lblEndAmount.SetColor (RGB(255,150,0));
	m_lblEndAmount.SetText (_T("Конец дня:100000"));
	m_lblEndAmount.SetLabelFont (_T("Arial"),14);
	m_lblCashValue.SetColor (RGB(0,150,0));
	m_lblCashValue.SetText (_T("Касса:100 0"));
	m_lblCashValue.SetLabelFont (_T("Arial"),14);
	m_lblSalary.SetColor (RGB(0,0,150));
	m_lblSalary.SetText (_T("Начислена зарплата:100000"));
	m_lblSalary.SetLabelFont (_T("Arial"),14);
	m_lblZabral.SetColor (RGB(0,150,0));
	m_lblZabral.SetText (_T("Изъята зарплата : 100000"));
	m_lblZabral.SetLabelFont (_T("Arial"),14);
	m_lblSdano.SetColor (RGB(0,0,0));
	m_lblSdano.SetText (_T("Сдано:100000"));
	m_lblSdano.SetLabelFont (_T("Arial"),14);
	m_lblOstatok.SetColor (RGB(0,0,0));
	m_lblOstatok.SetText (_T("Остаток в кассе:100000"));
	m_lblOstatok.SetLabelFont (_T("Arial"),14);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CThirdStepPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	pWizard->SetWizardButtons (PSWIZB_BACK|PSWIZB_FINISH);
	
	return CPropertyPage::OnSetActive();
}

BOOL CThirdStepPage::OnWizardFinish() 
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();

	pApp->pConn->BeginTrans ();
	
	
	CSalaryDoc* pSalaryDoc=CSalaryDoc::GetSalaryDoc ();

	_variant_t vt;
	
	
	if(!pWizard->pZReportDoc ->TransactZReport (vt))
	{
		pApp->pConn->RollbackTrans ();
	
		return FALSE;
	}

	if(!pSalaryDoc->TransactSalary(pWizard->pZReportDoc ->m_strDocId ,vt))
	{
		
		pApp->pConn ->RollbackTrans ();
		return FALSE;
	}
	
	if(!pSalaryDoc->WithdrawFromEmplAccount (pWizard->m_strSalerId,pWizard->m_flZabral))
		
	{
		pApp->pConn ->RollbackTrans ();
		return FALSE;
	}
	
	if(!pSalaryDoc->RecalculateSalaryRegisters (COleDateTime::GetCurrentTime ()))
		
	{
		pApp->pConn ->RollbackTrans ();
		return FALSE;
	}
	
	if(!TransactCashMove())
	{
		pApp->pConn ->RollbackTrans ();
		return FALSE;
	}
	pApp->pConn ->CommitTrans ();
	return CPropertyPage::OnWizardFinish();
}

BOOL CThirdStepPage::TransactSalary()
{

	///добавляем данные в dhsalary.dbf
/*	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();

	COleDateTime tmDocTime=COleDateTime::GetCurrentTime ();
	CString strDocId ;
	int nDayNumber=0;
	pMainDoc->CalculateDocId(pMainDoc->m_strPointId ,strDocId,&nDayNumber);
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	try
	{
		HRESULT hr=pRst->Open (_bstr_t("dhsalary"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);
		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(strDocId);
		pRst->Fields->GetItem("period")->Value =(_variant_t)tmDocTime;;
		pRst->Fields->GetItem("emplid")->Value =_bstr_t(pWizard->m_strSalerId);
		pRst->Fields->GetItem("summa")->Value =(double)pWizard->m_flZabral ;
		pRst->Fields->GetItem("basedoc")->Value =_bstr_t(pWizard->pZReportDoc ->m_strDocId );
		TESTHR(pRst->Update ());
		pRst->Close();
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		
		return FALSE;
	}
	//добавляем запись в журнал документов genjournal.dbf
	if(!pMainDoc->AddNewDocInJournal(tmDocTime,"SLR",strDocId,pWizard->m_flZabral))return FALSE;
	if(!pMainDoc->UpdateNumerator (tmDocTime))return FALSE;
	///добавляем данные в оборотный регистр оплаты труда rasalary.dbf
	//pRst=NULL;
	try
	{
		HRESULT hr=pRst->Open (_bstr_t("rasalary"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);

		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(strDocId);
		pRst->Fields->GetItem("debcredit")->Value =0L;;
		pRst->Fields->GetItem("emplid")->Value =_bstr_t(pWizard->m_strSalerId);
		pRst->Fields->GetItem("summa")->Value =(double)pWizard->m_flItogo  ;
		TESTHR(pRst->Update ());

		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(strDocId);
		pRst->Fields->GetItem("debcredit")->Value =1L;;
		pRst->Fields->GetItem("emplid")->Value =_bstr_t(pWizard->m_strSalerId);
		pRst->Fields->GetItem("summa")->Value =(double)pWizard->m_flZabral  ;
		TESTHR(pRst->Update ());

		pRst->Close();
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		
		return FALSE;
	}

	//проверяем и если нет записей или разница с последней записью > 30 дней записываем
	//значение в регистр остатков зарплаты rgsalary.dbf
	//pRst=NULL;
	try
	{
		BOOL blFlag1,blFlag2;
		HRESULT hr=pRst->Open (_bstr_t("rgsalary"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);

		if(pRst->GetRecordCount ()<=0) 
		{
			blFlag1=TRUE;
		}
		else
		{
			pRst->Sort="period ASC";
			TESTHR(pRst->MoveLast());
			COleDateTime tmLastDate=pRst->Fields ->GetItem("period")->Value;
			if(((double)tmDocTime-(double)tmLastDate)>30) blFlag2=TRUE;
		}

	
	if(blFlag1||blFlag2)
		{
			TESTHR(pRst->AddNew ());
			pRst->Fields->GetItem("period")->Value =(_variant_t)tmDocTime;
			pRst->Fields->GetItem("emplid")->Value =_bstr_t(pWizard->m_strSalerId);
			pRst->Fields->GetItem("value")->Value =pWizard->pZReportDoc ->GetSalaryBalance (pWizard->m_strSalerId ,tmDocTime) ;
			TESTHR(pRst->Update ());
		}

		pRst->Close();
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		
		return FALSE;
	}

	//ALL IS OK!!*/

	return TRUE;
}

BOOL CThirdStepPage::TransactCashMove()
{
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
	//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
	CCashDoc* pCashDoc=CUserThreadsApp::GetDocument<CCashDoc> ();
	//рассчитываем новый номер документа для ПеремещениеДенегКасса
	CString strDocId=_T("");
	int nDayNumber=0;
	//pMainDoc->CalculateDocId (pMainDoc->m_strPointId,strDocId,&nDayNumber);
	ASSERT(strDocId!="");
	//Готовим документ Перемещение денег
	
	if(!pCashDoc->AddCashMoveDocument (strDocId,
		pCashDoc->GetCashId (),//сдает наша касса
		pMainDoc->m_strPointId ,//наша точка
		pCashDoc->GetMainCashId (),//сдает в основную кассу
		pMainDoc->m_strMainPointId,//сдает на основную точку
		pWizard->m_flSdano )) return FALSE;//из поля сдано
	///Добавляем документ в журнал документов
	//if(!pMainDoc->AddNewDocInJournal (COleDateTime::GetCurrentTime (),_T("CMV"),strDocId,pWizard->m_flSdano )) return FALSE;

	//if(!pCashDoc->CashDoActionOutcome (strDocId,pWizard->m_flSdano))return FALSE;//обновляем регистры

	return TRUE;
}
