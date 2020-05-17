// RetView.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "RetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRetView

IMPLEMENT_DYNCREATE(CRetView, CFormView)

CRetView::CRetView()
	: CFormView(CRetView::IDD)
{
	//{{AFX_DATA_INIT(CRetView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CRetView::~CRetView()
{
}

void CRetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRetView)
	DDX_Control(pDX, IDC_TOOLBARPLACE, m_wndToolBarHolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRetView, CFormView)
	//{{AFX_MSG_MAP(CRetView)
	ON_BN_CLICKED(IDC_BTNEXEC, OnBtnexec)
	ON_BN_CLICKED(IDC_BTNSELDOC, OnBtnseldoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRetView diagnostics

#ifdef _DEBUG
void CRetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRetView message handlers

void CRetView::OnBtnexec() 
{
	// TODO: Add your control notification handler code here
	
}

void CRetView::OnBtnseldoc() 
{
	// TODO: Add your control notification handler code here
	
}
