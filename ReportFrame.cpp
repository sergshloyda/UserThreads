// ReportFrame.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ReportFrame.h"
#include "ReportView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportFrame

IMPLEMENT_DYNCREATE(CReportFrame, CFrameWnd)

CReportFrame::CReportFrame()
{
}

CReportFrame::~CReportFrame()
{
}


BEGIN_MESSAGE_MAP(CReportFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CReportFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportFrame message handlers

BOOL CReportFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return m_wndFolderFrame.Create(this,
		RUNTIME_CLASS(CReportView),
		pContext,
		IDR_FOLDERTABS);
}


BEGIN_MESSAGE_MAP(CReport, CWnd)
	//{{AFX_MSG_MAP(CReportWnd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
int CReport::nInstance =0;
void CReport::Head(CString &lstStr,int* pCurRow,int nBeginRow)
{
	ASSERT(m_spGrid!=NULL);

	
	m_spGrid->put_MergeCells (flexMergeFree);
	nBeginRow=1;
	_variant_t varRow((long)nBeginRow,VT_I4);
	_variant_t varColBegin(1L,VT_I4);
	long lColMergeEnd=m_spGrid->Cols-1;
	_variant_t varColEnd(lColMergeEnd,VT_I4);
	_bstr_t bstrValue=lstStr.AllocSysString ();
	_variant_t vrtValue(bstrValue);
	m_spGrid->put_MergeRow ((long)nBeginRow,TRUE);
	m_spGrid->put_Cell (flexcpText,varRow,varColBegin,varRow,varColEnd,vrtValue );
	m_spGrid->put_CellAlignment (flexAlignCenterCenter);
	*pCurRow=2;
}

void CReport::Body(int* pCurRow,int nBeginRow)
{
	m_spGrid->put_MergeCells (flexMergeFree);
	m_spGrid->Redraw =flexRDNone;
	
	if(!m_blIsDataSheet)
	
		ShowProperty(pCurRow,nBeginRow);
	else
		ShowMove(pCurRow,nBeginRow);
	
	m_spGrid->Redraw =flexRDDirect;
}
void CReport::UnderGround(CString& strUndGrnd,int nBeginRow)
{

}

BOOL CReport::ShowReport()
{
	int nCurRow=0;
	VARIANT v; 
	V_VT(&v) = VT_ERROR;
	_variant_t var(0L,VT_I4);
	m_spGrid->Clear (var,var);
	Head(m_strHead,&nCurRow);
	Body(&nCurRow,nCurRow);
	UnderGround(m_strUnderGround ,nCurRow);

	return TRUE;
}

BOOL CReport::CreateGrid(_bstr_t bstrFontName,int nFontSize)
{
	CRect rc(0,0,0,0);//empty rect get sizes from view
	
	// create control (hosted by an MFC CWnd)
	if(!CreateControl(_T("VSFlexGrid.VSFlexGrid.1"), NULL, WS_VISIBLE, rc, m_pParentWnd, IDC_GRID))
		return FALSE;
	// get dual interface
	m_spGrid = GetControlUnknown();
	if(m_spGrid==NULL)
		return FALSE;
	// use dual interface
	m_spGrid->put_FontName(bstrFontName);
	m_spGrid->put_FontSize ((float)nFontSize);	
	OLE_COLOR clrGrid=::GetSysColor(COLOR_WINDOW);
	m_spGrid->put_GridColor(clrGrid);
	m_spGrid->put_BackColor (clrGrid);
	m_spGrid->put_BackColorBkg (clrGrid);
	m_spGrid->put_SheetBorder (clrGrid);
	m_spGrid->put_BackColorFixed(clrGrid);
	m_spGrid->put_GridLinesFixed (flexGridFlat);


	m_spGrid->put_GridColorFixed (clrGrid);
	m_spGrid->put_ScrollBars (flexScrollBarNone	);
	m_spGrid->put_ColWidth (0,0);
	m_spGrid->put_RowHeight  (0,0);
	

	return TRUE;

}

//DEL void CReport::SetRecordset(CString strQuery, CString strParam)
//DEL {
//DEL //m_vrtQuery.ChangeType (VT_BSTR);beneath
//DEL m_bstrQuery =strQuery.AllocSysString ();
//DEL //m_vrtFilter.ChangeType (VT_BSTR);
//DEL m_bstrFilter =strParam.AllocSysString ();
//DEL }

void CReport::ShowReport(int nSettings)
{
///////////
	int nCurRow=0;
	_variant_t var(0L,VT_I4);
	m_spGrid->Clear (var,var);
	switch (nSettings)
	{
	case rprtPropertyView:
		m_blIsDataSheet =FALSE;
		nCurRow=1;
		Body(&nCurRow,nCurRow);
		break;
	case rprtMoveView:
		m_blIsDataSheet=TRUE;
		if(blFirstTime)
		{
		Head(m_strHead,&nCurRow);
		Body(&nCurRow,nCurRow);
		UnderGround(m_strUnderGround ,nCurRow);
		SetAutoSizeForGrid();
		SaveGrid();
		}
		else
			RestoreGrid();

		break;

	}


}

void CReport::GetGridSize(CSize *szGrid)
{
	long lGridWidth=0;
	long lGridHeight=0;
	SHORT wc=0;
	m_spGrid->get_GridLineWidth (&wc);
	for(long c=0;c<m_spGrid->Cols;c++)
	{
		long w=0;
		
		m_spGrid->get_ColWidth (c,&w);
		
		lGridWidth+=(w+wc);
	}
	for(long r=0;r<m_spGrid->Rows;r++)
	{
		long w=0;
		
		m_spGrid->get_RowHeight  (r,&w);
		
		lGridHeight+=(w+wc);
	}
	szGrid->cx =lGridWidth;
	szGrid->cy =lGridHeight;
}

BOOL CReport::IsSubclassed()
{
return(m_hWnd!=NULL);
}
BOOL CReport::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::PreCreateWindow(cs);
}

void CReport::ShowProperty(int *pCurRow, int nBeginRow)
{
	_RecordsetPtr pRst=NULL;
		m_spGrid->put_FixedRows (0L);
		try
		{
			
			
			TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
			CInfoConsole* pInfo=static_cast<CInfoConsole*>(AfxGetThread());
			HRESULT hr=pRst->Open (m_bstrPropertyQuery,_variant_t((IDispatch*)pInfo->pConn),
				adOpenStatic, adLockBatchOptimistic, adCmdText);
			TESTHR(hr);
			//pRst->Filter =m_bstrFilter;
			VARIANT v; 
			V_VT(&v) = VT_ERROR; 
			long lFieldCount=pRst->Fields ->Count ;
			m_spGrid->Rows=(long)nBeginRow+lFieldCount;
			for(long lItem=0;lItem<lFieldCount;lItem++)
			{
				_variant_t varRow((long)nBeginRow+lItem,VT_I4);
				_variant_t varColBegin(1L,VT_I4);
				_variant_t varColEnd(3L,VT_I4);
				
				_bstr_t bstrFName=pRst->Fields->Item[lItem]->Name;
				_bstr_t bstrValue=pRst->Fields ->Item [lItem]->Value;
				_variant_t vrtFName(bstrFName);
				_variant_t vrtValue(bstrValue);
				m_spGrid->put_MergeRow ((long)nBeginRow+lItem,TRUE);
				m_spGrid->put_Cell (flexcpText,varRow,varColBegin,varRow,varColEnd,vrtFName );
				m_spGrid->put_CellAlignment (flexAlignLeftCenter);
				varColBegin.lVal +=(varColEnd.lVal) ;
				long lCols=m_spGrid->Cols ;
				varColEnd.lVal =lCols-1;
				m_spGrid->put_WordWrap (TRUE);

				CClientDC dc(this);
				CFont font;
				BSTR bstrFontName;
				m_spGrid->get_FontName (&bstrFontName);
				font.CreatePointFont ((int)(m_spGrid->FontSize*10),(TCHAR*)bstrFontName);
				::SysFreeString (bstrFontName);
				CFont* oldFont=dc.SelectObject (&font);
				CSize szTwPerPixel;
				szTwPerPixel.cy =1440/dc.GetDeviceCaps (LOGPIXELSY);
				szTwPerPixel.cx =1440/dc.GetDeviceCaps (LOGPIXELSX);
				CSize szText=dc.GetTextExtent ((TCHAR*)bstrValue);//calculate width of text in pixels
				dc.SelectObject (oldFont);

				long RowWidth=0;
				for(long i=varColBegin.lVal ;i<=varColEnd.lVal ;i++)
				{
					long lColWdt=0;
					m_spGrid->get_ColWidth(i,&lColWdt);
					RowWidth+=lColWdt;
				}//calculate merging cells width
				int nRows=((szText.cx *szTwPerPixel.cx) /RowWidth)+1;//calculate necessary rowheight for text
				long lRowHeight=0;
				m_spGrid->get_RowHeight (1,&lRowHeight);
				m_spGrid->put_Cell (flexcpText,varRow,varColBegin,varRow,varColEnd,vrtValue );
				m_spGrid->put_RowHeight (varRow,lRowHeight*nRows);
				m_spGrid->Select (varRow,varColBegin,v,v);
			
				m_spGrid->put_CellAlignment (flexAlignLeftCenter);
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
				AfxMessageBox(_T("Errors occured."),MB_ICONSTOP);
				break;
			}
		}
		
}

void CReport::ShowMove(int *pCurRow, int nBeginRow)
{
	
	COleVariant one(1l);
	COleVariant empty(0l);
	//long brows=m_spGrid->Rows ;
	m_spGrid->put_FixedRows ((long)(nBeginRow+1));



	AfxGetApp()->BeginWaitCursor ();
	
	_RecordsetPtr pRst=NULL;
	
	try
	{
		
		
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		CInfoConsole* pInfo=static_cast<CInfoConsole*>(AfxGetThread());
		HRESULT hr=pRst->Open (m_bstrMoveQuery,_variant_t((IDispatch*)pInfo->pConn),
			adOpenStatic, adLockBatchOptimistic, adCmdText);
		TESTHR(hr);
		//pRst->Filter =m_bstrFilter;
	 
		VARIANT v; 
			V_VT(&v) = VT_ERROR; 
			long lFieldCount=pRst->Fields ->Count ;
			
			for(long lItem=0;lItem<lFieldCount;lItem++)
			{
				
				
				_bstr_t bstrFName=pRst->Fields->Item[lItem]->Name;
				
				//_variant_t vrtFName(bstrFName);
				
				
				m_spGrid->put_TextMatrix ((long)nBeginRow,(long)(lItem+1),bstrFName);

			}
	
//////////////////////////////////////////////////////////////////////////////////////
		TESTHR(pRst->MoveLast ());
		long lRows=pRst->RecordCount ;
		TESTHR(pRst->MoveFirst ());
		varArrMoveData=pRst->GetRows (lRows);//get data from recordset 
		if(varArrMoveData.vt==(VT_ARRAY | VT_VARIANT))
			
			m_spGrid->LoadArray(varArrMoveData ,one,empty,empty,empty);
		TRACE1("Grid Rows=%d\n",m_spGrid->Rows);
		TESTHR(pRst->Close ());
		
		
	}
	
	catch (_com_error &e)
	{
		AfxGetApp()->EndWaitCursor ();	
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
			AfxMessageBox(_T("Errors occured."),MB_ICONSTOP);
			break;
		}
	}
	AfxGetApp()->EndWaitCursor ();	


	//m_spGrid->Rows =max(brows,m_spGrid->Rows);
		
}

void CReport::LoadMove()
{


}

void CReport::SetAutoSizeForGrid()
{
	VARIANT v; 
	V_VT(&v) = VT_ERROR; 
	m_spGrid->put_AutoResize(TRUE);
	m_spGrid->AutoSizeMode =flexAutoSizeColWidth;
	long lCols=m_spGrid->Cols -1;
	long lRows=m_spGrid->Rows -1;
	_variant_t varColEnd(lCols,VT_I4);
	_variant_t varRowEnd(lRows,VT_I4);
	m_spGrid->AutoSize (0L,varColEnd,v,v);
	//border around table
	m_spGrid->Select (2L,1L,varRowEnd,varColEnd);
	m_spGrid->CellBorder (RGB(0,0,0),2, 3, 2, 2, 1, 1);
	//border around title
	m_spGrid->Select (2L,1L,2L,varColEnd);
	m_spGrid->CellBorder (RGB(0,0,0),-1, -1, -1, 3, 2, 2);
}

void CReport::SaveGrid()
{
	VARIANT v; 
	V_VT(&v) = VT_ERROR;
	DWORD len;
	TCHAR buff[255];
	len=255;
	::GetTempPath (len,buff);
	
	strMoveGridPath.Format (_T("%sMoveGood%d.tmp"),buff,nInstance);
	MessageBoxHelper::ShowError(strMoveGridPath);
	m_spGrid->SaveGrid ((_bstr_t)strMoveGridPath,flexFileAll,v);
	blFirstTime=FALSE;
}

void CReport::RestoreGrid()
{
	VARIANT v; 
	V_VT(&v) = VT_ERROR;
m_spGrid->LoadGrid ((_bstr_t)strMoveGridPath,flexFileAll,v);
}
void CReport::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

}


