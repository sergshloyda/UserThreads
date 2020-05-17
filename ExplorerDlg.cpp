// ExplorerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ExplorerDlg.h"
//#include "userthreadsdoc.h"
#include "InfoConsole.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExplorerDlg dialog


CExplorerDlg::CExplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExplorerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExplorerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pAssocView=pParent;
}


void CExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExplorerDlg)
	DDX_Control(pDX, IDC_TREE1, m_STreeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExplorerDlg, CDialog)
	//{{AFX_MSG_MAP(CExplorerDlg)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GETINFO_FROMNODE,OnGetInfoFromNode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExplorerDlg message handlers

BOOL CExplorerDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();
	
	CInfoConsole* pThread=(CInfoConsole*)AfxGetThread();
	ASSERT(pThread!=NULL);
	CMainDocument* pDoc=(CMainDocument*)pThread->m_pDocument;
	m_STreeCtrl.Init ();
	m_STreeCtrl.SetAssociatedView ((CWnd*)this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CExplorerDlg::OnGetInfoFromNode (WPARAM wParam,LPARAM lParam)
{
	m_pNode=reinterpret_cast<CTreeNode*>(wParam);
//	BOOL  m_blItemHasChilren =(BOOL)lParam;
	SetDlgItemText(IDC_STATIC1,m_STreeCtrl.strFullPath );
	return 0L;
}
