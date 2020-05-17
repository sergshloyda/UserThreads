// UserThreadsView.cpp : implementation of the CUserThreadsView class
//

#include "stdafx.h"
#include "UserThreads.h"

//#include "UserThreadsDoc.h"
#include "UserThreadsView.h"
#include "MainFrm.h"
#include "MainChildFrame.h"
#include "DlgInsert.h"
#include "DlgEnterCash.h"
#include "CheckDoc.h"
#include "CashPrinter.h"
#include "DlgSetQuantity.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define NAME_COL 2
#include "PSDlgInsertGood.h"
//#include "PPLAPrinter.h"
#define IDC_MYBUTTON 1001
#include "drvfr.h"
#include "TableValue1.h"
#include "Resource.h"
#include "Repository.h"
#define LCID_RUSSIAN MAKELCID(MAKELANGID(0x19, 0x01), SORT_DEFAULT)
/////////////////////////////////////////////////////////////////////////////
// CUserThreadsView

IMPLEMENT_DYNCREATE(CUserThreadsView, CFormView)

BEGIN_MESSAGE_MAP(CUserThreadsView, CFormView)
	//{{AFX_MSG_MAP(CUserThreadsView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_INSERT, OnInsert)
	ON_UPDATE_COMMAND_UI(ID_INSERT, OnUpdateInsert)
	ON_MESSAGE(WM_VIEW_CLIENT_INFO,OnViewClientInfo)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_TRANSACT,OnCheckButton)
	ON_UPDATE_COMMAND_UI(IDC_TRANSACT, OnUpdateCheckButton)
	ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FNDDLG_SHOW, &CUserThreadsView::OnSelectProductDlg)
	ON_BN_CLICKED(IDC_TRANSACT, &CUserThreadsView::OnTransactBtnClck)
	ON_CBN_KILLFOCUS(IDC_COMBO_NUM, OnKillfocusCombo)
	ON_NOTIFY(NM_RETURN,IDC_COMBO_NUM,OnComboBoxReturnPressed)
	
END_MESSAGE_MAP()





BEGIN_EVENTSINK_MAP(CUserThreadsView, CFormView)
    
	ON_EVENT(CUserThreadsView, IDC_GRID, 0x00000018 /* from OLE/COM Object Viewer */, OnAfterEditGrid, VTS_I4 VTS_I4 )
	ON_EVENT(CUserThreadsView, IDC_GRID, 0xfffffda6 /* KeyDown */, OnGridKeyDown, VTS_PI2 VTS_I2)
	ON_EVENT(CUserThreadsView, IDC_GRID, 0xfffffda8 /* OnClick */, OnClick, VTS_NONE)
	ON_EVENT(CUserThreadsView, IDC_GRID, 0x00000003 /* EnterCell */, OnEnterCell, VTS_NONE)

END_EVENTSINK_MAP()
/////////////////////////////////////////////////////////////////////////////
// CUserThreadsView construction/destruction

CUserThreadsView::CUserThreadsView()
	: CFormView(CUserThreadsView::IDD)
{
	//{{AFX_DATA_INIT(CUserThreadsView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_pBarCodeReader=NULL;
	m_nQtyMultiplicator=1;

	

}

CUserThreadsView::~CUserThreadsView()
{

	if(m_pBarCodeReader)
	m_pBarCodeReader=NULL;

}

void CUserThreadsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserThreadsView)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TRANSACT, m_btnPrintCheck);
	DDX_Control(pDX, IDC_FNDDLG_SHOW, m_btnFindDlg);
}



 void CUserThreadsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	m_pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();

	if(m_wndLblNumDoc.GetSafeHwnd()==NULL)
	{
		m_wndLblNumDoc.SubclassDlgItem (IDC_ST_NUM_CHECK,this);
		m_wndLblNumDoc.SetLabelFont (m_pMainDoc->m_FontMap[_T("Check")].get());
		m_wndLblNumDoc.SetColor (RGB(0,0,0));
		m_wndLblNumDoc.SetWindowText(_T("Единиц: 0"));
	}
	
	if(m_wndLblNumPos.GetSafeHwnd()==NULL)
	{
		m_wndLblNumPos.SubclassDlgItem (IDC_ST_NUM_POS,this);
		m_wndLblNumPos.SetLabelFont (m_pMainDoc->m_FontMap[_T("Check")].get());
		m_wndLblNumPos.SetColor (RGB(0,100,0));
		m_wndLblNumPos.SetWindowText(_T("Позиций: 0"));
		
	}
	if(m_wndLblSumma.GetSafeHwnd()==NULL)
	{
	
		m_wndLblSumma.SubclassDlgItem (IDC_ST_SUMM,this);
		m_wndLblSumma.SetLabelFont (m_pMainDoc->m_FontMap[_T("Check")].get());
		m_wndLblSumma.SetColor (RGB(255,0,0));
		m_wndLblSumma.SetWindowText(_T("Сумма :0.00"));
		
	}
		if(m_wndLblClient.GetSafeHwnd()==NULL)
	{
		
		m_wndLblClient.SubclassDlgItem (IDC_ST_CLIENT,this);

		m_wndLblClient.SetFont (m_pMainDoc->m_FontMap[_T("Check")].get());
		m_wndLblClient.SetColor (RGB(0,0,0));
		m_wndLblClient.SetWindowText (_T("X 1 "));
	}
		//////////////////////////////////////////////////////////////////////
		//Setup Initial Grid View
	m_wndGrid.CreateFromStatic (IDC_GRID,this);



	m_wndGrid.SetCols(9);
	m_wndGrid.SetRows(1);

	m_wndGrid.SetTextMatrix(0,0,_T("№ п/п"));
	m_wndGrid.SetTextMatrix(0,1,_T(" ШтрихКод        "));
	m_wndGrid.SetColDataType (1,flexDTString);
	
	m_wndGrid.SetTextMatrix(0,2,_T("Наименование            "));
	m_wndGrid.SetColDataType (2,flexDTString);
	
	m_wndGrid.SetTextMatrix(0,3,_T("Цена    "));
	m_wndGrid.SetColDataType (3,flexDTDouble);
	
	m_wndGrid.SetTextMatrix(0,4,_T("Ед.Изм."));
	m_wndGrid.SetColDataType (4,flexDTString);
	
	m_wndGrid.SetTextMatrix(0,5,_T("Кол-во"));
	m_wndGrid.SetColDataType (5,flexDTLong);
	
	m_wndGrid.SetTextMatrix(0,6,_T("Сумма    "));
	m_wndGrid.SetColDataType (6,flexDTDouble);
	
	m_wndGrid.SetTextMatrix(0,7,_T("code"));
	m_wndGrid.SetColDataType (7,flexDTString);
	m_wndGrid.SetTextMatrix(0,8,_T("line_no"));
	m_wndGrid.SetColDataType (8,flexDTLong);
	LOGFONT logFont;
	m_pMainDoc->m_FontMap[_T("Check")]->GetLogFont(&logFont);
	long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
	CString strFontName(logFont.lfFaceName);
	m_wndGrid.SetFontSize((float)szFont);
	m_wndGrid.SetFontName(strFontName);
	m_wndGrid.SetFontBold(logFont.lfWeight==FW_BOLD);
	m_wndGrid.SetFontItalic(logFont.lfItalic);


	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	CString strTitle="";
	CCheckDoc* pCheckDoc=GetDocument();
	strTitle.Format (_T("Товарный чек №-%s"),pCheckDoc->m_strDocId);
	AfxSetWindowText(pFrame->m_hWnd ,strTitle);

	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_nCurView =CHECK;

		CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
		if(pApp->pSplash )
		{
			pApp->pSplash->Kill ();
			//::WaitForSingleObject (pApp->pSplash->m_hThread,INFINITE);
		}
	//wait before splash window destroyed
			CString strComPort=m_pMainDoc->GetComPort ();
	OpenCommPort (strComPort);


m_btnPrintCheck.SetFont(m_pMainDoc->m_FontMap[_T("Check")].get());
m_btnFindDlg   .SetFont(m_pMainDoc->m_FontMap[_T("Check")].get());
m_wndCombo.Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST,CRect(1,1,1,1),this,IDC_COMBO_NUM);

m_wndCombo.ShowWindow(SW_HIDE);

m_wndCombo.SetFont(m_pMainDoc->m_FontMap[_T("Check")].get());
    

	m_hAccelTable = ::LoadAccelerators(AfxGetResourceHandle(), 
        MAKEINTRESOURCE(IDR_MAINFRAME)); 
    ASSERT(m_hAccelTable); 


	CToolBar* pBar = pFrame->GetToolBar(IDR_RETURN);
	if (pBar != NULL)
	{
		pFrame->ShowControlBar(pBar, pMainFrame->m_nCurView ==RETURN, FALSE);
		return ;
	}
	SetTimer(1,1000,NULL);


}

/////////////////////////////////////////////////////////////////////////////
// CUserThreadsView diagnostics

#ifdef _DEBUG
void CUserThreadsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CUserThreadsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif



CCheckDoc* CUserThreadsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCheckDoc)));
	return (CCheckDoc*)m_pDocument;
}

void CUserThreadsView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RepositionControls ();
	
	
}

int CUserThreadsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_wndLblNumDoc.SubclassDlgItem (IDC_ST_NUM_CHECK,this);

	return 0;
}


LRESULT CUserThreadsView::OnViewClientInfo(WPARAM wParam,LPARAM)
{

	CString txt=reinterpret_cast<LPCTSTR>(wParam);
	MessageBoxHelper::ShowError(txt);


	return 0L;
}



void CUserThreadsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	_variant_t vtNone(0L,VT_ERROR);
	CMainFrame* pMainFrame=static_cast<CMainFrame*>(AfxGetMainWnd());
	pMainFrame->PostMessage (WM_CHANGE_MULTIPLICATOR);
	if(m_wndGrid.GetSafeHwnd ()!=NULL)
	{
		LOGFONT logFont;
		pDoc->m_FontMap[_T("Check")]->GetLogFont(&logFont);
		long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
		CString strFontName(logFont.lfFaceName);
		m_wndGrid.SetFontSize((float)szFont);
		m_wndGrid.SetFontName(strFontName);
		m_wndGrid.SetFontBold(logFont.lfWeight==FW_BOLD);
		m_wndGrid.SetFontItalic(logFont.lfItalic);
	}
	/*m_LabelFont.DeleteObject ();
	m_LabelFont.CreatePointFont (pDoc->GetFontSize()*15,pDoc->GetFontName());*/
	if(m_wndLblNumDoc.GetSafeHwnd()!=NULL)
	{
		//m_wndLblNumDoc.SubclassDlgItem (IDC_ST_NUM_CHECK,this);}
		m_wndLblNumDoc.SetLabelFont (pDoc->m_FontMap[_T("Check")].get());
		m_wndLblNumDoc.SetColor (RGB(0,0,0));
		m_wndLblNumDoc.SetWindowText(_T("Единиц: 0"));
	}
	
	if(m_wndLblNumPos.GetSafeHwnd()!=NULL)
	{
		//m_wndLblNumPos.SubclassDlgItem (IDC_ST_NUM_POS,this);
		m_wndLblNumPos.SetLabelFont (pDoc->m_FontMap[_T("Check")].get());
		m_wndLblNumPos.SetColor (RGB(0,100,0));
		m_wndLblNumPos.SetWindowText(_T("Позиций: 0"));
		
	}
	if(m_wndLblSumma.GetSafeHwnd()!=NULL)
	{
	
		//m_wndLblSumma.SubclassDlgItem (IDC_ST_SUMM,this);
		m_wndLblSumma.SetLabelFont (pDoc->m_FontMap[_T("Check")].get());
		m_wndLblSumma.SetColor (RGB(255,0,0));
		m_wndLblSumma.SetWindowText(_T("Сумма :0.00"));
		
	}
		if(m_wndLblClient.GetSafeHwnd()!=NULL)
	{
		

		m_wndLblClient.SetFont (pDoc->m_FontMap[_T("Check")].get());
			m_wndLblClient.SetColor (RGB(255,0,255));
		m_wndLblClient.SetWindowText (_T("Client "));
	}
		if(m_btnPrintCheck.GetSafeHwnd()!=NULL)
		{
		m_btnPrintCheck.SetFont(pDoc->m_FontMap[_T("Check")].get());
		m_btnFindDlg   .SetFont(pDoc->m_FontMap[_T("Check")].get());
		}
		if((pHint!=NULL)&&(pHint->IsKindOf(RUNTIME_CLASS(CCheckDoc))))
		{
	
		CCheckDoc* pCheckDoc=(CCheckDoc*) pHint;
		const CCheckDoc::SalesLineItemsType& si=pCheckDoc->GetSalesLineItems();
		IVSFlexGridPtr spGrid=m_wndGrid.GetControlUnknown();
		m_wndGrid.SetRows(1);
		USES_CONVERSION;
		for(CCheckDoc::SalesLineItemsType::const_iterator it=si.cbegin();it!=si.cend();++it)
		{
			
				CStringW strAdd=L"";
				
				strAdd.Format(L"%d\t%s\t%s\t%.2f\t%s\t%d\t%.2f\t%s\t%d",
								spGrid->Rows,
								it->barcode.c_str(),
								it->descr.c_str(),
								it->price,
								it->unit.c_str(),
								it->qty,
								it->price*it->qty,
								it->code.c_str(),
								it->line_no);

				spGrid->AddItem(strAdd.AllocSysString(),vtNone);
			//	CString strMsg;
			//	Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
			//	boost::shared_ptr<Repository::ProductRest> regProduct=pRep->getProductRest();
			//	_variant_t val(0.0);
			//	regProduct->SetFilterValue(L"product",it->code);
			//	regProduct->SetFilterValue(L"stock",L"C0001");
			////	_variant_t val(0.0);
			//	regProduct->GetRest(val);
			//	val.ChangeType(VT_BSTR);
			//	CString rest=OLE2A(val.bstrVal);
			//	strMsg.Format (_T("Name:%s Rest:%s"),W2A(it->descr.c_str()),rest);
			//pMainFrame->m_wndOutput.AddMsgToBuildList(strMsg);
		}
		ShowInfoOnPanel();

		}
		RepositionControls ();
		SetTimer(1,500,0);


}

void CUserThreadsView::OnDestroy() 
{
	CloseCommPort ();
	CFormView::OnDestroy();
	
}

void CUserThreadsView::OnAfterEditGrid (long Row,long Col)
{
	CCheckDoc* pDoc=GetDocument();
	OnUpdate(this,NULL,pDoc);
	::SetFocus (m_wndGrid.m_hWnd );
}

void CUserThreadsView::OnInsert() 
{
	// TODO: Add your command handler code here
	CPSDlgInsertGood dlg(_T("Выберите товар для добавления в чек"),this,0);
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	CDlgInsert pgSelBarCode(this);
	CDlgSelectGood pgSelGood;
	CDlgFindAll pgFindAll(this);
	dlg.AddPage (&pgSelGood);
	dlg.AddPage (&pgSelBarCode);
	dlg.AddPage (&pgFindAll);
	int nRet = 0xf;

	nRet = dlg.DoModal();

	switch ( nRet )
	{
	case 0xf: 
		MessageBoxHelper::ShowError(_T("Dialog box could not be created!"));
		break;
	case IDOK:
		break;
	case IDCANCEL:
		break;
	default:
		// Do something.
		break;
	};
	::SetFocus (m_wndGrid.m_hWnd );
	
}

void CUserThreadsView::OnUpdateInsert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


void CUserThreadsView::OnGridKeyDown(short* KeyCode,short Shift)
{
	if(*KeyCode==VK_MULTIPLY)//VK_BACKSPACE
	{

	}
	else if (*KeyCode==VK_DELETE)
	{
	DeleteRow();	
	}
	else if(*KeyCode==VK_RETURN)
	TransactCheck();
}

void CUserThreadsView::DeleteRow()
{
	CCheckDoc* pDoc=GetDocument();
	CString strrow=m_wndGrid.GetTextMatrix(m_wndGrid.GetRow(),8);
	int Row=_ttoi(strrow);
	pDoc->DeleteLineNo(Row);
	OnUpdate(this,0,pDoc);
	ShowInfoOnPanel ();
}

void CUserThreadsView::ShowInfoOnPanel()
{
	CString strPosInfo;

	CCheckDoc* pDoc=GetDocument();
	strPosInfo.Format(_T("Позиций: %d"),pDoc->GetSalesLineItems().size());
	m_wndLblNumPos.SetText (strPosInfo);
	
	CString strUnitsInfo;
	strUnitsInfo.Format(_T("Единиц: %d"),(int)m_wndGrid.GetSumColumn (5));
	m_wndLblNumDoc.SetText(strUnitsInfo);
	
	CString strSumma;
	strSumma.Format (_T("Сумма : % .2f"),pDoc->GetCurSumma());

	m_wndLblSumma.SetText(strSumma);
	CString strMul;
	strMul.Format (_T("X %d"),m_nQtyMultiplicator);
	m_wndLblClient.SetText (strMul);


}

void CUserThreadsView::SetFontSetting()
{
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	std::shared_ptr<CFont> spFont=pDoc->m_FontMap[_T("Check")];
	GetDlgItem(IDC_TRANSACT)->SetFont(spFont.get());
	GetDlgItem(IDC_FNDDLG_SHOW)->SetFont(spFont.get());
	GetDlgItem(IDC_ST_NUM_CHECK)->SetFont(spFont.get());
	GetDlgItem(IDC_ST_NUM_POS)->SetFont(spFont.get());
	GetDlgItem(IDC_ST_SUMM)->SetFont(spFont.get());
	GetDlgItem(IDC_ST_CLIENT)->SetFont(spFont.get());
	LOGFONT logFont;
	spFont->GetLogFont(&logFont);
	long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
	CString strFontName(logFont.lfFaceName);
	m_wndGrid.SetFontSize((float)szFont);
	m_wndGrid.SetFontName(strFontName);
	m_wndGrid.SetFontBold(logFont.lfWeight==FW_BOLD);
	m_wndGrid.SetFontItalic(logFont.lfItalic);
}

void CUserThreadsView::TransactCheck()
{
	int nPosCount=m_wndGrid.GetRows()-m_wndGrid.GetCountHiddenRows ()-1;
	if(nPosCount==0) return;
	CDlgEnterCash dlg(this);
	int ret=dlg.DoModal();
	
	CCheckDoc* pDoc=GetDocument();
	CString strMsg;
	USES_CONVERSION;
	
	try
	{
		
		switch(ret)
		{
		case IDOK:
			pDoc->TransactCheck ();
			PrintCheck(dlg.m_flCash );
			pDoc->ClearCheck();
			m_wndGrid.SetRows (m_wndGrid.GetFixedRows());
			OnUpdate(this,0,pDoc);
			ShowInfoOnPanel();
			break;
		case IDCANCEL:
#ifdef _DEBUG
			MessageBoxHelper::ShowError(_T("IDCANCEL"));
#endif
			break;
		default:
			break;
		}
	}
	catch(_com_error &e)
	{
		
	
		CComPtr<ICreateErrorInfo> spCEI;
		HRESULT hr = CreateErrorInfo(&spCEI);
		strMsg.Format (_T("ВНИМАНИЕ!!!Это самая страшная ошибка из возможных!!!\n%s\nЧек не будет проведен!!! \n1)Попробуйте перезагрузить сервер \n2)Проверьте связь с сервером"),(char*)e.Description());
		spCEI->SetDescription(_bstr_t(strMsg));
		spCEI->SetSource(e.Source());
		CComQIPtr<IErrorInfo> spEI=spCEI;
		SetErrorInfo(0, spEI);
		_com_error e2(e.Error(),spEI);
		Register::ShowErrorMessage(e2);
		
	}
}

BOOL CUserThreadsView::RepositionControls()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CSize szBorder(2,2);
	rcClient.DeflateRect (szBorder);
	CRect rcInfo;
	rcInfo=rcClient;
	rcInfo.DeflateRect (0,int(rcClient.Height ()/1.3),0,0);
	CRect rcGrid;
	rcGrid.left=rcInfo.left ;
	rcGrid.top =rcClient.top;
	rcGrid.bottom=rcInfo.top-3;
	rcGrid.right=rcClient.right;
	
	if(::IsWindow (GetDlgItem(IDC_INFO_ABOUT_CHECK)->GetSafeHwnd()))
	{
		GetDlgItem(IDC_INFO_ABOUT_CHECK)->SetWindowPos (&wndBottom ,rcInfo.left,rcInfo.top ,
			rcInfo.Width (),rcInfo.Height () ,
			SWP_NOZORDER|SWP_SHOWWINDOW);
		
	}
	
	if(::IsWindow (m_wndGrid.GetSafeHwnd()))
	{
		m_wndGrid.MoveWindow(rcGrid);
		VARIANT v; 
		V_VT(&v) = VT_ERROR; 
		//m_wndGrid.SetAllowUserResizing(TRUE);
		//m_wndGrid.SetAutoSizeMode (flexAutoSizeColWidth);
		/*long lCols=2;
		
		_variant_t varColEnd(lCols,VT_I4);

		m_wndGrid.AutoSize (0L,varColEnd,v,v);*/
		
	/*	long lClientWidth=m_wndGrid.GetClientWidth ();
		long lWithoutNameColWidth=0;
		
		for(long c=0;c<m_wndGrid.GetCols();c++)
		{
			if(c==NAME_COL)continue;
			lWithoutNameColWidth+=m_wndGrid.GetColWidth (c);
		}
		m_wndGrid.SetColWidth (NAME_COL,lClientWidth-lWithoutNameColWidth);*/
	IVSFlexGridPtr m_spGoodsGrid=m_wndGrid.GetControlUnknown ();
	m_spGoodsGrid->put_AutoSizeMode(flexAutoSizeColWidth);
	m_spGoodsGrid->put_AllowUserResizing (flexResizeColumns);
	m_spGoodsGrid->put_SelectionMode(flexSelectionByRow);
	m_spGoodsGrid->AutoSize(2,_variant_t(2L),v,v);

	}
	if(::IsWindow(GetDlgItem(IDC_ST_NUM_CHECK)->GetSafeHwnd()))
	{
		CSize szOffset(280,20);
		CSize szLabel(270,35);
		CRect rcWnd;
		CWnd* pWnd=GetDlgItem(IDC_ST_NUM_CHECK);
		
		rcWnd.left=rcInfo.left +szOffset.cx ;
		rcWnd.top =rcInfo.top+szOffset.cy;
		rcWnd.bottom =rcWnd.top+szLabel.cy ;
		rcWnd.right =rcWnd.left +szLabel.cx;
		
		pWnd->MoveWindow (rcWnd);
		
	}
	
	if(::IsWindow(GetDlgItem(IDC_ST_NUM_POS)->GetSafeHwnd()))
	{
		CSize szOffset(280,80);
		CSize szLabel(270,35);
		CRect rcWnd;
		CWnd* pWnd=GetDlgItem(IDC_ST_NUM_POS);
		
		rcWnd.left=rcInfo.left +szOffset.cx ;
		rcWnd.top =rcInfo.top+szOffset.cy;
		rcWnd.bottom =rcWnd.top+szLabel.cy ;
		rcWnd.right =rcWnd.left +szLabel.cx;
		
		pWnd->MoveWindow (rcWnd);
		
	}
	if(::IsWindow(GetDlgItem(IDC_ST_SUMM)->GetSafeHwnd()))
	{
		CSize szOffset(550,20);
		CSize szLabel(450,200);
		CRect rcWnd;
		CWnd* pWnd=GetDlgItem(IDC_ST_SUMM);
		
		rcWnd.left=rcInfo.left +szOffset.cx ;
		rcWnd.top =rcInfo.top+szOffset.cy;
		rcWnd.bottom =rcWnd.top+szLabel.cy ;
		rcWnd.right =rcWnd.left +szLabel.cx;
		
		pWnd->MoveWindow (rcWnd);
		
	}
	if(::IsWindow(GetDlgItem(IDC_ST_CLIENT)->GetSafeHwnd()))
	{
		CSize szOffset(550,80);
		CSize szLabel(200,40);
		CRect rcWnd;
		CWnd* pWnd=GetDlgItem(IDC_ST_CLIENT);
		
		rcWnd.left=rcInfo.left +szOffset.cx ;
		rcWnd.top =rcInfo.top+szOffset.cy;
		rcWnd.bottom =rcWnd.top+szLabel.cy ;
		rcWnd.right =rcWnd.left +szLabel.cx;
		
		pWnd->MoveWindow (rcWnd);
		
	}
	if(::IsWindow(m_btnPrintCheck.GetSafeHwnd()))
	{
	CSize szButton(200,50);
	CSize szOffset(20,15);
	CRect rcButton;
	rcButton.left=rcInfo.left +szOffset.cx ;
	rcButton.top =rcInfo.top+szOffset.cy;
	rcButton.bottom =rcButton.top+szButton.cy;
	rcButton.right =rcButton.left +szButton.cx;
	rcButton.NormalizeRect();
	m_btnPrintCheck.MoveWindow (rcButton);
	CString strCaption;
	strCaption.LoadStringA(IDS_CHECK_BUTTON_LABEL);
	m_btnPrintCheck.SetWindowTextA(strCaption);
	

	}
	if(::IsWindow(m_btnFindDlg.GetSafeHwnd()))
	{
		CSize szButton(200,50);
		CSize szOffset(20,5);
		CRect rcAnchorButton;
		m_btnPrintCheck.GetWindowRect(rcAnchorButton);
		ScreenToClient(rcAnchorButton);
		CRect rcButton;
		rcButton.left=rcAnchorButton.left ;
		rcButton.top =rcAnchorButton.bottom+szOffset.cy;
		rcButton.bottom =rcButton.top+szButton.cy;
		rcButton.right =rcButton.left +szButton.cx;
		rcButton.NormalizeRect();
		m_btnFindDlg.MoveWindow (rcButton);
		CString strCaption;
		strCaption.LoadStringA(IDS_SELECT_DLG_CAPTION);
		m_btnFindDlg.SetWindowTextA(strCaption);

	}

	return TRUE;
}

void CUserThreadsView::SetTitle(LPCTSTR strNewTitle)
{
	CMainChildFrame* pFrame=static_cast<CMainChildFrame*>(GetParent());
	AfxSetWindowText(pFrame->m_hWnd ,strNewTitle);
}




void CUserThreadsView::PrintCheck(float flCash)
{

	
	CString strSection       = "KKM";
	
	CString strStringItem       = "Printer";
	CString strPrinterName;
		CMainFrame* pMainFrm=(CMainFrame*)AfxGetMainWnd();
	
	strPrinterName =AfxGetApp()->GetProfileString(strSection,strStringItem,_T("Samsung"));
 if(strPrinterName==_T("Штрих ФР-К")){
		CShtrihFRK Driver;
		CTableValue table;
		table.AddField (_T("pos"));
		table.AddField (_T("name"));
		table.AddField (_T("qty"));
		table.AddField (_T("units"));
		table.AddField (_T("price"));
		double SummTotal=0.0;
		
		CString strMsg;
		CCheckDoc* pDoc=GetDocument();
		int i=0;
		USES_CONVERSION;
		for(CCheckDoc::SalesLineItemsType::const_iterator it=pDoc->GetSalesLineItems().cbegin();it!=pDoc->GetSalesLineItems().cend();++it){
			table.AddNewLine ();
			COleVariant val=(long)(++i);
			table.SetFieldValue (_T("pos"),&val);
			
			val.Clear ();
			std::wstring descr=it->descr;
			boost::trim(descr);
			//val.SetString (strName,VT_BSTR);
			val.SetString(W2A(descr.c_str()),VT_BSTR);
			table.SetFieldValue (_T("name"),&val);
			
			val.Clear ();
			long lQty=it->qty;
			val=lQty;
			table.SetFieldValue (_T("qty"),&val);
			val.Clear ();
			CString strUnits=W2A(it->unit.c_str());
			strUnits.TrimRight ();
			val.SetString (strUnits,VT_BSTR);
			table.SetFieldValue (_T("units"),&val);
			
			double price=it->price;
			COleCurrency cyPrice(long(price),0);
			val.Clear();
			val.cyVal=cyPrice;
			table.SetFieldValue (_T("price"),&val);
			SummTotal+=price*it->qty;
		
		}
		
	
		
		if(flCash<SummTotal)
		{
			strMsg.Format (_T("Сумма чека:%.2f Внесение в кассу%.2f"),SummTotal,flCash);
			MessageBoxHelper::ShowError(strMsg);
		}
		long NumCheck=0;
		COleCurrency cySummTotal(long(SummTotal),0);
		COleCurrency cyCash(long(flCash),0);
		Driver.PrintCheck (&table,(CURRENCY)cySummTotal,(CURRENCY)cyCash,false,1,&NumCheck);
		//CMainFrame* pMainFrm=(CMainFrame*)AfxGetMainWnd();
		strMsg.Format (_T("ErrNumber:%x ErrDescr:%s"),Driver.drv.GetResultCode(),Driver.m_strResultCodeDescription );
		pMainFrm->m_strErrorMsg=strMsg;
		//pMainFrm->m_wndOutput.AddMsgToBuildList(strMsg);
		//pMainFrm->m_wndOutput.FillBuildWindow();
		
	}
	else
	{

MessageBoxHelper::ShowError("Print check");
	}
	
	
	
}






BOOL CUserThreadsView::OpenCommPort(LPCTSTR strCommPort)
{


m_pBarCodeReader=new CBarcode(this->m_hWnd ,strCommPort);
if(!m_pBarCodeReader->InitComm ())
return FALSE;
else return TRUE;
}

BOOL CUserThreadsView::CloseCommPort()
{

m_pBarCodeReader->CloseCommPort();
if(m_pBarCodeReader)
delete m_pBarCodeReader;
return TRUE;
}


void CUserThreadsView::OnComboBoxReturnPressed(NMHDR* pNMHDR, LRESULT* pResult)
{
	CB_NMRETURN* pNMRTRN = (CB_NMRETURN*)pNMHDR;
	CString strCombo=pNMRTRN->strText;
	int iRow,iCol;
	iRow=m_wndGrid.GetRowSel();
	iCol=m_wndGrid.GetColSel();
	int qty=_ttoi(strCombo);
	CCheckDoc* pCheckDoc=GetDocument();
	CString strrow=m_wndGrid.GetTextMatrix(iRow,8);
	int editRow=_ttoi(strrow);
	CCheckDoc::SalesLineItemsType& si=const_cast<CCheckDoc::SalesLineItemsType&>(pCheckDoc->GetSalesLineItems());

	CCheckDoc::SalesLineItemsType::iterator it=std::find_if(si.begin(),si.end(),[editRow](CCheckDoc::SalesItemLine line)
	{
		return line.line_no==editRow;
	});
	if(it!=si.end())
		it->qty=qty;

	m_wndCombo.ShowWindow(SW_HIDE);
	OnUpdate(this,NULL,pCheckDoc);
	m_wndCombo.ShowWindow(SW_HIDE);
	*pResult=0;
}

//BOOL CUserThreadsView::AddItem(CStringList &strList)
//{
//	CString strItem;
//	_variant_t v; 
//	V_VT(&v) = VT_ERROR;
//	POSITION pos = strList.GetHeadPosition();
//	strItem.Format(_T("%d"),m_wndGrid.GetRows ()-m_wndGrid.GetFixedRows ()+1);
//	while( pos != NULL )
//	{
//		strItem+="\t";
//		strItem += strList.GetNext( pos );
//	}
//	
//	m_wndGrid.AddItem (strItem,v);
//	strList.RemoveAll ();
//	ShowInfoOnPanel();
//	return TRUE;
//}




void CUserThreadsView::OnCheckButton() 
{
	TransactCheck();
}
void CUserThreadsView::OnUpdateCheckButton(CCmdUI* pCmdUI) 
{
	CCheckDoc* pDoc=GetDocument();
	CString msg;
	msg.Format(_T("OnUpdateButton with nID=%d\n"),pCmdUI->m_nID);
	//OutputDebugString(msg);
	CWnd* pWnd=GetDlgItem(pCmdUI->m_nID);
	if(pWnd!=NULL)
		pWnd->EnableWindow(pDoc->GetSalesLineItems().size()>0);

	
	
}
void CUserThreadsView::OnIdleUpdateCmdUI()
{
	UpdateDialogControls(this, TRUE);
}


void CUserThreadsView::ShowKKMError()
{
	CMainFrame* pMainFrm=(CMainFrame*)AfxGetMainWnd();

}





BOOL CUserThreadsView::PreTranslateMessage(MSG* pMsg) 
{
	//OutputDebugString(_T("CUserThreadsView::PreTranslateMessage"));
	if (pMsg->message >= WM_KEYFIRST && 
		pMsg->message <= WM_KEYLAST) 
	{
		
#ifdef OutputDebugString_ENABLED

		OutputDebugString(_T("CUserThreadsView::PreTranslateMessage\n"));
#endif

		if (::TranslateAccelerator(m_hWnd, m_hAccelTable, pMsg)) {
			return(TRUE);
		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}


void CUserThreadsView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
if(nIDEvent==1){
		::SetFocus(m_btnPrintCheck.m_hWnd);
			_variant_t vr,vc(3L); 
			
			//V_VT(&v) = VT_ERROR;
			vr.lVal=m_wndGrid.GetRows()-1;
		m_wndGrid.Select(m_wndGrid.GetRows()-1,2,vr,vc);
		OnEnterCell();
		KillTimer(1);
	}


	CFormView::OnTimer(nIDEvent);
}


void CUserThreadsView::OnSelectProductDlg()
{
	OnInsert();// TODO: Add your control notification handler code here
}


void CUserThreadsView::OnTransactBtnClck()
{
	// TODO: Add your control notification handler code here
	TransactCheck();
}

void CUserThreadsView::OnEnterCell()
{
CMainFrame* pMainFrm=(CMainFrame*)AfxGetMainWnd();
CString sCurStrCode=m_wndGrid.GetTextMatrix(m_wndGrid.GetRow(),7);
Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
sCurStrCode.Trim();
USES_CONVERSION;
std::wstring curProduct_code(A2W(sCurStrCode));
refProducts->FindByCode(curProduct_code);
Repository::ReferenceItem product=refProducts->getCurrent();
CString name=W2A(product->_descr.c_str());
name.Trim();
boost::shared_ptr<Repository::ProductRest> regProduct=pRep->getProductRest();
_variant_t val(0.0);
regProduct->SetFilterValue(L"product",curProduct_code);
regProduct->SetFilterValue(L"stock",L"C0001");
			//	_variant_t val(0.0);
regProduct->GetRest(val);
val.ChangeType(VT_BSTR);
CString rest=OLE2A(val.bstrVal);
CString strMsg;
strMsg.Format(_T("%s Rest:%s"),name,rest);
pMainFrm->SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPCTSTR)strMsg);
}

void CUserThreadsView::OnClick()
{
	if(m_wndGrid.GetColSel()==5)
	{
		 
	
	CRect rcWnd;
	m_wndGrid.GetWindowRect(rcWnd);

	long left=m_wndGrid.GetCellLeft(),top=m_wndGrid.GetCellTop();
	long width=m_wndGrid.GetCellWidth(),height=m_wndGrid.GetCellHeight();
	CClientDC dc(this);

	int left_dc=m_wndGrid.TwipsToPixelX(left);
	int top_dc=m_wndGrid.TwipsToPixelY(top);
	int width_dc=m_wndGrid.TwipsToPixelX(width);;
	int height_dc=m_wndGrid.TwipsToPixelY(height);
	ScreenToClient(&rcWnd);
	CRect rcCell;
	rcCell.top=rcWnd.top+top_dc;
	rcCell.left=rcWnd.left+left_dc;
	rcCell.bottom=rcCell.top+height_dc;
	rcCell.right=rcCell.left+width_dc;
	m_wndCombo.ShowWindow(SW_NORMAL);
	m_wndCombo.ResetContent();
	m_wndCombo.SetWindowPos(&CWnd::wndTop,rcCell.left,rcCell.top,
		width_dc,height_dc+200,SWP_SHOWWINDOW);
	for(int i=1;i<11;i++){
		CString msg;
		msg.Format("%d",i);
	m_wndCombo.AddString(msg);
	}
	m_wndCombo.SetFocus();
	}
	//UpdateData(FALSE);

}

void CUserThreadsView::OnKillfocusCombo() 
{
	// TODO: Add your control notification handler code here
	CString strCombo;
	int iRow,iCol;
	iRow=m_wndGrid.GetRowSel();
	iCol=m_wndGrid.GetColSel();
	m_wndCombo.GetWindowText(strCombo);
	int qty=_ttoi(strCombo);
	CCheckDoc* pCheckDoc=GetDocument();
	CString strrow=m_wndGrid.GetTextMatrix(iRow,8);
	int editRow=_ttoi(strrow);
	CCheckDoc::SalesLineItemsType& si=const_cast<CCheckDoc::SalesLineItemsType&>(pCheckDoc->GetSalesLineItems());
	
	CCheckDoc::SalesLineItemsType::iterator it=std::find_if(si.begin(),si.end(),[editRow](CCheckDoc::SalesItemLine line)
	{
		return line.line_no==editRow;
	});
	if(it!=si.end())
		it->qty=qty;

	m_wndCombo.ShowWindow(SW_HIDE);
	OnUpdate(this,NULL,pCheckDoc);
	
}





BOOL CUserThreadsView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	NMHDR* pnmh = (LPNMHDR) lParam;
	if((pnmh->code==NM_FONTCHANGED)||(pnmh->idFrom==IDC_SET_FNT))
	{
	
		SetFontSetting();
		*pResult=0;
	}
	return CFormView::OnNotify(wParam, lParam, pResult);
}
