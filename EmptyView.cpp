// EmptyView.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "EmptyView.h"
//#include "UserThreadsDoc.h"
#include "UserThreadsView.h"
#include "CheckDoc.h"
#include "MainFrm.h"
#include "MainChildFrame.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmptyView

IMPLEMENT_DYNCREATE(CEmptyView, CView)

CEmptyView::CEmptyView()
{
}

CEmptyView::~CEmptyView()
{
}


BEGIN_MESSAGE_MAP(CEmptyView, CView)
	//{{AFX_MSG_MAP(CEmptyView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmptyView drawing

void CEmptyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CEmptyView diagnostics

#ifdef _DEBUG
void CEmptyView::AssertValid() const
{
	CView::AssertValid();
}

void CEmptyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEmptyView message handlers

void CEmptyView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	
	CRuntimeClass* pNewDocClass;
	pNewDocClass = RUNTIME_CLASS(CCheckDoc);
	CCheckDoc* pDoc=static_cast <CCheckDoc*>(pNewDocClass->CreateObject ());
	pDoc->OnNewDocument ();

    CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CDocManager* pDM=pApp->m_pDocManager;
	POSITION posTempl=
	pDM->GetFirstDocTemplatePosition ();
	//we have 1 DocTemplate
	CDocTemplate* pTempl=pDM->GetNextDocTemplate (posTempl);
	pTempl->AddDocument (pDoc);

	
	
	return ;
}
