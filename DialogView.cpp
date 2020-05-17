// DialogView.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "DialogView.h"
#include "FindView.h"
#include "InfoConsole.h"
#include "GoodsGrid.h"
#include "ReportFrame.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "AFXCTL.H" // << needed for CPictureHolder

IMPLEMENT_DYNCREATE(CDialogView, CFormView)

CDialogView::CDialogView()
	: CFormView(CDialogView::IDD),m_constGridBorder(4)
{
	//{{AFX_DATA_INIT(CDialogView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDialogView::~CDialogView()
{
}

void CDialogView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogView, CFormView)
	//{{AFX_MSG_MAP(CDialogView)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogView diagnostics

BEGIN_EVENTSINK_MAP(CDialogView, CFormView)
    //{{AFX_EVENTSINK_MAP(CMFCDataDlg)
	ON_EVENT(CDialogView, IDC_GOODS_GRID, 82 /* AfterDataRefresh */, OnAfterDataRefresh, VTS_NONE)
	ON_EVENT(CDialogView, IDC_GOODS_GRID, -601 /* DblClick */, OnDblClickGrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

#ifdef _DEBUG
void CDialogView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDialogView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDialogView message handlers





void CDialogView::OnInitialUpdate() 
{
		CDBDoc* pDBDoc=GetDocument();
	ASSERT(pDBDoc);
	pDBDoc->m_strSQL="Select CODE,NAME,PCODE From catalog Where PCODE= ''";
	m_blFillCategory=TRUE;
	CFormView::OnInitialUpdate();
	
	m_crDefaultGridColor=m_GridGoods.GetGridColor ();
	EnableToolTips (TRUE);
	
}

CDBDoc* CDialogView::GetDocument()
{
	CInfoConsole* pThread=(CInfoConsole*)AfxGetThread();
	ASSERT(pThread!=NULL);
	return (CDBDoc*)m_pDocument;
}

void CDialogView::OnClose() 
{

	
	CFormView::OnClose();
	return;
}

int CDialogView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	CRect rc;
	GetClientRect(&rc);
	InflateRect(&rc,-m_constGridBorder,-m_constGridBorder);
	
	m_GridGoods.Create (_T("MyGrid"),WS_CHILD|WS_BORDER|WS_VISIBLE,rc,this,IDC_GOODS_GRID);
	HWND hwnd=m_GridGoods.Detach ();
	m_GridGoods.SubclassWindow (hwnd);
//	m_GridGoods.InitToolTip ();
	return 0;
}

void CDialogView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(&rc);
	InflateRect(&rc,-m_constGridBorder,-m_constGridBorder);

	m_GridGoods.MoveWindow(&rc);

	
}

void CDialogView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your message handler code here
	CWaitCursor cur;
	
	CDBDoc* pDBDoc=GetDocument();
	ASSERT(pDBDoc);
	
	m_GridGoods.SetFontName (pDBDoc->GetFontName () );
	m_GridGoods.SetFontSize ((float)pDBDoc->GetFontSize ());
	
	
	m_blFillCategory =static_cast<BOOL>(lHint);
	
	_RecordsetPtr pRstInt=NULL;
	_RecordsetPtr pRstDiffclt=NULL;
//	int id=0;
//	long r=0;
	_variant_t vtTemp;
	_bstr_t    bstrTemp;
	try
	{
		
		
		TESTHR(pRstInt.CreateInstance(__uuidof(Recordset)));
//		CInfoConsole* pInfo=static_cast<CInfoConsole*>(AfxGetThread());
		CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
		CInfoConsole* pInfo=pApp->m_pInfoConsoleThread;
		CComVariant pSQLConn=_variant_t((IDispatch*)pInfo->pConn);
		HRESULT hr=pRstInt->Open ((_bstr_t)pDBDoc->m_strSQL,/*_variant_t((IDispatch*)pInfo->pConn)*/pSQLConn,
			adOpenKeyset, adLockBatchOptimistic, adCmdText);
		if (hr!=S_OK)
		{
			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
			return ;
		}
		
		long lFieldsCount=pRstInt->Fields->Count ;
		m_blFillCategory=(lFieldsCount==3);//this category?
		// bind grid to recordset
		m_GridGoods.SetEditable(flexEDNone);
		m_GridGoods.SetDataMode(0 /*flexDMFree*/);
		
		m_GridGoods.SetRefDataSource((LPUNKNOWN)pRstInt);
		
		// check binding
		if (m_GridGoods.GetDataSource() == NULL)
		{
			TRACE(_T("Failed to bind grid to recordset"));
			return ;
		}
		if (m_GridGoods.GetDataMode() != 1 /*flexDMBound*/)
		{
			TRACE(_T("Got recordset data, but can't update it ")
				_T("(check recordset parameters)"));
			m_GridGoods.SetEditable(0 /*flexEDNone*/);
		}	
		if((pSender!=NULL)&&(pSender->IsKindOf(RUNTIME_CLASS(CFindView))))
		{
			if (!pDBDoc->m_strDiffSQL.IsEmpty())
			{
				TESTHR(pRstDiffclt.CreateInstance(__uuidof(Recordset)));
				TESTHR(pRstDiffclt->Open ((_bstr_t)pDBDoc->m_strDiffSQL,pSQLConn,
					adOpenKeyset, adLockBatchOptimistic, adCmdText));
				ASSERT(pRstDiffclt->Fields->Count==pRstInt->Fields->Count);
				DWORD nRows = 0;
				
				nRows = pRstDiffclt->GetRecordCount();
				
				if(nRows == -1)
				{
					nRows = 0;
					if(!pRstDiffclt->EndOfFile )
						pRstDiffclt->MoveFirst();
					
					while(!pRstDiffclt->EndOfFile )
					{
						nRows++;
						pRstDiffclt->MoveNext();
					}
					if(nRows > 0)
						pRstDiffclt->MoveFirst();
				}
				
				if (nRows>0)
				{	m_GridGoods.SetRedraw (FALSE);
				pRstDiffclt->MoveFirst();
				pRstInt->MoveLast();
				while(!pRstDiffclt->EndOfFile)
				{	
					//hr=pRstInt->AddNew ();
					long r=m_GridGoods.GetRows();
					m_GridGoods.SetRows(r+1);
					for (long i=0 ;i<pRstDiffclt->Fields->Count ;i++)
					{
						
						_bstr_t strValue=pRstDiffclt->Fields->GetItem((long)i)->Value;
						m_GridGoods.SetTextMatrix (r,i+1,strValue);
						//	pRstInt->Fields->GetItem((long)i)->Value=strOld;
					}
					//TESTHR(pRstInt->Update ());
					//break;
					hr=pRstDiffclt->MoveNext  ();
				}
				//pRstInt->UpdateBatch (adAffectAll);
				
				m_GridGoods.SetRedraw (TRUE);
				}
				TESTHR(pRstDiffclt->Close ());
			}
		}
		TESTHR(pRstInt->Close ());
	
	}
		
		catch (_com_error &e)
		{
			// Notify the user of errors if any.
			// Pass a connection pointer accessed from the Recordset.
			_variant_t vtConnect = pRstInt->GetActiveConnection();
			
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
		
				break;
			}
		}
		
	m_GridGoods.SetAutoSizeMode (flexAutoSizeColWidth);	

	
	m_GridGoods.SetAutoResize (TRUE);	
		
		
		
		
	

}




void CDialogView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	
	// Do not call CFormView::OnPaint() for painting messages
}
//DEL LRESULT CDialogView::OnInfoChanged (WPARAM wParam,LPARAM lParam)
//DEL {
//DEL 	CTreeNode* pNode=reinterpret_cast<CTreeNode*>(wParam);
//DEL 	m_blItemHasChilren =(BOOL)lParam;
//DEL 	_RecordsetPtr pRstInt=NULL;
//DEL 	int id=0;
//DEL 	long r=0;
//DEL 	_variant_t vtTemp;
//DEL 	_bstr_t    bstrTemp;
//DEL 		  try
//DEL 		  {
//DEL 			  
//DEL 			  
//DEL 			  TESTHR(pRstInt.CreateInstance(__uuidof(Recordset)));
//DEL 			  CInfoConsole* pInfo=static_cast<CInfoConsole*>(AfxGetThread());
//DEL 			  
//DEL 			  id=pNode->item.Id  ;
//DEL 			  TCHAR buff[_MAX_PATH];
//DEL 			  memset(buff,0,sizeof(buff));
//DEL 			  _itot(id,buff,10);
//DEL 			  CString strSQL;
//DEL 			  if(pNode->firstChild )
//DEL 			  {
//DEL 				  m_blFillCategory=TRUE;
//DEL 				  strSQL="Select PartId,PartName,PartIdF From Parts Where PartIdF=";
//DEL 				  strSQL=strSQL+buff+" And PartId<>" +buff;
//DEL 			  }
//DEL 			  else
//DEL 			  {
//DEL 				  m_blFillCategory=FALSE;
//DEL 				  strSQL.LoadString(IDS_QUERY_GOODS_FROM_PARTID);
//DEL 				  CString strFilter;
//DEL 				  strFilter.LoadString(IDS_FILTER_GOODS_FROM_PARTID);
//DEL 				  strSQL+=strFilter+buff;
//DEL 			  }
//DEL 			  
//DEL 			  HRESULT hr=pRstInt->Open (strSQL.AllocSysString (),_variant_t((IDispatch*)pInfo->pConn),
//DEL 				  adOpenStatic, adLockBatchOptimistic, adCmdText);
//DEL 			  if (hr!=S_OK)
//DEL 			  {
//DEL 				  AfxMessageBox("Error in Open Recordset",MB_OK|MB_ICONSTOP);
//DEL 				  return -1;
//DEL 			  }
//DEL 			  
//DEL 			  
//DEL 			  // bind grid to recordset
//DEL 			  m_GridGoods.SetEditable(flexEDNone);
//DEL 			  m_GridGoods.SetDataMode(0 /*flexDMFree*/);
//DEL 			   //IVSFlexGridPtr spGrid = m_GridGoods.GetControlUnknown();
//DEL 		//	IVSFlexDataSourcePtr pSource;
//DEL 			//_bstr_t bstr=_T("gdfbgjhdbgsjh");
//DEL 		//	pSource->raw_SetData (1,1,bstr);
//DEL 		//	spGrid->put_FlexDataSource(pSource);
//DEL 			  m_GridGoods.SetRefDataSource((LPUNKNOWN)pRstInt);
//DEL 			  
//DEL 			  // check binding
//DEL 			  if (m_GridGoods.GetDataSource() == NULL)
//DEL 			  {
//DEL 				  TRACE("Failed to bind grid to recordset");
//DEL 				  return -1;
//DEL 			  }
//DEL 			  if (m_GridGoods.GetDataMode() != 1 /*flexDMBound*/)
//DEL 			  {
//DEL 				  TRACE("Got recordset data, but can't update it "
//DEL 					  "(check recordset parameters)");
//DEL 				  m_GridGoods.SetEditable(0 /*flexEDNone*/);
//DEL 			  }
//DEL 			  TESTHR(pRstInt->Close ());
//DEL 			  
//DEL 		  }
//DEL 		  
//DEL 		  catch (_com_error &e)
//DEL 		  {
//DEL 			  // Notify the user of errors if any.
//DEL 			  // Pass a connection pointer accessed from the Recordset.
//DEL 			  _variant_t vtConnect = pRstInt->GetActiveConnection();
//DEL 			  
//DEL 			  // GetActiveConnection returns connect string if connection
//DEL 			  // is not open, else returns Connection object.
//DEL 			  switch(vtConnect.vt)
//DEL 			  {
//DEL 			  case VT_BSTR:
//DEL 				  PrintComError(e);
//DEL 				  break;
//DEL 			  case VT_DISPATCH:
//DEL 				  PrintProviderError(vtConnect);
//DEL 				  break;
//DEL 			  default:
//DEL 				  printf("Errors occured.");
//DEL 				  break;
//DEL 			  }
//DEL 		  }
//DEL 		  
//DEL 		  
//DEL 		  
//DEL 		  return 0L;
//DEL }

          
 void CDialogView::OnAfterDataRefresh() 
{
	CWaitCursor cur;
	CClientDC dc(this);
	CSize szTwPerPixel;
	szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
	szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);

  
	

	m_GridGoods.SetRedraw (FALSE);

	if(m_blFillCategory)
	{
		m_GridGoods.SetGridColor(m_crDefaultGridColor);
		COleVariant vtNone(0L, VT_ERROR);
		m_GridGoods.AutoSize(2, vtNone, vtNone, vtNone);

		m_GridGoods.SetColWidth (0,0);
		m_GridGoods.SetColWidth (3,0);
		m_GridGoods.SetAllowUserResizing (flexResizeColumns);
		m_GridGoods.SetTextMatrix (0,2,_T("Наименование"));
		m_GridGoods.SetTextMatrix (0,1,_T("№ п/п"));
		
		CPictureHolder picFolder;
		HICON hIcon1=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_CLOSEFOLDERS),
			IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
		picFolder.CreateFromIcon(hIcon1,TRUE);
		CPictureHolder picFolders;
		HICON hIcon2=(HICON)::LoadImage(AfxGetInstanceHandle (),MAKEINTRESOURCE(IDI_CLOSEFOLDERS),
			IMAGE_ICON,18,16,LR_LOADTRANSPARENT|LR_LOADMAP3DCOLORS);
		picFolders.CreateFromIcon(hIcon2,TRUE);
		long wdt,ht;
		//size in HIMETRIC (0.01mm)
		picFolder.m_pPict->get_Width (&wdt);
		picFolder.m_pPict->get_Height (&ht);
		
		CSize szPict(wdt,ht);
		dc.HIMETRICtoLP (&szPict);
		//note grid size units is twips
		
		
		m_GridGoods.SetColWidth (0,szPict.cx *szTwPerPixel.cx +100);
		
		//pic.CreateFromIcon (IDI_ICON1);
		// assign picture to grid's current cell
		LPDISPATCH pDispFolder = picFolder.GetPictureDispatch();
		LPDISPATCH pDispFolders = picFolders.GetPictureDispatch();
		for(long i=1;i<m_GridGoods.GetRows();i++){
			m_GridGoods.SetRow (i);
			m_GridGoods.SetCol(0);
			m_GridGoods.SetCellPictureAlignment (flexPicAlignCenterCenter);	


			if(m_blItemHasChilren )
			m_GridGoods.SetCellPicture(pDispFolders);
			else
			m_GridGoods.SetCellPicture(pDispFolder);

			m_GridGoods.SetCol(1);
			TCHAR buff[_MAX_PATH];
			_itot(i,buff,10);
			m_GridGoods.SetText (buff);
			for(long c=1;c<m_GridGoods.GetCols()-1;c++)
			{
				m_GridGoods.SetCol(c);
				if(i%2)
				{
					
					m_GridGoods.SetCellBackColor (RGB(223,223,223));
				}
				else
					
				{
					m_GridGoods.SetCellBackColor (RGB(255,255,255));
				}
			}
		}
		pDispFolders->Release();
		pDispFolder->Release();
		m_GridGoods.SetCol(2);
	}
	else
	{
		m_GridGoods.SetGridColor(RGB(0,0,223));
		COleVariant vtNone(0L, VT_ERROR);
		m_GridGoods.AutoSize(1L, vtNone, vtNone, vtNone);
		m_GridGoods.AutoSize(4L, vtNone, vtNone, vtNone);

		m_GridGoods.SetAllowUserResizing (flexResizeColumns);
		m_GridGoods.SetTextMatrix (0,1,_T("№ п/п"));
		m_GridGoods.SetTextMatrix (0,3,_T("Наименование"));
		m_GridGoods.SetTextMatrix (0,2,_T("Штрих код"));
		m_GridGoods.SetTextMatrix (0,4,_T("РознЦена"));
		m_GridGoods.SetColFormat (4,_T("#,###.##"));
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
		
		
		m_GridGoods.SetColWidth (0,szPict.cx *szTwPerPixel.cx+100 );
		m_GridGoods.SetColWidth (1,1000);
		//set visible price column in client area
		long lColsWidth=0;
		for(int c=0;c<m_GridGoods.GetCols();c++)
			lColsWidth+=m_GridGoods.GetColWidth (c);
		CRect rc;
		m_GridGoods.GetClientRect(&rc);
		long lDelta=lColsWidth-m_GridGoods.GetClientWidth();
		long lCol3Width=m_GridGoods.GetColWidth (3);
		m_GridGoods.SetColWidth (3,lCol3Width-lDelta);
		
		// assign picture to grid's current cell
		LPDISPATCH pDisp = pic.GetPictureDispatch();
		for(long i=1;i<m_GridGoods.GetRows();i++){
			m_GridGoods.SetRow (i);
			m_GridGoods.SetCol(0);
			m_GridGoods.SetCellPictureAlignment (flexPicAlignCenterCenter);	
			m_GridGoods.SetCellPicture(pDisp);
			m_GridGoods.SetCol(1);
			TCHAR buff[_MAX_PATH];
			_itot(i,buff,10);
			m_GridGoods.SetText (buff);
			for(long c=1;c<m_GridGoods.GetCols();c++)
			{
				m_GridGoods.SetCol(c);
				if(i%2)
				{
					
					m_GridGoods.SetCellBackColor (RGB(223,223,223));
				}
				else
					
				{
					m_GridGoods.SetCellBackColor (RGB(255,255,255));
				}
			}
		}
		pDisp->Release();
	
		m_GridGoods.SetCol(2);	
		
		
		
	}
	m_GridGoods.SetRedraw (TRUE);

}
void CDialogView::OnDblClickGrid() 
{
	if(m_blFillCategory) 
		return;

	CDBDoc* pDoc=GetDocument();
	CString strBarCode =m_GridGoods.GetTextMatrix (m_GridGoods.GetRow (),2);
	strBarCode.TrimRight ();
	ASSERT(strBarCode.GetLength ()<=13);

	CString strQuery,strFilter,strQueryGoodMove;
	strQuery.LoadString(IDS_GOODPROP_QUERY);
	strFilter.LoadString(IDS_GOODPROP_FILTER);
	strFilter+=_T("='");
	strFilter+=strBarCode;
	strFilter+=_T("'");
	strQuery+=strFilter;
	pDoc->m_strPropertyQuery =strQuery;

		

	CString strFormat;
	strFormat.LoadString (IDS_FORMAT_DATE);
	strQueryGoodMove.Format(IDS_QUERY_GOOD_MOVE,strBarCode ,
		pDoc->m_dtStart.Format (strFormat),
		pDoc->m_dtEnd.Format (strFormat));

	pDoc->m_strMoveQuery =strQueryGoodMove;
//	TRACE("%s\n",strQueryGoodMove );
	CReportFrame* pFrame=new CReportFrame();
	pFrame->LoadFrame (IDR_INFOFRAME);
	if(::IsWindow (pFrame->m_hWnd))
	{
	pFrame->SetMenu (NULL);
	CString strCaption=_T("Свойства - [");
	strCaption+=m_GridGoods.GetText ();
	pDoc->m_strHead =m_GridGoods.GetText();
	strCaption.TrimRight ();
	strCaption+=_T("]");
	pFrame->SetTitle (strCaption);
	pFrame->SetWindowText (strCaption);
	



	//pFrame->SetParent (GetParent());
	pFrame->ShowWindow (SW_SHOW);
	}


}

BOOL CDialogView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
		long lTopRow=m_GridGoods.GetTopRow ();
	if(zDelta<0)
		m_GridGoods.SetTopRow (++lTopRow);
	else
		m_GridGoods.SetTopRow (--lTopRow);
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}




BOOL CDialogView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::DestroyWindow();
}
