// KategoryTree.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "CategoryTree.h"
#include "SuperTree.h"
#include "InfoConsole.h"
#include "DictGoodsFrame.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategoryTree

IMPLEMENT_DYNCREATE(CCategoryTree, CTreeView)

CCategoryTree::CCategoryTree()
{
}

CCategoryTree::~CCategoryTree()
{
}


BEGIN_MESSAGE_MAP(CCategoryTree, CTreeView)
	//{{AFX_MSG_MAP(CCategoryTree)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GETINFO_FROMNODE,OnGetInfoFromNode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCategoryTree drawing

void CCategoryTree::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCategoryTree diagnostics

#ifdef _DEBUG
void CCategoryTree::AssertValid() const
{
	CTreeView::AssertValid();
}

void CCategoryTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCategoryTree message handlers

int CCategoryTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP |
		TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	
	// Create the list control.  Don't worry about specifying
	// correct coordinates.  That will be handled in OnSize()
	BOOL bResult = m_TreeCtrl.Create(dwStyle, CRect(0,0,0,0),
		this, IDC_CATEGORY_TREE);


	return (bResult ? 0 : -1);
}

void CCategoryTree::OnSize(UINT nType, int cx, int cy) 
{
	CTreeView::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_TreeCtrl.GetSafeHwnd ()))
  m_TreeCtrl.MoveWindow(0, 0, cx, cy, TRUE);
	
}

LRESULT CCategoryTree::OnGetInfoFromNode(WPARAM wParam,LPARAM lParam)
{
	CTreeNode* pNode=reinterpret_cast<CTreeNode*>(wParam);
	//m_blItemHasChilren =(BOOL)lParam;
	CString code;
	BOOL blFillCategory;

	code=pNode->item.code.c_str()   ;
	//TCHAR buff[_MAX_PATH];
	//memset(buff,0,sizeof(buff));
	//_itot(id,buff,10);
	CString strSQL;
	if(pNode->firstChild )
	{
		blFillCategory=TRUE;
		strSQL="Select CODE,NAME,PCODE From catalog Where PCODE='";
		strSQL=strSQL/*+code+"' And PCODE<>'" */+code+"'";
	}
	else
	{
		blFillCategory=FALSE;
		strSQL.LoadString(IDS_QUERY_GOODS_FROM_PARTID);
		CString strFilter;
		strFilter.LoadString(IDS_FILTER_GOODS_FROM_PARTID);
		strSQL+=strFilter+"'"+code+"'";
	}
	CDBDoc* pDoc=(CDBDoc*)GetDocument();
	pDoc->m_strSQL=strSQL;
	pDoc->UpdateAllViews (this,LPARAM(blFillCategory),NULL);
	return 0L;

}

CDBDoc* CCategoryTree::GetDocument()
{
	CSplitterWnd* pWnd=static_cast<CSplitterWnd*>(GetParent());
	CDialogView* pView=static_cast<CDialogView*>(pWnd->GetPane (0,1));
	CDBDoc* pDoc=pView->GetDocument();
	return (CDBDoc*)pDoc;
}


void CCategoryTree::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
		// TODO: Add your message handler code here

	CDBDoc* pDBDoc=(CDBDoc*)GetDocument();
	if(pDBDoc!=NULL)
	{
		static CFont font;
		font.CreatePointFont (pDBDoc->GetFontSize ()*10,pDBDoc->GetFontName ());
		m_TreeCtrl.SetFont (&font);
	}
}
void CCategoryTree::OnInitialUpdate ()
{
	
	
	CDBDoc* pDBDoc=(CDBDoc*)GetDocument();
	if(pDBDoc!=NULL)
	{
		
		m_TreeCtrl.Init ();
		static CFont font;
		font.CreatePointFont (pDBDoc->GetFontSize ()*10,pDBDoc->GetFontName ());
		m_TreeCtrl.SetFont (&font);
	}
}


void CCategoryTree::OnClose() 
{

	
	//CTreeView::OnClose();
	return;
}