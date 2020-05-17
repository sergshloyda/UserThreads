// ReportWnd.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ReportWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportWnd

CReportWnd::CReportWnd()
{
}

CReportWnd::~CReportWnd()
{
}


BEGIN_MESSAGE_MAP(CReportWnd, CWnd)
	//{{AFX_MSG_MAP(CReportWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReportWnd message handlers

BOOL CReportWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::PreCreateWindow(cs);
}

void CReportWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
