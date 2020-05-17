// DlgFindAll.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgFindAll.h"
#include "PSDlgInsertGood.h"
#include "Repository.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFindAll property page

IMPLEMENT_DYNCREATE(CDlgFindAll, CPropertyPage)

CDlgFindAll::CDlgFindAll(CView* pParent) : CPropertyPage(CDlgFindAll::IDD)
{
	//{{AFX_DATA_INIT(CDlgFindAll)
	m_strFind = _T("");
	//}}AFX_DATA_INIT


}

CDlgFindAll::CDlgFindAll() : CPropertyPage(CDlgFindAll::IDD)
{


}
CDlgFindAll::~CDlgFindAll()
{
}

void CDlgFindAll::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFindAll)
	DDX_Control(pDX, IDC_EDIT3, m_wndEdit);
	DDX_Text(pDX, IDC_EDIT3, m_strFind);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BTN_FIND, m_btnFind);
}


BEGIN_MESSAGE_MAP(CDlgFindAll, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgFindAll)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_RETURN, IDC_EDIT3, OnEditReturnPressed)
	ON_BN_CLICKED(IDC_BTN_FIND, &CDlgFindAll::OnBnClickedButton)
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////
BEGIN_EVENTSINK_MAP(CDlgFindAll, CPropertyPage)
    
	
	ON_EVENT(CDlgFindAll, IDC_GRID3, 0xfffffda6 /* KeyDown */, OnGridKeyDown, VTS_PI2 VTS_I2)
	ON_EVENT(CDlgFindAll, IDC_GRID3, 0x00000003 /* EnterCell */, OnEnterCell, VTS_NONE)
	ON_EVENT(CDlgFindAll, IDC_GRID3, 0x0000000b , AfterScroll, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
END_EVENTSINK_MAP()
/////////////////////////////////////////////////////////////////////////////
// CDlgFindAll message handlers

BOOL CDlgFindAll::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	LOGFONT logFont;
	pDoc->m_FontMap[_T("Dialogs")]->GetLogFont(&logFont);
	long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
	CString strFontName(logFont.lfFaceName);
	m_Font.CreatePointFont (szFont*10,strFontName);
	m_wndEdit.SetFont (pDoc->m_FontMap[_T("Dialogs")].get());
	m_Grid.CreateFromStatic(IDC_GRID3,this);
	m_Grid.SetFontName (strFontName);
	m_Grid.SetFontSize((float)(szFont));
	SetupGrid();
	blGridIsLoaded=false;
	//HWND hwndGrid=m_wndGrid.Detach ();
	//m_wndGrid.SubclassWindow (hwndGrid);

	//RepositionControls();
	// TODO: Add extra initialization here
	

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFindAll::SetupGrid()
{
	IVSFlexGridPtr spGoodsGrid=m_Grid.GetControlUnknown ();
	spGoodsGrid->put_AutoSizeMode(flexAutoSizeColWidth);
	spGoodsGrid->put_AllowUserResizing (flexResizeColumns);
	spGoodsGrid->put_SelectionMode(flexSelectionByRow);
	m_Grid.SetRows(1);
	m_Grid.SetCols(1);
	
	m_Grid.SetFormatString (_T("|<Код|<Наименование|<Ед.Изм.|<Цена|<Остаток"));

}

void CDlgFindAll::LoadSelectedProducts(const std::wstring& filter)
{
	USES_CONVERSION;
	try
	{
		
		SelectedProducts.clear();
		Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
		boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();

		if(refProducts->SelectItemsByAttribute(IReference::ListOfAttr::Descr(),filter)>0)
		{

			do{

				RefItemPtr curProduct=refProducts->getCurrent();
			
					std::wstring unit_descr;
				if(!curProduct->IsFolder()){
					_variant_t var=curProduct->getAttribute(Products::ListOfAttr::BaseUnit());
					unit_descr=(_bstr_t)var;
				
				GridLine line=boost::make_tuple(curProduct->_code,curProduct->_descr,unit_descr);
				SelectedProducts.push_back(line);
				}
			
			}while(refProducts->getNext());
		
			std::sort(SelectedProducts.begin(),SelectedProducts.end(),[](GridLine line1,GridLine line2)
			{
				return (line1.get<2>()<line2.get<2>());
			});
		
		}
	}
	catch (DbContext::DbContextError &e)
	{
		MessageBoxHelper::ShowError(e.what());

	}
	catch(_com_error& err)
	{
		MessageBoxHelper::PrintComError(err);
	}
}

void CDlgFindAll::LoadItemsInGrid(long begin_row)
{

	CWaitCursor wait;
	USES_CONVERSION;
	_variant_t vtNone(0L,VT_ERROR),colBeg(1L),colEnd(1L);
	Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
	boost::shared_ptr<Repository::TypePriceReference> refTypePrice=pRep->getType_price();
	refTypePrice->FindByCode(A2W(CUserThreadsApp::GetDocument<CMainDocument>()->m_strTypePriceId));
	Repository::ReferenceItem curTypePrice=refTypePrice->getCurrent();
	boost::shared_ptr<Repository::PricesReference> refPrice=pRep->getPrices();
	boost::shared_ptr<Repository::ProductRest> regProduct=pRep->getProductRest();
	std::wstring typePrice=curTypePrice->_code;
	int szSelProds=SelectedProducts.size();
	long client_h=m_Grid.GetClientHeight();
	long row_h=max(m_Grid.GetRowHeight(0),1);
	int rowsInClient=client_h/row_h;
	int gap=0;
	if(szSelProds>rowsInClient) gap=max((m_Grid.GetRows()),0);
	for(std::vector<GridLine>::const_iterator it=SelectedProducts.begin()+gap;it!=SelectedProducts.end();++it)
	{
#pragma region //#LoadGridLine

		CString strItem='\t';
		GridLine line=(*it);
		std::wstring curProduct_code=line.get<0>();
		std::wstring price_code=curProduct_code+typePrice;
		strItem+=W2A(curProduct_code.c_str());
		strItem+='\t';
		strItem+=W2A(line.get<1>().c_str());
		strItem+='\t';
		strItem+=W2A(line.get<2>().c_str());
		strItem+='\t';
		if(refPrice->FindByCode(price_code)){
			//refPrice->SelectItemsByAttribute(IReference::ListOfAttr::Descr(),L"Домоде");

			Repository::ReferenceItem curPrice=refPrice->getCurrent();
			if(curPrice!=nullptr)
			{
				_variant_t var=curPrice->getAttribute(Prices::ListOfAttr::PriceValue());
				if(var.vt==VT_NULL)
					strItem+="";
				else
					strItem+=W2A((_bstr_t)var);
			}
			_variant_t val(0.0);
			regProduct->SetFilterValue(L"product",curProduct_code);
			regProduct->SetFilterValue(L"stock",L"C0001");
			//	_variant_t val(0.0);
			regProduct->GetRest(val);
			val.ChangeType(VT_BSTR);
			strItem+='\t';
			strItem+=W2A((_bstr_t)val);
		}
		m_Grid.AddItem(strItem, vtNone); 
#pragma endregion //#LoadGridLine
		long curRow=m_Grid.GetRows()-1;

	
		blGridIsLoaded=((it+1)==SelectedProducts.end());
		if(curRow>(rowsInClient+5)) break;

	}
	IVSFlexGridPtr spGrid=m_Grid.GetControlUnknown();
	colEnd=spGrid->Cols-1;
	spGrid->AutoSize(colBeg,colEnd,vtNone,vtNone);

}

void CDlgFindAll::AfterScroll(long OldTopRow,long OldLeftCol,long NewTopRow, long NewLeftCol)
{
	if((OldTopRow<NewTopRow)&&(!blGridIsLoaded))
		LoadItemsInGrid(OldTopRow);
}

void CDlgFindAll::UpdateLayout()
{
	int nGap=0;
	const int iBorder = 3;
	CRect rc;
	GetClientRect(&rc);
	InflateRect(&rc, -iBorder, -iBorder);


	if(!::IsWindow (m_Grid.m_hWnd)) return;
	if(!::IsWindow (m_wndEdit.m_hWnd)) return;
	// move and position main label
	CRect rcGrid;
	CRect rcEdit;
	m_wndEdit.GetWindowRect (&rcEdit);
	ScreenToClient(&rcEdit);
	CRect rcBtnFind;
	m_btnFind.GetWindowRect(&rcBtnFind);
	ScreenToClient(&rcBtnFind);
	int nBtnWidth=rcBtnFind.Width();
	rcEdit.top =rcBtnFind.top=rc.top;
	rcBtnFind.right =rc.right ;
	rcBtnFind.left=rc.right-nBtnWidth;
	CWindowDC dc(this);
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	LOGFONT logFont;
	pDoc->m_FontMap[_T("Dialogs")]->GetLogFont(&logFont);
	nGap=-logFont.lfHeight/2;
	rcBtnFind.bottom=rc.top-logFont.lfHeight+nGap;
	m_btnFind.MoveWindow(&rcBtnFind);
	rcEdit.left =rc.left ;
	rcEdit.right =rcBtnFind.left-nGap;


	rcEdit.bottom =rcBtnFind.bottom;;
	m_wndEdit.MoveWindow (&rcEdit);
	rcGrid=rc;
	rcGrid.top=rcEdit.bottom +iBorder;
	//rcGrid.left = rcTree.right + iBorder + 2;
	m_Grid.MoveWindow(&rcGrid);
		
	long C1Width=(long)(rcGrid.Width ()*0.10);
	long C2Width=(long)(rcGrid.Width ()*0.50);
	long C3Width=(long)(rcGrid.Width ()*0.10);
	long C4Width=(long)(rcGrid.Width ()*0.15);
	long C5Width=(long)(rcGrid.Width ()*0.15);
	m_Grid.SetColWidth (0,0);
	m_Grid.SetColWidth(1,C1Width*m_Grid.TwipsPerPixelX ());
	m_Grid.SetColWidth(2,C2Width*m_Grid.TwipsPerPixelX ());
	m_Grid.SetColWidth(3,C3Width*m_Grid.TwipsPerPixelX ());
	m_Grid.SetColWidth(4,C4Width*m_Grid.TwipsPerPixelX ());
	m_Grid.SetColWidth(5,C5Width*m_Grid.TwipsPerPixelX ());
}

void CDlgFindAll::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	UpdateLayout();
}
void CDlgFindAll::OnEditReturnPressed(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMRETURN* pNMRTRN = (NMRETURN*)pNMHDR;
	// TODO: Add your control notification handler
try{
	m_Grid.SetRows(1);	//       code here
	CString strName=pNMRTRN->pszText ;
	USES_CONVERSION;
	LoadSelectedProducts(A2W(strName));
	LoadItemsInGrid();
			
		//_RecordsetPtr pRst;
		//TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		//
		//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		//
		//HRESULT hr=pRst->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
		//	adOpenKeyset, adLockBatchOptimistic, adCmdText);
		//if (hr!=S_OK)
		//{
		//	AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
		//	return ;
		//}
		//SetupGrid(pRst);
		//while(1)
		//{
		//	::Sleep(100);
		//	if(pRst->State!=adStateFetching)//not more fetching rows
		//	{
		//		break;
		//	pRst->Close();
		//	}
		//}
	UpdateLayout();
	::SetFocus(m_Grid.m_hWnd );
	}
	catch (DbContext::DbContextError &e)
	{
		MessageBoxHelper::ShowError(e.what());

	}
	catch(_com_error& err)
	{
		MessageBoxHelper::ShowError(err.Description());
	}
	*pResult = 0;
}
//////////////////////////////////////////////////////////////////////////
void CDlgFindAll::OnGridKeyDown(short* KeyCode,short Shift)
{
	if(*KeyCode==VK_RETURN)//VK_RETURN
	{
		CPSDlgInsertGood* dlgPS=static_cast<CPSDlgInsertGood*>(GetParent());
		
		CString strCode=m_Grid.GetTextMatrix(m_Grid.GetRow(),1);
		strCode.TrimRight();
		dlgPS->OnSelectGood (strCode);
		::SetFocus(m_Grid.m_hWnd );
	
	}
}
/////////////////////////////////////////////////////////////////////////////
void CDlgFindAll::OnEnterCell()
{
	CPSDlgInsertGood* dlgPS=static_cast<CPSDlgInsertGood*>(GetParent());
	dlgPS->m_strSelectProduct=m_Grid.GetTextMatrix(m_Grid.GetRow(),1);
	CString strRest(_T("0")),strTipTxt;
	strTipTxt=m_Grid.GetTextMatrix(m_Grid.GetRow(),2);
	strTipTxt+=_T(" Остаток : ");
	strRest=m_Grid.GetTextMatrix(m_Grid.GetRow(),5);
	strTipTxt+=strRest;
	strTipTxt+=_T(" шт.");
	dlgPS->SetTipText (strTipTxt);
}
BOOL CDlgFindAll::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(1,500,NULL);
	return TRUE;
}

void CDlgFindAll::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		::SetFocus(m_wndEdit.m_hWnd);
		KillTimer(1);
		break;
	default:

	
	CPropertyPage::OnTimer(nIDEvent);
	}
}


void CDlgFindAll::OnBnClickedButton()
{
	m_Grid.SetRows(1);
	try{	//       code here
		CString strName;
		m_wndEdit.GetWindowTextA(strName) ;
		strName.Trim();
		USES_CONVERSION;
		LoadSelectedProducts(A2W(strName));
		LoadItemsInGrid();

		//_RecordsetPtr pRst;
		//TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		//
		//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		//
		//HRESULT hr=pRst->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
		//	adOpenKeyset, adLockBatchOptimistic, adCmdText);
		//if (hr!=S_OK)
		//{
		//	AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
		//	return ;
		//}
		//SetupGrid(pRst);
		//while(1)
		//{
		//	::Sleep(100);
		//	if(pRst->State!=adStateFetching)//not more fetching rows
		//	{
		//		break;
		//	pRst->Close();
		//	}
		//}
		UpdateLayout();
		::SetFocus(m_Grid.m_hWnd );
	}
	catch (DbContext::DbContextError &e)
	{
		MessageBoxHelper::ShowError(e.what());

	}
	catch(_com_error& err)
	{
		MessageBoxHelper::ShowError(err.Description());
	}
}


BOOL CDlgFindAll::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			if(pMsg->hwnd==m_Grid.m_hWnd){

				m_Grid.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
				return TRUE;}
		}
	}
	return CPropertyPage::PreTranslateMessage(pMsg);
}
