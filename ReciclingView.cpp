// ReciclingView.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ReciclingView.h"
//#include "UserThreadsDoc.h"
//#include "ChildFrm.h"
#include "MainChildFrame.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReciclingView

IMPLEMENT_DYNCREATE(CReciclingView, CFormView)

CReciclingView::CReciclingView()
	: CFormView(CReciclingView::IDD)
{
	//{{AFX_DATA_INIT(CReciclingView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CReciclingView::~CReciclingView()
{
}

void CReciclingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReciclingView)
	DDX_Control(pDX, IDC_LABEL, m_Label);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReciclingView, CFormView)
	//{{AFX_MSG_MAP(CReciclingView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReciclingView diagnostics

#ifdef _DEBUG
void CReciclingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CReciclingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReciclingView message handlers

BOOL CReciclingView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	cAnimCtrl.Stop();
   cAnimCtrl.Close();	
	return CFormView::DestroyWindow();
}

void CReciclingView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
//	CUserThreadsDoc* pDoc=(CUserThreadsDoc*)GetDocument();	
	// TODO: Add your specialized code here and/or call the base class
	m_Label.SetLabelFont (_T("Arial"),24);
	m_Label.SetColor (RGB(255,10,0));
	m_Label.SetText (_T("Recicling View"));
	
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	AfxSetWindowText(pFrame->m_hWnd ,_T("Списание товара в брак"));

	

   // Create the animation control.
	if (!cAnimCtrl.Create(WS_CHILD|WS_VISIBLE|ACS_CENTER|ACS_TRANSPARENT, 
      CRect(10,10,500,500), this, 1))
         return ;

   // Open the AVI file.
   if (!cAnimCtrl.Open(IDR_ANIMATION))
      return ;

	if (!cAnimCtrl.Play(0, (UINT)-1, (UINT)-1))
               return ;

	CToolBar* pBar = pFrame->GetToolBar(IDR_RETURN);
	if (pBar != NULL)
	{
		pFrame->ShowControlBar(pBar, FALSE, FALSE);
		return ;
	}

}


