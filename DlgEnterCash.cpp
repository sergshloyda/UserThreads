// DlgEnterCash.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgEnterCash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnterCash dialog


CDlgEnterCash::CDlgEnterCash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnterCash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEnterCash)
	
	m_flCash = 0.0f;
	//}}AFX_DATA_INIT
	pDoc=static_cast<CUserThreadsView*>(pParent)->GetDocument ();
}


void CDlgEnterCash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnterCash)
	DDX_Control(pDX, IDC_CASH, m_wndEdit);
	DDX_Control(pDX, IDC_LABEL, m_lblWnd);
	DDX_Control(pDX, IDC_CHANGE, m_lblChange);
	DDX_Text(pDX, IDC_CASH, m_flCash);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnterCash, CDialog)
	//{{AFX_MSG_MAP(CDlgEnterCash)
	ON_EN_CHANGE(IDC_CASH, OnChangeCash)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnterCash message handlers

BOOL CDlgEnterCash::OnInitDialog() 
{

	CDialog::OnInitDialog();

	CClientDC dc(this);
	
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
	CFont* pOldFont=dc.SelectObject (pMainDoc->m_FontMap[_T("Dialogs")].get());
	m_wndEdit.SetFont(pMainDoc->m_FontMap[_T("Dialogs")].get());
	
	
	TEXTMETRIC tm;
	dc.GetTextMetrics (&tm);
	int  nHeight=tm.tmHeight+tm.tmHeight/4  ; 
	CRect rc;
	m_wndEdit.GetWindowRect (&rc);
	ScreenToClient(&rc);
	int nOldHeight=rc.Height();
	rc.bottom=rc.top + nHeight;
	int nDelta=rc.Height()-nOldHeight;
	m_wndEdit.MoveWindow (&rc);

	GetDlgItem(IDC_LABEL)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top+=nDelta;
	rc.bottom +=nDelta;
	GetDlgItem(IDC_LABEL)->MoveWindow(&rc);
	m_lblWnd.SetLabelFont (pMainDoc->m_FontMap[_T("Dialogs")].get());
	m_lblWnd.SetText ("Сдача:");
	GetDlgItem(IDC_LABEL)->SetFont(pMainDoc->m_FontMap[_T("Dialogs")].get());
	GetDlgItem(IDC_CHANGE)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top+=nDelta;
	rc.bottom +=nDelta;
	GetDlgItem(IDC_CHANGE)->MoveWindow(&rc);
	m_lblChange.SetLabelFont(pMainDoc->m_FontMap[_T("Dialogs")].get());
	m_lblChange.SetColor (RGB(255,0,0));
	m_lblChange.SetText ("0.00");

	GetDlgItem(IDOK)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top+=nDelta;
	rc.bottom +=nDelta;
	GetDlgItem(IDOK)->MoveWindow(&rc);

	GetDlgItem(IDCANCEL)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top+=nDelta;
	rc.bottom +=nDelta;
	GetDlgItem(IDCANCEL)->MoveWindow(&rc);

	GetWindowRect(&rc);
	rc.bottom +=nDelta;
	MoveWindow(&rc);
	m_flCash =pDoc->GetCurSumma() ;
	//dlg.UpdateData (TRUE);
	UpdateData(FALSE);

//	SetWindowText(m_strCaption);
	// TODO: Add extra initialization here
	dc.SelectObject (pOldFont);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEnterCash::OnChangeCash() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	float flDelta=m_flCash-pDoc->GetCurSumma() ;
	CString strChange;
	strChange.Format(_T("%.2f"),flDelta);
	m_lblChange.SetText (strChange);
	// TODO: Add your control notification handler code here
	
}


int CDlgEnterCash::DoModal() 
{
   CDialogTemplate dlt;
   int             nResult;
   // load dialog template
   if (!dlt.Load(MAKEINTRESOURCE(CDlgEnterCash::IDD))) return -1;
   CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
   LOGFONT logFont;
   pMainDoc->m_FontMap[_T("Dialogs")]->GetLogFont(&logFont);
   DWORD szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
   CString strFontName(logFont.lfFaceName);
   dlt.SetFont(strFontName, LOWORD(szFont));
	
   // get pointer to the modified dialog template
   LPSTR pdata = (LPSTR)GlobalLock(dlt.m_hTemplate);
	
   // let MFC know that you are using your own template
   m_lpszTemplateName = NULL;
   InitModalIndirect(pdata);
   // display dialog box
   nResult = CDialog::DoModal();
   // unlock memory object
   GlobalUnlock(dlt.m_hTemplate);
   return nResult;	
}

void CDlgEnterCash::OnOk() 
{
	UpdateData(TRUE);	// TODO: Add your control notification handler code here
if(m_flCash < pDoc->GetCurSumma() )
	{
	AfxMessageBox(_T("Сумма наличных меньше суммы чека!!!"),MB_ICONSTOP|MB_TOPMOST | MB_SETFOREGROUND | MB_OK );
	CEdit* pWnd=(CEdit*)GetDlgItem(IDC_CASH);
		pWnd->SetSel (0,-1);
		pWnd->Clear ();
		//pWnd->SendMessage(WM_CLEAR);
		pWnd->SetFocus ();	
	}
	else
	{
		
		CDialog::OnOK();
	}
}