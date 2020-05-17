// UserThreadsDoc.cpp : implementation of the CUserThreadsDoc class
//

#include "stdafx.h"
#include "UserThreads.h"
#include "MainFrm.h"
//#include "UserThreadsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//inline void TESTHR(HRESULT x){if FAILED(x) _com_issue_error(x);};


static TCHAR szSection[]     = _T("Font1");
static TCHAR szFontName[]    = _T("Font Name");
static TCHAR szFontSize[]    = _T("Font Size");

/////////////////////////////////////////////////////////////////////////////
// CUserThreadsDoc

IMPLEMENT_DYNCREATE(CUserThreadsDoc, CDocument)

BEGIN_MESSAGE_MAP(CUserThreadsDoc, CDocument)
	//{{AFX_MSG_MAP(CUserThreadsDoc)
	ON_COMMAND(ID_FONT_BOLD, OnFontBold)
	ON_COMMAND(ID_FONT_ITALIC, OnFontItalic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserThreadsDoc construction/destruction


CUserThreadsDoc::CUserThreadsDoc()
{
	// TODO: add one-time construction code here
	blCatalogOpen=FALSE;

}

CUserThreadsDoc::~CUserThreadsDoc()
{
	AfxMessageBox("Destructor CUserThreadsDoc\n");
}

BOOL CUserThreadsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	CString szText=_T("Привет с другой планеты");
//	SetText(szText);
	
	//AfxMessageBox(szText);
	ReadFont();
	ReadComPort();
//	HRESULT hr=0;
	
	pRstCatalog.CreateInstance (__uuidof(Recordset));
	if(!OpenRecordsetList())return FALSE;
	LoadCategoryTree();
	//OpenRecordsetList();

//	WaitForSingleObject(waited when splash will be closed)
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUserThreadsDoc serialization

void CUserThreadsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CUserThreadsDoc diagnostics

#ifdef _DEBUG
void CUserThreadsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUserThreadsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUserThreadsDoc commands



void CUserThreadsDoc::LoadCategoryTree()
{
//	Sleep(2000);
//	HRESULT    hr = S_OK;
    _RecordsetPtr    pRst  = NULL;

    	//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
//     int intCommand = 0;

    // Temporary string variable for type conversion .
    _bstr_t  bstrPartId;
    _bstr_t  bstrPartName;
	_bstr_t  bstrPartIdF;

    try
    {
	//TESTHR(pApp->pConn.CreateInstance (__uuidof(Connection)));
		//TESTHR(pApp->pConn->Open ("File Name=..\\data\\connstring.udl","","",adConnectUnspecified));
			CNodeItem item;
			_variant_t vtTemp;
		
			_tcscpy(item.code   ,_T("00000004"));
	
			_tcscpy(item.pcode  ,_T("") );
		
			_bstr_t bstrBuff="Товары" ;
			lstrcpy(item.text ,(char*)bstrBuff) ;
			m_dataTree.SetRootData (item);
			
			populatetree(m_dataTree.GetRootNode ());
		
			
			//TESTHR(pApp->pConn->Close());
    }
    catch (...)
    {
   
    
           AfxMessageBox("Error occured!!LoadCategoryTree");
        
    }

}

void CUserThreadsDoc::populatetree(CTreeNode *ptrNode)
{
if(ptrNode!=NULL)
	{
		_RecordsetPtr pRstInt=NULL;
		CString code;
		static BOOL flag=TRUE;
		CTreeNode* pNode=NULL;
		_variant_t vtTemp;
		_bstr_t    bstrTemp;
		TESTHR(pRstInt.CreateInstance(__uuidof(Recordset)));
		CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		code=ptrNode->item.code ;
		code.TrimRight();
		code.TrimLeft();
		//_tcscpy(code,ptrNode->item.code )  ;
		/*TCHAR buff[255];
		memset(buff,0,sizeof(buff));
		itoa(id,buff,10);*/
		CString strSQL="Select CODE,NAME,PCODE From catalog Where PCODE='";
		strSQL=strSQL+code+"' And CODE<>'" +code+"' AND ISFOLDER=1";
		
		HRESULT hr=pRstInt->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
			adOpenStatic, adLockBatchOptimistic, adCmdText);
		if (hr!=S_OK)
		{
			AfxMessageBox("Error in Open Recordset",MB_OK|MB_ICONSTOP);
			return;
		}
		CWnd* pSplash=CWnd::FindWindow (NULL,"Загрузка Продажи 1.3");
		while(!pRstInt->EndOfFile )
		{
			CNodeItem item;
			CString strTemp=_T("");

			bstrTemp=pRstInt->Fields ->Item ["CODE"]->Value;
			strTemp=(TCHAR*)bstrTemp;
			strTemp.TrimLeft();
			strTemp.TrimRight ();
			memset(item.code,0,sizeof(item.code ));
			strcpy(item.code  ,/*(TCHAR*)b*/strTemp);
		//	item.Id  =vtTemp.intVal ;
			bstrTemp=pRstInt->Fields ->Item ["PCODE"]->Value;
			strTemp=(TCHAR*)bstrTemp;
			strTemp.TrimRight ();
			strTemp.TrimLeft();
			memset(item.pcode,0,sizeof(item.pcode));
			_tcscpy(item.pcode  ,/*(TCHAR*)b*/strTemp);
			//_tcscpy(item.pcode   ,(TCHAR*)bstrTemp);
			bstrTemp=pRstInt->Fields ->Item ["NAME"]->Value;
			strTemp=(TCHAR*)bstrTemp;
			TRACE("CUserThreadsDoc:%s\n",strTemp);
			if(pSplash)
			pSplash->PostMessage (WM_SPLASH_INFO,(WPARAM)(LPCTSTR)strTemp,0L);
			strTemp.TrimRight ();
			strTemp.TrimLeft();
			_tcscpy(item.text ,strTemp);
			if(flag)
				pNode=m_dataTree.AttachFirstChild (item,ptrNode);
			else
				pNode=m_dataTree.AttachNextChild (item,pNode);
			flag=FALSE;
			pRstInt->MoveNext ();
		}
		TESTHR(pRstInt->Close ());
		
		flag=TRUE;
		populatetree(ptrNode->firstChild );
		populatetree(ptrNode->nextChild );

	}

}

CNTree& CUserThreadsDoc::GetCategoryTree()
{
return m_dataTree;
}

void CUserThreadsDoc::SetLogFont(LOGFONT *lf)
{
m_font.CreateFontIndirect (lf);
}

void CUserThreadsDoc::SetFont(CFont &newFont)
{
m_font.Attach(newFont.Detach ());
}
void CUserThreadsDoc::SetPointFont(LPCTSTR szName, int nSize)
{
	if ((HFONT)m_font) 
	{
		// first time init: create font
		m_font.DeleteObject ();
	}
	m_font.CreatePointFont (nSize*10,szName);
	m_nFontSize=nSize;
}




void CUserThreadsDoc::OnFontBold() 
{
	// TODO: Add your command handler code here
	LOGFONT lf;
	m_font.GetLogFont (&lf);
	AfxMessageBox(lf.lfFaceName );
}

void CUserThreadsDoc::OnFontItalic() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("Not Implemented");
}

void CUserThreadsDoc::ReadFont()
{
	CMainFrame* pFrame=static_cast<CMainFrame*>(AfxGetMainWnd());

	m_szFontName=AfxGetApp()->GetProfileString (szSection,szFontName,_T("Arial"));
	m_nFontSize=AfxGetApp()->GetProfileInt(szSection,szFontSize,10);

	pFrame->m_wndFontTB.SetupToolBar (m_szFontName,m_nFontSize);

	SetPointFont(m_szFontName,m_nFontSize);
}

void CUserThreadsDoc::SaveFont()
{
	CString szBuffer;
	CMainFrame* pFrame=static_cast<CMainFrame*>(AfxGetMainWnd());
	if(!IsWindow(pFrame->m_wndFontTB.m_hWnd )) return;
	szBuffer=pFrame->m_wndFontTB.GetFontName ();

	int nSize=10;
  
	nSize=pFrame->m_wndFontTB.GetFontSize ();

	AfxGetApp()->WriteProfileString(szSection, szFontName, szBuffer);
	AfxGetApp()->WriteProfileInt (szSection,szFontSize,nSize);
}

void CUserThreadsDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
	CloseAllRecordsets();
	SaveFont();
	AfxMessageBox("CUserThreadsDoc::OnCloseDocument()\n");
	//if(blCatalogOpen)
	//{
	//	TESTHR(pRstCatalog->Close ());
	//	blCatalogOpen=FALSE;
	//}
	
	//TESTHR(pApp->pConn->Close());
	CDocument::OnCloseDocument();

}

void CUserThreadsDoc::ReadComPort()
{
	int nComPort=0;
	TCHAR szComPortSection[] =_T("ComPort");
	TCHAR szComPort[]=_T("ComPort");
	nComPort = AfxGetApp()->GetProfileInt(szComPortSection, szComPort, 1);
	m_strComPort.Format ("COM%d",nComPort);
}

void CUserThreadsDoc::DisconnectBase()
{
	CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
	//SaveFont();
	//TRACE("On Close Document\n");

	CloseAllRecordsets();

	if(pApp->pConn->State ==adStateOpen)
	TESTHR(pApp->pConn->Close());
	while(pApp->pConn->State ==adStateOpen){
		TRACE("Connection no Closed\n");
			::Sleep(1500);
	}
	

}


BOOL CUserThreadsDoc::OpenRecordsetList()
{
	try
    {
		CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		if(pApp->pConn->State ==adStateOpen)
		{
			
			
			_RecordsetPtr pRst=NULL;
			TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
			
			HRESULT hResult=pRst->Open(_bstr_t("master"),_variant_t((IDispatch*)pApp->pConn), 
				adOpenKeyset, adLockOptimistic,adCmdTable);
			if(hResult!=S_OK)
				return -1;
			TESTHR(pRst->MoveFirst ());
			CString strPointInfo;
			strPointInfo.Format ("Точка:%s\n",(char*)(_bstr_t)(pRst->Fields->Item["pointname"]->Value));
			m_strPointId=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("pointid")->Value);
			m_strPointId.TrimRight();
			TESTHR(pRst->Close());
			hResult=pRst->Open(_bstr_t("employee"),_variant_t((IDispatch*)pApp->pConn), 
				adOpenKeyset, adLockOptimistic,adCmdTable);
			if(hResult!=S_OK)
				return -1;
			strPointInfo+=(LPCTSTR)"Продавцы:\n";
			while(pRst->EndOfFile !=VARIANT_TRUE)
			{		
				CString strSaler;
				strSaler.Format("%s\n",(char*)(_bstr_t)(pRst->Fields->Item["emplname"]->Value));
				strPointInfo+=strSaler;
				TESTHR(pRst->MoveNext());
			}
			TESTHR(pRst->Close());
			CWnd* pSplash=CWnd::FindWindow (NULL,"Загрузка Продажи 1.3");
			if(pSplash&&IsWindow(pSplash->m_hWnd ))
			pSplash->SendMessage (WM_SPLASH_INFO,(WPARAM)strPointInfo.GetBuffer (255),1L);
		
		
		
		hResult=pRst->Open(_bstr_t("Select id from contragents where contrname='Частное лицо'"),_variant_t((IDispatch*)pApp->pConn), 
				adOpenKeyset, adLockOptimistic,adCmdText);
			if(hResult!=S_OK)
				return -1;
			TESTHR(pRst->MoveFirst ());
			
			m_strContragId=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("id")->Value);
			m_strContragId.TrimRight();
			TESTHR(pRst->Close());
		
		pRstCatalog->CursorLocation = adUseClient;
		
		pRstCatalog->Open(_bstr_t("catalog"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		//pRst=pApp->pConn->Execute (strTable.AllocSysString (),&(_variant_t(0L)),adCmdTable);
		char buff[255];
		sprintf(buff,"%s pRst is=%x\n", 
			(char*) ((_bstr_t) pRstCatalog->GetFields()->GetItem("name")->GetValue()),pRstCatalog);
		blCatalogOpen=TRUE;	
		
		}
		
		return TRUE;
	}
	catch(_com_error &e)
    {
		// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
        _variant_t vtConnect = pRstCatalog->GetActiveConnection();
		
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
			printf("Errors occured.");
			break;
        }
		return FALSE;
    }
	

}

BOOL CUserThreadsDoc::CloseAllRecordsets()
{
	if(pRstCatalog->State ==adStateOpen)
	{
		try
		{
			pRstCatalog->Close ();
			return TRUE;
		}
		catch(_com_error &e)
		{
			TRACE("%s\n",(char*)e.Description ());
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CUserThreadsDoc::CashDoActionIncome()
{

CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	//_variant_t v;
	try
	{
		pRst->Open (_bstr_t("racash"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(m_strCurDocId);
		pRst->Fields->GetItem("debcredit")->Value =0L;
		pRst->Fields->GetItem("value")->Value =_variant_t(m_flCurSumma );
		
		TESTHR(pRst->Update ());
		pRst->Close();
		return TRUE;
		
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;
		
	}
}

BOOL CUserThreadsDoc::CashDoActionOutcome()
{
	return TRUE;
}

BOOL CUserThreadsDoc::TransactCheck(_variant_t& vtArray)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	pApp->pConn->BeginTrans ();
	COleDateTime tmCheckTime=COleDateTime::GetCurrentTime ();
	CString strDocId;
	int nDayNumber=0;
	CalculateDocId(m_strPointId ,strDocId,&nDayNumber);
	if(!SaveHeadCheck(tmCheckTime) )pApp->pConn->RollbackTrans ();
	if(!SaveTableCheck(vtArray))pApp->pConn->RollbackTrans ();;
	if(!AddNewCheckInJournal(tmCheckTime))pApp->pConn->RollbackTrans ();
	if(!UpdateNumerator (tmCheckTime))pApp->pConn->RollbackTrans ();
	if(!CashDoActionIncome())pApp->pConn->RollbackTrans ();
	pApp->pConn->CommitTrans ();
	return TRUE;
}

BOOL CUserThreadsDoc::CalculateDocId(CString strPointId, CString &strDocId, int *pDayNumber)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CString strSQL="Select MAX(tnumber),prefix From Numerator group by prefix having prefix='";
	strSQL+=strPointId;
	strSQL+=(LPCTSTR)"'";
	_RecordsetPtr pRst=NULL;
	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	
	try
	{
		pRst=pApp->pConn->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
		CString strMaxNum=(LPCTSTR)(_bstr_t)pRst->Fields->GetItem(0L)->Value ;
		int nMaxNum=_ttoi(strMaxNum);
		nMaxNum++;
		
		m_nCurMaxDocNum=nMaxNum;
		strMaxNum.Empty ();
		strMaxNum.Format("%d",nMaxNum);
		CString strPrefix=(LPCTSTR)(_bstr_t)pRst->Fields->GetItem(1L)->Value ;
		strPrefix.TrimRight ();
		CString strDIWZ=strPrefix+strMaxNum;//strDocId without zero
		int nLen=strDIWZ.GetLength ();
		int nZero=10-nLen;
		while(nZero--)
			strPrefix+="0";
		m_strCurDocId=strPrefix+strMaxNum;
		*pDayNumber=0;
		(*pDayNumber)++;
		
		return TRUE ;	
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description ());
		return FALSE;
	}
}

BOOL CUserThreadsDoc::SaveHeadCheck(COleDateTime &tmCheckTime)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	//_variant_t v;
	try
	{
		pRst->Open (_bstr_t("headcheck"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(m_strCurDocId);
		pRst->Fields->GetItem("pointid")->Value =_bstr_t(m_strPointId);
		pRst->Fields->GetItem("contragid")->Value =_bstr_t(m_strContragId);
		pRst->Fields->GetItem("salerid")->Value =_bstr_t(m_strUserId);
		pRst->Fields->GetItem("checkdate")->Value =_bstr_t(tmCheckTime.Format (VAR_DATEVALUEONLY));
		pRst->Fields->GetItem("checktime")->Value =_bstr_t(tmCheckTime.Format (VAR_TIMEVALUEONLY));
		pRst->Fields->GetItem("descript")->Value =_bstr_t("Здесь могла быть ваша реклама");
		TESTHR(pRst->Update ());
		pRst->Close();
		return TRUE;
		
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;
		
	}
}

BOOL CUserThreadsDoc::SaveTableCheck(_variant_t& vt )
{
	ASSERT(vt.vt ==(VT_ARRAY | VT_VARIANT));
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	
	_RecordsetPtr pRst;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	//_variant_t v;
	try
	{
		ASSERT(pApp->pConn->State ==adStateOpen);
		pRst->Open (_bstr_t("tablecheck"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		COleSafeArray sa(vt);
		long lNumRows;
		long lNumCols;
		sa.GetUBound(1, &lNumRows);
		sa.GetUBound(2, &lNumCols);
		
		//Display the elements in the SAFEARRAY.
		long index[2];
		VARIANT val;
		
		//Determine upper bounds for both dimensions
		long r, c;
		sa.GetLBound(1, &r);
		sa.GetLBound(2, &c);
		
		for(;r <= lNumRows; r++ )
		{
			TESTHR(pRst->AddNew ());
			pRst->Fields->GetItem("docid")->Value =_bstr_t(m_strCurDocId);
			long numpos=r+1;
			_variant_t varNumPos(numpos);
			pRst->Fields->GetItem("numpos")->Value =varNumPos;
			index[0]=r;
			index[1]=lNumCols;
			sa.GetElement(index, &val);
			pRst->Fields->GetItem("nomenid")->Value=val ;
			index[1]=4L;
			sa.GetElement(index, &val);
			pRst->Fields->GetItem("qty")->Value =val;
			index[1]=2L;
			sa.GetElement(index, &val);
			pRst->Fields->GetItem("price")->Value =val;		
			
		}
		TESTHR(pRst->UpdateBatch (adAffectAll));
		pRst->Close();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;
	}
/*		for(long i=1;i<m_wndGrid.GetRows();i++)
		{
		

	

		
		CString strNomCode=m_wndGrid.GetTextMatrix(i,7);
		strNomCode.TrimRight ();
		pRst->Fields->GetItem("nomenid")->Value =_bstr_t( strNomCode);
		
		long nQty=0;
		nQty=_ttoi(m_wndGrid.GetTextMatrix(i,5));
		_variant_t varQty(nQty);
		pRst->Fields->GetItem("qty")->Value =varQty;

		double fPrice=atof(m_wndGrid.GetTextMatrix(i,3));
		_variant_t varPrice(fPrice);
		pRst->Fields->GetItem("price")->Value =varPrice;;
		}
		TESTHR(pRst->UpdateBatch (adAffectAll));
		pRst->Close();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;
	}
	*/

}

BOOL CUserThreadsDoc::AddNewCheckInJournal(COleDateTime &tmCheckTime)
{	
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();

	_RecordsetPtr pRstGJ=NULL;
	
	pRstGJ.CreateInstance (__uuidof(Recordset));

	
	try
	{
		pRstGJ->Open (_bstr_t("genjournal"),_variant_t((IDispatch*)pApp->pConn), 
				adOpenDynamic, adLockPessimistic,adCmdTable);
		TESTHR(pRstGJ->MoveLast ());
		CString strLastId=(LPCTSTR)(_bstr_t)pRstGJ->Fields->GetItem("id")->Value;
		int nId=_ttoi(strLastId);
		strLastId.Empty ();
		strLastId.Format("%d",++nId);
		_variant_t varTime(tmCheckTime);
		TESTHR(pRstGJ->AddNew ());
		pRstGJ->Fields->GetItem("id")->Value =_bstr_t(strLastId);
		pRstGJ->Fields->GetItem("doctype")->Value =_bstr_t("CHK");
		pRstGJ->Fields->GetItem("hdocid")->Value =_bstr_t(m_strCurDocId);
		pRstGJ->Fields->GetItem("tdocid")->Value =_bstr_t(m_strCurDocId);
		pRstGJ->Fields->GetItem("docdate")->Value =_bstr_t(tmCheckTime.Format (VAR_DATEVALUEONLY));
		pRstGJ->Fields->GetItem("doctime")->Value =varTime;
		_variant_t varSumma(m_flCurSumma);
	
		pRstGJ->Fields->GetItem("summa")->Value =varSumma;
		pRstGJ->Fields->GetItem("isloaded")->Value =VARIANT_FALSE;
	
		TESTHR(pRstGJ->Update ());
		pRstGJ->Close();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;

	}
}

BOOL CUserThreadsDoc::UpdateNumerator(COleDateTime &tmCheckTime)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	_RecordsetPtr pRstNum=NULL;
	_RecordsetPtr pRstCount=NULL;
	pRstNum.CreateInstance (__uuidof(Recordset));
	_variant_t varTime(tmCheckTime);
	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	try
	{
		pRstCount=pApp->pConn->Execute (_bstr_t("Select count(id) from genjournal where isloaded=0 and doctype='CHK'"),&v,adOptionUnspecified);
		_variant_t val=pRstCount->Fields ->GetItem(0L)->Value ;//получили количество непроведенных чеков
		val.lVal++ ;

		pRstNum->Open (_bstr_t("numerator"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenDynamic, adLockPessimistic,adCmdTable);
		TESTHR(pRstNum->AddNew ());
		
		pRstNum->Fields->GetItem("prefix")->Value =(_bstr_t)m_strPointId;
		pRstNum->Fields->GetItem("tnumber")->Value =(long)m_nCurMaxDocNum;
		pRstNum->Fields->GetItem("dnumber")->Value =val;
		
		pRstNum->Fields->GetItem("lastdocid")->Value =(_bstr_t)m_strCurDocId;
		
		pRstNum->Fields->GetItem("tlastdoc")->Value =varTime;
		TESTHR(pRstNum->Update ());
		pRstNum->Close();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;
		
	}
}
BOOL CUserThreadsDoc::LoadAllChecksOnDate(COleDateTime tmDate, _Recordset** pRs)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	_RecordsetPtr pRst=NULL;
	pRst.CreateInstance(__uuidof(Recordset));
	_variant_t varDate(tmDate);
	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	CString strDate=tmDate.Format ("%m/%d/%y");
	CString strSQLPredicat=
		_T("SELECT genjournal.isloaded, doctable.descr, genjournal.hdocid, headcheck.checkdate, ") 
		_T(" headcheck.checktime,genjournal.summa, (employee.emplname+contragents.contrname) as Info")
		_T(" FROM genjournal INNER JOIN")
		_T(" doctable ON genjournal.doctype = doctable.doctype INNER JOIN")
		_T(" headcheck ON genjournal.hdocid = headcheck.docid INNER JOIN")
		_T(" employee ON headcheck.salerid = employee.emplid INNER JOIN")
		_T(" contragents ON headcheck.contragid = contragents.id where genjournal.docdate=");
	CString strSQL;
	strSQL.Format ("%s{%s} and genjournal.doctype='CHK'",strSQLPredicat,strDate);
	
	try
	{
		pRst=pApp->pConn->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
	
		TRACE("%d\n",(pRst)->GetRecordCount ());
		*pRs=pRst.Detach ();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;
		
	}
}

BOOL CUserThreadsDoc::LoadEntryDoc(LPCTSTR szDocId, _Recordset **ppRst)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	_RecordsetPtr pRstFile=NULL;
	_RecordsetPtr pRst=NULL;
	pRst.CreateInstance(__uuidof(Recordset));
	
	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	//либо пишем хитрый запрос, либо сначала находим по номеру документа тип,
	//по типу- файл таблицы. открываем его и возвращаем все записи
	//select doctable.dtname from doctable inner join genjournal on 
	//doctable.doctype=genjournal. doctype where genjournal.tdocid=szdocId
	CString strSQLPredicat=
		_T("select doctable.dtname from doctable inner join genjournal on ") 
		_T(" doctable.doctype=genjournal. doctype where genjournal.tdocid=");
		
	CString strSQL;
	strSQL.Format ("%s'%s' ",strSQLPredicat,szDocId);
	
	try
	{
		if(pApp->pConn->State !=adStateOpen)
		{
			*ppRst=pRst.Detach ();
			return FALSE;
		}
		pRstFile=pApp->pConn->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
		TRACE("pRstFile=%x\n",pRstFile);
		if((pRstFile)->GetRecordCount ()<1)
		{
			*ppRst=pRst.Detach ();
			return FALSE;
		}
		CString strFile=(char*)(_bstr_t)pRstFile->Fields->GetItem ("dtname")->Value ;
		strFile.TrimRight ();
		strSQL.Empty ();
		/*
		SELECT     dbo.tablecheck.nomenid, dbo.tablecheck.numpos, dbo.[catalog].barcode, dbo.[catalog].name, dbo.tablecheck.qty, dbo.tablecheck.price
		FROM         dbo.tablecheck INNER JOIN
                      dbo.[catalog] ON dbo.tablecheck.nomenid = dbo.[catalog].code
		 */
		strSQLPredicat="";
		strSQLPredicat.Format("select %s.numpos,catalog.code,catalog.name,%s.qty,%s.price from %s INNER JOIN catalog ON %s.nomenid = catalog.code ",strFile,strFile,strFile,strFile,strFile);
		strSQL.Format("%s where %s.docid='%s'",strSQLPredicat,strFile,szDocId);
		pRst=pApp->pConn->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
	

		*ppRst=pRst.Detach ();
		return TRUE;
	}
	catch(_com_error &e)
    {
		// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
        _variant_t vtConnect = pApp->pConn.GetInterfacePtr ();
		
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
			AfxMessageBox("Errors occured. in CUserThreadsDoc::LoadEntryDoc");
			break;
        }
		return FALSE;
    }
}
BOOL CUserThreadsDoc::LoadAllSalesOnDate(COleDateTime tmDate, _Recordset** pRs)
{
CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	_RecordsetPtr pRst=NULL;
	pRst.CreateInstance(__uuidof(Recordset));
	_variant_t varDate(tmDate);
	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	CString strDate=tmDate.Format ("%m/%d/%y");
	CString strSQLPredicat=
	"SELECT catalog.barcode, catalog.name, tablecheck.price, tablecheck.qty," 
     "tablecheck.price * tablecheck.qty AS Summa, genjournal.hdocid, "
	 "headcheck.checkdate, headcheck.checktime "
     "FROM tablecheck INNER JOIN catalog ON tablecheck.nomenid = catalog.code "
	 "INNER JOIN genjournal ON tablecheck.docid = genjournal.tdocid INNER JOIN "
     "headcheck ON genjournal.hdocid = headcheck.docid "
	 "WHERE headcheck.checkdate =";

	CString strSQL;
	strSQL.Format ("%s{%s} and genjournal.doctype='CHK' ORDER BY headcheck.checktime",strSQLPredicat,strDate);
	
	try
	{
		pRst=pApp->pConn->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
	
		TRACE("%d\n",(pRst)->GetRecordCount ());
		*pRs=pRst.Detach ();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE("%s\n",(LPCTSTR)e.Description ());
		AfxMessageBox(e.Description ());
		return FALSE;
		
	}
}