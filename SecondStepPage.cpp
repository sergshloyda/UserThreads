// SecondStepPage.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "SecondStepPage.h"
#include "ZReportWizard.h"
#include "SalaryDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CZReportWizard* pWizard;
/////////////////////////////////////////////////////////////////////////////
// CSecondStepPage property page

IMPLEMENT_DYNCREATE(CSecondStepPage, CPropertyPage)

CSecondStepPage::CSecondStepPage() : CPropertyPage(CSecondStepPage::IDD)
{
	//{{AFX_DATA_INIT(CSecondStepPage)
	m_flZabral = 0.0f;
	m_flSdano = 0.0f;
	//}}AFX_DATA_INIT
	m_Font.CreatePointFont (140,_T("Arial"));
	m_hAccel = NULL;
	m_blFirstTime=TRUE;
}

CSecondStepPage::~CSecondStepPage()
{
}

void CSecondStepPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSecondStepPage)
	DDX_Control(pDX, IDC_SSCASHMOVE, m_lblCashMove);
	DDX_Control(pDX, IDC_SSCASHOSTEND, m_lblOstKassa);
	DDX_Control(pDX, IDC_EDZABRAL2, m_edSdanaKassa);
	DDX_Control(pDX, IDC_SSCASHNOW, m_lblCashNow);
	DDX_Control(pDX, IDC_SSOSTEND, m_lblBalans);
	DDX_Control(pDX, IDC_EDZABRAL, m_edZabral);
	DDX_Control(pDX, IDC_SSZABRAL, m_lblZabral);
	DDX_Control(pDX, IDC_SSZARPLATA, m_lblZarplata);
	DDX_Control(pDX, IDC_SSOSTATOK, m_lblOstBegin);
	DDX_Control(pDX, IDC_SSSALER, m_lblSaler);
	DDX_Text(pDX, IDC_EDZABRAL, m_flZabral);
	DDX_Text(pDX, IDC_EDZABRAL2, m_flSdano);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSecondStepPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSecondStepPage)
	ON_EN_CHANGE(IDC_EDZABRAL, OnChangeEdzabral)
	ON_EN_CHANGE(IDC_EDZABRAL2, OnChangeSdano)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE,			OnKickIdle)
	ON_COMMAND(ID_RETURNED,			OnReturn)
	ON_COMMAND_EX(ID_NEXT_FIELD,  OnNextPrevField)
	ON_COMMAND_EX(ID_PREV_FIELD,  OnNextPrevField)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecondStepPage message handlers

BOOL CSecondStepPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_lblSaler.SetColor (RGB(255,0,0));
	m_lblSaler.SetText (_T("Продавец:Сивун Петр Юрьевич"));
	m_lblSaler.SetLabelFont (_T("Arial"),14);

	m_lblOstBegin.SetColor (RGB(255,150,0));
	m_lblOstBegin.SetText (_T("Текущий баланс зарплаты:10000"));
	m_lblOstBegin.SetLabelFont (_T("Arial"),14);

	m_lblZarplata.SetColor (RGB(0,150,0));
	m_lblZarplata.SetText (_T("Начислена зарплата:10000"));
	m_lblZarplata.SetLabelFont (_T("Arial"),14);
	m_lblZabral.SetColor (RGB(0,0,150));
	m_lblZabral.SetText (_T("Изымаемая сумма:"));
	m_lblZabral.SetLabelFont (_T("Arial"),14);
	m_edZabral.SetFont (&m_Font);
	m_edSdanaKassa.SetFont (&m_Font);
	m_lblBalans.SetColor (RGB(0,150,0));
	m_lblBalans.SetText (_T("Остаток на счету:10000"));
	m_lblBalans.SetLabelFont (_T("Arial"),14);
	m_lblCashNow.SetColor (RGB(0,0,200));
	m_lblCashNow.SetText (_T("Остаток в кассе до сдачи:100000"));
	m_lblCashNow.SetLabelFont (_T("Arial"),14);
	m_lblCashMove.SetColor (RGB(0,0,200));
	m_lblCashMove.SetText (_T("Сдаваемая сумма:"));
	m_lblOstKassa.SetLabelFont (_T("Arial"),14);
	m_lblOstKassa.SetColor (RGB(0,0,200));
	m_lblOstKassa.SetText (_T("Остаток в кассе после сдачи:100000"));
	m_lblCashMove.SetLabelFont (_T("Arial"),14);

	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDD_SECONDSTEP));
	ASSERT(m_hAccel);
	GotoDlgCtrl((CWnd*)&m_edZabral);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSecondStepPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	pWizard->SetWizardButtons (PSWIZB_BACK|PSWIZB_NEXT);
	if(!LoadInfo()) return FALSE;
	return CPropertyPage::OnSetActive();
}

BOOL CSecondStepPage::LoadInfo()
{
	CSalaryDoc *pSlryDoc=CSalaryDoc::GetSalaryDoc ();
	m_lblSaler.SetText (_T("Продавец:")+pWizard->m_strSalerName );

	pWizard->m_flSalaryBalance=pSlryDoc->GetSalaryBalance (pWizard->m_strSalerId,COleDateTime::GetCurrentTime ());;
	CString strBalance;
	strBalance.Format (_T("Текущий баланс зарплаты:%.2f"),pWizard->m_flSalaryBalance);
	m_lblOstBegin.SetText(strBalance);
	
	CString strZarplata;
	strZarplata.Format(_T("Начислена зарплата:%.2f"),pWizard->m_flItogo );
	m_lblZarplata.SetText (strZarplata);
	strZarplata.Empty ();
	strZarplata.Format (_T("%.2f"),pWizard->m_flItogo );
	m_edZabral.SetWindowText (strZarplata);
	m_edZabral.SendMessage (EM_SETSEL,(WPARAM)0,(LPARAM)-1);

	CString str;
	str.Format (_T("Остаток в кассе до сдачи:%.2f"),
		pWizard->pZReportDoc ->m_flOstatok /* +
		pWizard->pZReportDoc ->m_flCurSummSale -
		pWizard->pZReportDoc ->m_flCurSummReturn */);
	m_lblCashNow.SetText (str);
	m_flSdano=pWizard->pZReportDoc ->m_flOstatok /*+
		pWizard->pZReportDoc ->m_flCurSummSale -
		pWizard->pZReportDoc ->m_flCurSummReturn*/ ;
	return TRUE;
}
                                

LRESULT CSecondStepPage::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	if(m_flZabral<0) 
	{
		MessageBoxHelper::ShowError(_T("Введите положительное значение"));
		m_edZabral.SetFocus ();
		return -1L;
	}

	pWizard->m_flZabral =m_flZabral;

	if(m_flSdano<0) 
	{
		MessageBoxHelper::ShowError(_T("Введите положительное значение"));
		m_edSdanaKassa.SetFocus ();
		return -1L;
	}

	pWizard->m_flSdano  =m_flSdano;

	return CPropertyPage::OnWizardNext();
}

void CSecondStepPage::OnChangeEdzabral() 
{
	UpdateData(TRUE);
	float flDelta=pWizard->m_flSalaryBalance +pWizard->m_flItogo -m_flZabral ;
	CString strChange;
	strChange.Format(_T("Остаток на счету:%.2f"),flDelta);
	m_lblBalans.SetText (strChange);
	
}

BOOL CSecondStepPage::PreTranslateMessage(MSG* pMsg) 
{
		if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST) 
		{
		// Translate the message using accelerator table
		ASSERT(m_hAccel);
		return ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg);
		}
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

LRESULT CSecondStepPage::OnKickIdle(WPARAM wp, LPARAM lCount)
{
	UpdateDialogControls(this, TRUE);
	return 0;
}

void CSecondStepPage::OnReturn()
{
	OnNextPrevField(ID_NEXT_FIELD);
}

/////////////////
// Go to next or previous field
//
BOOL CSecondStepPage::OnNextPrevField(UINT nCmdID)
{
	if(m_blFirstTime)
	{
	CWnd* pWnd = CWnd::GetFocus();
	 
		// Normal next/prev using dialog's TAB order.
	pWnd = GetNextDlgTabItem(pWnd, FALSE);

	ASSERT(pWnd);
	GotoDlgCtrl(pWnd);
	m_blFirstTime=!m_blFirstTime;
	UpdateData(FALSE);
	m_lblOstKassa.SetText (_T("Остаток в кассе после сдачи:0.00"));
	m_edSdanaKassa.SendMessage (EM_SETSEL,(WPARAM)0,(LPARAM)-1);
	}
	else
	{
		CWnd* pNext = pWizard->GetDlgItem(ID_WIZNEXT);
		pNext->SetFocus ();
	}
	return TRUE;
}

void CSecondStepPage::OnChangeSdano() 
{
	float flTemp=pWizard->pZReportDoc ->m_flOstatok +
				 pWizard->pZReportDoc ->m_flCurSummSale -
				 pWizard->pZReportDoc ->m_flCurSummReturn;
	UpdateData(TRUE);
	float flDelta=flTemp - m_flSdano ;
	CString strChange;
	strChange.Format(_T("Остаток в кассе после сдачи:%.2f"),flDelta);
	m_lblOstKassa.SetText(strChange);
	
}
