// DictGoodsFrame.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DictGoodsFrame.h"
#include "CategoryTree.h"
#include "FindView.h"
#include "InfoFrame.h"
#include "InfoConsole.h"
#include "DBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FOLDER_VIEW  31
#define FINDER_VIEW  32
/////////////////////////////////////////////////////////////////////////////
// CDictGoodsFrame
const int NBUTTONS = 2;

// This table is used to load the buttons
// One table is worth a thousand lines of code (well, a lot, anyway)
// Use tables!!!
//
static struct {
	UINT id;										 // command ID
	UINT style;									 // button style
	UINT iImage;								 // index of image in normal/hot bitmaps

} Buttons[NBUTTONS] = {

	// command ID					button style						image index
	{ ID_FOLDER_VIEW_SHOW,	TBSTYLE_BUTTON,							0 },
	{ ID_FIND_VIEW_SHOW,	TBSTYLE_BUTTON,							1 }

};
IMPLEMENT_DYNCREATE(CDictGoodsFrame, CMDIChild)

CDictGoodsFrame::CDictGoodsFrame()
{
}

CDictGoodsFrame::~CDictGoodsFrame()
{
}


BEGIN_MESSAGE_MAP(CDictGoodsFrame, CMDIChild)
	//{{AFX_MSG_MAP(CDictGoodsFrame)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_COMMAND(ID_FOLDER_VIEW_SHOW, OnFolderViewShow)
	ON_UPDATE_COMMAND_UI(ID_FOLDER_VIEW_SHOW, OnUpdateFolderViewShow)
	ON_COMMAND(ID_FIND_VIEW_SHOW, OnFindViewShow)
	ON_UPDATE_COMMAND_UI(ID_FIND_VIEW_SHOW, OnUpdateFindViewShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDictGoodsFrame message handlers

BOOL CDictGoodsFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRect r;
	GetWindowRect(r);
	// create a splitter with 1 row, 2 columns
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}


	UINT u_IDVIEW=m_wndSplitter.IdFromRowCol(0, 0);	
   m_wndSplitter.AddSwitchableView(u_IDVIEW,
            RUNTIME_CLASS(CCategoryTree) ,pContext, CRect(0,0,r.Width(), r.Height()) ,
			true , FOLDER_VIEW);


   m_wndSplitter.AddSwitchableView(FINDER_VIEW, 
			RUNTIME_CLASS( CFindView), pContext,
			CRect(0,0,r.Width(), (int)(r.Height()*0.60)) );
   	if (!m_wndSplitter.CreateView(0, 1,
	pContext->m_pNewViewClass	, CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
      m_wndSplitter.SetColumnInfo(0,(int)(r.Width()*0.33), 50);
   m_wndSplitter.RecalcLayout();

return TRUE;
}

void CDictGoodsFrame::OnClose() 
{
	CInfoFrame* pFrame=static_cast<CInfoFrame*>(AfxGetMainWnd());
	POSITION tmpPos;
	POSITION pos = pFrame->m_lsForms.GetHeadPosition();
	while( pos != NULL )
	{
		tmpPos=pos;

		CString szCmp = pFrame->m_lsForms.GetNext( pos );
		
		if (szCmp == _T("DictionaryForm")) 
		{
			pFrame->m_lsForms.RemoveAt (tmpPos);
		}
	
	}
	CMDIChild::OnClose();
}

int CDictGoodsFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if(!LoadToolBar(ID_DLG_TOOLBAR,this))
		return -1;
	m_uCurrentButton=ID_FOLDER_VIEW_SHOW;
	return 0;
}

BOOL CDictGoodsFrame::LoadToolBar(UINT IDD, CWnd *parentWnd)
{
	CRect rectOld;
	CRect rectNew;
	CRect rect;
	CPoint ptOffset;
	CWnd *pWndCtrl;
	parentWnd->GetClientRect(&rectOld);
		if (!m_wndToolBar.CreateEx(parentWnd, TBSTYLE_FLAT|TBSTYLE_LIST, WS_CHILD | WS_VISIBLE | CBRS_TOP
	| CBRS_TOOLTIPS | CBRS_FLYBY  ) )
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if(!m_wndToolBar.LoadToolBar(IDD))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	TRACE0("1 create toolbar\n");
	//m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle()|CBRS_TOOLTIPS|CBRS_FLYBY);
	
	parentWnd->RepositionBars
		(
		AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST,
		0,
		CWnd::reposQuery,
		rectNew
		);
	ptOffset.x=rectNew.left -rectOld.left;
	ptOffset.y=rectNew.top-rectOld.top;
	pWndCtrl=parentWnd->GetWindow (GW_CHILD);
	
	while(pWndCtrl)
	{
		pWndCtrl->GetWindowRect (rect);
		parentWnd->ScreenToClient(rect);
		rect.OffsetRect(ptOffset);
		pWndCtrl->MoveWindow (rect,FALSE);
		pWndCtrl=pWndCtrl->GetNextWindow();
	}
	parentWnd->GetWindowRect(rect);
	rect.right +=rectOld.Width ()-rectNew.Width ();
	rect.bottom +=rectOld.Height ()-rectNew.Height ();
	parentWnd->MoveWindow(rect);
	parentWnd->RepositionBars
		(
		AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST,
		0);
	CSize szImage(16,16);
	CSize szMargin(45,7);//for button labels
	CImageList il;
	VERIFY(il.Create (szImage.cx ,szImage.cy ,ILC_COLOR8|ILC_MASK,4,szMargin.cx ));
	il.SetBkColor (TRANSPARENT);

	HICON hIcon[2];
	int n;
	hIcon[0]=AfxGetApp()->LoadIcon (IDI_CLOSEFOLDER);
	hIcon[1]=AfxGetApp()->LoadIcon (IDI_FIND);
	for(n=0;n<2;n++)
		il.Add (hIcon[n]);

	m_wndToolBar.SetSizes (szImage+szMargin,szImage);

	m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)il.Detach());

	m_wndToolBar.SetButtons(NULL, NBUTTONS);
	for (int i=0; i<NBUTTONS; i++) {
		m_wndToolBar.SetButtonInfo(i,
			Buttons[i].id,						 // command id
			Buttons[i].style,					 // buttons style
			Buttons[i].iImage);	                 // index of image in bitmap
			m_wndToolBar.SetButtonText (i,_T(" "));//set text later in OnUpdateViewInfoconsole
	}
	
	return TRUE;
}

void CDictGoodsFrame::OnFolderViewShow() 
{
	// TODO: Add your command handler code here
		m_wndSplitter.SwitchView(FOLDER_VIEW,0,0);
	m_uCurrentButton=ID_FOLDER_VIEW_SHOW;
	
}

void CDictGoodsFrame::OnUpdateFolderViewShow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
pCmdUI->SetRadio(pCmdUI->m_nID==m_uCurrentButton);	
}

void CDictGoodsFrame::OnFindViewShow() 
{
	// TODO: Add your command handler code here
	m_wndSplitter.SwitchView(FINDER_VIEW,0,0);
	m_uCurrentButton=ID_FIND_VIEW_SHOW;	
}

void CDictGoodsFrame::OnUpdateFindViewShow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CString msg1,msg2;
	msg1.LoadString(ID_FOLDER_VIEW_SHOW);
	msg2.LoadString(ID_FIND_VIEW_SHOW);
	m_wndToolBar.SetButtonText (0,msg1);	
	m_wndToolBar.SetButtonText (1,msg2);
	pCmdUI->SetRadio(pCmdUI->m_nID==m_uCurrentButton);
	//HKL hKL=GetKeyboardLayout (0);
	WORD wdLId=LOWORD(GetKeyboardLayout (0));
	CInfoFrame* pFrame=static_cast<CInfoFrame*>(AfxGetMainWnd());
	switch(wdLId)
	{
	case 0x0419://RUS
		pFrame->m_strStatusBarInfoLang ="RUS";
		break;
	default:
		pFrame->m_strStatusBarInfoLang ="LAT";
	}
}




