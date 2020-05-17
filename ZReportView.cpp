// ZReportView.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ZReportView.h"
#include "ZReportDoc.h"
#include "ZReportWizard.h"
#include "CashDoc.h"
#include "MainChildFrame.h"
#include "ReturnDoc.h"
#include "drvfr.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZReportView

IMPLEMENT_DYNCREATE(CZReportView, CFormView)

CZReportView::CZReportView()
	: CFormView(CZReportView::IDD)
{
	//{{AFX_DATA_INIT(CZReportView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CZReportView::~CZReportView()
{
}

void CZReportView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZReportView)
	DDX_Control(pDX, IDC_LBL_CURSUMMA, m_lblCurTotal);
	DDX_Control(pDX, IDC_LBL_OSTATOK, m_lblOstatok);
	DDX_Control(pDX, IDC_LBL_SUMSALE, m_lblSumSale);
	DDX_Control(pDX, IDC_CAPTION, m_lblCaption);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZReportView, CFormView)
	//{{AFX_MSG_MAP(CZReportView)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_VIEW_CLIENT_INFO,OnShowReturn)
	ON_NOTIFY(FTN_TABCHANGED, IDC_FOLDERTAB, OnChangedTab)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CZReportView, CFormView)
    //{{AFX_EVENTSINK_MAP(CMFCDataDlg)
	ON_EVENT(CZReportView, IDC_GRIDZREPORT, 82 /* AfterDataRefresh */, OnAfterDataRefresh, VTS_NONE)

	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZReportView diagnostics

#ifdef _DEBUG
void CZReportView::AssertValid() const
{
	CFormView::AssertValid();
}

void CZReportView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZReportView message handlers

void CZReportView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_wndGrid.CreateFromStatic(IDC_GRIDZREPORT,this);	///Покажем таблицу продаж
	m_spGrid=m_wndGrid.GetControlUnknown ();
	CZReportDoc* pDoc=GetDocument();
	pDoc->CalculateDaySales ();
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	m_lblCaption.SetColor(RGB(0,0,0));
	LOGFONT logFont;
	pMainDoc->m_FontMap[_T("Return")]->GetLogFont(&logFont);
	long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
	CString strFontName(logFont.lfFaceName);
	m_lblCaption.SetLabelFont(strFontName,szFont);
//	SetLocaleID (0x0423);
	SetThreadLocale (MAKELCID(0x0423,SORT_DEFAULT));
	//CString strTime=pDoc->m_tmDocTime.Format(VAR_DATEVALUEONLY ,MAKELANGID(LANG_RUSSIAN,SUBLANG_NEUTRAL));
	
	CString buffer;
	
	m_lblOstatok.SetColor(RGB(0,100,0));
	m_lblOstatok.SetLabelFont(strFontName,szFont);
	buffer.Empty();

	CCashDoc *pCashDoc=CUserThreadsApp::GetDocument<CCashDoc>();
	COleDateTime tmCurTime=COleDateTime::GetCurrentTime ();
	COleDateTime tmYesterday;
	tmYesterday.SetDateTime(tmCurTime.GetYear(),tmCurTime.GetMonth(),
		tmCurTime.GetDay(),0,0,0);

	float flBalance=(float)pCashDoc->CalculateCashBalance (pDoc->m_tmLastZReportTime );
	//float flBalance=(float)pCashDoc->CalculateCashBalance (tmYesterday );
 	buffer.Format (_T("Текущий остаток по кассе: %0.2f руб."),flBalance);
	pDoc->m_flOstatok =flBalance;
	m_lblOstatok.SetText(buffer);

	m_lblSumSale.SetColor(RGB(0,0,255));
	m_lblSumSale.SetLabelFont(strFontName,szFont);
	buffer.Empty();
	buffer.Format (_T("Продажа: %0.2f руб."),pDoc->m_flCurSummSale );
	m_lblSumSale.SetText(buffer);
		if(m_lblSumReturn.GetSafeHwnd()==NULL)
	{
		
		m_lblSumReturn.SubclassDlgItem (IDC_LBL_SUMRETURN,this);
	
		m_lblSumReturn.SetFont (pMainDoc->m_FontMap[_T("Return")].get());
		buffer.Empty();
		buffer.Format (_T("Возвратов на сумму: %0.2f руб."),pDoc->m_flCurSummReturn );
		m_lblSumReturn.SetColor (RGB(200,0,0));
		m_lblSumReturn.SetWindowText (buffer);
	}
//	m_lblSumReturn.SetColor(RGB(255,0,0));
	//m_lblSumReturn.SetLabelFont(pMainDoc->GetFontName (),pMainDoc->GetFontSize ());

	//m_lblSumReturn.SetText();

	m_lblCurTotal.SetColor(RGB(0,150,0));
	m_lblCurTotal.SetLabelFont(strFontName,szFont);
	buffer.Empty();
	buffer.Format (_T("Текущая сумма в кассе: %0.2f руб."),pDoc->m_flOstatok/*+pDoc->m_flCurSummSale-pDoc->m_flCurSummReturn*/);
	m_lblCurTotal.SetText(buffer);
	LoadZReportTable ();
	CString strTime=pDoc->m_tmDocTime.Format(_T("%d/%m/%Y"));

	buffer.Format (_T("Отчет по кассе №:%s от %s"),pDoc->m_strDocId,strTime );
	m_lblCaption.SetText(buffer);
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	AfxSetWindowText(pFrame->m_hWnd ,buffer);
	CToolBar* pBar = pFrame->GetToolBar(IDR_RETURN);
	m_wndFolderTab.CreateFromStatic(IDC_FOLDERTAB, this);
	m_wndFolderTab.AddItem (_T("Продажи"));
	m_wndFolderTab.AddItem (_T("Возвраты"));
	m_wndFolderTab.AddItem (_T("Расчет зарплаты"));
	m_wndFolderTab.RecomputeLayout ();
	if (pBar != NULL)
	{
		pFrame->ShowControlBar(pBar, FALSE, FALSE);
		return ;
	}
	

}
 

CZReportDoc* CZReportView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZReportDoc)));
	return (CZReportDoc*)m_pDocument;
}

void CZReportView::OnOk() 
{
	CZReportDoc* pDoc=(CZReportDoc*)GetDocument();
	//_variant_t vt;
	//pDoc->TransactZReport (vt);
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	CZReportWizard ZReport(pMainDoc->m_strUserId,this );
	ZReport.SetWizardMode ();
	if(pDoc->CalculateDaySales()==0.0){
	CShtrihFRK Driver;
	Driver.CloseDay (30);
	CMainFrame* pMainFrm=(CMainFrame*)AfxGetMainWnd();
	CString strMsg;
	strMsg.Format (_T("ErrNumber:%x ErrDescr:%s"),Driver.drv.GetResultCode(),Driver.m_strResultCodeDescription );
	pMainFrm->m_strErrorMsg=strMsg;
	}
	else
	ZReport.DoModal ();

}

void CZReportView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RepositionControls();
}

void CZReportView::RepositionControls()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CSize szBorder(2,2);
	rcClient.DeflateRect (szBorder);
	CRect rcInfo;
	rcInfo=rcClient;
	rcInfo.bottom=rcClient.top+(int)(rcClient.Height ()/6);
	CRect rcGrid;
	rcGrid.left=rcInfo.left ;
	rcGrid.top =rcInfo.bottom+szBorder.cy ;
	rcGrid.bottom=rcClient.bottom;
	rcGrid.right=rcClient.right;
	

	
	if(::IsWindow (m_wndGrid.GetSafeHwnd()))
	{
//		CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
		CMainDocument *pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
		m_wndGrid.MoveWindow(rcGrid);
		LOGFONT logFont;
		pMainDoc->m_FontMap[_T("Reports")]->GetLogFont(&logFont);
		long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
		CString strFontName(logFont.lfFaceName);
		m_wndGrid.SetFontSize((float)szFont);
		m_wndGrid.SetFontName(strFontName);
		m_wndGrid.SetFontBold(logFont.lfWeight==FW_BOLD);
		m_wndGrid.SetFontItalic(logFont.lfItalic);
		VARIANT v; 
		V_VT(&v) = VT_ERROR; 
		m_wndGrid.SetAllowUserResizing(TRUE);
		m_wndGrid.SetAutoSizeMode (flexAutoSizeColWidth);
		long lCols=m_wndGrid.GetCols();
		lCols-=1;
		_variant_t varColEnd(lCols,VT_I4);
		//_variant_t varRowEnd(lRows,VT_I4);
		//m_spGrid->AutoSize (0L,varColEnd,v,v);
		m_wndGrid.AutoSize (0L,varColEnd,v,v);
		
		
	
	}

	if(::IsWindow(m_wndFolderTab.GetSafeHwnd()))
	{ 
		long lFixWidth=m_wndGrid.GetColWidth (0);
		rcGrid.top +=2;
		rcGrid.left +=lFixWidth/m_wndGrid.TwipsPerPixelX ();
		CRect rcFolderTabs;
		m_wndFolderTab.GetWindowRect(&rcFolderTabs);
		rcFolderTabs.top =rcGrid.top-rcFolderTabs.Height ();
		rcFolderTabs.left =rcGrid.left ;
		rcFolderTabs.right =rcGrid.left+rcFolderTabs.Width ();
		rcFolderTabs.bottom =rcGrid.top ;
		
		m_wndFolderTab.MoveWindow(&rcFolderTabs);	
		
	}
}

BOOL CZReportView::LoadZReportTable()
{
	CZReportDoc* pDoc=GetDocument();
	
	m_wndGrid.SetRows(m_wndGrid.GetFixedRows ());
	_RecordsetPtr pRst=pDoc->GetZReportRecordset () ;
	if(NULL!=pRst)
		m_wndGrid.LoadRecordset (pRst);
	else
	{
		m_wndGrid.SetCols(8);
		m_wndGrid.SetRows(max(1,m_wndGrid.GetRows()));
		m_wndGrid.SetTextMatrix (0,1,_T("ШтрихКод"));
		m_wndGrid.SetTextMatrix (0,2,_T("Наименование"));
		m_wndGrid.SetTextMatrix (0,3,_T("Кол-во"));
		m_wndGrid.SetTextMatrix (0,4,_T("Цена"));
		m_wndGrid.SetTextMatrix (0,5,_T("Сумма"));
		m_wndGrid.SetTextMatrix (0,6,_T("Номер документа"));
		m_wndGrid.SetTextMatrix (0,7,_T("Время документа"));
	}
	for (int i=1;i<m_wndGrid.GetCols();i++)
	{
		m_wndGrid.SetRow (0);
		m_wndGrid.SetCol(i);
		//m_wndGrid.Select (0,0,(_variant_t)1L,(_variant_t)5L);
		m_wndGrid.SetCellBackColor (::GetSysColor (COLOR_INFOBK));
	}
	
	RepositionControls ();
	return TRUE;
}
void CZReportView::OnAfterDataRefresh() 

{
	
	if(1==m_spGrid->Rows)
	{
		
		return;
	}
	ULONG ulSELCOLOR =	::GetSysColor (COLOR_3DFACE);
	ULONG ulBKCOLOR  =	::GetSysColor (COLOR_WINDOW);
	CComBSTR bstrNumDocBehind;
	ULONG ulCELLCOLOR=ulBKCOLOR;
	for (long r=1;r<m_spGrid->Rows ;r++)
	{
		
		CComBSTR bstrNumDoc=(BSTR)m_spGrid->GetTextMatrix(r,6);
		if(bstrNumDoc==bstrNumDocBehind)
		{	
			m_spGrid->Row=r-1;
			m_spGrid->get_CellBackColor (&ulCELLCOLOR);
			bstrNumDocBehind=bstrNumDoc;
			m_spGrid->Row =r;
			for(long c=1;c<m_spGrid->Cols ;c++)
			{
				m_spGrid->Col=c;
				m_spGrid->put_CellBackColor (ulCELLCOLOR);
			}
		}
		else
		{
			if(r==1)
			{
				bstrNumDocBehind=bstrNumDoc;
				for(long c=1;c<m_spGrid->Cols ;c++)
				{
					m_spGrid->Col=c;
					m_spGrid->put_CellBackColor (ulBKCOLOR);
				}
			}
			else
			{
				m_spGrid->Row=r-1;
				m_spGrid->get_CellBackColor (&ulCELLCOLOR);
				if(ulCELLCOLOR==ulSELCOLOR)
					ulCELLCOLOR=ulBKCOLOR;
				else
					ulCELLCOLOR=ulSELCOLOR;
				bstrNumDocBehind=bstrNumDoc;
				m_spGrid->Row =r;
				for(long c=1;c<m_spGrid->Cols ;c++)
				{
					m_spGrid->Col=c;
					m_spGrid->put_CellBackColor (ulCELLCOLOR);
				}
			}
			
		}	
	}
	
	m_spGrid->TopRow   =m_spGrid->Rows;
	
}

LRESULT CZReportView::OnShowReturn(WPARAM wParam, LPARAM lParam)
{

	LoadReturns();
	return 0L;
}

BOOL CZReportView::LoadReturns()
{
	CReturnDoc* pRetDoc=CReturnDoc::GetReturnDoc();
	CZReportDoc* pZRDoc=GetDocument();
	_RecordsetPtr pRst=NULL;
	pRetDoc->LoadAllReturns (pZRDoc->m_tmLastZReportTime ,&pRst);
	m_wndGrid.SetRows(m_wndGrid.GetFixedRows ());
	m_wndGrid.LoadRecordset (pRst);
	m_wndGrid.SetRows(max(1,m_wndGrid.GetRows()));
	m_wndGrid.SetTextMatrix (0,1,_T("ШтрихКод"));
	m_wndGrid.SetTextMatrix (0,2,_T("Наименование"));
	m_wndGrid.SetTextMatrix (0,3,_T("Кол-во"));
	m_wndGrid.SetTextMatrix (0,4,_T("Цена"));
	m_wndGrid.SetTextMatrix (0,5,_T("Сумма"));
	m_wndGrid.SetTextMatrix (0,6,_T("Документ продажи"));
	m_wndGrid.SetTextMatrix (0,7,_T("Дата продажи"));
	for (int i=1;i<m_wndGrid.GetCols();i++)
	{
		m_wndGrid.SetRow (0);
		m_wndGrid.SetCol(i);
		//m_wndGrid.Select (0,0,(_variant_t)1L,(_variant_t)5L);
		m_wndGrid.SetCellBackColor (::GetSysColor (COLOR_INFOBK));
	}
	
	RepositionControls ();
	return TRUE;

}
void CZReportView::OnChangedTab(NMHDR* nmhdr, LRESULT* pRes)
{
	NMFOLDERTAB* nmtab=static_cast<NMFOLDERTAB*>( nmhdr);
	CString msg;
	switch (nmtab->iItem)
	{
	case 0:
		
		LoadZReportTable();
		
		break;
	case 1:
		LoadReturns();
		break;
	case 2:
		msg.Format (_T("%s  %d"),nmtab->pItem->GetText (),nmtab->iItem );
		MessageBoxHelper::ShowError(msg);
		break;
	}
	
	
}
