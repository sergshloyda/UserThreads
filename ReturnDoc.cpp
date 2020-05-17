// ReturnDoc.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ReturnDoc.h"
#include "CheckDoc.h"
#include "MainFrm.h"
#include "CashDoc.h"
#include"DocSetter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReturnDoc

IMPLEMENT_DYNCREATE(CReturnDoc, CDocument)

CReturnDoc::CReturnDoc()
{
		m_strBaseDocId="";
		m_strDocId="";
}

 BOOL CReturnDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_blLoadDocs=TRUE;

	return TRUE;
}

CReturnDoc::~CReturnDoc()
{
	m_vtArray.Clear ();
}


BEGIN_MESSAGE_MAP(CReturnDoc, CDocument)
	//{{AFX_MSG_MAP(CReturnDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReturnDoc diagnostics

#ifdef _DEBUG
void CReturnDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CReturnDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReturnDoc serialization

void CReturnDoc::Serialize(CArchive& ar)
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
// CReturnDoc commands

void CReturnDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	//AfxMessageBox("CReturnDoc::OnCloseDocument()\n");
	if(IsModified())
		OnSaveDocument(NULL);
	CDocument::OnCloseDocument();
}

BOOL CReturnDoc::LoadAllChecksOnDate( _Recordset** pRs)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	try
	{
		_RecordsetPtr pRstSale=NULL;
 		TESTHR(pRstSale.CreateInstance(__uuidof(Recordset)));
		_CommandPtr pcmdSales = NULL;
		_ParameterPtr pprmSales1 = NULL;
		_ParameterPtr pprmSales2 = NULL;
		TESTHR(pcmdSales.CreateInstance(__uuidof(Command)));
		pcmdSales->CommandText = "spSelectAllDocsFromPointPerDay";
		pcmdSales->CommandType = adCmdStoredProc;
		
		// Get parameter value and append parameter
		
		
		// Define String/variant.
		_bstr_t vtPointId=(_bstr_t)pMainDoc->m_strCashId.AllocSysString () ;
		
		pprmSales1 = pcmdSales->CreateParameter("@chPoint", adBSTR , adParamInput, vtPointId.length (), vtPointId);
		
		
		
		
		
		CString strCurTime;

		strCurTime.Format (_T("%d%.2d%.2d"),m_tmDateView.GetYear(),m_tmDateView.GetMonth(),m_tmDateView.GetDay());
		_bstr_t vtDate=(_bstr_t)strCurTime.AllocSysString ();
		pprmSales2 = pcmdSales->CreateParameter("@chDate", adBSTR , adParamInput, vtDate.length (), vtDate);
		pcmdSales->Parameters->Append(pprmSales1);
		pprmSales1->Value = vtPointId;
		pcmdSales->Parameters->Append(pprmSales2);
		pprmSales2->Value = vtDate;
		
		// Create Recordset by executing the command
		pcmdSales->ActiveConnection = pApp->GetDbContext()->getConnection().get() ;
		_variant_t recordsAffected = long(0);
		pRstSale = pcmdSales->Execute(&recordsAffected, 0, adOptionUnspecified);
		
		
		long lRowsCount=pRstSale->GetRecordCount ();
		if(lRowsCount<=0) 
		{
			
			return FALSE;
		}
		*pRs=pRstSale.Detach ();
		return TRUE;
	}
	catch(_com_error &ce)
	{	// Notify the user of errors if any.
		Register::ShowErrorMessage(ce);
		return FALSE;

	}
	
	

}

BOOL CReturnDoc::LoadEntryDoc(LPCTSTR szDocId, _Recordset **ppRst)
{
CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();

	try
	{
		_RecordsetPtr pRstEntryDoc=NULL;
 		TESTHR(pRstEntryDoc.CreateInstance(__uuidof(Recordset)));
		_CommandPtr pcmdEntryDoc = NULL;
		_ParameterPtr pprmDocNum = NULL;
		
		TESTHR(pcmdEntryDoc.CreateInstance(__uuidof(Command)));
		CComBSTR bstrSQL;
		PrepareEntryDocSQLStatement(szDocId,&bstrSQL);
		pcmdEntryDoc->CommandText = _bstr_t(bstrSQL);
		pcmdEntryDoc->CommandType = adCmdText;
		
		// Get parameter value and append parameter
		
		
		// Define String/variant.
	
		// Create Recordset by executing the command
		pcmdEntryDoc->ActiveConnection = pApp->GetDbContext()->getConnection().get() ;
		_variant_t recordsAffected = long(0);
		pRstEntryDoc = pcmdEntryDoc->Execute(&recordsAffected, 0, adOptionUnspecified);


	
		long lRowsCount=pRstEntryDoc->GetRecordCount ();
		if(lRowsCount<=0) 
		{
			
			_raise_error(E_FAIL,_bstr_t("lRowsCount<=0"),_bstr_t(" CReturnDoc::LoadEntryDoc"));
		}
		*ppRst=pRstEntryDoc.Detach ();
		return TRUE;
	}
	catch(_com_error &ce)
	{	// Notify the user of errors if any.
		Register::ShowErrorMessage(ce);
	
	
	return FALSE;
	}


}
BOOL CReturnDoc::LoadAllSalesOnDate( _Recordset** pRs)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	try
	{
		_RecordsetPtr pRstSale=NULL;
 		TESTHR(pRstSale.CreateInstance(__uuidof(Recordset)));
		_CommandPtr pcmdSales = NULL;
		_ParameterPtr pprmSales1 = NULL;
		_ParameterPtr pprmSales2 = NULL;
		TESTHR(pcmdSales.CreateInstance(__uuidof(Command)));
		pcmdSales->CommandText = "spselectAllSalesFromPointPerDay";
		pcmdSales->CommandType = adCmdStoredProc;
		
		// Get parameter value and append parameter
		
		
		// Define String/variant.
		_bstr_t vtPointId=(_bstr_t)pMainDoc->m_strCashId.AllocSysString () ;
		
		pprmSales1 = pcmdSales->CreateParameter("@chPoint", adBSTR , adParamInput, vtPointId.length (), vtPointId);
		
		
		
		
		
		CString strCurTime;
	
		strCurTime.Format (_T("%d%.2d%.2d"),m_tmDateView.GetYear(),m_tmDateView.GetMonth(),m_tmDateView.GetDay());
		_bstr_t vtDate=(_bstr_t)strCurTime.AllocSysString ();
		pprmSales2 = pcmdSales->CreateParameter("@chDate", adBSTR , adParamInput, vtDate.length (), vtDate);
		pcmdSales->Parameters->Append(pprmSales1);
		pprmSales1->Value = vtPointId;
		pcmdSales->Parameters->Append(pprmSales2);
		pprmSales2->Value = vtDate;
		
		// Create Recordset by executing the command
		pcmdSales->ActiveConnection = pApp->GetDbContext()->getConnection().get() ;
		_variant_t recordsAffected = long(0);
		pRstSale = pcmdSales->Execute(&recordsAffected, 0, adOptionUnspecified);
		
		
		long lRowsCount=pRstSale->GetRecordCount ();
		if(lRowsCount<=0) 
		{
			
			return FALSE;
		}
		*pRs=pRstSale.Detach ();
		return TRUE;
	}
	catch(_com_error &ce)
	{	// Notify the user of errors if any.
		Register::ShowErrorMessage(ce);
	
	return FALSE;
	}
}

BOOL CReturnDoc::LoadAllReturns(const COleDateTime& tmDateTime, _Recordset** pRs)
{
	//вывести все возвраты с момента(именно с момента, так как отчета по кассе может быть два за день) последнего отчета по кассе
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	_RecordsetPtr pRst=NULL;
	try{
		pRst.CreateInstance(__uuidof(Recordset));
		_variant_t varDateTime(tmDateTime);
		_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
		CString strDateTime=tmDateTime.Format(_T("{^%Y-%m-%d,%H:%M:%S}"));//,tmQuery.GetYear (),tmQuery.GetMonth (),tmQuery.GetDay (),tmQuery.GetHour (),tmQuery.GetMinute (),tmQuery.GetSecond ());
		TRACE1("%s\n",strDateTime);
		CString strSQL;
		strSQL.Format(_T("SELECT catalog.barcode as [STRIHKOD], catalog.name as [NAIMENOVANIE], dtreturn.qty as [KOLVO], dtreturn.price as [CENA],dtreturn.qty * dtreturn.price AS [SUMMA], dtreturn.docid as [NOMERDOCPRODAZHI],")
			_T("genjournal.doctime as [VREMADOCUMENTA] FROM dtreturn INNER JOIN  catalog ON dtreturn.code = catalog.code INNER JOIN genjournal ON dtreturn.iddoc = genjournal.tdocid")
			_T("  WHERE  (genjournal.doctime >%s) AND (genjournal.doctype = 'RTN') ORDER BY genjournal.doctime"),strDateTime);
		HRESULT	hr=pRst->Open((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->GetDbContext()->getConnection().get()),
			adOpenKeyset, adLockOptimistic, adCmdText);
		if (hr!=S_OK)
		{
			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
			return FALSE;
		}
		
		
		*pRs=pRst.Detach ();
		return TRUE;
	}
	catch(_com_error &e)
	{
		Register::ShowErrorMessage(e);
		return FALSE;
	}
	

}
BOOL CReturnDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if(!(m_vtArray.vt & VT_ARRAY))
	{
		MessageBoxHelper::ShowError(_T("vtArray not SAFEARRAY"));
		return FALSE;
	}
	SAFEARRAY* pSA;
	pSA=m_vtArray.parray;
	

	if(::SafeArrayGetDim (pSA)>0)
	{
		int nRes=AfxMessageBox(_T("Документ не пуст.Провести документ?"),
			MB_YESNO|MB_ICONEXCLAMATION);
		if (nRes==IDYES)
			return TransactReturn(&m_vtArray);
		
		else
			return FALSE;
	}
	return FALSE;
	
}
BOOL CReturnDoc::TransactReturn(VARIANT* vtArray )
{
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
	
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	
	COleDateTime tmCheckTime=COleDateTime::GetCurrentTime ();
	
	int nDayNumber=0;
	m_strDocId="0001";
/*		pMainDoc->CalculateDocId(pMainDoc->m_strPointId ,m_strDocId,&nDayNumber);*/
	CComBSTR bstrNumDoc=m_strDocId;
	int NumDoc=0;
	::VarI4FromStr (bstrNumDoc,LOCALE_SYSTEM_DEFAULT,LOCALE_NOUSEROVERRIDE,(long*)&NumDoc);
	
	
	USES_CONVERSION;
	
	try
	{
		
	/*	IDocOneCPtr pDoc;
		
		HRESULT hr=pDoc.CreateInstance (L"DocOneCHolder.DocOneC");
		
		//	=CComObject<IDraw>::CreateInstance (&pObj);
		
		if(FAILED(hr))
		{
			AfxMessageBox(_T("Объект не создан"));
			return FALSE;
		}
		pDoc->put_Kind (L"Возврат");
		COleDateTime now;
		now=COleDateTime::GetCurrentTime();
		pDoc->put_DateDoc ((DATE)now);
		CComPtr<IDispatch> pDisp;
		hr=pDoc->get_Head (&pDisp);
		IHeadPtr pHead=NULL;
		pDisp.QueryInterface (&pHead);
		_variant_t varPrefix;
		CString strPref=pMainDoc->m_strCashId  ;
		strPref=strPref.Left(3);
		varPrefix=(_bstr_t)strPref.AllocSysString ();
		pHead->SetAttribute (L"Prefix",varPrefix);
		pHead->SetAttribute (L"Author",_variant_t((_bstr_t)(pMainDoc->m_strUserNick)));
		pHead->SetAttribute (L"PointCode",_variant_t((_bstr_t)(pMainDoc->m_strPointName)));
		pHead->SetAttribute(L"NumDoc",_variant_t(10L));
		pHead->SetAttribute(L"Machine",_variant_t((_bstr_t)(pMainDoc->m_strMachineName)));
		pHead->SetAttribute(L"BaseDoc",_variant_t((_bstr_t)(m_strBaseDocId)));
		ITablePtr pTable=NULL;
		pTable=pDoc->CreateTable ();
		pTable->AddField (L"code");
		pTable->AddField (L"barcode");
		pTable->AddField (L"Qty");
		pTable->AddField (L"Price");
		pTable->AddField (L"Summa");
		*/

		
	CheckBuilder* pCheckBuilder=new CheckBuilder();
	CCheckContainer* pCheck=new CCheckContainer(pCheckBuilder);
	pCheck->Init(true);//возврат
	pCheck->SetNumber (_T("007"));
	pCheck->SetAuthor (pMainDoc->m_strUserNick);
	pCheck->SetDescription (_T("Very very important document; can't  lousing anybody data"));
	pCheck->SetPointCode(pMainDoc->m_strPointName);
	pCheck->SetPrefix(pMainDoc->m_strPrefix);
	pCheck->SetBaseDocNumber(m_strBaseDocId);
		//чешем по таблице 
		if(!((*vtArray).vt & VT_ARRAY))
		{
			MessageBoxHelper::ShowError(_T("vtArray not SAFEARRAY"));
			return FALSE;
		}
		SAFEARRAY* pSA;
		pSA=vtArray->parray;
		::SafeArrayLock(pSA);
		//sa.Attach (vtArray);
		long lNumRows;
		long lNumCols;
		::SafeArrayGetUBound(pSA,1, &lNumRows);
		::SafeArrayGetUBound(pSA,2, &lNumCols);
		
		//Display the elements in the SAFEARRAY.
		long index[2];
		
		
		//Determine upper bounds for both dimensions
		long r, c;
		::SafeArrayGetLBound(pSA,1, &r);
		::SafeArrayGetLBound(pSA,2, &c);
		
		for(;r <= lNumRows; r++ )
		{
		CComVariant val;
			TESTHR(pCheck->AddNewLine ());
			
			index[0]=r;
			index[1]=lNumCols;
			::SafeArrayGetElement(pSA,index,&val);//код товара
			TESTHR(pCheck->SetNomenclatureCode(_bstr_t(val.bstrVal)));
			VariantClear(&val);
			CComBSTR bstrBarCode;
			ULONG lBarCode=0;
			index[1]=0L;
			::SafeArrayGetElement(pSA,index,&val);//штрихкод товара
			switch(val.vt)
			{
			case VT_R8:
				//::MessageBox (NULL,"YES1","",MB_OK|MB_SETFOREGROUND);
				
				TESTHR(::VarBstrFromR8(val.dblVal,LOCALE_SYSTEM_DEFAULT,LOCALE_NOUSEROVERRIDE,&bstrBarCode));
			
				break;
			case VT_BSTR:
				//::MessageBox (NULL,"YES2","",MB_OK|MB_SETFOREGROUND);
				bstrBarCode=val.bstrVal ;
				break;
				
			}
		
			
			TESTHR(pCheck->SetBarCode(_bstr_t(bstrBarCode)));
			
			VariantClear(&val);
			index[1]=2L;
			::SafeArrayGetElement(pSA,index, &val);
			double dblQty=0.0 ;
			switch(val.vt )
			{
			case VT_BSTR:
				::VarR8FromStr (val.bstrVal,LOCALE_USER_DEFAULT,LOCALE_NOUSEROVERRIDE,&dblQty);
				break;
			case VT_R8:
				dblQty=val.dblVal ;
				break;
			}
			
			
			if(!(val.vt&VT_BSTR)||(val.vt&VT_R8)||(dblQty==0.0))
			{
				MessageBoxHelper::ShowError(_T("ДокЧек.Количество=Kol"));
				return E_FAIL;
			}
			
			TESTHR(pCheck->SetQty((int)dblQty));
			//	ДокЧек.Цена=140;
			VariantClear(&val);
			index[1]=3L;
			::SafeArrayGetElement(pSA,index, &val);
			double dblPrice=0.0;
			TCHAR buff[255];
			CComBSTR bstrPrice=V_BSTR(&val);
			
			switch(val.vt )
			{
			case VT_BSTR:
				//::MessageBox(NULL,W2A(bstrPrice ),"",MB_OK);
				wsprintf(buff,_T("%d"),bstrPrice.Length ());
				//	::MessageBox(NULL,buff,"",MB_OK);
				TESTHR(::VarR8FromStr (bstrPrice,LOCALE_USER_DEFAULT,LOCALE_NOUSEROVERRIDE,&dblPrice));
				ZeroMemory(buff,255);
				wsprintf(buff,_T("%.2f"),dblPrice);
				//::MessageBox(NULL,buff,"",MB_OK);
				break;
			case VT_R8:
				dblPrice=val.dblVal ;
				break;
			}
		TESTHR(pCheck->SetPrice(dblPrice));
		}
		
	
		
		::SafeArrayUnlock(pSA);
	
		
		
		
		
		
		BSTR bstrData;
		pCheck->SaveToString(&bstrData);
		delete pCheck;
		pMainDoc->SendDataInQueue(bstrData);
	
	
		
	
			//В этом месте уже известен номер проведенного документа
			m_strDocId=pMainDoc->m_strCurDocId ;
//			::VariantClear (vtArray);
			UpdateAllViews(NULL,UpdateSelectGoods);
		
	
	
		return TRUE;
}
catch(_com_error &e)
{
	Register::ShowErrorMessage(e);
	
	
	return FALSE;
}

}

BOOL CReturnDoc::SaveHeadReturn(COleDateTime &tmDocTime, LPCTSTR szDocId)
{

	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CDocInfo* pDocInfo=new CDocInfo;
//	pMainDoc->GetInfoDoc (m_strBaseCheckId,pDocInfo);

	COleDateTime tmCheckDate;
	CCheckDoc* pCheckDoc=CUserThreadsApp::GetDocument<CCheckDoc> ();;
	TCHAR* strContrId=new TCHAR[15];
	TCHAR* strSalerId=new TCHAR[15];
	TCHAR* strPointId=new TCHAR[15];
	pCheckDoc->GetCheckInfo (m_strBaseCheckId,strPointId,strSalerId,
							strContrId,sizeof(strContrId),tmCheckDate);
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	try
	{
		pRst->Open (_bstr_t("dhreturn"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("iddoc")->Value =_bstr_t(szDocId);
		pRst->Fields->GetItem("docsale")->Value =_bstr_t(pDocInfo->szBaseDoc );
		pRst->Fields->GetItem("contrid")->Value =_bstr_t(strContrId);
		pRst->Fields->GetItem("pointid")->Value =_bstr_t(strPointId);
		pRst->Fields->GetItem("summa")->Value =(double)(m_flCurSumma);
		pRst->Fields->GetItem("descript")->Value =_bstr_t("Здесь могла быть ваша реклама");
		TESTHR(pRst->Update ());
		pRst->Close();
		if(pDocInfo!=NULL)delete pDocInfo;
		delete strContrId;
		delete strSalerId;
		delete strPointId;
		return TRUE;
		
	}
	catch(_com_error &e)
	{
		TRACE1("%s\n",(LPCTSTR)e.Description ());
		MessageBoxHelper::ShowError(e.Description ());
		if(pDocInfo!=NULL)delete pDocInfo;
		delete strContrId;
		delete strSalerId;
		delete strPointId;
		return FALSE;
		
	}
}

BOOL CReturnDoc::SaveTableReturn(_variant_t &vt, LPCTSTR szDocId)
{
	ASSERT(vt.vt ==(VT_ARRAY | VT_VARIANT));
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	
	_RecordsetPtr pRst;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	//_variant_t v;
	try
	{
		ASSERT(pApp->pConn->State ==adStateOpen);
		pRst->Open (_bstr_t("dtreturn"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		COleSafeArray sa(vt);
		long lNumRows;
		long lNumCols;
		sa.GetUBound(1, &lNumRows);
		sa.GetUBound(2, &lNumCols);
		
		//Display the elements in the SAFEARRAY.
		long index[2];
		_variant_t val;
		m_flCurSumma=0.0;
		
		//Determine upper bounds for both dimensions
		long r, c;
		sa.GetLBound(1, &r);
		sa.GetLBound(2, &c);
		
		for(;r <= lNumRows; r++ )
		{
			TESTHR(pRst->AddNew ());
			pRst->Fields->GetItem("iddoc")->Value =_bstr_t(szDocId);
			long numpos=r+1;
			_variant_t varNumPos(numpos);
			pRst->Fields->GetItem("lineno")->Value =varNumPos;

			index[0]=r;
			index[1]=lNumCols-1;
			sa.GetElement(index, &val);
			pRst->Fields->GetItem("code")->Value=val ;
			CString strCode=(LPCTSTR)(_bstr_t)val;
			strCode.TrimRight ();
			index[0]=r;
			index[1]=lNumCols;
			sa.GetElement(index, &val);
			pRst->Fields->GetItem("docid")->Value=val ;
			CString strCheckId=(LPCTSTR)(_bstr_t)val;
			strCheckId.TrimRight ();
			if(!CheckReturnRow(strCode,strCheckId))throw("Вы уже делали возврат этого товара из чека");
			double lQty=0L;
			index[1]=4L;
			sa.GetElement(index, &val);
			lQty=val.dblVal ;
			pRst->Fields->GetItem("qty")->Value =val;
			
			double dblPrice=0.0;
			index[1]=2L;
			sa.GetElement(index, &val);
			dblPrice=val.dblVal;
			pRst->Fields->GetItem("price")->Value =val;	
			double dblSumma=lQty*dblPrice;
			pRst->Fields->GetItem ("summa")->Value =dblSumma;

			m_flCurSumma+=(float)(dblSumma);
			
		}
		TESTHR(pRst->UpdateBatch (adAffectAll));
		pRst->Close();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE1("%s\n",(LPCTSTR)e.Description ());
		MessageBoxHelper::ShowError(e.Description ());
		return FALSE;
	}
	catch(LPCTSTR strMsg)
	{
	
		AfxMessageBox(strMsg,MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	
}



BOOL CReturnDoc::EditSales(COleDateTime& tmDocTime,LPCTSTR szDocId)
{
	/*	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
		CRuntimeClass* pNewDocClass;
		pNewDocClass = RUNTIME_CLASS(CCheckDoc);
		CCheckDoc* pDoc=static_cast <CCheckDoc*>(pNewDocClass->CreateObject ());
		CCashDoc* pCashDoc=CUserThreadsApp::GetDocument<CCashDoc> ();
		pDoc->OnNewDocument ();
		if(!pDoc->DeleteCheck (szDocId))
		{
		
			return FALSE;
		}
		
		CReturnView* pView=CReturnView::GetView ();
		if(pView->m_wndGridGoods.GetRows()>1)
		{
			if(!pDoc->SaveHeadCheck (tmDocTime,szDocId))
			{	
			
				return FALSE;
			}
			_variant_t vtArray;
			vtArray=pView->m_wndGridGoods.GetGridArray ();
			//ASSERT(pGrid!=NULL);

			if(!pDoc->SaveTableCheck(&vtArray,szDocId))//we must get m_flCurSumma
			{	
				
				return FALSE;
			}
			pMainDoc->AddNewDocInJournal (tmDocTime,_T("CHK") ,szDocId,pDoc->m_flCurSumma );
			pCashDoc->CashDoActionIncome (szDocId,pDoc->m_flCurSumma );
			
			pView->m_wndGridSelGoods.SetRows(1);
			pView->OnUpdate  (pView,(LPARAM)pView->m_blLoadDocs );
			
		
				return TRUE;
		
		
		}
		else
		{
			pView->OnUpdate  (pView,(LPARAM)pView->m_blLoadDocs );
			return TRUE;
		}

		

*/
		
	
		return FALSE;
}

BOOL CReturnDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return TRUE;
}



CReturnDoc* CReturnDoc::GetReturnDoc()
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	POSITION posTempl=pApp->m_pDocManager->GetFirstDocTemplatePosition ();
	//we have the 1 DocTemplate
	CDocTemplate* pTempl=pApp->m_pDocManager->GetNextDocTemplate (posTempl);
	POSITION posDoc=pTempl->GetFirstDocPosition ();
	CDocument *pDoc=NULL;
	while(posDoc)
	{
		pDoc=pTempl->GetNextDoc (posDoc);
		if(pDoc->IsKindOf (RUNTIME_CLASS(CReturnDoc)))
			break;
	}
	return (CReturnDoc*)pDoc;
}


BOOL CReturnDoc::CheckReturnRow(LPCTSTR strCode, LPCTSTR strCheckId)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	_RecordsetPtr pRst=NULL;
	pRst.CreateInstance(__uuidof(Recordset));
	
	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	
	CString strSQL;
	strSQL.Format (_T("SELECT qty FROM dtreturn  WHERE  code='%s' AND docid='%s'"),strCode,strCheckId);
	

	
	try
	{
		pRst->Open (_bstr_t(strSQL),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdText);
		CString errMessage;
		errMessage.Format (_T("Вы не можете сделать возврат одного и того же товара из чека № %s дважды"),strCheckId);
	long lRecCount=0;
		if(pRst!=NULL)
		{
		lRecCount=pRst->GetRecordCount ();
		pRst->Close();
		}
		if(lRecCount>0)return FALSE;
		
		
		return TRUE;
	}
	catch(_com_error &e)
	{	// Notify the user of errors if any.
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
			MessageBoxHelper::ShowError(_T("Errors occured. in CReturnDoc::LoadAllSalesOnDate"));
			break;
        }
		return FALSE;
	}
}

BOOL CReturnDoc::LoadReturnDocIn1C(_variant_t &vtArray)
{
	CMainDocument *pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp ();
	HRESULT hr=S_OK;
	if(pMainDoc->m_blKKMOnLine )
	{
		//if(!pMainDoc->App1C.SaveCheckIn1C (pMainDoc->m_strPointName ,pMainDoc->m_strUserNick   ,NumDoc,vtArray))pApp->pConnLocal->RollbackTrans ();
//		HRESULT hr=pApp->m_pDataProvider->LoadReturnDoc(&vtArray,&vtArray);
		if(hr==S_OK) return TRUE;

	}
	return FALSE;
}

void CReturnDoc::SetDate(COleDateTime *pNewDate)
{
	m_tmDateView=*pNewDate;

	OutputDebugString(_T("CReturnDoc::SetDate"));
	UpdateAllViews(NULL,(m_blLoadDocs?UpdateDocs:UpdateGoods));
}



void CReturnDoc::PrepareEntryDocSQLStatement(LPCTSTR szDocId ,BSTR* bstrSQL)
{
	CString tmpSQL;
	const long lChkDocDef=3046L;
	const long lZRepDocDef=1582L;//3114
	_variant_t varDocDef;
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	
	_RecordsetPtr pRstDocDef=NULL;
	TESTHR(pRstDocDef.CreateInstance(__uuidof(Recordset)));
	_CommandPtr pcmdDocDef = NULL;
	
	
	TESTHR(pcmdDocDef.CreateInstance(__uuidof(Command)));
	CString strSQLDocDef;
	strSQLDocDef.Format("SELECT dbo._1SJOURN.IDDOCDEF as [DocDef]	FROM  dbo._1SJOURN  WHERE  dbo._1SJOURN.DOCNO='%s' AND dbo._1SJOURN.ISMARK=0",szDocId);
	pcmdDocDef->CommandText = strSQLDocDef.AllocSysString();
	pcmdDocDef->CommandType = adCmdText;
	
	// Get parameter value and append parameter
	// Create Recordset by executing the command
	pcmdDocDef->ActiveConnection = pApp->GetDbContext()->getConnection().get() ;
	_variant_t recordsAffected = long(0);
	pRstDocDef = pcmdDocDef->Execute(&recordsAffected, 0, adOptionUnspecified);
	long lRowsCount=pRstDocDef->GetRecordCount ();
	if(lRowsCount<=0) 
	{
		
		_raise_error(E_FAIL,_bstr_t("lRowsCount<=0"),_bstr_t(" CReturnDoc::PrepareEntryDocSQLStatement"));
	}
	pRstDocDef->MoveFirst();
	varDocDef=pRstDocDef->Fields->Item["DocDef"]->Value;
	if(varDocDef.vt!=VT_I4)
		_raise_error(E_FAIL,_bstr_t("varDocDef.vt!=VT_I4"),_bstr_t(" CReturnDoc::PrepareEntryDocSQLStatement"));
	long lDocDef=varDocDef.lVal;
	
	if(lDocDef<=0)
		_raise_error(E_FAIL,_bstr_t("lDocDef<=0"),_bstr_t(" CReturnDoc::PrepareEntryDocSQLStatement"));
	CString strWhereCause;
	strWhereCause.Format("WHERE (Жур.DOCNO='%s' AND Жур.ISMARK=0)",szDocId);
	switch(lDocDef)
	{
		
	case lZRepDocDef:
		tmpSQL="SELECT СпрТовар.CODE  AS Код,СпрТовар.DESCR AS Наименование, SUM(ДокС.SP3103) AS Количество,ДокС.SP3106 AS Цена,SUM(ДокС.SP3103)*ДокС.SP3106 AS Сумма , ДокС.LINENO_ as LINE FROM  dbo.DT3114 ДокС INNER JOIN  dbo.DH3114 Док ON Док.IDDOC = ДокС.IDDOC INNER JOIN  dbo._1SJOURN Жур ON Жур.IDDOC = ДокС.IDDOC "
			"INNER JOIN  dbo.SC84 СпрТовар ON СпрТовар.ID = ДокС.SP3102 ";
		tmpSQL+=strWhereCause;
		tmpSQL+="GROUP BY СпрТовар.CODE , "
			"ДокС.LINENO_, "
			"СпрТовар.DESCR, "
			"ДокС.SP3106 "
			"ORDER BY СпрТовар.DESCR";
		break;
	case lChkDocDef:
		tmpSQL="SELECT ДокС.SP3038  AS ШтрихКод, СпрТовар.DESCR AS Наименование, SUM(ДокС.SP3040) AS Количество, "
			"ДокС.SP3043 AS Цена,SUM(ДокС.SP3040)*ДокС.SP3043 AS Сумма,Жур.DOCNO AS [Номер Чека], dbo.sp_gettime(SUBSTRING(Жур.DATE_TIME_IDDOC, 9, 6)) AS [Время Чека],СпрТовар.CODE FROM " 
			"dbo.DT3046 as  ДокС INNER JOIN  dbo.DH3046 Док ON Док.IDDOC = ДокС.IDDOC INNER JOIN  dbo._1SJOURN Жур ON Жур.IDDOC = ДокС.IDDOC " 
			"INNER JOIN  dbo.SC84 СпрТовар ON СпрТовар.ID = ДокС.SP3039 ";
		tmpSQL+=strWhereCause;
		tmpSQL+="GROUP BY ДокС.sp3038, "
			"СпрТовар.DESCR,"
			"ДокС.sp3043,"
			"dbo.sp_gettime(SUBSTRING(Жур.DATE_TIME_IDDOC, 9, 6)),"
			"Жур.DOCNO ,"
			"СпрТовар.CODE";
		break;
		
	}
	*bstrSQL=tmpSQL.AllocSysString();
}
