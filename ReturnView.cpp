// ReturnView.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ReturnView.h"
#include "DlgSelDate.h"
#include "MainChildFrame.h"
#include "DlgSetQuantity.h"
#include "PSDlgInsertGood.h"
#include "MDIClient.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define NBUTTONS 3
/////////////////////////////////////////////////////////////////////////////
// CReturnView
static struct {
	UINT id;										 // command ID
	UINT style;									 // button style
	UINT iImage;								 // index of image in normal/hot bitmaps

} Buttons[NBUTTONS] = {

	// command ID					button style						image index
	{ ID_SEL1GOOD, 	   TBSTYLE_BUTTON, 0 },
	{ ID_SELALLGOODS,  TBSTYLE_BUTTON, 1 },
	{ ID_UNDOALLGOODS, TBSTYLE_BUTTON, 2 }

};
static CString szGoodsGridName=	_T("ReturnGoodGrid");
IMPLEMENT_DYNCREATE(CReturnView, CFormView)

CReturnView::CReturnView()
	: CFormView(CReturnView::IDD)
{
	//{{AFX_DATA_INIT(CReturnView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_strSelDocId=_T("");
	m_blSelectCheck=FALSE;
}

CReturnView::~CReturnView()
{
}

void CReturnView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReturnView)
		DDX_Control(pDX, IDC_TOOLBARPLACE, m_wndToolBarHolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReturnView, CFormView)
	//{{AFX_MSG_MAP(CReturnView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNEXEC, OnBtnexec)
	ON_COMMAND(ID_EXECRETURN, OnExecreturn)
	ON_COMMAND(ID_SELGOOD, OnSelgood)
	ON_UPDATE_COMMAND_UI(ID_SELGOOD, OnUpdateSelgood)
	ON_COMMAND(ID_DATESELECT, OnDateselect)
	ON_UPDATE_COMMAND_UI(ID_DATESELECT, OnUpdateDateselect)
	ON_COMMAND(ID_SELSALEDOC, OnSelsaledoc)
	ON_UPDATE_COMMAND_UI(ID_SELSALEDOC, OnUpdateSelsaledoc)
	ON_COMMAND(ID_SEL1GOOD, OnSel1good)
	ON_COMMAND(ID_SELALLGOODS, OnSelallgoods)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_SEL1GOOD, OnUpdateSel1good)
	ON_UPDATE_COMMAND_UI(ID_SELALLGOODS, OnUpdateSelallgoods)
	ON_COMMAND(ID_UNDOALLGOODS,OnUndoAllGoods)
	ON_UPDATE_COMMAND_UI(ID_UNDOALLGOODS, OnUpdateUndoAllGoods)
	ON_BN_CLICKED(IDC_BTNPODBOR, OnBtnpodbor)
	ON_WM_COPYDATA()
	ON_UPDATE_COMMAND_UI(ID_EXECRETURN, OnUpdateExecReturn)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()



BEGIN_EVENTSINK_MAP(CReturnView, CFormView)
    //{{AFX_EVENTSINK_MAP(CMFCDataDlg)
	ON_EVENT(CReturnView, IDC_DOCLIST, 82 /* AfterDataRefresh */, OnGridDocsAfterDataRefresh, VTS_NONE)
	ON_EVENT(CReturnView, IDC_DOCLIST, -601 /* DblClick */, OnGridDocsDblClickGrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT(CReturnView, IDC_DOCLIST, 0x00000003 /* EnterCell */, OnGridDocsEnterCell, VTS_NONE)
	ON_EVENT(CReturnView, IDC_ENTRYDOC, 82 /* AfterDataRefresh */, OnGridGoodsAfterDataRefresh, VTS_NONE)
	ON_EVENT(CReturnView, IDC_RETGOODS, 82 /* AfterDataRefresh */, OnReturnAfterDataRefresh, VTS_NONE)
	ON_EVENT(CReturnView, IDC_ENTRYDOC, 0x00000012 /* AfterUserResize */, OnGridGoodsAfterResizeColumn, VTS_I4 VTS_I4)
	END_EVENTSINK_MAP()
/////////////////////////////////////////////////////////////////////////////
// CReturnView diagnostics

#ifdef _DEBUG
void CReturnView::AssertValid() const
{
	CFormView::AssertValid();
}

void CReturnView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReturnView message handlers

CReturnDoc* CReturnView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReturnDoc)));
	return (CReturnDoc*)m_pDocument;
}

BOOL CReturnView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//DebugBreak();	
	WriteGridPlacement();
	return CFormView::DestroyWindow();
}

void CReturnView::OnInitialUpdate() 
{
	OutputDebugString (_T("CReturnView::OnInitialUpdate"));
	CFormView::OnInitialUpdate();
	CReturnDoc* pDoc=GetDocument();
	CString strTitle="";
	strTitle.Format (_T("Возврат товара от покупателя №: %s"),pDoc->m_strDocId);
	SetTitle(strTitle);
			//Setup Initial Grid View
//	m_tmDateView=COleDateTime::GetCurrentTime ();
	pDoc->SetDate(&(COleDateTime::GetCurrentTime ()));
	LoadToolbar();
	
	SetupGrids();
	
	
	//сделаем доступным подбор только в отладочной версии
#ifndef _DEBUG
	GetDlgItem(IDC_BTNPODBOR)->ShowWindow(SW_HIDE);
#endif
	
	
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	CToolBar* pBar = pFrame->GetToolBar(IDR_RETURN);
	if (pBar != NULL)
	
		pFrame->ShowControlBar(pBar, TRUE, FALSE);
	

	GetParentFrame()->RecalcLayout();
	int nDocsGridHeight=ReadDocsGridPlacement ();
	RepositionControls(nDocsGridHeight);

	WINDOWPLACEMENT wndPlmnt;
	// Get the window placements of each toolbar holder
	// and set each toolbar to its correspondent area.
	m_wndToolBarHolder.GetWindowPlacement(&wndPlmnt);
	m_wndSelGoodToolBar.GetToolBarCtrl().SetWindowPlacement(&wndPlmnt);/**/
	try
	{
		_RecordsetPtr pRst;
		TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
		
		BOOL blRes=pDoc->LoadAllChecksOnDate (&pRst);
		if((pRst!=NULL)&&(blRes))
		{
			TRACE1("%d\n",pRst->GetRecordCount ());
			m_wndGridDocs.LoadRecordset (pRst);
			TESTHR(pRst->Close());
		}
		else
		{
			m_wndGridDocs.Clear (_variant_t(0L),variant_t(0L));
			m_wndGridDocs.SetRowHidden (m_wndGridDocs.GetFixedRows ()-1,TRUE);
			m_wndGridGoods.SetRowHidden (m_wndGridGoods.GetFixedRows ()-1,TRUE);
			m_wndGridSelGoods.SetRowHidden (m_wndGridSelGoods.GetFixedRows ()-1,TRUE);
		}

	}
	catch(...)
	{
		MessageBoxHelper::ShowError(_T("Error in OnInitialUpdate"));
	}
	m_lblInfoDocNum.Create (NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_INFONUMRETURN);
	m_lblInfoBaseDoc.Create (NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_INFOBASERETURN);
	m_lblInfoNumPos.Create (NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_INFONPOSRETURN);
	m_lblInfoNumUnits.Create (NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_INFONUNITSRETURN);
	m_lblInfoSumma.Create (NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_INFOSUMMARETURN);
	
	m_fntLabel.CreatePointFont (100,_T("Arial"));
	m_lblInfoDocNum.SetLabelFont (&m_fntLabel);
	m_lblInfoBaseDoc.SetLabelFont (&m_fntLabel);
	m_lblInfoBaseDoc.SetColor (RGB(0,0,255));
	m_lblInfoNumPos.SetLabelFont (&m_fntLabel);
	m_lblInfoNumUnits.SetLabelFont (&m_fntLabel);
	static CFont boldFont;
	VERIFY(boldFont.CreateFont(
		28,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		TRUE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial")));                 
	m_lblInfoSumma.SetLabelFont (&boldFont);
	m_lblInfoSumma.SetColor (RGB(255,78,78));
}

void CReturnView::SetTitle(LPCTSTR strNewTitle)
{
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	AfxSetWindowText(pFrame->m_hWnd ,strNewTitle);
}

void CReturnView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RepositionControls();
	
	
}

void CReturnView::RepositionControls(int nGridDocHeight)
{
	CRect rcCaption;
	CRect rcEdit;
	CRect rcGridDocs;
	CRect rcClient;
	CRect rcBtnSelDoc;
	CRect rcBtnSelGood;
	CRect rcGridGoods;
	CRect rcGridSelGoods;
	CRect rcInfo;
	CRect rcBtnExec;
	const CSize szBorder(4,6);
	
	GetClientRect(&rcClient);
	
	
	rcClient.DeflateRect (szBorder);
	
	
	if(IsWindow (m_wndGridDocs.GetSafeHwnd()))
	{
		m_wndGridDocs.GetClientRect(&rcGridDocs);
		if(nGridDocHeight<0)nGridDocHeight=rcGridDocs.bottom ;
		rcGridDocs=rcClient;
		//rcGridDocs.top =rcEdit.bottom + szBorder.cy;
	rcGridDocs.bottom =rcGridDocs.top +nGridDocHeight+szBorder.cy ;
	
	

		//rcGridDocs.bottom =	rcGridDocs.top+200;
		
		m_wndGridDocs.MoveWindow(rcGridDocs);

		
	}
	if(IsWindow(GetDlgItem(IDC_TOOLBARPLACE)->GetSafeHwnd()))
	{
		//CRect rc;
		GetDlgItem(IDC_TOOLBARPLACE)->GetWindowRect(&rcBtnSelGood);
		
	}
	if(IsWindow (m_wndGridGoods.GetSafeHwnd()))
	{
		CRect rc;
		rcGridGoods=rcClient;
		rcGridGoods.top =rcGridDocs.bottom + szBorder.cy;
		rcGridGoods.right =	rcClient.Width ()/2-rcBtnSelGood.Width ()/2-szBorder.cx ;
		m_wndGridGoods.MoveWindow(rcGridGoods);
		
		rc=rcGridGoods;
		rc.left =rcGridGoods.right;
		rc.right =rc.left +30;
		GetDlgItem(IDC_TOOLBARPLACE)->MoveWindow(&rc);
		
		
		rcBtnSelGood=rc;
		m_rcResizeArea = rcClient;
		m_rcResizeArea.top  = rcGridDocs.bottom;
		m_rcResizeArea.bottom = rcGridGoods.top;
		
		

	}
	
	
	
	if(IsWindow (m_wndGridSelGoods.GetSafeHwnd()))
	{
		CRect rc;
		rcGridSelGoods=rcClient;
		rcGridSelGoods.top =rcGridDocs.bottom + szBorder.cy;
		rcGridSelGoods.left =rcBtnSelGood.right;
		GetDlgItem(IDC_INFO)->GetWindowRect(&rcInfo);
		rc=rcClient;
		rc.left =rcGridSelGoods.left;
		rc.top =rc.bottom -rcInfo.Height();
		rcInfo=rc;
		GetDlgItem(IDC_INFO)->MoveWindow(&rc);

	

		rcGridSelGoods.bottom =rc.top -szBorder.cy ;
		
		GetDlgItem(IDC_BTNEXEC)->GetWindowRect(&rc);
		int nHeight=rc.Height ();
		int nWidth=rc.Width ();
		rc=rcInfo;
		rc.DeflateRect (szBorder);
		rc.top =rc.bottom -nHeight;
		rc.left =rc.right -nWidth;
		GetDlgItem(IDC_BTNEXEC)->MoveWindow(&rc);
		rcBtnExec=rc;
		//rc=rcInfo;
		rc.bottom =rcBtnExec.top -szBorder.cy;
		rc.top =rc.bottom -nHeight;
		GetDlgItem(IDC_BTNPODBOR)->MoveWindow(&rc);
		m_wndGridSelGoods.MoveWindow(rcGridSelGoods);


		
	
		
	}	

}

void CReturnView::OnBtnexec() 
{
	
	CReturnDoc* pDoc=(CReturnDoc*)m_pDocument;
	pDoc->m_vtArray =m_wndGridSelGoods.GetGridArray ();
	pDoc->OnSaveDocument (NULL);	
}



void CReturnView::OnExecreturn() 
{
	CReturnDoc* pDoc=(CReturnDoc*)m_pDocument;
	pDoc->OnSaveDocument (NULL);
	
}

void CReturnView::OnSelgood() 
{
	// TODO: Add your command handler code here
OnBtnpodbor(); 
}

void CReturnView::OnUpdateSelgood(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	CToolBar*pBar=pFrame->GetToolBar(IDR_RETURN);
	pBar->SetButtonText (2,_T("Подбор  "));

	//pCmdUI->Enable (FALSE);

}

void CReturnView::OnDateselect() 
{
//	DebugBreak();
	CString	str;
	BOOL	bOK = FALSE;
	str.Format(_T("%d/%d/%d"),COleDateTime::GetCurrentTime ().GetMonth() ,COleDateTime::GetCurrentTime ().GetDay(),COleDateTime::GetCurrentTime ().GetYear());
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	CToolBar*pBar=pFrame->GetToolBar(IDR_RETURN);
	CRect rc;
	pBar->GetItemRect (1,&rc);
	ClientToScreen(&rc);
	CDlgSelDate dlg(&str, &bOK, rc.left , rc.top ,this);
	dlg.DoModal ();
	


}

void CReturnView::OnUpdateDateselect(CCmdUI* pCmdUI) 
{
CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	CToolBar*pBar=pFrame->GetToolBar(IDR_RETURN);
	pBar->SetButtonText (1,_T("Дата продажи"));


	pBar->SetButtonText (3,_T("Оформить"));
	
}

void CReturnView::OnSelsaledoc() 
{
	// TODO: Add your command handler code here
	CReturnDoc* pDoc=(CReturnDoc*)m_pDocument;
	pDoc->m_blLoadDocs=!pDoc->m_blLoadDocs;
	m_blSelectCheck=pDoc->m_blLoadDocs;
	
	pDoc->UpdateAllViews (NULL,(pDoc->m_blLoadDocs?CReturnDoc::UpdateDocs:CReturnDoc::UpdateGoods));

}

void CReturnView::OnUpdateSelsaledoc(CCmdUI* pCmdUI) 
{
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	CToolBar*pBar=pFrame->GetToolBar(IDR_RETURN);
	CReturnDoc* pDoc=(CReturnDoc*)m_pDocument;
	if(!pDoc->m_blLoadDocs)
	{
		pBar->SetButtonText (pCmdUI->m_nIndex,_T("Продажи"));
		pBar->SetButtonInfo(pCmdUI->m_nIndex,
			pCmdUI->m_nID ,						 // command id
			pBar->GetButtonStyle (pCmdUI->m_nIndex ),					 // buttons style
			4);	
		
	}
	else 
	{
	pBar->SetButtonText (pCmdUI->m_nIndex,_T("Чеки"));
	
	pBar->SetButtonInfo(pCmdUI->m_nIndex,
		pCmdUI->m_nID ,						 // command id
		pBar->GetButtonStyle (pCmdUI->m_nIndex ),					 // buttons style
		0);
	}
	pCmdUI->SetCheck (!pDoc->m_blLoadDocs);
	
}

void CReturnView::OnSel1good() 
{
	IVSFlexGridPtr pRetGoods=m_wndGridSelGoods .GetControlUnknown ();
	IVSFlexGridPtr pEntryDoc=m_wndGridGoods.GetControlUnknown ();
	pRetGoods->PutCols(pEntryDoc->Cols-2);
	long lSelRow=pEntryDoc->Row;
	if(lSelRow<pEntryDoc->GetFixedRows ()) return;
	CString strItem="";
	int nQty=0;
	CString strQty=(LPCTSTR)pEntryDoc->GetTextMatrix (lSelRow,3L);
	nQty=_ttoi(strQty);
	COleCurrency curPrice;
	curPrice.ParseCurrency ((LPCTSTR)pEntryDoc->GetTextMatrix (lSelRow,4L));
	CDlgSetQuantity dlgQty;
	dlgQty.DoModal ();
	if(dlgQty.m_nQty >nQty)
	{
		MessageBoxHelper::ShowError(_T("Количество возвращаемого товара не может быть больше проданного"));
		return;
	}

	for(long c=pEntryDoc->GetFixedCols ();c<pEntryDoc->Cols ;c++)
	{
	
		if(c==3)
		{ 
			CString strBuff;
			strBuff.Format(_T("%d"),dlgQty.m_nQty );
			strItem+="\t";
			strItem+=strBuff;
		}
		else if(c==5)
		{
			CString strBuff;
			double dblSumma=(double)(dlgQty.m_nQty*curPrice.m_cur.int64)/10000 ;
			strBuff.Format(_T("%.2f"),dblSumma  );
			strItem+="\t";
			strItem+=strBuff;
		}
		else if((c==6)||(c==7))continue;
		else
		{
		strItem+="\t";
		strItem+=(LPCTSTR)pEntryDoc->GetTextMatrix (lSelRow,c);
		}
		
	}
	if(nQty==dlgQty.m_nQty )
	pEntryDoc->RemoveItem(lSelRow);
	else
	{
		CString strNewQty;
		strNewQty.Format(_T("%d"),nQty-dlgQty.m_nQty);
		double dblNewSumma=(double)((nQty-dlgQty.m_nQty)*curPrice.m_cur.int64)/10000;
		CString strNewSumma;
		strNewSumma.Format (_T("%.2f"),dblNewSumma);

		pEntryDoc->PutTextMatrix(lSelRow,3,(_bstr_t)strNewQty);
		pEntryDoc->PutTextMatrix(lSelRow,5,(_bstr_t)strNewSumma);
	}

	//AfxMessageBox(strItem);
	pRetGoods->AddItem((_bstr_t)strItem);
	
	
	OnReturnAfterDataRefresh();
	
}

void CReturnView::OnSelallgoods() 
{
	IVSFlexGridPtr pRetGoods=m_wndGridSelGoods .GetControlUnknown ();
	IVSFlexGridPtr pEntryDoc=m_wndGridGoods.GetControlUnknown ();

	pRetGoods->PutCols(pEntryDoc->Cols);
	//pRetGoods->PutRows(1);
	for(long r=pEntryDoc->GetFixedRows();r<pEntryDoc->Rows;r++)
	{
		CString strItem="";
		for(long c=pEntryDoc->GetFixedCols ();c<pEntryDoc->Cols ;c++)
		{
			strItem+="\t";
			strItem+=(LPCTSTR)pEntryDoc->GetTextMatrix (r,c);
			
		}
		
		pRetGoods->AddItem((_bstr_t)strItem/*,r*/);
		//pEntryDoc->RemoveItem(r);
		
		OnReturnAfterDataRefresh();
	}
	pEntryDoc->PutRows (pEntryDoc->GetFixedRows());
}
void CReturnView::OnUndoAllGoods() 
{	
	long Row=m_wndGridSelGoods.GetRow ();
	if (Row==0)return;
	_variant_t vt(0L);
	vt.lVal =Row;
	m_wndGridSelGoods.RemoveItem (vt);
	ShowInfoOnPanel ();
	CReturnDoc* pDoc=GetDocument();
	pDoc->SetModifiedFlag (FALSE);
	
}

void CReturnView::LoadToolbar()
{
if (!m_wndSelGoodToolBar.Create( this ) ||
			!m_wndSelGoodToolBar.LoadToolBar(IDR_SELGOODSTB))
	{
			TRACE0("Failed to create toolbar1\n");
			return;      // fail to create	
	}
m_wndSelGoodToolBar.SetBarStyle(CBRS_ALIGN_RIGHT | CBRS_TOOLTIPS | CBRS_FLYBY);


CSize szImage(16,16);
	CSize szMargin(7,7);//for button labels
	CImageList il;
	VERIFY(il.Create (szImage.cx ,szImage.cy ,ILC_COLOR8|ILC_MASK,2,szMargin.cx ));
	il.SetBkColor (TRANSPARENT);

	HICON hIcon[NBUTTONS];
	int n;
	hIcon[0]=AfxGetApp()->LoadIcon (IDI_RIGHTARROW);
	hIcon[1]=AfxGetApp()->LoadIcon (IDI_DBLRIGHTARROW);
	hIcon[2]=AfxGetApp()->LoadIcon (IDI_DELETE);
	for(n=0;n<NBUTTONS;n++)
		il.Add (hIcon[n]);
	
	m_wndSelGoodToolBar.SetSizes (szImage+szMargin,szImage);

	m_wndSelGoodToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)il.Detach());

	m_wndSelGoodToolBar.SetButtons(NULL, NBUTTONS+1);
	for (int i=0; i<NBUTTONS-1; i++) {
		m_wndSelGoodToolBar.SetButtonInfo(i,
			Buttons[i].id,						 // command id
			Buttons[i].style,					 // buttons style
			Buttons[i].iImage);	                 // index of image in bitmap
		
	}
	
	m_wndSelGoodToolBar.SetButtonInfo (NBUTTONS-1,0,TBBS_SEPARATOR,50);//make gap
	
	m_wndSelGoodToolBar.SetButtonInfo (NBUTTONS,ID_UNDOALLGOODS,
		TBSTYLE_BUTTON,2);//set last button

}

void CReturnView::SetupGrids()
{
//	long lCols=5;
	_variant_t v(DISP_E_PARAMNOTFOUND,VT_ERROR); 
	//V_VT(&v) = ; 
	m_wndGridDocs.CreateFromStatic (IDC_DOCLIST,this);
	HWND hwnd=m_wndGridDocs.Detach ();
	m_wndGridDocs.SubclassWindow (hwnd);
//	m_wndGridDocs.InitToolTip ();
	//m_wndGridDocs.LoadGridPlacement (AfxGetApp(),_T("ReturnDocGrid"));
	m_wndGridDocs.SetRows(1L);
	m_wndGridDocs.SetSelectionMode(flexSelectionByRow);
	m_wndGridDocs.SetAutoSizeMode (flexAutoSizeColWidth);
	m_wndGridDocs.SetAllowUserResizing (flexResizeColumns);

	m_wndGridGoods.CreateFromStatic (IDC_ENTRYDOC,this);
    hwnd=m_wndGridGoods.Detach ();
	m_wndGridGoods.SubclassWindow (hwnd);
	m_wndGridGoods.ModifyStyleEx (WS_EX_LEFTSCROLLBAR,0);
	//m_wndGridGoods.InitToolTip ();
	m_wndGridGoods.SetRows(1L);
	m_wndGridGoods.SetSelectionMode(flexSelectionByRow);
 
	m_wndGridGoods.SetAllowUserResizing(flexResizeColumns);
	m_wndGridGoods.SetAutoSizeMode (flexAutoSizeColWidth);
	

	
	m_wndGridSelGoods.CreateFromStatic (IDC_RETGOODS,this);
	hwnd=m_wndGridSelGoods.Detach ();
	m_wndGridSelGoods.SubclassWindow (hwnd);
	//m_wndGridSelGoods.InitToolTip ();
	m_wndGridSelGoods.SetRows(1L);
	m_wndGridSelGoods.SetSelectionMode(flexSelectionByRow);
 
	m_wndGridSelGoods.SetAllowUserResizing(flexResizeColumns);
	m_wndGridSelGoods.SetAutoSizeMode (flexAutoSizeColWidth);
}
 void CReturnView::OnGridDocsAfterDataRefresh() 
{
	 if(false)
		 DebugBreak();
	 CWaitCursor cur;
	 CClientDC dc(this);
	 CSize szTwPerPixel;
	 szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	 szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	 
	 COleVariant vtNone(0L, VT_ERROR);
	 
	 if (m_wndGridDocs.GetRows()<=m_wndGridDocs.GetFixedRows())
	 {
		 m_wndGridDocs.SetRowHidden(m_wndGridDocs.GetFixedRows()-1,TRUE);
		 ShowInfoOnPanel(TRUE);
		 return;
	 }
	 else
		 m_wndGridDocs.SetRowHidden(m_wndGridDocs.GetFixedRows()-1,FALSE);
		IVSFlexGridPtr pGrid=m_wndGridDocs.GetControlUnknown ();
			ASSERT(pGrid!=NULL);
	pGrid->PutRedraw (flexRDNone);
	 CReturnDoc*pDoc=GetDocument();
	 if(pDoc->m_blLoadDocs)
	 {
		 m_wndGridDocs.SetGridColor(RGB(0,0,0));
		 
    
		_variant_t colEnd(0L);
		_variant_t colBeg(0L);
		colBeg.lVal =2L;
		colEnd.lVal =m_wndGridDocs.GetCols()-1;
		
		m_wndGridDocs.SetAutoSizeMode(flexAutoSizeColWidth);

		m_wndGridDocs.SetTextMatrix (0,1,_T("Наименование документа"));
		m_wndGridDocs.SetTextMatrix (0,2,_T("Номер"));
		
		m_wndGridDocs.SetTextMatrix (0,3,_T("Дата"));	
		m_wndGridDocs.SetTextMatrix (0,4,_T("Время"));
		m_wndGridDocs.SetTextMatrix (0,5,_T("Сумма"));
		

		m_wndGridDocs.AutoSize(colBeg, colEnd, vtNone, vtNone);
		CPictureHolder picFolder;
		HICON hIcon1=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_DOCTRANSACT),
			IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
		picFolder.CreateFromIcon(hIcon1,TRUE);
		CPictureHolder picFolders;
		HICON hIcon2=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_DOCNOTRANSACT),
			IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
		picFolders.CreateFromIcon(hIcon2,TRUE);
		long wdt,ht;
		//size in HIMETRIC (0.01mm)
		picFolder.m_pPict->get_Width (&wdt);
		picFolder.m_pPict->get_Height (&ht);
		
		CSize szPict(wdt,ht);
		dc.HIMETRICtoLP (&szPict);
		//note grid size units is twips
		
		
		m_wndGridDocs.SetColWidth (0,szPict.cx *szTwPerPixel.cx +100);
		m_wndGridDocs.SetRowHeightMin (szPict.cy *szTwPerPixel.cy +20);
		m_wndGridDocs.SetFontSize (14.0);
		m_wndGridDocs.SetColWidth (1,m_wndGridDocs.GetClientWidth ()-
			(m_wndGridDocs.GetColWidth (0)+
			m_wndGridDocs.GetColWidth (2)+
			m_wndGridDocs.GetColWidth (3)+
			m_wndGridDocs.GetColWidth (4)+
			m_wndGridDocs.GetColWidth (5)));
		
		LPDISPATCH pDispFolder = picFolder.GetPictureDispatch();
		LPDISPATCH pDispFolders = picFolders.GetPictureDispatch();
	
		for(long i=1;i<m_wndGridDocs.GetRows();i++)
		{
			pGrid->put_Row (i);
			pGrid->put_Col(0);
			pGrid->put_CellPictureAlignment (flexPicAlignCenterCenter);	
			//m_wndGridDocs.SetCellPicture(pDispFolder);
			pGrid->put_CellPicture((IPictureDisp*)pDispFolder);

			pGrid->Select(i,1L,_variant_t(i),_variant_t(pGrid->Cols-1L));
			pGrid->FillStyle = flexFillRepeat;



			if(i%2)
				{
					
					pGrid->put_CellBackColor (RGB(223,223,223));
				}
				else
					
				{
					pGrid->put_CellBackColor (RGB(255,255,255));
				}
			/**/
		}
		pDispFolders->Release();
		pDispFolder->Release();
	 
		m_wndGridDocs.SetFocus ();
		m_wndGridDocs.SetCol(2);

		
		if(m_strSelDocId.GetLength()>0)
			m_wndGridDocs.SetRow(m_wndGridDocs.FindInColumn (m_strSelDocId,3,1));
		else
		{

			m_wndGridDocs.SetRow (m_wndGridDocs.GetRows()-1);
		
		
		
		}

		m_wndGridDocs.SetTopRow (m_wndGridDocs.GetRows());
		pGrid->Redraw =flexRDDirect;
		m_wndGridDocs.Select (m_wndGridDocs.GetRows()-1,m_wndGridDocs.GetFixedCols (),vtMissing,vtMissing);

		
	}


}
void CReturnView::OnGridDocsDblClickGrid() 
{
	MessageBoxHelper::ShowError(_T("OnGridDocsDblClickGrid()"));
}


void CReturnView::OnGridDocsEnterCell() 
{

	if(m_wndGridDocs.GetRedraw ()==flexRDNone) return;
	m_wndGridGoods.SetRows(m_wndGridGoods.GetFixedRows());
//	m_wndGridGoods.SetRows(10);

	CReturnDoc* pDoc=GetDocument();
	if(pDoc->m_blLoadDocs)
	{
			if(false)
		DebugBreak();
	
		_RecordsetPtr pRst=NULL;;
		TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
		if(m_wndGridDocs.GetRow()<m_wndGridDocs.GetFixedRows ()) return;
		m_strSelDocId=(LPCTSTR)m_wndGridDocs.GetTextMatrix (m_wndGridDocs.GetRow(),2);
		CString strDocKind=(LPCTSTR)m_wndGridDocs.GetTextMatrix (m_wndGridDocs.GetRow(),1);
		if(strDocKind.Compare (_T("ЧекККМ"))==0)
			m_blSelectCheck=TRUE;
		else
			m_blSelectCheck=FALSE;

		pDoc->m_strBaseDocId =m_strSelDocId;
		pDoc->LoadEntryDoc (m_strSelDocId,&pRst);
		if (pRst==NULL)
		{
		
			return;
		}
		
	
		long lRows=pRst->GetRecordCount ();
		if(lRows<1)
		{
			m_wndGridGoods.SetRows(m_wndGridGoods.GetFixedRows());
			return;
		}
		m_wndGridGoods.SetRowHidden (m_wndGridGoods.GetFixedRows ()-1,FALSE);
		m_wndGridSelGoods.SetRowHidden (m_wndGridSelGoods.GetFixedRows ()-1,FALSE);
		varArrEntryDoc =pRst->GetRows (pRst->GetRecordCount ());
		m_wndGridGoods.LoadRecordset (pRst);
		TESTHR(pRst->Close());
		//pRst.Release();
		
	
	}

		m_wndGridSelGoods.SetRows(1);
		ShowInfoOnPanel ();
	OnReturnAfterDataRefresh();
}
void CReturnView::OnGridDocsLeaveCell() 
{
	DebugBreak();
	
}

void CReturnView::OnLButtonDown(UINT nFlags, CPoint pt) 
{
	if (!PtInRect(&m_rcResizeArea, pt)) return ;
	SetCursor(LoadCursor(NULL, IDC_SIZENS));
	
	// prepare to work
	CRect rcClient, rcSizeBar,rcInfo;
	GetClientRect(&rcClient);
	GetDlgItem(IDC_INFO)->GetWindowRect(&rcInfo);
	ScreenToClient(&rcInfo);
	InflateRect(&rcClient, -10, -3);
	rcSizeBar = m_rcResizeArea;
	int iBarHeight = rcSizeBar.bottom - rcSizeBar.top;
	
	// capture the mouse until the user is done resizing
	SetCapture();
	MSG  msg={0};
	BOOL bErase = false;
	for (BOOL bDone = false; !bDone;) {
		if (PeekMessage(&msg, NULL, WM_KEYFIRST, WM_MOUSELAST, PM_REMOVE)) {
			switch (msg.message) {
				
				// quit when the button is released or a key is hit
			case WM_KEYDOWN:
			case WM_LBUTTONUP:
				
				bDone = true;
				break;
				
				// handle mouse movement
			case WM_MOUSEMOVE:
				SetCursor(LoadCursor(NULL, IDC_SIZENS));
				pt.x = LOWORD(msg.lParam);
				pt.y = HIWORD(msg.lParam);  
				if (!PtInRect(&rcClient, pt)) break;
				if (pt.y >rcInfo.top ) break;
				if (bErase) DrawResizeBar(&rcSizeBar);
				rcSizeBar.top  = pt.y - iBarHeight / 2;
				rcSizeBar.bottom = rcSizeBar.top + iBarHeight;
				DrawResizeBar(&rcSizeBar);
				bErase = true;
			}
		}
	}
	
	// release everything
	if (bErase) DrawResizeBar(&rcSizeBar);
	ReleaseCapture();
	SetCursor(NULL);
	
	// if the user canceled, we're done
	if (msg.message != WM_LBUTTONUP) return ;
	
	// do the resize
	m_wndGridDocs.GetClientRect(&rcClient);
	rcClient.bottom += rcSizeBar.top - m_rcResizeArea.top;
	m_nDocsGridHeight=rcClient.bottom;
	RepositionControls(m_nDocsGridHeight);
	WINDOWPLACEMENT wndPlmnt;
	// Get the window placements of each toolbar holder
	// and set each toolbar to its correspondent area.
	m_wndToolBarHolder.GetWindowPlacement(&wndPlmnt);
	m_wndSelGoodToolBar.GetToolBarCtrl().SetWindowPlacement(&wndPlmnt);
	m_wndSelGoodToolBar.Invalidate ();



	CFormView::OnLButtonDown(nFlags, pt);
}

void CReturnView::OnMouseMove(UINT nFlags, CPoint pt) 
{
	if (PtInRect(&m_rcResizeArea, pt))
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
	
	CFormView::OnMouseMove(nFlags, pt);
}

void CReturnView::DrawResizeBar(CRect *rc)
{
	ClientToScreen(rc);
		HDC  hdc = ::GetDC(NULL);
		CDC dc;
		dc.Attach (hdc);
		dc.InvertRect( rc);
		//ReleaseDC(hdc);
		ScreenToClient(rc);
}



void CReturnView::OnDraw(CDC* pDC) 
{
	HDC  hdc = ::GetDC(m_hWnd);
	CDC dc;
	dc.Attach (hdc);
	COLORREF clrBtnHilight = ::GetSysColor(COLOR_BTNHILIGHT);
	COLORREF clrBtnShadow  = ::GetSysColor(COLOR_BTNSHADOW);
	CRect rcGrip;
	rcGrip=m_rcResizeArea;
	rcGrip.DeflateRect (0,1);
	dc.Draw3dRect (&rcGrip,clrBtnHilight, clrBtnShadow);
	
}



void CReturnView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	OutputDebugString(_T("CReturnView::OnUpdate"));
	try
	{
		BOOL blIsWnd=::IsWindow (m_wndGridDocs.GetSafeHwnd());
		CString strTitle="";
		CString msg;
		msg.Format (_T("CReturnView::OnUpdate IsWindow=%d"),blIsWnd);
		OutputDebugString(msg);
		if(blIsWnd)
		{
			CReturnDoc* pDoc=(CReturnDoc*)m_pDocument;
			_RecordsetPtr pRst;
			//	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
			BOOL blRes=FALSE;
			m_wndGridSelGoods.Clear (_variant_t(0L),variant_t(0L));
			m_wndGridSelGoods.SetRows (m_wndGridSelGoods.GetFixedRows ());
			m_wndGridSelGoods.SetRowHidden (m_wndGridSelGoods.GetFixedRows ()-1,TRUE);
			
			switch(lHint)
			{
				
			case CReturnDoc::UpdateDocs:
				blRes=pDoc->LoadAllChecksOnDate (&pRst);
				m_wndGridDocs.Clear (_variant_t(0L),variant_t(0L));
				m_wndGridDocs.SetRows (m_wndGridDocs.GetFixedRows ());
				m_wndGridDocs.SetRowHidden (m_wndGridDocs.GetFixedRows ()-1,TRUE);
				
				if(blRes)
				{		
					m_wndGridDocs.LoadRecordset (pRst);
					TESTHR(pRst->Close());
				}
				break;
			case CReturnDoc::UpdateGoods:
				blRes=pDoc->LoadAllSalesOnDate (&pRst);
				m_wndGridDocs.Clear (_variant_t(0L),variant_t(0L));
				m_wndGridDocs.SetRows (m_wndGridDocs.GetFixedRows ());
				m_wndGridDocs.SetRowHidden (m_wndGridDocs.GetFixedRows ()-1,TRUE);
				if(blRes)
				{
					
					m_wndGridGoods.SetRedraw (FALSE);
					m_wndGridGoods.LoadRecordset (pRst);
					m_wndGridGoods.SetRedraw (TRUE);
					TESTHR(pRst->Close());
				}
				break;
			case CReturnDoc::UpdateSelectGoods:
				m_wndGridSelGoods.Clear (_variant_t(0L),variant_t(0L));
				m_wndGridSelGoods.SetRows (m_wndGridSelGoods.GetFixedRows ());
				m_wndGridSelGoods.SetRowHidden (m_wndGridSelGoods.GetFixedRows ()-1,TRUE);
				strTitle.Format (_T("Чек на Возврат№-%s Проведен."),pDoc->m_strDocId);
				SetTitle (strTitle);
				ShowInfoOnPanel(FALSE);
				if(pDoc->m_blLoadDocs )
				{
					blRes=pDoc->LoadAllChecksOnDate (&pRst);
					m_wndGridDocs.Clear (_variant_t(0L),variant_t(0L));
					m_wndGridDocs.SetRows (m_wndGridDocs.GetFixedRows ());
					m_wndGridDocs.SetRowHidden (m_wndGridDocs.GetFixedRows ()-1,TRUE);
					
					if(blRes)
					{
						m_wndGridDocs.LoadRecordset (pRst);
						TESTHR(pRst->Close());
					}
				}
				break;
				
			}
			
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description (),MB_ICONSTOP);
	}
	
}
 void CReturnView::OnGridGoodsAfterDataRefresh() 
 {
	

	 CWaitCursor cur;
	 CClientDC dc(this);
	 CSize szTwPerPixel;
	 szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	 szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	  COleVariant vtNone(0L,VT_ERROR);
	  m_wndGridGoods.SetGridColor(RGB(0,0,0));
	 IVSFlexGridPtr pGoodsGrid;
	 pGoodsGrid=m_wndGridGoods.GetControlUnknown ();

	pGoodsGrid->PutRedraw (flexRDNone);
	 _variant_t colEnd(0L);
	 _variant_t colBeg(0L);
	 colBeg.lVal =1L;
	 colEnd.lVal =pGoodsGrid->Cols-1;
	 
	 pGoodsGrid->put_AutoSizeMode(flexAutoSizeColWidth);
	 
	/* */pGoodsGrid->put_AllowUserResizing (flexResizeColumns);
	 pGoodsGrid->put_TextMatrix (0,1,_bstr_t("Штрихкод"));
	 pGoodsGrid->put_TextMatrix (0,2,_bstr_t("Наименование"));
	 pGoodsGrid->put_TextMatrix (0,3,_bstr_t("Количество"));
	 pGoodsGrid->put_TextMatrix (0,4,_bstr_t("Цена"));
	 pGoodsGrid->put_TextMatrix (0,5,_bstr_t("Сумма"));
	 pGoodsGrid->put_TextMatrix (0,6,_bstr_t("Номер"));
	 pGoodsGrid->put_TextMatrix (0,7,_bstr_t("Время"));
	  pGoodsGrid->put_TextMatrix (0,8,_bstr_t("CODE"));
	 pGoodsGrid->AutoSize(colBeg, colEnd, vtNone, vtNone);
	 CPictureHolder pic;
	 HICON hIcon=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_GOOD_GRD),
		 IMAGE_ICON,16,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	 pic.CreateFromIcon(hIcon,TRUE);
	 
	 long wdt,ht;
	 //size in HIMETRIC (0.01mm)
	 pic.m_pPict->get_Width (&wdt);
	 pic.m_pPict->get_Height (&ht);
	 
	 CSize szPict(wdt,ht);
	 dc.HIMETRICtoLP (&szPict);
	 //note grid size units is twips
	 
	 
	 pGoodsGrid->put_ColWidth (0,szPict.cx *szTwPerPixel.cx +100);
	 pGoodsGrid->put_RowHeightMin (szPict.cy *szTwPerPixel.cy +20);
	 //pGoodsGrid->put_ColWidth (4,szPict.cx *szTwPerPixel.cx +100);
	 pGoodsGrid->put_ColWidth (8,0);
	 pGoodsGrid->put_FontSize (10.0);
	 m_wndGridGoods.LoadGridPlacement (AfxGetApp(),szGoodsGridName);
	 if(m_wndGridGoods.GetColWidth (1)==CGoodsGrid::MinColWidth)
	 {
	 pGoodsGrid->put_ColWidth (2,pGoodsGrid->ClientWidth -
		 (pGoodsGrid->GetColWidth (0)+
		 pGoodsGrid->GetColWidth (1)+
		 pGoodsGrid->GetColWidth (3)+
		 pGoodsGrid->GetColWidth (4)+
		 pGoodsGrid->GetColWidth (5)+
		 pGoodsGrid->GetColWidth (6)+
		 pGoodsGrid->GetColWidth (7)));
	 }
	 // assign picture to grid's current cell
	 LPDISPATCH pDisp = pic.GetPictureDispatch();
	 for(long i=1;i<pGoodsGrid->Rows;i++){
		 pGoodsGrid->put_Row (i);
		 pGoodsGrid->put_Col(0);
		 pGoodsGrid->put_CellPictureAlignment (flexPicAlignCenterCenter);	
		 pGoodsGrid->PutCellPicture((IPictureDisp*)pDisp);
	 }
	 pGoodsGrid->put_Row (pGoodsGrid->Rows-1);
	 // pGoodsGrid->Select (2 ,2);
	 pGoodsGrid->Redraw =flexRDDirect;
	

 }
 void CReturnView::OnReturnAfterDataRefresh() 
 {
	 if(false)
		 DebugBreak();
	 CWaitCursor cur;
	 CClientDC dc(this);
	 CSize szTwPerPixel;
	 szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	 szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	  COleVariant vtNone(0L,VT_ERROR);
	 IVSFlexGridPtr pGoodsGrid;
	 pGoodsGrid=m_wndGridSelGoods.GetControlUnknown ();

	pGoodsGrid->PutRedraw (flexRDNone);
	 _variant_t colEnd(0L);
	 _variant_t colBeg(0L);
	 colBeg.lVal =1L;
	 colEnd.lVal =pGoodsGrid->Cols-1;
	 
	 pGoodsGrid->put_AutoSizeMode(flexAutoSizeColWidth);
	 
	 pGoodsGrid->put_AllowUserResizing (flexResizeColumns);
	 pGoodsGrid->put_TextMatrix (0,1,_bstr_t("Штрихкод"));
	 pGoodsGrid->put_TextMatrix (0,2,_bstr_t("Наименование"));
	 pGoodsGrid->put_TextMatrix (0,3,_bstr_t("Количество"));
	 pGoodsGrid->put_TextMatrix (0,4,_bstr_t("Цена"));
	 pGoodsGrid->put_TextMatrix (0,5,_bstr_t("Сумма"));
	 pGoodsGrid->put_TextMatrix (0,6,_bstr_t("Номер"));
	 pGoodsGrid->AutoSize(colBeg, colEnd, vtNone, vtNone);
	 CPictureHolder pic;
	 HICON hIcon=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_GOOD_GRD),
		 IMAGE_ICON,16,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	 pic.CreateFromIcon(hIcon,TRUE);
	 
	 long wdt,ht;
	 //size in HIMETRIC (0.01mm)
	 pic.m_pPict->get_Width (&wdt);
	 pic.m_pPict->get_Height (&ht);
	 
	 CSize szPict(wdt,ht);
	 dc.HIMETRICtoLP (&szPict);
	 //note grid size units is twips
	 
	 
	 pGoodsGrid->put_ColWidth (0,szPict.cx *szTwPerPixel.cx +100);
	 pGoodsGrid->put_RowHeightMin (szPict.cy *szTwPerPixel.cy +20);
	 
	 pGoodsGrid->put_FontSize (10.0);
	 pGoodsGrid->put_ColWidth (2,pGoodsGrid->ClientWidth -
		 (pGoodsGrid->GetColWidth (0)+
		 pGoodsGrid->GetColWidth (1)+
		 pGoodsGrid->GetColWidth (3)+
		 pGoodsGrid->GetColWidth (4)+
		 pGoodsGrid->GetColWidth (5)+
		 pGoodsGrid->GetColWidth (6)));
	 
	 // assign picture to grid's current cell
	 LPDISPATCH pDisp = pic.GetPictureDispatch();
	 for(long i=1;i<pGoodsGrid->Rows;i++){
		 pGoodsGrid->put_Row (i);
		 pGoodsGrid->put_Col(0);
		 pGoodsGrid->put_CellPictureAlignment (flexPicAlignCenterCenter);	
		 pGoodsGrid->PutCellPicture((IPictureDisp*)pDisp);
	 }

	 CReturnDoc* pDoc=GetDocument();
	  if(pGoodsGrid->Rows>pGoodsGrid->GetFixedRows ())
	  {
		    pDoc->SetModifiedFlag ();
			pDoc->m_vtArray =m_wndGridSelGoods.GetGridArray ();
	  }
	  else
		  pDoc->SetModifiedFlag (FALSE);
	 pGoodsGrid->Redraw =flexRDDirect;
	 //**************************************************************
	if(m_lblInfoDocNum.m_hWnd )
	{
		CRect rc;
		CRect rcInfo;
		GetDlgItem(IDC_INFO)->GetWindowRect(&rcInfo);
		ScreenToClient(&rcInfo);
		rc=rcInfo;
		CSize szBorder(4,4);
		CWindowDC dc(this);
		const int nFontSize=14;
		int lfHeight = ((nFontSize * GetDeviceCaps(+dc.GetSafeHdc (), 
			LOGPIXELSY)) / 72);
		rc.DeflateRect (szBorder);
		//rc.left   =rcInfo.left +szBorder.cx ;
		rc.top    =rcInfo.top+szBorder.cy*4 ;
		rc.bottom =rc.top+lfHeight;
		m_lblInfoDocNum.MoveWindow (rc);

		//m_lblInfoDocNum.SetText ("m_lblInfoDocNum");

		rc.top =rc.bottom +szBorder.cy;
		rc.bottom =rc.top+lfHeight;
		m_lblInfoBaseDoc .MoveWindow (rc);


		CRect rcBtnExec;
		GetDlgItem(IDC_BTNEXEC)->GetWindowRect(&rcBtnExec);
		rc.top    =rc.bottom +szBorder.cy;
		rc.right  =rcBtnExec.left -szBorder.cx ;
		rc.bottom =rc.top+lfHeight;
		m_lblInfoNumPos.MoveWindow (rc);
		//m_lblInfoNumPos.SetText("m_lblInfoNumPos");

		rc.top    =rc.bottom +szBorder.cy;
		rc.bottom =rc.top+lfHeight;
		m_lblInfoNumUnits.MoveWindow (rc);
		//m_lblInfoNumUnits.SetText ("m_lblInfoNumUnits");
		CFont* pFont	=m_lblInfoSumma .GetFont ();
		if (pFont)
		{
			LOGFONT lf;
			pFont->GetLogFont(&lf);
			lfHeight=lf.lfHeight ;
		}
		rc.top    =rc.bottom +szBorder.cy;
		
		rc.bottom =rc.top+lfHeight;
		m_lblInfoSumma.MoveWindow (rc);
		//m_lblInfoSumma.SetText ("m_lblSumma");
	
		ShowInfoOnPanel (FALSE);
	}
		
 }
/*
Эта процедура вызывается в OnIdle постоянно; здесь мы установим видимость элементов вида
  */
void CReturnView::OnUpdateSel1good(CCmdUI* pCmdUI) 
{
CReturnDoc* pDoc=GetDocument();
	IVSFlexGridPtr pEntryDoc=m_wndGridGoods.GetControlUnknown ();
	//если в документе есть строчки и если это ЧекККМ
	BOOL blEnable=(pEntryDoc->Rows>pEntryDoc->GetFixedRows ())&&(m_blSelectCheck||(!pDoc->m_blLoadDocs));
	TRACE(_T("blEnabled=%d\n"),m_blSelectCheck);
	pCmdUI->Enable (blEnable);
	
	
}
void CReturnView::OnUpdateExecReturn(CCmdUI* pCmdUI) 
{

	IVSFlexGridPtr pRetGoods=m_wndGridSelGoods .GetControlUnknown ();
	BOOL blEnable=pRetGoods->Rows>pRetGoods->GetFixedRows ();
 
	GetDlgItem(IDC_BTNEXEC)->EnableWindow(blEnable);
	pCmdUI->Enable (blEnable);
	
	
}
void CReturnView::OnUpdateSelallgoods(CCmdUI* pCmdUI) 
{
	IVSFlexGridPtr pEntryDoc=m_wndGridGoods.GetControlUnknown ();
	//если в документе есть строчки и если это ЧекККМ
	BOOL blEnable=(pEntryDoc->Rows>pEntryDoc->GetFixedRows ())&&(m_blSelectCheck);
	pCmdUI->Enable (blEnable);
	
}
void CReturnView::OnUpdateUndoAllGoods(CCmdUI* pCmdUI)
{
	IVSFlexGridPtr pRetGoods=m_wndGridSelGoods .GetControlUnknown ();
	pCmdUI->Enable (pRetGoods->Rows>pRetGoods->GetFixedRows ());
}





void CReturnView::ShowInfoOnPanel(BOOL blErase)
{
	if(blErase)
	{
		m_lblInfoDocNum. SetText("");
		m_lblInfoBaseDoc.SetText("");
		m_lblInfoNumPos.SetText("");
		m_lblInfoNumUnits.SetText("");
		m_lblInfoSumma.SetText("");
	}
	else
	{
		CReturnDoc* pDoc=(CReturnDoc*)m_pDocument;
		CString strInfo="";
		strInfo.Format (_T("Возврат № -%s"),pDoc->m_strDocId);
		m_lblInfoDocNum. SetText(strInfo);
		strInfo="";
		strInfo.Format (_T("Основание:Товарный чек №-%s"),pDoc->m_strBaseDocId);
		m_lblInfoBaseDoc.SetText(strInfo);
		int nRows=m_wndGridSelGoods.GetRows()-m_wndGridSelGoods.GetFixedRows ();
		strInfo.Format (_T("Позиций-%d"),nRows);
		m_lblInfoNumPos.SetText(strInfo);
		int nUnits=(int)m_wndGridSelGoods.GetSumColumn (3);
		strInfo.Format (_T("Единиц-%d"),nUnits);
		m_lblInfoNumUnits.SetText(strInfo);
		float flSumma=(float)m_wndGridSelGoods.GetSumColumn (5);
		pDoc->m_flCurSumma =flSumma;
		strInfo.Format (_T("Сумма-%0.2f"),flSumma);
		m_lblInfoSumma.SetText(strInfo);

	}
}

CReturnView* CReturnView::GetView()
{
	CMDIChildWnd * pChild =
          ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

      if ( !pChild )
          return NULL;

      CView * pView = pChild->GetActiveView();

      if ( !pView )
         return NULL;

      // Fail if view is of wrong kind
      if ( ! pView->IsKindOf( RUNTIME_CLASS(CReturnView) ) )
         return NULL;

      return (CReturnView *) pView;

}

void CReturnView::CheckReturn(LPCTSTR strNomId, LPCTSTR strDocId)
{


}

void CReturnView::OnBtnpodbor() 
{
	CPSDlgInsertGood dlg(_T("Выберите товар для добавления в документ"),this,0);
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	
	CDlgInsert pgSelBarCode(this);
	CDlgSelectGood pgSelGood;
	CDlgFindAll pgFindAll(this);
	dlg.AddPage (&pgSelGood);
	dlg.AddPage (&pgSelBarCode);
	dlg.AddPage (&pgFindAll);
	int nRet = 0xf;
	

	//dlg.SetPageTitle (1,"Abracadabra");
	//CString strBarCode;
	nRet = dlg.DoModal();
	//dlg.UpdateData (TRUE);
	// Handle the return value from DoModal.
	switch ( nRet )
	{
	case 0xf: 
		MessageBoxHelper::ShowError(_T("Dialog box could not be created!"));
		break;
	//case IDABORT:
		// Do something.
		//break;
	case IDOK:
		//ProcessingBarCode(pgSelBarCode.m_strBarCode );	
		//strBarCode=dlg.m_strBarCode ;
		
		break;
	case IDCANCEL:
		//AfxMessageBox("Cancel");
		
		break;
	default:
		// Do something.
		break;
	};
	
}

BOOL CReturnView::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	_variant_t v; 
	V_VT(&v) = VT_ERROR;
	CString strData=(LPCTSTR)pCopyDataStruct->lpData;
	int nLength=strData.GetLength();
	//ASSERT(nLength==pCopyDataStruct->cbData);
	if(strData.GetLength ()>15)
	{
		IVSFlexGridPtr pRetGoods=m_wndGridSelGoods .GetControlUnknown ();
	IVSFlexGridPtr pEntryDoc=m_wndGridGoods.GetControlUnknown ();
	pRetGoods->PutCols(pEntryDoc->Cols-2);
		CString strItem,strItems;
		for(int i=0;i<3;i++)
		{
		AfxExtractSubString (strItem,strData,i,'\t');
		strItems+=strItem;
		strItems+="\t";
		}
		AfxExtractSubString (strItem,strData,5,'\t');
		strItems+=strItem;
		strItems+="\t";
		AfxExtractSubString (strItem,strData,3,'\t');
		strItems+=strItem;
		strItems+="\t";
		AfxExtractSubString (strItem,strData,6,'\t');
		strItems+=strItem;
		strItems+="\t";
	
		AfxExtractSubString (strItem,strData,7,'\t');
		strItems+=strItem;
		//strItems+="\t";
		m_wndGridSelGoods.AddItem (strItems,v);
		OnReturnAfterDataRefresh();
		ShowInfoOnPanel();
	}
	else
	{
	//ProcessingBarCode ((LPCTSTR)pCopyDataStruct->lpData );//<-----Вот где собака порылась!!!
	//любые проблемы в этой ф-ии и мы не вернемся в поток сканера штрих кода !!!виииииснем!!!!
	m_strReceivingBarCode=strData;//сохранились
	PostMessage(WM_RECEIVED_BARCODE);//теперь обрабатывай хоть до ишачьей пасхи
	}
	TRACE0("PostMessage(WM_RECEIVED_BARCODE)\n");
	return TRUE;
	

}

BOOL CReturnView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
 if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		switch (pMsg->wParam)
        {
		case VK_INSERT:
			OnBtnpodbor (); 
			break;
		default:
			return CFormView::PreTranslateMessage(pMsg);
			break;
		}
		return TRUE;
	}
	
		
	return CFormView::PreTranslateMessage(pMsg);
}

void CReturnView::WriteGridPlacement()
{
	CString szSection=_T("Settings");
//	CString szWindowPos=_T("DocsViewHeight");
	CRect rc;
	GetClientRect(&rc);
if((m_nDocsGridHeight>0)&&(m_nDocsGridHeight<rc.Height()))
{
	AfxGetApp()->WriteProfileInt(szSection, _T("DocsViewHeight"), m_nDocsGridHeight);

}
}

int CReturnView::ReadDocsGridPlacement()
{
	CString szSection=_T("Settings");
	
	int nHeight=AfxGetApp()->GetProfileInt(szSection, _T("DocsViewHeight"), -1);
	return nHeight;
}

void CReturnView::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//	DebugBreak();
WriteGridPlacement();
	CFormView::OnClose();
}
void CReturnView::OnGridGoodsAfterResizeColumn(int row,int col)
{
	m_wndGridGoods.SaveGridPlacement(AfxGetApp(),szGoodsGridName);
}