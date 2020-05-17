// ZReportWizard.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ZReportWizard.h"
#include "ZReportView.h"
#include "SalaryDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZReportWizard
extern CZReportWizard* pWizard;
IMPLEMENT_DYNAMIC(CZReportWizard, CPropertySheet)

CZReportWizard::CZReportWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CZReportWizard::CZReportWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	Construct(pszCaption,this);
	m_FStepPage.Construct (IDD_FIRSTSTEP,0);
	m_SStepPage.Construct (IDD_SECONDSTEP,0);
	m_TStepPage.Construct (IDD_THIRDSTEP,0);
	AddPage(&m_FStepPage);
	AddPage(&m_SStepPage);
	AddPage(&m_TStepPage);
	pWizard=this;
	m_strSalerId=pszCaption;
	CZReportView* pView=static_cast<CZReportView*>(pParentWnd);
	pZReportDoc=pView->GetDocument ();
}

CZReportWizard::~CZReportWizard()
{

}


BEGIN_MESSAGE_MAP(CZReportWizard, CPropertySheet)
	//{{AFX_MSG_MAP(CZReportWizard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZReportWizard message handlers





BOOL CZReportWizard::OnInitDialog() 
{
	_RecordsetPtr pRst=NULL;
	CSalaryDoc* pSalaryDoc=CSalaryDoc::GetSalaryDoc ();
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	float flCalcSalary=0.0;
	CZReportDoc* pZRDoc=CZReportDoc::GetZReportDoc ();
	pRst=pZRDoc->GetZReportRecordset ();
	pSalaryDoc->CalculateAmountSalary(pRst,&flCalcSalary);
	m_flPremia=flCalcSalary ;	
	pSalaryDoc->GetBaseSalary (m_strSalerId,&flCalcSalary);
	m_flSalary =flCalcSalary ;
	if(pRst!=NULL)
	{
		if(pRst->State ==adStateOpen)
			pRst->Close ();
	}

	
	BOOL bResult = CPropertySheet::OnInitDialog();
	return bResult;
}
