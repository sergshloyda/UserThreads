// NaklForm.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "NaklForm.h"
#include "InfoConsole.h"
#include "MDIChild.h"
#include "DlgSetPeriod.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NBUTTONS 3
static struct {
	UINT id;										 // command ID
	UINT style;									 // button style
	UINT iImage;								 // index of image in normal/hot bitmaps

} Buttons[NBUTTONS] = {

	// command ID					button style						image index
	{ ID_PREVIEW_DOC,  TBSTYLE_BUTTON, 0 },
	{ ID_SETINTERVAL,  TBSTYLE_BUTTON, 1 },
	{ ID_FINDDOC,      TBSTYLE_BUTTON, 2 }

};
/////////////////////////////////////////////////////////////////////////////
// CNaklForm

IMPLEMENT_DYNCREATE(CNaklForm, CFormView)

CNaklForm::CNaklForm()
	: CFormView(CNaklForm::IDD),m_constGridBorder(4)
{
	//{{AFX_DATA_INIT(CNaklForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}

CNaklForm::~CNaklForm()
{
}

void CNaklForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNaklForm)
	DDX_Control(pDX, IDC_TOOLBARPLACE1, m_wndToolBarHolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNaklForm, CFormView)
	//{{AFX_MSG_MAP(CNaklForm)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_PREVIEW_DOC, OnPreviewDoc)
	ON_UPDATE_COMMAND_UI(ID_PREVIEW_DOC, OnUpdatePreviewDoc)
	ON_COMMAND(ID_SETINTERVAL, OnSetinterval)
	ON_UPDATE_COMMAND_UI(ID_SETINTERVAL, OnUpdateSetinterval)
	ON_COMMAND(ID_FINDDOC, OnFinddoc)
	ON_UPDATE_COMMAND_UI(ID_FINDDOC, OnUpdateFinddoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BEGIN_EVENTSINK_MAP(CNaklForm, CFormView)
    //{{AFX_EVENTSINK_MAP(CMFCDataDlg)
	ON_EVENT(CNaklForm, IDC_GRID_GJ, 82 /* AfterDataRefresh */, OnAfterDataRefresh, VTS_NONE)
	ON_EVENT(CNaklForm, IDC_GRID_GJ, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
/////////////////////////////////////////////////////////////////////////////
// CNaklForm diagnostics

#ifdef _DEBUG
void CNaklForm::AssertValid() const
{
	CFormView::AssertValid();
}

void CNaklForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNaklForm message handlers

void CNaklForm::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	EnableToolTips (TRUE);
	LoadToolbar();

	RepositionControls();

	WINDOWPLACEMENT wndPlmnt;
	// Get the window placements of each toolbar holder
	// and set each toolbar to its correspondent area.
	m_wndToolBarHolder.GetWindowPlacement(&wndPlmnt);
	m_wndToolBar.GetToolBarCtrl().SetWindowPlacement(&wndPlmnt);
	CDBDoc* pDoc=GetDocument();
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CDBDoc)));
	COleDateTime tmStart=pDoc->m_dtStart ;
	CString strStart=tmStart.Format(_T("%d/%m/%Y"));
	m_wndGrid.SetTextMatrix(1,1,strStart);
	SetupGrid();
	CString strTitle="";
	strTitle.Format(_T("Общий журнал документов.Интервал с %s по %s"),pDoc->m_dtStart.Format(_T("%d/%m/%Y")),pDoc->m_dtEnd.Format(_T("%d/%m/%Y")) );

	pDoc->SetTitle (strTitle);
	//PostMessage(WM_NEXTDLGCTL ,(WPARAM)m_wndGrid.m_hWnd ,(LPARAM)TRUE);
	//m_Grid.SetFocus();
	//m_wndGrid.SetRow(1);
	//m_wndGrid.SetCol(1);
	
}

CDBDoc* CNaklForm::GetDocument()
{
	//CInfoConsole* pThread=(CInfoConsole*)AfxGetThread();
	return (CDBDoc*)m_pDocument;
}

void CNaklForm::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CInfoFrame* pFrame=static_cast<CInfoFrame*>(AfxGetMainWnd());
	POSITION tmpPos;
	POSITION pos = pFrame->m_lsForms.GetHeadPosition();
	while( pos != NULL )
	{
		tmpPos=pos;

		CString szCmp = static_cast<CString>(pFrame->m_lsForms.GetNext( pos ));
		
		if (szCmp == _T("NaklForm")) 
		{
			pFrame->m_lsForms.RemoveAt (tmpPos);
		}
	}
	
	CFormView::OnClose();
}

void CNaklForm::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if(m_wndGrid.m_hWnd)
		RepositionControls();

	
}

int CNaklForm::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rc;
	GetClientRect(&rc);
	InflateRect(&rc,-m_constGridBorder,-m_constGridBorder);
	
	m_wndGrid.Create (_T("MyGrid"),WS_CHILD|WS_BORDER|WS_VISIBLE,rc,this,IDC_GRID_GJ);
	HWND hwnd=m_wndGrid.Detach ();
	m_wndGrid.SubclassWindow (hwnd);
//	m_wndGrid.InitToolTip ();
	return 0;
	
	return 0;
}

void CNaklForm::RepositionControls()
{
	CRect rcGrid;
	CRect rcToolBar;
	CRect rcClient;
	CRect rc;
	GetClientRect(&rcClient);
	//InflateRect(&rcClient,-m_constGridBorder,-m_constGridBorder);
	CSize szImage(16,16);
	CSize szMargin(7,7);//for ToolBar size
	
	
	if(IsWindow(GetDlgItem(IDC_TOOLBARPLACE1)->GetSafeHwnd()))
	{
		//CRect rc;
		GetDlgItem(IDC_TOOLBARPLACE1)->GetWindowRect(&rcToolBar);
		
	
	rc=rcClient;
	rc.bottom =rc.top +szImage.cy +szMargin.cy *2;
	rcToolBar=rc;
	GetDlgItem(IDC_TOOLBARPLACE1)->MoveWindow(&rcToolBar);
	}
	rc=rcClient;
	InflateRect(&rc,-m_constGridBorder,-m_constGridBorder);
	rc.top =rcToolBar.bottom +m_constGridBorder;
	rcGrid=rc;
		if(m_wndGrid.m_hWnd)
	m_wndGrid.MoveWindow(&rcGrid);

}


void CNaklForm::LoadToolbar()
{


if (!m_wndToolBar.Create( this ) ||
			!m_wndToolBar.LoadToolBar(IDR_GENJOURNAL_TB))
	{
			TRACE0("Failed to create toolbar1\n");
			return;      // fail to create	
	}
m_wndToolBar.SetBarStyle( CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY);


	CSize szImage(16,16);
	CSize szMargin(7,7);//for button labels
	CImageList il;
	VERIFY(il.Create (szImage.cx ,szImage.cy ,ILC_COLOR8|ILC_MASK,2,szMargin.cx ));
	il.SetBkColor (TRANSPARENT);

	HICON hIcon[NBUTTONS];
	int n;
	hIcon[0]=AfxGetApp()->LoadIcon (IDI_DOCVIEW);
	hIcon[1]=AfxGetApp()->LoadIcon (IDI_INTERVAL);
	hIcon[2]=AfxGetApp()->LoadIcon (IDI_SELSALEDOC);
	for(n=0;n<NBUTTONS;n++)
		il.Add (hIcon[n]);
	
	m_wndToolBar.SetSizes (szImage+szMargin,szImage);

	m_wndToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)il.Detach());

	m_wndToolBar.SetButtons(NULL, NBUTTONS);
	for (int i=0; i<NBUTTONS; i++) {
		m_wndToolBar.SetButtonInfo(i,
			Buttons[i].id,						 // command id
			Buttons[i].style,					 // buttons style
			Buttons[i].iImage);	                 // index of image in bitmap
		
	}
	
		

}



void CNaklForm::OnPreviewDoc() 
{
	MessageBoxHelper::ShowError(_T("Not implemented"));// TODO: Add your command handler code here
	
}

void CNaklForm::OnUpdatePreviewDoc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CNaklForm::OnSetinterval() 
{
	CDlgSetPeriod dlgSetPeriod;
//	CDBDoc* pDoc=(CDBDoc*)GetDocument();
	int res=dlgSetPeriod.DoModal ();
	switch(res)
	{
	case IDOK:
		OnUpdate(this,0L,NULL);
		break;
	case IDCANCEL:
	
		break;
	}

}

void CNaklForm::OnUpdateSetinterval(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CNaklForm::OnFinddoc() 
{
	// TODO: Add your command handler code here
		MessageBoxHelper::ShowError(_T("Not implemented"));
}

void CNaklForm::OnUpdateFinddoc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CNaklForm::SetupGrid()
{
	pGrid=m_wndGrid.GetControlUnknown();
	ASSERT(pGrid!=NULL);
	

	CDBDoc* pDBDoc=GetDocument();
	m_wndGrid.SetFontName (pDBDoc->GetFontName () );
	m_wndGrid.SetFontSize ((float)pDBDoc->GetFontSize ());
	
	pGrid->AllowUserResizing=flexResizeColumns;
	pGrid->AutoSizeMode =flexAutoSizeColWidth;	
	pGrid->AutoResize=TRUE;
	
}

void CNaklForm::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(!::IsWindow(m_wndGrid.m_hWnd))return;
	CDBDoc* pDBDoc=GetDocument();
	m_wndGrid.SetFontName (pDBDoc->GetFontName () );
	m_wndGrid.SetFontSize ((float)pDBDoc->GetFontSize ());
	_RecordsetPtr pRst;
	CString strStart,strEnd;
	strStart=pDBDoc->m_dtStart.Format(_T("%m/%d/%y"));
	strEnd=pDBDoc->m_dtEnd.Format(_T("%m/%d/%y"));
	CString strTitle;
	strTitle.Format(_T("Общий журнал документов.Интервал с %s по %s"),pDBDoc->m_dtStart.Format(_T("%d/%m/%Y")),pDBDoc->m_dtEnd.Format(_T("%d/%m/%Y")) );

	pDBDoc->SetTitle (strTitle);
		try
		{
			
			CString strSQL;
			strSQL.Format(_T("Select GenJournal.IsLoaded,doctable.descr,genjournal.")
				_T("hdocid,genjournal.docdate,genjournal.doctime,genjournal.summa, '                        ' as Информация from ")
				_T("GenJournal inner join doctable on genjournal.doctype=doctable.doctype ")
				_T("where genjournal.docdate between {%s} and {%s} order by genjournal.doctime"),strStart,strEnd);
			TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
			CInfoConsole* pInfo=static_cast<CInfoConsole*>(AfxGetThread());
			
			HRESULT hr=pRst->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pInfo->pConn),
				adOpenKeyset, adLockBatchOptimistic, adCmdText);
			if (hr!=S_OK)
			{
				AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
				return ;
			}
			
			
			m_wndGrid.SetEditable(flexEDNone);
			m_wndGrid.SetDataMode(0 /*flexDMFree*/);
			
			m_wndGrid.SetRefDataSource((LPUNKNOWN)pRst);
			
			// check binding
			if (m_wndGrid.GetDataSource() == NULL)
			{
				TRACE0("Failed to bind grid to recordset");
				return ;
			}
			if (m_wndGrid.GetDataMode() != 1 /*flexDMBound*/)
			{
				TRACE0("Got recordset data, but can't update it "
					"(check recordset parameters)");
				m_wndGrid.SetEditable(0 /*flexEDNone*/);
			}	
			
		
			TESTHR(pRst->Close ());
			
		}
		
		catch (_com_error &e)
		{
			// Notify the user of errors if any.
			// Pass a connection pointer accessed from the Recordset.
			_variant_t vtConnect = pRst->GetActiveConnection();
			
			// GetActiveConnection returns connect string if connection
			// is not open, else returns Connection object.
			switch(vtConnect.vt)
			{
			case VT_BSTR:
				PrintComError(e);
				break;
			case VT_DISPATCH:
				PrintProviderError(vtConnect);
				break;
			default:
			TRACE0("Errors occured.");
				break;
			}
		}
	
	
}


void CNaklForm::OnAfterDataRefresh()
{
	CWaitCursor cur;
	CClientDC dc(this);
	CSize szTwPerPixel;
	szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	
	if(pGrid==NULL) return;
	
	m_wndGrid.SetTextMatrix(0,2,_T("Название документа"));
	m_wndGrid.SetTextMatrix(0,3,_T("Номер"));
	m_wndGrid.SetTextMatrix(0,4,_T("Дата"));
	m_wndGrid.SetTextMatrix(0,5,_T("Время"));
	m_wndGrid.SetTextMatrix(0,6,_T("Сумма"));
	m_wndGrid.SetTextMatrix(0,7,_T("Информация"));
	pGrid->SelectionMode=flexSelectionByRow;
	pGrid->PutRedraw ( flexRDNone);
	
	COleVariant vtNone(0L, VT_ERROR);
	pGrid->AutoSize(2, vtNone, vtNone, vtNone);
	
	pGrid->PutColWidth (1,0);
	
	pGrid->PutAllowUserResizing (flexResizeColumns);
	
	
	CPictureHolder picTransact;
	HICON hIcon1=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_DOCTRANSACT),
		IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	picTransact.CreateFromIcon(hIcon1,TRUE);
	CPictureHolder picNoTransact;
	HICON hIcon2=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_DOCNOTRANSACT),
		IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	picNoTransact.CreateFromIcon(hIcon2,TRUE);
	long wdt,ht;
	//size in HIMETRIC (0.01mm)
	picNoTransact.m_pPict->get_Width (&wdt);
	picNoTransact.m_pPict->get_Height (&ht);
	
	CSize szPict(wdt,ht);
	dc.HIMETRICtoLP (&szPict);
	//note grid size units is twips
	
	
	pGrid->PutColWidth (0,szPict.cx *szTwPerPixel.cx +100);
	
	//pic.CreateFromIcon (IDI_ICON1);
	// assign picture to grid's current cell
	LPDISPATCH pDispTrans = picTransact.GetPictureDispatch();
	LPDISPATCH pDispNoTrans = picNoTransact.GetPictureDispatch();
	for(long i=1;i<pGrid->GetRows();i++){
		pGrid->PutRow (i);
		
		pGrid->PutCellPictureAlignment (flexPicAlignCenterCenter);	
		
		
		
		pGrid->PutCol(1);
		
		_variant_t val=pGrid->GetValue();
		pGrid->PutCol(0);
		if(val.dblVal < 0)//TRUE ?????
			pGrid->PutCellPicture((IPictureDisp*)pDispTrans);
		else
			
			pGrid->PutCellPicture((IPictureDisp*)pDispNoTrans);
		
		
		for(long c=1;c<pGrid->GetCols();c++)
		{
			pGrid->PutCol(c);
			if(i%2)
			{
				
				pGrid->PutCellBackColor (RGB(223,223,223));
			}
			else
				
			{
				pGrid->PutCellBackColor (RGB(255,255,255));
			}
		}
	}
	pDispTrans->Release();
	pDispNoTrans->Release();
	pGrid->PutCol(2);
	
	pGrid->PutRedraw ( flexRDDirect);
	//Прокручиваем таблицу к низу и фокус на нее
	pGrid->Select(pGrid->Rows-1,1);
//	long r=pGrid->CellTop;

	PostMessage(WM_NEXTDLGCTL ,(WPARAM)m_wndGrid.m_hWnd ,(LPARAM)TRUE);//set focus to grid
	
	
}

void CNaklForm::OnDblClickGrid()
{
	MessageBoxHelper::ShowError(_T("OnDblClick"));
}
