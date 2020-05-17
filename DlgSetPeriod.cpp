// DlgSetPeriod.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgSetPeriod.h"
#include "DBDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetPeriod dialog


CDlgSetPeriod::CDlgSetPeriod(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetPeriod::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetPeriod)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSetPeriod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetPeriod)

	DDX_Control(pDX, IDC_DTPICKER1, m_dateStart);
	DDX_Control(pDX, IDC_DTPICKER2, m_dateEnd);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgSetPeriod, CDialog)
	//{{AFX_MSG_MAP(CDlgSetPeriod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetPeriod message handlers

BOOL CDlgSetPeriod::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CFrameWnd* pFrame=(CFrameWnd*)AfxGetMainWnd();
	CDBDoc* pDoc=(CDBDoc*)pFrame->GetActiveDocument();

	m_dateStart.SetValue((COleVariant)pDoc->m_dtStart);

	m_dateEnd.SetValue((COleVariant)pDoc->m_dtEnd);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSetPeriod::OnOK() 
{
	// TODO: Add extra validation here
	COleDateTime tmStart=m_dateStart.GetValue ();
	COleDateTime tmEnd=m_dateEnd.GetValue ();
	if(tmStart>tmEnd)
	{
		AfxMessageBox(IDS_WRONGPERIOD,MB_ICONSTOP|MB_OK);
		m_dateStart.SetFocus ();
	}
	else
	{
		CFrameWnd* pFrame=(CFrameWnd*)AfxGetMainWnd();
		CDBDoc* pDoc=(CDBDoc*)pFrame->GetActiveDocument();
		pDoc->m_dtStart =tmStart;
		pDoc->m_dtEnd =m_dateEnd.GetValue ();
		CDialog::OnOK();
	}

}

void CDlgSetPeriod::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
