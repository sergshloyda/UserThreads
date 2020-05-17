// DlgSelectGood.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgSelectGood.h"
#include "PSDlgInsertGood.h"
#include "InfoConsole.h"
#include "NotyfyFndProduct.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectGood dialog

IMPLEMENT_DYNCREATE(CDlgSelectGood, CPropertyPage)
CDlgSelectGood::CDlgSelectGood()
	: CPropertyPage(CDlgSelectGood::IDD/*, pParent*/)
{
	//{{AFX_DATA_INIT(CDlgSelectGood)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CDlgSelectGood::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectGood)
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectGood, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgSelectGood)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	//ON_MESSAGE(WM_GETINFO_FROMNODE,OnGetInfoFromNode)
	//ON_MESSAGE(WM_SETFOCUSGRID,OnSetFocusToGrid)
	ON_WM_DESTROY()
	ON_NOTIFY(DBL_CLICK_FOLDER,IDC_TREE1,&CDlgSelectGood::OnFolderDblClk)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CDlgSelectGood, CPropertyPage)
   	ON_EVENT(CDlgSelectGood, IDC_GRID1, 0xfffffda6 , OnGridKeyDown, VTS_PI2 VTS_I2)
	ON_EVENT(CDlgSelectGood, IDC_GRID1, 0xfffffda7 , OnDblClick, VTS_NONE )
	ON_EVENT(CDlgSelectGood, IDC_GRID1, 0x00000003 , OnEnterCell, VTS_NONE)
	ON_EVENT(CDlgSelectGood, IDC_GRID1, 0x0000000b , AfterScroll, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectGood message handlers

BOOL CDlgSelectGood::OnInitDialog() 
 {
	CPropertyPage::OnInitDialog();
	//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetThread());
//	CPSDlgInsertGood* pParentSheet=static_cast<CPSDlgInsertGood*>(GetParent());
//	CUserThreadsView* pView=static_cast<CUserThreadsView*>(pParentSheet->pParent);
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();

	m_TreeCtrl.Init ();

	m_TreeCtrl.SetFont (pDoc->m_FontMap[_T("Dialogs")].get());
	m_Grid.CreateFromStatic (IDC_GRID1,this);
	LoadIcons();
	LOGFONT logFont;
	pDoc->m_FontMap[_T("Dialogs")]->GetLogFont(&logFont);
	long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
	CString strFontName(logFont.lfFaceName);
	m_Grid.SetFontSize((float)szFont);
	m_Grid.SetFontName(strFontName);
	m_Grid.SetFontBold(logFont.lfWeight==FW_BOLD);
	m_Grid.SetFontItalic(logFont.lfItalic);


	SetupGrid();
	blGridIsLoaded=false;
	Repository *pRep=CUserThreadsApp::GetDocument<Repository>();
	boost::shared_ptr<Repository::ProductsReference> products=pRep->getProducts();
	if(products->FindByDescription(L"Товары",true)){
		root=products->getCurrent();

	}
	curProdFolderCode=root->_code;
	LoadsSelectedProducts(curProdFolderCode);
	LoadItemsInGrid();
	
	
	
	PostMessage(WM_SETFOCUSGRID,0L,0L);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectGood::OnGridKeyDown(short* KeyCode,short Shift)
{
	BOOL blCtrlDown= (Shift==2);//нажата клавиша CTRL
//	CPSDlgInsertGood* dlgPS=static_cast<CPSDlgInsertGood*>(GetParent());
	if(*KeyCode==VK_RETURN)//VK_RETURN
	{
		OnReturnPressed();	
	}
	//else if(*KeyCode==VK_ESCAPE)
		//dlgPS->SendMessage(WM_CLOSE,0L,0L);

	else if(blCtrlDown && *KeyCode==VK_DOWN)
	{
		OnDownLevel();
		*KeyCode=VK_ESCAPE;//не надо стандартной обработки 
		//при которой выделяется последняя строчка 
	}
	else if (blCtrlDown && *KeyCode==VK_UP)
		OnUpLevel();
	
	
}

void CDlgSelectGood::OnFolderDblClk(NMHDR* pNMHDR, LRESULT* pResult)
{
	//OutputDebugString(_T("CDlgSelectGood::OnFolderDblClk"));
	LPNMFLDR_DBL_CLK pNM = reinterpret_cast<LPNMFLDR_DBL_CLK>(pNMHDR);
	curProdFolderCode=pNM->code;
	// #LoadFromTreeItem
	try
	{
	m_Grid.SetFocusRect (flexFocusHeavy);
	//CClientDC dc(this);
	//CSize szTwPerPixel;
	//szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	//szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	
	//CPictureHolder picFolder;
	//HICON hIcon1=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_CLOSEFOLDERS),
	//	IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	//picFolder.CreateFromIcon(hIcon1,TRUE);
	//long wdt,ht;
	////size in HIMETRIC (0.01mm)
	//picFolder.m_pPict->get_Width (&wdt);
	//picFolder.m_pPict->get_Height (&ht);
	//
	//CSize szPict(wdt,ht);
	//dc.HIMETRICtoLP (&szPict);
	////note grid size units is twips
	//LPDISPATCH pDispFolder = picFolder.GetPictureDispatch();
	//
	//m_Grid.SetColWidth (0,szPict.cx *szTwPerPixel.cx +100);
	//CPictureHolder picGood;
	//HICON hIcon2=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_GOOD_GRD),
	//	IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	//picGood.CreateFromIcon(hIcon2,TRUE);
	//LPDISPATCH pDispGood = picGood.GetPictureDispatch();
	//CPictureHolder picOpenFolder;
	//HICON hIcon3=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_OPENING),
	//	IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	//picOpenFolder.CreateFromIcon (hIcon3,TRUE);
	//LPDISPATCH pDispOpenFolder = picOpenFolder.GetPictureDispatch();
	m_Grid.SetRows(1);
	m_Grid.SetRedraw (FALSE);
	/*HTREEITEM hCurItem=reinterpret_cast<HTREEITEM>(lParam) ;
	
	CString strDelimiter='\t';
	CString strIsLoaded="1";
	CString strBarCode="";

	do{
		CString strItem="";
		CTreeNode* pNode;
		TCHAR text[255];
		TV_ITEM item;
		item.mask=TVIF_HANDLE|TVIF_TEXT|TVIF_PARAM;
		item.hItem=hCurItem;
		item.pszText=text;
		item.cchTextMax=255; 
		
		VERIFY(m_TreeCtrl.GetItem (&item));
		pNode=(CTreeNode*)item.lParam;
		hCurItem=m_TreeCtrl.GetParentItem(hCurItem);
		CString strCode=pNode->item.code.c_str();
		CString strTxt=pNode->item.text.c_str();
		strItem=strDelimiter+strIsLoaded+strDelimiter+strCode +strDelimiter+strTxt ;
		_variant_t v(1L);
		m_Grid.AddItem (strItem,v);
		m_Grid.SetFixedRows (m_Grid.GetRows());
		
		
		m_Grid.SetRow(1);
		m_Grid.SetCol(0);
		m_Grid.SetCellPictureAlignment (flexPicAlignCenterCenter);	
		m_Grid.SetCellPicture((CComPtr<IDispatch>)icons[_T("open_folder")]);
	
		
		
	}	while(hCurItem!=NULL);*/
	USES_CONVERSION;
	
	
	LoadHierarchy(curProdFolderCode);
	LoadsSelectedProducts(curProdFolderCode);
	LoadItemsInGrid();
		//CString strSQL;
		//strSQL.Format (_T("Select IsFolder,BarCode,Code,Name,Units,Price From Catalog Where pcode ='%s'"),pNode->item.code );
		//// TODO: Add extra initialization here
		//
		//TESTHR(pRstInt.CreateInstance(__uuidof(Recordset)));
		//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetThread());
		//
		//HRESULT hr=pRstInt->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
		//	adOpenKeyset, adLockBatchOptimistic, adCmdText);
		//if (hr!=S_OK)
		//{
		//	AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
		//	return 1L;
		//}
		//long curRow=m_Grid.GetRows();
		//while(!pRstInt->EndOfFile )
		//{
		//	
		//	
		//	VARIANT v; 
		//	V_VT(&v) = VT_ERROR;
		//	CString strItem="";
		//	COleCurrency currVal;
		//	for(long i=0;i<pRstInt->Fields->Count ;i++)
		//	{
		//		_variant_t FldVal=pRstInt->Fields->GetItem((long)i)->Value;
		//		CString buff="";

		//		switch(FldVal.vt)
		//		{
		//			
		//		case (VT_BSTR):
		//			strItem+='\t';
		//			strItem+=(char*)(_bstr_t)FldVal.bstrVal;
		//			
		//			
		//			break;
		//		case (VT_I2):
		//			if(i==0)
		//				buff.Format(_T("%d"),FldVal.iVal);
		//			else
		//				buff.Format(_T("%.2f"),(float)FldVal.lVal/100);
		//			strItem+='\t';
		//			strItem+=buff;
		//			
		//			buff="";
		//			break;
		//		case(VT_CY):
		//			currVal=FldVal.cyVal;
		//			buff=currVal.Format ();
		//				strItem+='\t';
		//			strItem+=buff;
		//			break;
		//		case (VT_EMPTY):
		//			buff.Format(_T("%s"),(LPCSTR)FldVal.iVal);
		//			strItem+='\t';
		//			strItem+=buff;
		//			
		//			buff="";
		//			break;
		//			
		//		default:
		//			break;
		//		}
		//		
		//		
		//	}
		//	m_Grid.AddItem(strItem, v);
		//	m_Grid.SetRow(curRow++);
		//	m_Grid.SetCol(0);
		//	m_Grid.SetText (_T(""));
		//	m_Grid.SetCellPictureAlignment (flexPicAlignCenterCenter);	
		//	_variant_t val=pRstInt->Fields->GetItem(0L)->Value;
		//	if(val.intVal ==1)
		//		m_Grid.SetCellPicture(pDispFolder);
		//	else
		//		m_Grid.SetCellPicture(pDispGood);
		//	
		//	
		//	
		//	
		//	pRstInt->MoveNext();
		//}
	m_Grid.SetRedraw (TRUE);
	m_TreeCtrl.RedrawWindow();
	}
	catch (_com_error &e)
	{
		
			PrintComError(e);
	
		
	}	
	catch(DbContext::DbContextError &e)
	{
		MessageBoxHelper::ShowError(e.what());
	}
	
	PostMessage(WM_SETFOCUSGRID,0L,0L);
	
	//void* data=(void*)pNM->code;
	//delete data;
	*pResult=0;
}

void CDlgSelectGood::OnReturnPressed(long row)
{

	try
	{
		long lCurRow=0;
		if(row<0)

			lCurRow=m_Grid.GetRow();
		else
			lCurRow=row;
		CString strCode=m_Grid.GetTextMatrix(lCurRow,2);
		strCode.TrimRight ();
		CString strIsFolder=m_Grid.GetTextMatrix (lCurRow,1);
		strIsFolder.TrimRight ();


		BOOL blIsFolder=(strIsFolder=="1");

		if(blIsFolder)
		{
			m_Grid.SetFocusRect (flexFocusHeavy);
			//CClientDC dc(this);
			//CSize szTwPerPixel;
			//szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
			//szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);

			//CPictureHolder picFolder;
			//HICON hIcon1=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_CLOSEFOLDERS),
			//	IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
			//picFolder.CreateFromIcon(hIcon1,TRUE);
			//long wdt,ht;
			////size in HIMETRIC (0.01mm)
			//picFolder.m_pPict->get_Width (&wdt);
			//picFolder.m_pPict->get_Height (&ht);
			//
			//CSize szPict(wdt,ht);
			//dc.HIMETRICtoLP (&szPict);
			////note grid size units is twips
			//LPDISPATCH pDispFolder = picFolder.GetPictureDispatch();
			//
			//m_Grid.SetColWidth (0,szPict.cx *szTwPerPixel.cx +100);
			//CPictureHolder picGood;
			//HICON hIcon2=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_GOOD_GRD),
			//	IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
			//picGood.CreateFromIcon(hIcon2,TRUE);
			//LPDISPATCH pDispGood = picGood.GetPictureDispatch();
			//CPictureHolder picOpenFolder;
			//HICON hIcon3=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_OPENING),
			//	IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
			//picOpenFolder.CreateFromIcon (hIcon3,TRUE);
			//LPDISPATCH pDispOpenFolder = picOpenFolder.GetPictureDispatch();
			m_Grid.SetRows(1);
			m_Grid.SetRedraw (FALSE);
			//CTreeNode* pNode=reinterpret_cast<CTreeNode*>(wParam);
			/*HTREEITEM hCurItem=reinterpret_cast<HTREEITEM>(lParam) ;

			CString strDelimiter='\t';
			CString strIsLoaded="1";
			CString strBarCode="";

			do{
			CString strItem="";
			CTreeNode* pNode;
			TCHAR text[255];
			TV_ITEM item;
			item.mask=TVIF_HANDLE|TVIF_TEXT|TVIF_PARAM;
			item.hItem=hCurItem;
			item.pszText=text;
			item.cchTextMax=255; 

			VERIFY(m_TreeCtrl.GetItem (&item));
			pNode=(CTreeNode*)item.lParam;
			hCurItem=m_TreeCtrl.GetParentItem(hCurItem);
			CString strCode=pNode->item.code.c_str();
			CString strTxt=pNode->item.text.c_str();
			strItem=strDelimiter+strIsLoaded+strDelimiter+strCode +strDelimiter+strTxt ;
			_variant_t v(1L);
			m_Grid.AddItem (strItem,v);
			m_Grid.SetFixedRows (m_Grid.GetRows());


			m_Grid.SetRow(1);
			m_Grid.SetCol(0);
			m_Grid.SetCellPictureAlignment (flexPicAlignCenterCenter);	
			m_Grid.SetCellPicture((CComPtr<IDispatch>)icons[_T("open_folder")]);



			}	while(hCurItem!=NULL);*/


			LoadHierarchy((LPWSTR)_bstr_t(strCode.AllocSysString()));
			LoadsSelectedProducts((LPWSTR)_bstr_t(strCode.AllocSysString()));
			LoadItemsInGrid();
			//CString strSQL;
			//strSQL.Format (_T("Select IsFolder,BarCode,Code,Name,Units,Price From Catalog Where pcode ='%s'"),pNode->item.code );
			//// TODO: Add extra initialization here
			//
			//TESTHR(pRstInt.CreateInstance(__uuidof(Recordset)));
			//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetThread());
			//
			//HRESULT hr=pRstInt->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
			//	adOpenKeyset, adLockBatchOptimistic, adCmdText);
			//if (hr!=S_OK)
			//{
			//	AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
			//	return 1L;
			//}
			//long curRow=m_Grid.GetRows();
			//while(!pRstInt->EndOfFile )
			//{
			//	
			//	
			//	VARIANT v; 
			//	V_VT(&v) = VT_ERROR;
			//	CString strItem="";
			//	COleCurrency currVal;
			//	for(long i=0;i<pRstInt->Fields->Count ;i++)
			//	{
			//		_variant_t FldVal=pRstInt->Fields->GetItem((long)i)->Value;
			//		CString buff="";

			//		switch(FldVal.vt)
			//		{
			//			
			//		case (VT_BSTR):
			//			strItem+='\t';
			//			strItem+=(char*)(_bstr_t)FldVal.bstrVal;
			//			
			//			
			//			break;
			//		case (VT_I2):
			//			if(i==0)
			//				buff.Format(_T("%d"),FldVal.iVal);
			//			else
			//				buff.Format(_T("%.2f"),(float)FldVal.lVal/100);
			//			strItem+='\t';
			//			strItem+=buff;
			//			
			//			buff="";
			//			break;
			//		case(VT_CY):
			//			currVal=FldVal.cyVal;
			//			buff=currVal.Format ();
			//				strItem+='\t';
			//			strItem+=buff;
			//			break;
			//		case (VT_EMPTY):
			//			buff.Format(_T("%s"),(LPCSTR)FldVal.iVal);
			//			strItem+='\t';
			//			strItem+=buff;
			//			
			//			buff="";
			//			break;
			//			
			//		default:
			//			break;
			//		}
			//		
			//		
			//	}
			//	m_Grid.AddItem(strItem, v);
			//	m_Grid.SetRow(curRow++);
			//	m_Grid.SetCol(0);
			//	m_Grid.SetText (_T(""));
			//	m_Grid.SetCellPictureAlignment (flexPicAlignCenterCenter);	
			//	_variant_t val=pRstInt->Fields->GetItem(0L)->Value;
			//	if(val.intVal ==1)
			//		m_Grid.SetCellPicture(pDispFolder);
			//	else
			//		m_Grid.SetCellPicture(pDispGood);
			//	
			//	
			//	
			//	
			//	pRstInt->MoveNext();
			//}
			m_Grid.SetRedraw (TRUE);
		}
		else
		{
		/**/
			//AfxMessageBox(strCode);
			CPSDlgInsertGood* dlgPS=static_cast<CPSDlgInsertGood*>(GetParent());
			strCode.TrimRight();
			dlgPS->OnSelectGood (strCode);
			::SetFocus(m_Grid.m_hWnd );
		}

	}
	catch (_com_error &e)
	{

		PrintComError(e);


	}	
	catch(DbContext::DbContextError &e)
	{
		MessageBoxHelper::ShowError(e.what());
	}

	PostMessage(WM_SETFOCUSGRID,0L,0L);

	SetModified ();	
	return;	
	//OnOK ();
}

void CDlgSelectGood::OnDownLevel()
{
	short KeyCode=VK_RETURN;
	OnGridKeyDown(&KeyCode,0);//to imitate ENTER press
}

void CDlgSelectGood::OnUpLevel()
{
	if(m_Grid.GetFixedRows()>2)
	{
	//	m_Grid.SetRows(1);
	//	curProdFolderCode=L"00000004";
	//	LoadsSelectedProducts(curProdFolderCode);
	//	LoadItemsInGrid();
	//}
	//else
	//{
		m_Grid.SetFixedRows (m_Grid.GetFixedRows()-2);
		m_Grid.SetRow(m_Grid.GetFixedRows());
		short KeyCode=VK_RETURN;
		OnGridKeyDown(&KeyCode,0);//to imitate ENTER press
	}
}

void CDlgSelectGood::LoadItemsInGrid(long begin_row)
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
	long fixed_rows=m_Grid.GetFixedRows();
	long client_h=m_Grid.GetClientHeight();
	long row_h=max(m_Grid.GetRowHeight(0),1);
	int rowsInClient=client_h/row_h-fixed_rows;
	int gap=0;
	if(szSelProds>rowsInClient) gap=max((m_Grid.GetRows()-fixed_rows),0);
	const_iter iter_begin=SelectedProducts.begin()+gap,iter_end=SelectedProducts.end();

		for(const_iter it=iter_begin;it!=iter_end;++it)
		{
#pragma region //#LoadGridLine

			CString strItem='\t';
			GridLine line=(*it);
			int isfolder=line.get<0>();
			CAtlString strFolder;
			strFolder.Format("%d",isfolder);
			strItem+=strFolder;
			strItem+='\t';
			std::wstring curProduct_code=line.get<1>();
			std::wstring price_code=curProduct_code+typePrice;
			strItem+=W2A(curProduct_code.c_str());
			strItem+='\t';
			strItem+=W2A(line.get<2>().c_str());
			strItem+='\t';
			strItem+=W2A(line.get<3>().c_str());
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
		
			if(curRow>0)
			{
				m_Grid.SetRow(curRow);
				m_Grid.SetCol(0);
				m_Grid.SetText (_T(""));
				m_Grid.SetCellPictureAlignment (flexPicAlignCenterCenter);	
				if(isfolder==1)
					m_Grid.SetCellPicture((CComPtr<IDispatch>)icons[_T("close_folder")]);
				else
					m_Grid.SetCellPicture((CComPtr<IDispatch>)icons[_T("good")]);
			}
				blGridIsLoaded=((it+1)==SelectedProducts.end());
				if(curRow>(rowsInClient+fixed_rows+3)) break;
				//blGridIsLoaded=true;
		}
		
	
	

			m_Grid.SetColHidden(1,TRUE);
			colEnd.lVal=m_Grid.GetCols()-1;
			m_spGoodsGrid->AutoSize(colBeg, colEnd, vtNone, vtNone);
			//m_Grid.SetTopRow(gap);
}

void CDlgSelectGood::LoadsSelectedProducts(const std::wstring& parent)
{

		USES_CONVERSION;
		try
		{
			SelectedProducts.clear();

				Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
				boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
				
				if(refProducts->FindByCode(parent)>0)
				{

					Repository::ReferenceItem prodRoot=refProducts->getCurrent();
					refProducts->UseParent(prodRoot);
					refProducts->SelectItems();
					bool blUnit_PriceFieldShow=false;
					do{
				
							RefItemPtr curProduct=refProducts->getCurrent();
							_variant_t var=curProduct->getAttribute(IHReference::ListOfAttr::IsFolder());
							int isFolder=(int)var.iVal;
							boost::trim(curProduct->_code);
							boost::trim(curProduct->_descr);

							std::wstring unit_descr;
							if(!curProduct->IsFolder()){
							var=curProduct->getAttribute(Products::ListOfAttr::BaseUnit());
							unit_descr=(_bstr_t)var;
							boost::trim(unit_descr);
							}
							GridLine line=boost::make_tuple(isFolder,curProduct->_code,curProduct->_descr,unit_descr);
							SelectedProducts.push_back(line);
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
					MessageBoxHelper::ShowError(err.Description());
				}
}

void CDlgSelectGood::LoadHierarchy(const std::wstring& root)
{

	Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
	boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
	
		if(refProducts->FindByCode(root)>0)
		{
			USES_CONVERSION;
			Repository::ReferenceItem prodRoot=refProducts->getCurrent();
			CString strItem='\t';
			strItem+=OLE2A((_bstr_t)prodRoot->getAttribute(IHReference::ListOfAttr::IsFolder()));
			strItem+='\t';
			strItem+=OLE2A((_bstr_t)prodRoot->getAttribute(IReference::ListOfAttr::Code()));
			strItem+='\t';
			strItem+=OLE2A((_bstr_t)prodRoot->getAttribute(IReference::ListOfAttr::Descr()));
			_variant_t v(1L);
			m_Grid.AddItem (strItem,v);
			m_Grid.SetFixedRows (m_Grid.GetRows());
			m_Grid.SetRow(1);
			m_Grid.SetCol(0);
			m_Grid.SetCellPictureAlignment (flexPicAlignCenterCenter);	
			m_Grid.SetCellPicture((CComPtr<IDispatch>)icons[_T("open_folder")]);
			_variant_t var=prodRoot->getAttribute(IHReference::ListOfAttr::Parent());
			if(var.vt==VT_NULL) return;
			std::wstring parent_code=(_bstr_t)var;
			return LoadHierarchy(parent_code);

		}
		
	
	
	
}
#pragma region (Splitter)

void CDlgSelectGood::OnMouseMove(UINT nFlags, CPoint pt) 
{
	if (PtInRect(&m_rcResizeArea, pt))
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
	
	CPropertyPage::OnMouseMove(nFlags, pt);
}

void CDlgSelectGood::OnLButtonDown(UINT nFlags, CPoint pt) 
{

		if (!PtInRect(&m_rcResizeArea, pt)) return ;
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));

		// prepare to work
		RECT rcClient, rcSizeBar;
		GetClientRect(&rcClient);
		InflateRect(&rcClient, -10, -3);
		rcSizeBar = m_rcResizeArea;
		int iBarWidth = rcSizeBar.right - rcSizeBar.left;

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
						SetCursor(LoadCursor(NULL, IDC_SIZEWE));
						pt.x = LOWORD(msg.lParam);
						pt.y = HIWORD(msg.lParam);  
						if (!PtInRect(&rcClient, pt)) break;
						if (bErase) DrawResizeBar(&rcSizeBar);
						rcSizeBar.left  = pt.x - iBarWidth / 2;
						rcSizeBar.right = rcSizeBar.left + iBarWidth;
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
		GetDlgItem(IDC_TREE1)->GetClientRect(&rcClient);
		rcClient.right += rcSizeBar.left - m_rcResizeArea.left;
		UpdateLayout(rcClient.right);

	
	CPropertyPage::OnLButtonDown(nFlags, pt);
}
void CDlgSelectGood::DrawResizeBar(LPRECT rc)
{
		ClientToScreen(rc);
		HDC  hdc = ::GetDC(NULL);
		CDC dc;
		dc.Attach (hdc);
		dc.InvertRect( rc);
		//ReleaseDC(hdc);
		ScreenToClient(rc);
}
void CDlgSelectGood::UpdateLayout(int iTreeWidth)
{

	try{
		int iBorder = 3;
		RECT rc;
		GetClientRect(&rc);
		InflateRect(&rc, -iBorder, -iBorder);

		// move and position tree control
		RECT rcTree;
		if(!::IsWindow (m_Grid.m_hWnd)) return;
		GetDlgItem(IDC_TREE1)->GetClientRect(&rcTree);
		if (iTreeWidth < 0) iTreeWidth = rcTree.right;
		rcTree = rc;
		rcTree.right = rcTree.left + iTreeWidth+4;
		GetDlgItem(IDC_TREE1)->MoveWindow(&rcTree);

	
		RECT rcGrid = rc;
		rcGrid.left = rcTree.right + iBorder + 2;
		m_Grid.MoveWindow(&rcGrid);
    
		// save resizing area
		m_rcResizeArea = rc;
		m_rcResizeArea.left  = rcTree.right;
		m_rcResizeArea.right = rcGrid.left;

		// Adjust colwidth for grid


		m_Grid.ShrinkColumn(2);

	}
	catch(_com_error& err)
	{
		MessageBoxHelper::ShowError(err.Description());
	}
		

}
#pragma endregion (Splitter)
void CDlgSelectGood::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	UpdateLayout();
	// TODO: Add your message handler code here
	
}

void CDlgSelectGood::OnEnterCell()
{
	
	CPSDlgInsertGood* dlgPS=static_cast<CPSDlgInsertGood*>(GetParent());
	IVSFlexGridPtr spGrid=m_Grid.GetControlUnknown();
	CComBSTR bstrTxt,bstrRest;
	long row=spGrid->Row;
	//bstrTxt=m_Grid.GetTextMatrix(row,3);
	spGrid->get_TextMatrix(row,3,&(bstrTxt));
	spGrid->get_TextMatrix(row,6,&(bstrRest));
	if(bstrRest!=NULL){
	bstrTxt.AppendBSTR(CComBSTR(L" Остаток : "));
	bstrTxt.AppendBSTR(bstrRest);
	bstrTxt.AppendBSTR(CComBSTR(L" шт. "));
	}
	USES_CONVERSION;
	dlgPS->SetTipText (W2A(bstrTxt));
}

void CDlgSelectGood::OnDblClick()
{
	try{
		IVSFlexGridPtr pGrid=m_Grid.GetControlUnknown ();
		long lRow,fixRow;
		TESTHR(pGrid->get_MouseRow(&lRow));

		TESTHR(pGrid->get_FixedRows(&fixRow));
		//lRow=m_Grid.GetMouseRow();
		if(lRow<max(fixRow,0))
		{
			OnReturnPressed(lRow);
		}
		else
		{
			short KeyCode=13;
			OnGridKeyDown(&KeyCode,0);//to imitate ENTER press
		}
	}
	catch(_com_error& err)
	{
		MessageBoxHelper::ShowError(err.Description());
	}

}

BOOL CDlgSelectGood::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	
	//OutputDebugString(_T("CDlgSelectGood::OnCmdMsg"));
	if((nID==IDC_GRID1)&&(nCode== CN_EVENT))
	{
		AFX_EVENT* pEvent=(AFX_EVENT*)pExtra;
		int disp_id=pEvent->m_dispid;
	
		if(disp_id==0xfffffda6){
			short* kk=pEvent->m_pDispParams->rgvarg[1].piVal;
		
			if((*kk)==13){
				OnReturnPressed();
				return false;
			}
		}
	}


	return CDialog::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}
void CDlgSelectGood::LoadIcons()
{
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	CPictureHolder picFolder;
	//SHFILEINFO Info;
	//::SHGetFileInfo(_T("c:\\windows"),0,&Info,sizeof(SHFILEINFO),SHGFI_ICON|SHGFI_SMALLICON);
	//int id=Info.iIcon;
	//HICON hIII=ImageList_GetIcon(pMainDoc->m_hSysImgLst,id,ILD_TRANSPARENT);
	HICON hIcon=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_CLOSEFOLDERS),
		IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	picFolder.CreateFromIcon(hIcon);
	CComPtr<IDispatch> pDispFolder;
	pDispFolder.Attach(picFolder.GetPictureDispatch());
	icons.insert(std::make_pair(TypeIcons::CloseFolder(),pDispFolder));
	CPictureHolder picGood;
	HICON hIcon2=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_GOOD_GRD),
		IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	picGood.CreateFromIcon(hIcon2,TRUE);
	CComPtr<IDispatch> pDispGood;
	pDispGood.Attach(picGood.GetPictureDispatch());
	icons.insert(std::make_pair(TypeIcons::Goods(),pDispGood));
	CPictureHolder picOpenFolder;
	HICON hIcon3=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_OPENING),
		IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
	picOpenFolder.CreateFromIcon (hIcon3,TRUE);
	CComPtr<IDispatch> pDispOpenFolder;
	pDispOpenFolder.Attach(picOpenFolder.GetPictureDispatch());
	icons.insert(std::make_pair(TypeIcons::OpenFolder(),pDispOpenFolder));
	CClientDC dc(this);
	m_szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	m_szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
	long wdt,ht;
	//size in HIMETRIC (0.01mm)
	picFolder.m_pPict->get_Width (&wdt);
	picFolder.m_pPict->get_Height (&ht);
	m_szPict.cx=wdt;
	m_szPict.cy=ht;

	dc.HIMETRICtoLP (&m_szPict);
}
void CDlgSelectGood::SetupGrid(){  

	m_spGoodsGrid=m_Grid.GetControlUnknown ();
	m_spGoodsGrid->put_AutoSizeMode(flexAutoSizeColWidth);
	m_spGoodsGrid->put_AllowUserResizing (flexResizeColumns);
	m_spGoodsGrid->put_SelectionMode(flexSelectionByRow);
	m_Grid.SetRows(1);
	m_Grid.SetCols(1);
	//note grid size units is twips
	m_Grid.SetFormatString (_T("|<IsFolder|<Код|<Наименование|<Ед.Изм.|<Цена|<Остаток"));
	m_Grid.SetColWidth (0,m_szPict.cx *m_szTwPerPixel.cx +100);

}
void CDlgSelectGood::AfterScroll(long OldTopRow, long OldLeftCol, long NewTopRow, long NewLeftCol)
{
	if((OldTopRow<NewTopRow)&&(!blGridIsLoaded))
	LoadItemsInGrid(OldTopRow-m_Grid.GetFixedRows());

}
BOOL CDlgSelectGood::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//	OutputDebugString(_T("From CDlgSelectGood::PreTranslate"));
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
void CDlgSelectGood::OnDestroy()
{

	m_TreeCtrl.Clear();
	CPropertyPage::OnDestroy();

	// TODO: Add your message handler code here
}
BOOL CDlgSelectGood::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: Add your specialized code here and/or call the base class
	NMHDR* pnmh = (LPNMHDR) lParam;
	if(pnmh->code==FND_BY_CODE)
	{
		LPNMFNDPRODUCT lpnmhdr=reinterpret_cast<LPNMFNDPRODUCT>(pnmh);
		CNotyfyFndProduct* pObject=lpnmhdr->pObject;
		Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
		boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
		CString root=pObject->GetCode();
		USES_CONVERSION;
		if(refProducts->FindByCode(A2W(root))>0)
		{
			
			Repository::ReferenceItem prodRoot=refProducts->getCurrent();
			std::wstring curProdFolderCode=(_bstr_t)prodRoot->getAttribute(IHReference::ListOfAttr::Parent());
			try
			{
				m_Grid.SetFocusRect (flexFocusHeavy);
				m_Grid.SetRows(1);
				m_Grid.SetRedraw (FALSE);
				LoadHierarchy(curProdFolderCode);
				LoadsSelectedProducts(curProdFolderCode);
		/*		std::wstring filter=A2W(root);
				std::vector<GridLine>::const_iterator it=std::find_if(SelectedProducts.cbegin(),SelectedProducts.cend(),
					[filter](GridLine line)
				{
					return line.get<1>()==filter;
				});
				int dist=std::distance(SelectedProducts.cbegin(),it);*/
				LoadItemsInGrid();
				m_Grid.SetRedraw (TRUE);
				
				m_TreeCtrl.RedrawWindow();
			}
			catch (_com_error &e)
			{

				PrintComError(e);


			}	
			catch(DbContext::DbContextError &e)
			{
				MessageBoxHelper::ShowError(e.what());
			}
		}
		delete pObject;
		return TRUE;
	}
	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}
