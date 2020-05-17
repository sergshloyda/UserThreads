// ReportView.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "ReportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportView

IMPLEMENT_DYNCREATE(CReportView, CFolderView)

CReportView::CReportView()
{

	pReport=NULL;
}

CReportView::~CReportView()
{
	delete pReport;
}


BEGIN_MESSAGE_MAP(CReportView, CFolderView)
	//{{AFX_MSG_MAP(CReportView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportView drawing

void CReportView::OnInitialUpdate()
{
	CFolderView::OnInitialUpdate();
	
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	
	GetFolderFrame()->ShowControls(TRUE ?
		CFolderFrame::bestFit : CFolderFrame::hide);
	
	
	
	CDBDoc* pDoc=GetDocument();
	TRACE0("Show Reportage\n");

	pReport->SetPropertyQuery  (pDoc->m_strPropertyQuery  );
	pReport->SetMoveQuery(pDoc->m_strMoveQuery );
	pReport->LoadMove();
	pReport->ShowReport (CReport::rprtPropertyView);

	pReport->GetGridSize (&sizeTotal);
	CClientDC dc(this);
	CSize szTwPerPixel;
	szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	sizeTotal.cx /=szTwPerPixel.cx;
	sizeTotal.cy /=szTwPerPixel.cy;
	
	SetScrollSizes(MM_TEXT, sizeTotal);

}

void CReportView::OnDraw(CDC* pDC)
{
//	CDBDoc* pDoc = GetDocument();
	// TODO: add draw code here


}

/////////////////////////////////////////////////////////////////////////////
// CReportView diagnostics

#ifdef _DEBUG
void CReportView::AssertValid() const
{
	CFolderView::AssertValid();
}

void CReportView::Dump(CDumpContext& dc) const
{
	CFolderView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportView message handlers


int CReportView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFolderView::OnCreate(lpCreateStruct) == -1)
		return -1;
	 pReport=new CReport(FALSE,this);
	// TODO: Add your specialized creation code here

	CDBDoc* pDoc=GetDocument();
	if(!pReport->CreateGrid (_bstr_t(pDoc->GetFontName ()),pDoc->GetFontSize ()))
		return -1;
	pDoc->AddView (this);
	return 0;
}

void CReportView::OnSize(UINT nType, int cx, int cy) 
{
	CFolderView::OnSize(nType, cx, cy);

	//GetClientRect(&rc);
/*	if(pReport->IsSubclassed () )
	{
	pReport->GetWindowRect(&rc);
	//	pReport->SendMessage (WM_SIZE);
		CSize szGrid;
		pReport->GetGridSize (&szGrid);
		CClientDC dc(this);
		CSize szTwPerPixel;
		szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
		szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
		szGrid.cx /=szTwPerPixel.cx;
		szGrid.cy /=szTwPerPixel.cy;
		if((szGrid.cx <cx)||(szGrid.cy < cy))//if client area more then grid size
			pReport->MoveWindow (0,0,cx ,szGrid.cy,TRUE);
		else
			pReport->MoveWindow (0,0,szGrid.cx ,szGrid.cy,TRUE);
			SetScrollSizes(MM_TEXT, szGrid);
	}
	
//pReport->MoveWindow (&rc);
	// TODO: Add your message handler code here
	  
     }
*/	if (pReport->IsSubclassed ())
     {
         // need to push non-client borders out of the client area
         CRect rect;

         GetClientRect(rect);
         ::AdjustWindowRectEx(rect,
             pReport->GetStyle(), FALSE, WS_EX_CLIENTEDGE);
		 CSize szGrid;
		pReport->GetGridSize (&szGrid);
		CClientDC dc(this);
		CSize szTwPerPixel;
		szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
		szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
		szGrid.cx /=szTwPerPixel.cx;
		szGrid.cy /=szTwPerPixel.cy;
		
         pReport->SetWindowPos(NULL, rect.left-GetScrollPos(SB_HORZ), rect.top-GetScrollPos(SB_VERT),
            max(szGrid.cx,rect.Width ()), max(szGrid.cy,rect.Height ()), SWP_NOACTIVATE | SWP_NOZORDER);
	 
	 
	 }

	
}
CDBDoc* CReportView::GetDocument()
{
	CDocument* pDoc=((CFrameWnd*) (AfxGetThread()->m_pMainWnd))->GetActiveDocument();
	return (CDBDoc*)pDoc;
}

void CReportView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDBDoc* pDBDoc=GetDocument();
	if(pDBDoc!=NULL)
	{
	pReport->m_spGrid ->put_FontName ((_bstr_t)pDBDoc->GetFontName () );
	pReport->m_spGrid ->put_FontSize ((float)pDBDoc->GetFontSize ());
	}
}
 void CReportView::OnChangedFolder(int iPage)
 {
	 CDBDoc* pDoc=GetDocument();
	 CSize sizeTotal;
	 if(iPage==0)
	 {
		 
		 //pReport->SetPropertyQuery (pDoc->m_strPropertyQuery );
		 pReport->ShowReport (iPage);
		 
		 
	 }
	 
	 else
	 {
		 pReport->m_blIsDataSheet =TRUE;
		 CString strHead;
		 	CString strFormat;
	strFormat.LoadString (IDS_FORMAT_DATE);
		 strHead.Format (IDS_HEAD_FOR_MOVE_GOODS,pDoc->m_strHead ,
			 pDoc->m_dtStart.Format(_T("%d/ %m/ %Y")),pDoc->m_dtEnd.Format (_T("%d/ %m/ %Y")));
		 pReport->PrepareHeadString (strHead );
		 //pReport->SetMoveQuery (pDoc->m_strMoveQuery );
		 pReport->ShowReport (iPage);
		 
	 }
	 pReport->GetGridSize (&sizeTotal);
	 CClientDC dc(this);
	 CSize szTwPerPixel;
	 szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	 szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	 sizeTotal.cx /=szTwPerPixel.cx;
	 sizeTotal.cy /=szTwPerPixel.cy;
	 POINT pt;
	 pt.x =0;
	 pt.y=0;
	 ScrollToPosition(pt);//set scroll to origin window
	 SetScrollSizes(MM_TEXT, sizeTotal);
	 CRect rc;
	 GetClientRect(&rc);
	 pReport->MoveWindow (0,0,max(sizeTotal.cx,rc.Width ()) ,max(sizeTotal.cy,rc.Height ()),TRUE);
 }


