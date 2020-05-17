// DlgMultQty.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgMultQty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMultQty dialog


CDlgMultQty::CDlgMultQty(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMultQty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMultQty)
	m_nQty = 1;
	//}}AFX_DATA_INIT
}


void CDlgMultQty::DoDataExchange(CDataExchange* pDX)
{
	CString strSection       = "";
	CString strStringItem    = "MaxQtyMul";
	
	int nMaxQty=AfxGetApp()->GetProfileInt (strSection,strStringItem,10);
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMultQty)
	
	DDX_Text(pDX, IDC_EDIT1, m_nQty);
	DDV_MinMaxInt(pDX, m_nQty, 1, nMaxQty); 
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(CDlgMultQty, CDialog)
	//{{AFX_MSG_MAP(CDlgMultQty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMultQty message handlers

BOOL CDlgMultQty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	CWnd* pEdit=GetDlgItem (IDC_EDIT1);

	CClientDC dc(this);
	/*m_Font.CreatePointFont (pDoc->GetFontSize ()*10,pDoc->GetFontName());*/
	pEdit->SetFont(pDoc->m_FontMap[_T("Dialogs")].get());
	
	CFont* pOldFont=dc.SelectObject (pDoc->m_FontMap[_T("Dialogs")].get());
	TEXTMETRIC tm;
	dc.GetTextMetrics (&tm);
	int  nHeight=tm.tmHeight+tm.tmHeight/4  ; 
	CRect rc;
	pEdit->GetWindowRect (&rc);
	ScreenToClient(&rc);
	
	rc.bottom=rc.top + nHeight;
	
	pEdit->MoveWindow (&rc);
	pEdit->SendMessage (EM_SETSEL,0,-1);
	pEdit->SetFocus ();
	
	dc.SelectObject (pOldFont);
	// TODO: Add extra initialization here
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
