// DlgInsert.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "DlgInsert.h"
#include "PSDlgInsertGood.h"
#include "Repository.h"
#include "WntRetEdit.h"
#include "MainDocument.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgInsert dialog
 int CDlgInsert::stnLen =0;

CDlgInsert::CDlgInsert(CView* pParent)
	: CPropertyPage(CDlgInsert::IDD)
{
	//{{AFX_DATA_INIT(CDlgInsert)
	m_strBarCode = _T("");
	
	//}}AFX_DATA_INIT

	
}


void CDlgInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInsert)
	DDX_Control(pDX, IDC_BUTTON1, m_btnBarCodeFind);
	DDX_Control(pDX, IDC_EDIT, m_wndEdit);
	DDX_Text(pDX, IDC_EDIT, m_strBarCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInsert, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgInsert)
	ON_WM_SIZE()
	ON_MESSAGE(WM_SETFOCUSGRID,OnSetFocusToGrid)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RETURN, IDC_EDIT, OnEditReturnPressed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CDlgInsert, CPropertyPage)
  	ON_EVENT(CDlgInsert, IDC_GRID2, 0xfffffda6 /* KeyDown */, OnGridKeyDown, VTS_PI2 VTS_I2)
	ON_EVENT(CDlgInsert, IDC_GRID2, 0x00000003 /* KeyDown */, OnEnterCell, VTS_NONE)
	ON_EVENT(CDlgFindAll, IDC_GRID2, 0x0000000b , AfterScroll, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////

void CDlgInsert::SetupGrid()
{
	
	IVSFlexGridPtr spGoodsGrid=m_Grid.GetControlUnknown ();
	spGoodsGrid->put_AutoSizeMode(flexAutoSizeColWidth);
	spGoodsGrid->put_AllowUserResizing (flexResizeColumns);
	spGoodsGrid->put_SelectionMode(flexSelectionByRow);
	m_Grid.SetRows(1);
	m_Grid.SetCols(1);

	m_Grid.SetFormatString (_T("|<Код|<Наименование|<Ед.Изм.|<Цена|<Остаток|<ШтрихКод"));
}


void CDlgInsert::OnGridKeyDown(short* KeyCode,short Shift)
{
	short kode=0;
	CPSDlgInsertGood* dlgPS=static_cast<CPSDlgInsertGood*>(GetParent());
	if(*KeyCode==VK_DELETE)
	{
		m_strBarCode.Empty();
		m_wndEdit.SetWindowText(m_strBarCode);
	}
	else if(*KeyCode==VK_BACK)
	{
		CString strText;
		m_wndEdit.GetWindowText(strText);
		if(m_strBarCode.GetLength ()>0)
		{
			m_strBarCode=m_strBarCode.Left (m_strBarCode.GetLength ()-1);
			m_wndEdit.SetWindowText(m_strBarCode);
		}
		
		
	}

	else	if(*KeyCode==VK_RETURN)//VK_RETURN
	{
		CString strCode=m_Grid.GetTextMatrix(m_Grid.GetRow(),1);
		strCode.TrimRight();
		dlgPS->OnSelectGood (strCode);
		::SetFocus(m_Grid.m_hWnd );
		//OnOK ();
	}
}

BOOL CDlgInsert::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	m_Grid.CreateFromStatic(IDC_GRID2,this);
	LOGFONT logFont;
	pDoc->m_FontMap[_T("Dialogs")]->GetLogFont(&logFont);
	long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
	CString strFontName(logFont.lfFaceName);
	m_Grid.SetFontSize((float)szFont);
	m_Grid.SetFontName(strFontName);
	m_Grid.SetFontBold(logFont.lfWeight==FW_BOLD);
	m_Grid.SetFontItalic(logFont.lfItalic);
	SetupGrid();
	m_wndEdit.SetFont (pDoc->m_FontMap[_T("Dialogs")].get());
	blGridIsLoaded=false;
	LoadSelectedProducts(L"0000000000001");
	LoadItemsInGrid();
	
	PostMessage(WM_SETFOCUSGRID,0L,0L);
	return TRUE;  // return TRUE unless you set the focus to a control
	            // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgInsert::UpdateLayout()
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
		m_btnBarCodeFind.GetWindowRect(&rcBtnFind);
		ScreenToClient(&rcBtnFind);
		int nBtnWidth=rcBtnFind.Width();
		rcEdit.top =rcBtnFind.top=rc.top;
		rcBtnFind.right =rc.right ;
		rcBtnFind.left=rc.right-nBtnWidth;
		CWindowDC dc(this);
		CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
		LOGFONT logFont;
		pDoc->m_FontMap[_T("Dialogs")]->GetLogFont(&logFont);
		int lfHeight = -logFont.lfHeight;
		nGap=lfHeight/2;
		rcBtnFind.bottom=rc.top+lfHeight+nGap;
		m_btnBarCodeFind.MoveWindow(&rcBtnFind);
		rcEdit.left =rc.left ;
		rcEdit.right =rcBtnFind.left-nGap;
		

		rcEdit.bottom =rcBtnFind.bottom;;
		m_wndEdit.MoveWindow (&rcEdit);
		rcGrid=rc;
		rcGrid.top=rcEdit.bottom +iBorder;
		//rcGrid.left = rcTree.right + iBorder + 2;
		m_Grid.MoveWindow(&rcGrid);
	
}

void CDlgInsert::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	UpdateLayout ();
	
	// TODO: Add your message handler code here
	
}

void CDlgInsert::OnEnterCell()
{
	CPSDlgInsertGood* dlgPS=static_cast<CPSDlgInsertGood*>(GetParent());
	dlgPS->m_strSelectProduct=m_Grid.GetTextMatrix(m_Grid.GetRow(),1);
	dlgPS->SetTipText (m_Grid.GetTextMatrix(m_Grid.GetRow(),2));
}

LRESULT CDlgInsert::OnSetFocusToGrid(WPARAM wParam,LPARAM lParam)
{
	try{
	PostMessage(WM_NEXTDLGCTL ,(WPARAM)m_Grid.m_hWnd ,(LPARAM)TRUE);
	//m_Grid.SetFocus();
	m_Grid.SetRow(m_Grid.GetFixedRows());
	m_Grid.SetCol(1);
	return 0L;
	}
	catch(_com_error& err)
	{
		MessageBoxHelper::PrintComError(err);
	}
	return 1L;
}

void CDlgInsert::LoadSelectedProducts(const std::wstring& filter)
{
	USES_CONVERSION;
	try
	{
		SelectedProducts.clear();

		Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
		
		boost::shared_ptr<Repository::UnitsReference> refUnits=pRep->getUnits();
		if(refUnits->SelectItemsByAttribute(IReference::ListOfAttr::Code(),filter)>0){
			do{
				RefItemPtr curUnit=refUnits->getCurrent();
				std::wstring product_code=(_bstr_t)curUnit->getAttribute(ISReference<Products>::ListOfAttr::Owner());
				//if(refProducts->FindByCode(product_code)>0){
				//	RefItemPtr curProduct=refProducts->getCurrent();
					_variant_t var=curUnit->getAttribute(IReference::ListOfAttr::Descr());
					std::wstring unit_descr=(_bstr_t)var;
					GridLine line=boost::make_tuple(product_code,L"",unit_descr,curUnit->_code);
					SelectedProducts.push_back(line);
				
			}while(refUnits->getNext());
		}
			std::sort(SelectedProducts.begin(),SelectedProducts.end(),[](GridLine line1,GridLine line2)
			{
				return (line1.get<0>()<line2.get<0>());
			});

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

void CDlgInsert::LoadItemsInGrid(long begin_row/*=0*/)
{


	CWaitCursor wait;
	USES_CONVERSION;
	_variant_t vtNone(0L,VT_ERROR),colBeg(1L),colEnd(1L);
	Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
	boost::shared_ptr<Repository::TypePriceReference> refTypePrice=pRep->getType_price();
	refTypePrice->FindByCode(A2W(CUserThreadsApp::GetDocument<CMainDocument>()->m_strTypePriceId));
	Repository::ReferenceItem curTypePrice=refTypePrice->getCurrent();
	boost::shared_ptr<Repository::PricesReference> refPrice=pRep->getPrices();
	boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
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
		if(refProducts->FindByCode(curProduct_code))
		{
			Repository::ReferenceItem curProduct=refProducts->getCurrent();
			strItem+=W2A(curProduct->_descr.c_str());
		}
		else
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
		strItem+='\t';
		strItem+=W2A(line.get<3>().c_str());
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

void CDlgInsert::AfterScroll(long OldTopRow,long OldLeftCol,long NewTopRow, long NewLeftCol)
{
	if((OldTopRow<NewTopRow)&&(!blGridIsLoaded))
		LoadItemsInGrid(OldTopRow);
}

void CDlgInsert::OnButton1() 
{
	m_Grid.SetRows(1);
	try{	//       code here
		CString strName;
		m_wndEdit.GetWindowTextA(strName) ;
		strName.Trim();
		USES_CONVERSION;
		LoadSelectedProducts(A2W(strName));
		LoadItemsInGrid();


		//UpdateLayout();
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

BOOL CDlgInsert::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(1,500,NULL);
	return TRUE;
}


void CDlgInsert::OnTimer(UINT nIDEvent) 
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
void CDlgInsert::OnEditReturnPressed(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMRETURN* pNMRTRN = (NMRETURN*)pNMHDR;
	_variant_t vtNone(0L,VT_ERROR);
	// TODO: Add your control notification handler
	try{
		
		m_Grid.SetRows(1);//       code here
		CString strName=pNMRTRN->pszText ;
		USES_CONVERSION;
		LoadSelectedProducts(A2W(strName));
		LoadItemsInGrid();
		//UpdateLayout();
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

BOOL CDlgInsert::PreTranslateMessage(MSG* pMsg)
{
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
