// DlgSelDate.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgSelDate.h"
#include "ReturnView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelDate dialog


CDlgSelDate::CDlgSelDate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelDate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelDate)

	//}}AFX_DATA_INIT
}
CDlgSelDate::CDlgSelDate(CString *pDate, BOOL *pbOK, int x, int y, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelDate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKalenderPopupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_tmDate = COleDateTime::GetCurrentTime();
	m_bFirstTime = TRUE;
	m_pDate = pDate;
	m_pbOK	= pbOK;
	m_x		= x;
	m_y		= y;
	m_bOk	= true;
	if(IsWindow(pParent->m_hWnd ))
		m_pParentView=(CView*)pParent;
}


void CDlgSelDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelDate)
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_ctrlCalendar);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_tmDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelDate, CDialog)
	//{{AFX_MSG_MAP(CDlgSelDate)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR1, OnSelectMonthcalendar1)
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelDate message handlers

void CDlgSelDate::OnSelectMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
NMSELCHANGE	*pSel = (NMSELCHANGE *)pNMHDR;
	
	m_pDate->Format(_T("%04d-%02d-%02d"), 
		pSel->stSelStart.wYear,
		pSel->stSelStart.wMonth,
		pSel->stSelStart.wDay);
	
	*m_pbOK = TRUE;
	CReturnView* pView=reinterpret_cast<CReturnView*>(m_pParentView);
	COleDateTime tmDateView;
	tmDateView .SetDate (pSel->stSelStart.wYear ,pSel->stSelStart.wMonth ,pSel->stSelStart.wDay );
	CReturnDoc *pDoc=pView->GetDocument();
	pDoc->SetDate(&tmDateView);
	m_bOk = false; // Sätts för att inte köra en extra OnCancel/OnOK genom OnWindowsPosChanging.
	CDialog::OnOK();
}


BOOL CDlgSelDate::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
		static CString sClassName;
	if (sClassName.IsEmpty())
		sClassName = AfxRegisterWndClass(0);
	cs.lpszClass = sClassName;
	cs.style = WS_POPUP|WS_BORDER;
	//cs.dwExStyle |= WS_EX_TOOLWINDOW;

	return CDialog::PreCreateWindow(cs);
}

BOOL CDlgSelDate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	WINDOWPLACEMENT	wpDlg, wpTmp, wpCal;
	GetWindowPlacement(&wpDlg);

	// Anpassare Dialogen efter storleken på kalendern
	m_ctrlCalendar.SizeMinReq();
	m_ctrlCalendar.GetWindowPlacement(&wpCal);
	int	nCalWidth	= wpCal.rcNormalPosition.right - wpCal.rcNormalPosition.left;
	int	nCalHeight	= wpCal.rcNormalPosition.bottom - wpCal.rcNormalPosition.top;
	wpDlg.rcNormalPosition.right	= wpDlg.rcNormalPosition.left + nCalWidth;
	wpDlg.rcNormalPosition.bottom	= wpDlg.rcNormalPosition.top + nCalHeight;

	//	Anpassar bredden på Dialogen
	wpTmp = wpDlg;
	wpDlg.rcNormalPosition.bottom	= m_y + wpDlg.rcNormalPosition.bottom - wpDlg.rcNormalPosition.top;
	wpDlg.rcNormalPosition.left		= m_x;
	wpDlg.rcNormalPosition.top		= m_y;
	wpDlg.rcNormalPosition.right	= m_x + wpTmp.rcNormalPosition.right - wpTmp.rcNormalPosition.left;
	int	y = wpDlg.rcNormalPosition.bottom-(GetSystemMetrics(SM_CYMAXIMIZED)-GetSystemMetrics(SM_CYBORDER));
	int	x = wpDlg.rcNormalPosition.right-(GetSystemMetrics(SM_CXMAXIMIZED)-GetSystemMetrics(SM_CXBORDER));
	if (y > 0) {
		wpDlg.rcNormalPosition.top		-= y;
		wpDlg.rcNormalPosition.bottom	-= y;
	}
	if (x > 0) {
		wpDlg.rcNormalPosition.left		-= x;
		wpDlg.rcNormalPosition.right	-= x;
	}

	VERIFY(SetWindowPlacement(&wpDlg) != 0);

	return TRUE;  // 
}

void CDlgSelDate::OnWindowPosChanging(WINDOWPOS * lpwndpos) 
{
	if (IsWindowVisible() && m_bOk) 
		CDialog::OnCancel();
	
}
