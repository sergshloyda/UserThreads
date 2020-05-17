// ZReportDoc.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "ZReportDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZReportDoc

IMPLEMENT_DYNCREATE(CZReportDoc, CDocument)
long CZReportDoc::m_lRowsCount =0L;
CZReportDoc::CZReportDoc()
{
	m_flCurSummReturn =0.0;
	m_flCurSummSale =0.0;
	m_strDocId=_T("");
}

BOOL CZReportDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
/*	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	m_tmDocTime=COleDateTime::GetCurrentTime ();
	if(pApp->m_pDataProvider==NULL)
	{
		CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
		int nDayNumber=0;
		pMainDoc->CalculateDocId(pMainDoc->m_strPointId ,m_strDocId,&nDayNumber);
		
		
		pMainDoc->UpdateNumerator (m_tmDocTime);
		
		_RecordsetPtr pRst=NULL;
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		try
		{
			
			
			CString strSQL;
			strSQL=_T("Select doctime from genjournal where doctype='ZRT' order by doctime");
			
			
			HRESULT hr=pRst->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
				adOpenKeyset, adLockOptimistic, adCmdText);
			if (hr!=S_OK)
			{
				AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
				return FALSE;
			}
			
			if(pRst->GetRecordCount ()>0)
			{ 
				
				
				
				TESTHR(pRst->MoveLast());
				_variant_t vtLastZReport=pRst->Fields->GetItem("doctime")->Value ;
				m_tmLastZReportTime=(COleDateTime)vtLastZReport;
			}
			
			TESTHR(pRst->Close());
			
			TESTHR(m_pRstZReport.CreateInstance(__uuidof(Recordset)));
			strSQL.Empty ();
			strSQL="SELECT catalog.barcode as [STRIHKOD], catalog.name as [NAIMENOVANIE], tablecheck.qty as [KOLVO], tablecheck.price as [CENA],tablecheck.qty * tablecheck.price AS [SUMMA], genjournal.tdocid as [NOMERDOCUMENTA],"
				"genjournal.doctime as [VREMADOCUMENTA] FROM tablecheck INNER JOIN  catalog ON tablecheck.nomenid = catalog.code INNER JOIN genjournal ON tablecheck.docid = genjournal.tdocid"
				" INNER JOIN racash ON genjournal.hdocid = racash.docid WHERE  (genjournal.isloaded = 0) AND (genjournal.doctype = 'CHK') ORDER BY genjournal.doctime";
			hr=m_pRstZReport->Open((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
				adOpenKeyset, adLockOptimistic, adCmdText);
			if (hr!=S_OK)
			{
				AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
				return FALSE;
			}
			
			TRACE1("Record count=%d\n",m_pRstZReport->GetRecordCount ());
			
			
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
			return FALSE;
		}
	}
	*/
	return TRUE;
}

CZReportDoc::~CZReportDoc()
{
}


BEGIN_MESSAGE_MAP(CZReportDoc, CDocument)
	//{{AFX_MSG_MAP(CZReportDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZReportDoc diagnostics

#ifdef _DEBUG
void CZReportDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CZReportDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZReportDoc serialization

void CZReportDoc::Serialize(CArchive& ar)
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





















BOOL CZReportDoc::TransactZReport(_variant_t &vtArray)
{

	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	_RecordsetPtr pRstSale=NULL;
	TESTHR(pRstSale.CreateInstance(__uuidof(Recordset)));
	try
	{
		
		
		pRstSale=GetZReportRecordset ();
		long lRecCount=pRstSale->GetRecordCount (); 
		vtArray=pRstSale->GetRows (lRecCount);
		if(!SaveHeadZReport()) return FALSE;
		double dblSumma=0;	
		if(!SaveTableZReport(pRstSale,&dblSumma)) return FALSE;	
	//Выставит всем чекам базов документ "отчет по кассе"

	//	if(!pMainDoc->AddNewDocInJournal (COleDateTime::GetCurrentTime (),_T("ZRT"),m_strDocId,(float)dblSumma))return FALSE;
		//if(!SetCheckMarked(pRstSale))return FALSE;
		TESTHR(pRstSale->Close());
	
	

	}
	catch (_com_error &e)
	{
		// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
		_variant_t vtConnect = pRstSale->GetActiveConnection();
		
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
		return FALSE;
	}


	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CZReportDoc commands

double CZReportDoc::CalculateDaySales()
{
	//скорректировать нужно выводить продажи с момента последнего отчета по касе
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
/*	if(pApp->m_pDataProvider ==NULL)
	{
		COleDateTime tmCurTime=COleDateTime::GetCurrentTime ();
		CString strDate=tmCurTime.Format (_T("%m/%d/%y"));
		double dSumma=0;
		_RecordsetPtr pRstSale=NULL;
		TESTHR(pRstSale.CreateInstance(__uuidof(Recordset)));
		try
		{
			
			
			CString strSQL;
			strSQL.Format(_T("Select racash.docid,racash.value as val,genjournal.docdate")
				_T(" from racash inner join genjournal on racash.docid=genjournal.hdocid where (genjournal.doctype='CHK' and genjournal.isloaded=0 and racash.debcredit=0)"),strDate);
			
			
			
			HRESULT hr=pRstSale->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
				adOpenKeyset, adLockBatchOptimistic, adCmdText);
			if (hr!=S_OK)
			{
				AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
				return FALSE;
			}
			
			if(pRstSale->GetRecordCount ()>0)
			{ 
				
				
				
				TESTHR(pRstSale->MoveFirst());
				while(!pRstSale->EndOfFile )
				{	
					
					double dVal=pRstSale->Fields->GetItem ("val")->Value;	
					
					dSumma+=dVal;
					TESTHR(pRstSale->MoveNext());
					
				}
			}
			
			TESTHR(pRstSale->Close());
			m_flCurSummSale=(float)dSumma;
			return dSumma;
			
		}
		catch (_com_error &e)
		{
			// Notify the user of errors if any.
			// Pass a connection pointer accessed from the Recordset.
			_variant_t vtConnect = pRstSale->GetActiveConnection();
			
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
			return 0.0;
		}
	}
	else*/
		return 0.0;

}

//DEL float CZReportDoc::GetSalaryBalance(LPCTSTR strEmplId, COleDateTime tmDate)
//DEL {
//DEL 	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
//DEL 	COleDateTime tmCurTime=COleDateTime::GetCurrentTime ();
//DEL 	CString strCurDate=tmCurTime.Format ("%m/%d/%y");
//DEL 	CString strDate=tmDate.Format("%m/%d/%y");
//DEL 	float flBalance=0.0;
//DEL 	_RecordsetPtr pRstEndPointDate=NULL;
//DEL 	TESTHR(pRstEndPointDate.CreateInstance(__uuidof(Recordset)));
//DEL 	try
//DEL 	{
//DEL 	//находим точку последнего вычисленного значения, далее будем делать вычисления
//DEL 	//позже этой точки (точка актуальности итогов)
//DEL 		
//DEL 		CString strSQL;
//DEL 		strSQL.Format("Select value , period "
//DEL 			"from rgsalary  where rgsalary.period < {%s} and rgsalary.emplid='%s' order by rgsalary.period",strDate,strEmplId);
//DEL 		HRESULT hr=pRstEndPointDate->Open (strSQL.AllocSysString (),_variant_t((IDispatch*)pApp->pConn),
//DEL 			adOpenKeyset, adLockBatchOptimistic, adCmdText);
//DEL 		if (hr!=S_OK)
//DEL 		{
//DEL 			AfxMessageBox("Error in Open Recordset",MB_OK|MB_ICONSTOP);
//DEL 			return 0.0;
//DEL 		}
//DEL 		
//DEL 		if(pRstEndPointDate->GetRecordCount ()<=0)
//DEL 			return 0.0; 
//DEL 		TESTHR(pRstEndPointDate->MoveLast());
//DEL 		COleDateTime tmLastPoint=(COleDateTime)pRstEndPointDate->Fields ->GetItem("period")->Value;	
//DEL 		CString strLastPointDate=tmLastPoint.Format ("%m/%d/%y");
//DEL 		double dblLastPointValue=pRstEndPointDate->Fields ->GetItem("value")->Value;
//DEL 		TESTHR(pRstEndPointDate->Close());
//DEL 
//DEL 		_RecordsetPtr pRstDebet=NULL;
//DEL 		TESTHR(pRstDebet.CreateInstance(__uuidof(Recordset)));
//DEL 		strSQL.Empty ();
//DEL 		strSQL.Format("SELECT rasalary.summa as val from rasalary inner join genjournal on rasalary.docid=genjournal.hdocid "
//DEL 					"where rasalary.debcredit=0 and rasalary.emplid='%s' and (genjournal.doctime between {%s} and {%s})",strEmplId,strLastPointDate,strDate);
//DEL 
//DEL 		hr=pRstDebet->Open(strSQL.AllocSysString (),_variant_t((IDispatch*)pApp->pConn ),adOpenKeyset, adLockBatchOptimistic, adCmdText);
//DEL 		
//DEL 		TESTHR(hr);
//DEL 		if(pRstDebet->GetRecordCount ()<=0) return 0.0;
//DEL 		pRstDebet->MoveFirst ();
//DEL 		double dblDebet=0.0;
//DEL 		while(pRstDebet->EndOfFile !=VARIANT_TRUE)
//DEL 		{	
//DEL 			
//DEL 			double dVal=pRstDebet->Fields->GetItem ("val")->Value;	
//DEL 			
//DEL 			dblDebet+=dVal;
//DEL 			TESTHR(pRstDebet->MoveNext());
//DEL 			
//DEL 		}
//DEL 		TESTHR(pRstDebet->Close());
//DEL 
//DEL 		_RecordsetPtr pRstCredit=NULL;
//DEL 		TESTHR(pRstCredit.CreateInstance(__uuidof(Recordset)));
//DEL 		strSQL.Empty ();
//DEL 		strSQL.Format("SELECT rasalary.summa as val from rasalary inner join genjournal on rasalary.docid=genjournal.hdocid "
//DEL 					"where rasalary.debcredit=1 and rasalary.emplid='%s' and (genjournal.doctime between {%s} and {%s})",strEmplId,strLastPointDate,strDate);
//DEL 
//DEL 		hr=pRstCredit->Open(strSQL.AllocSysString (),_variant_t((IDispatch*)pApp->pConn ),adOpenKeyset, adLockBatchOptimistic, adCmdText);
//DEL 		
//DEL 		TESTHR(hr);
//DEL 		if(pRstCredit->GetRecordCount ()<=0) return 0.0;
//DEL 		pRstCredit->MoveFirst ();
//DEL 		double dblCredit=0.0;
//DEL 		while(pRstCredit->EndOfFile !=VARIANT_TRUE)
//DEL 		{	
//DEL 			
//DEL 			double dVal=pRstCredit->Fields->GetItem ("val")->Value;	
//DEL 			
//DEL 			dblCredit+=dVal;
//DEL 			TESTHR(pRstCredit->MoveNext());
//DEL 			
//DEL 		}
//DEL 		TESTHR(pRstCredit->Close());
//DEL 		flBalance=(float)dblLastPointValue+(float)dblDebet-(float)dblCredit;
//DEL 
//DEL 		return flBalance;
//DEL 		
//DEL 	}
//DEL 	catch (_com_error &e)
//DEL 	{
//DEL 		// Notify the user of errors if any.
//DEL 		// Pass a connection pointer accessed from the Recordset.
//DEL 		_variant_t vtConnect = pRstEndPointDate->GetActiveConnection();
//DEL 		
//DEL 		// GetActiveConnection returns connect string if connection
//DEL 		// is not open, else returns Connection object.
//DEL 		switch(vtConnect.vt)
//DEL 		{
//DEL 		case VT_BSTR:
//DEL 			PrintComError(e);
//DEL 			break;
//DEL 		case VT_DISPATCH:
//DEL 			PrintProviderError(vtConnect);
//DEL 			break;
//DEL 		default:
//DEL 		AfxMessageBox("Errors occured.CZReportDoc::GetSalaryBalance");
//DEL 			break;
//DEL 		}
//DEL 	}
//DEL return 0.0;
//DEL }

BOOL CZReportDoc::SaveHeadZReport()
{
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();

	COleDateTime tmDocTime=COleDateTime::GetCurrentTime ();

	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	try
	{
		HRESULT hr=pRst->Open (_bstr_t("headzreport"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);
		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("salerid")->Value =(_bstr_t)(pMainDoc->m_strUserId );
		pRst->Fields->GetItem("pointid")->Value =(_bstr_t)(pMainDoc->m_strPointId ) ;
		pRst->Fields->GetItem("docid")->Value =_bstr_t(m_strDocId);
		pRst->Fields->GetItem("customerid")->Value =(_bstr_t)(pMainDoc->m_strContragId );;
		pRst->Fields->GetItem("docdate")->Value =(DATE)(tmDocTime);
		pRst->Fields->GetItem("doctime")->Value=(_bstr_t)(tmDocTime.Format (_T("%H:%M:%S")));
		pRst->Fields->GetItem("descript")->Value =(_bstr_t)("txtDescription");
		TESTHR(pRst->Update ());
		pRst->Close();
		return TRUE;
	}
	catch(_com_error &e)
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
		MessageBoxHelper::ShowError(_T("Errors occured.CZReportDoc::SaveHeadZReport"));
			break;
		}
		
		return FALSE;
	}
}

BOOL CZReportDoc::SaveTableZReport(LPUNKNOWN pRst,double* pSumma)
{
	_RecordsetPtr pRstSale=(_RecordsetPtr)pRst;
	
	TESTHR(pRstSale->MoveFirst());
	
//	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	
	COleDateTime tmDocTime=COleDateTime::GetCurrentTime ();
	
	_RecordsetPtr pRstTable=NULL;
	TESTHR(pRstTable.CreateInstance (__uuidof(Recordset)));
	try
	{
		HRESULT hr=pRstTable->Open (_bstr_t("tablezreport"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);
		double dS=0.0;
		while(!pRstSale->EndOfFile )
		{
			
			TESTHR(pRstTable->AddNew ());
			
			pRstTable->Fields->GetItem("tdocid")->Value =(_bstr_t)(m_strDocId );
			CString strDocId=(LPCTSTR)(_bstr_t)pRstSale->Fields->GetItem("docid")->Value;
			strDocId.TrimRight();
			SetCheckMarked(strDocId);
			pRstTable->Fields->GetItem("docid")->Value =(_bstr_t)strDocId;
			_bstr_t bstrNomId=pRstSale->Fields->GetItem("code")->Value;
			CString strNomId=(LPCTSTR)bstrNomId;
			strNomId.TrimRight ();
			pRstTable->Fields->GetItem("nomenid")->Value =(_bstr_t)strNomId;
			
			pRstTable->Fields->GetItem("qty")->Value =pRstSale->Fields->GetItem("qty")->Value;
			pRstTable->Fields->GetItem("price")->Value =pRstSale->Fields->GetItem("price")->Value;
			TESTHR(pRstTable->Update ());
			double dVal=((double)(pRstSale->Fields->GetItem ("price")->Value) * (long)(pRstSale->Fields->GetItem ("qty")->Value));	
			dS+=dVal;
			TESTHR(pRstSale->MoveNext());
		}
		*pSumma=dS;
		pRstTable->Close();
		
	}
	catch(_com_error &e)
	{	// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
		_variant_t vtConnect = pRstTable->GetActiveConnection();
		
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
			MessageBoxHelper::ShowError(_T("Errors occured.CZReportDoc::SaveTableZReport"));
			break;
		}
		return FALSE;
	}
	

	return TRUE;
}

BOOL CZReportDoc::SetCheckMarked(LPCTSTR strDocId)
{
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CString strExecute,strExec2;
	strExecute.Format (_T("Update genjournal set isloaded=1 where doctype='CHK'and hdocid='%s'"),strDocId);
	strExec2.Format(_T("Update genjournal set isloaded=1,basedoc='%s' where doctype='CHK'and hdocid='%s'"),m_strDocId,strDocId); 
	try
	{

	//pApp->pConn->Execute (strExecute.AllocSysString (), NULL, adExecuteNoRecords);
	pApp->pConn->Execute ((_bstr_t)strExec2, NULL, adExecuteNoRecords);
		
	}
	catch(_com_error &e)
	{	// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
		_variant_t vtConnect = pApp->pConn ;
		
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
			MessageBoxHelper::ShowError(_T("Errors occured.CZReportDoc::SetCheckMarked"));
			break;
		}
		return FALSE;
	}
	

	return TRUE;

}

void CZReportDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	if((m_pRstZReport!=NULL)&&
	(m_pRstZReport->State ==adStateOpen))
	TESTHR(m_pRstZReport->Close ());
	m_pRstZReport=NULL;
	CDocument::OnCloseDocument();
}

_RecordsetPtr CZReportDoc::GetZReportRecordset()
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
		COleDateTime Now=COleDateTime::GetCurrentTime ();
		strCurTime.Format (_T("%d%.2d%.2d"),Now.GetYear(),Now.GetMonth(),Now.GetDay());
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
		
		
		
		/*	_RecordsetPtr pRstCashID=NULL;
		CString strSQLCashID;
		strSQLCashID.Format ("SELECT СпрКассы.ID as Касса FROM sc1809 as СпрКассы WHERE СпрКассы.CODE='%s'",pMainDoc->m_strCashId );
		TESTHR(pRstCashID.CreateInstance (__uuidof(Recordset)));
		try
		{
		TESTHR(pRstCashID->Open ((_bstr_t)strSQLCashID,_variant_t((IDispatch*)pApp->pConn),
		adOpenKeyset, adLockBatchOptimistic, adCmdText));
		if(pRstCashID->GetRecordCount ()<=0)
		{
		AfxMessageBox("Нет ID кассы");
		return NULL;
		}
		
		  pRstCashID->MoveFirst ();
		  CString strCashID=(LPCTSTR)(_bstr_t)pRstCashID->Fields->GetItem ("Касса")->Value;
		  m_strDocId=strCashID;
		  pRstCashID->Close ();
		  pRstCashID.Release ();
		  _RecordsetPtr pRstSale=NULL;
		  TESTHR(pRstSale.CreateInstance(__uuidof(Recordset)));
		  CString strCurTimeBeg;
		  COleDateTime Now=COleDateTime::GetCurrentTime ();
		  strCurTimeBeg.Format ("%d%.2d%.2d",Now.GetYear(),Now.GetMonth(),Now.GetDay());
		  CString strCurTimeEnd=strCurTimeBeg+'Z';
		  
			
			  
				CString strSQL;
				strSQL.Format("SELECT ДокС.SP3038 AS ШтрихКод, СпрТовар.DESCR AS Наименование, ДокС.SP3040 AS Количество, ДокС.SP3043 AS Цена,ДокС.SP3044 AS Сумма,Жур.DOCNO AS [Номер Чека], dbo.sp_gettime(SUBSTRING(Жур.DATE_TIME_IDDOC, 9, 9)) AS [Время Чека] FROM  dbo.DT3046 ДокС INNER JOIN  dbo.DH3046 Док ON Док.IDDOC = ДокС.IDDOC AND Док.SP3361 = '%s' INNER JOIN  dbo._1SJOURN Жур ON Жур.IDDOC = ДокС.IDDOC INNER JOIN  dbo.SC84 СпрТовар ON СпрТовар.ID = ДокС.SP3039 WHERE (Жур.DATE_TIME_IDDOC BETWEEN '%s' AND '%s')",strCashID,strCurTimeBeg,strCurTimeEnd);
				
				  TRACE(strSQL);
				  
					HRESULT hr=pRstSale->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
					adOpenKeyset, adLockBatchOptimistic, adCmdText);
		TESTHR(hr);*/
		m_lRowsCount=pRstSale->GetRecordCount ();
		if(m_lRowsCount<=0) 
		{
			
			return NULL;
		}
		return pRstSale;
	}
	catch(_com_error &ce)
	{	// Notify the user of errors if any.
	CString adoStr,msgStr,tempStr;
		
 
	// Trace COM error information.
	// 
	adoStr=_T("");
	TRACE0( "\nCom Exception Information\n-----------------------------------------------\n" );
	TRACE1( "Description : %s\n",   (char*) ce.Description()  );
	TRACE1( "Message     : %s\n",   (char*) ce.ErrorMessage() );
	TRACE1( "HResult     : 0x%08x\n", ce.Error() );
	// 
	// Trace ADO exception information only if connection is not null.
	// 
	if ( NULL != pApp->pConn )
	{
	   TRACE0( "\nADO Exception Information\n-----------------------------------------------\n" );
 	   ErrorPtr err;
	   for ( long i=0; i<pApp->pConn->Errors->Count; i++ ) 
	   {
		tempStr=_T("");
		err = pApp->pConn->Errors->Item[i];
		TRACE1( "Number      : 0x%08x\n", err->Number );
		TRACE1( "Description : %s\n",	  (char*) err->Description );
		TRACE1( "SQLState    : %s\n",     (char*) err->SQLState );
		TRACE1( "Source      : %s\n\n",   (char*) err->Source );
		tempStr.Format(_T("Ado Exception :\n===============\nDescription : %s\nSource : %s\n"),(char*) err->Description,(char*) err->Source);  
		adoStr += tempStr;
	   } 
	}
	msgStr.Format(_T("Com Exception :\n===============\nDescription : %s\nMessage     : %s\n%s"),(char*) ce.Description(),(char*) ce.ErrorMessage(), (LPCTSTR) adoStr);  
	MessageBox(::GetDesktopWindow(),msgStr,_T("Error Message"), MB_OK);
   }

	
		return NULL;

	
}
CZReportDoc* CZReportDoc::GetZReportDoc()
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
		if(pDoc->IsKindOf (RUNTIME_CLASS(CZReportDoc)))
			break;
	}
	return (CZReportDoc*)pDoc;
}