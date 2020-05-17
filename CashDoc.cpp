// CashDoc.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "CashDoc.h"
#include "drvfr.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCashDoc

IMPLEMENT_DYNCREATE(CCashDoc, CDocument)

CCashDoc::CCashDoc()
{
	
	m_blFlag=FALSE;
	
}

BOOL CCashDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
/*	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	TESTHR(pRstCashMove.CreateInstance (__uuidof(Recordset)));
	try
	{	
		TESTHR(pRstRaCash.CreateInstance (__uuidof(Recordset)));
		
		CString strSQL="Select racash.docid,racash.value,genjournal.doctime as doctime from racash inner "
			"join genjournal on racash.docid=genjournal.hdocid order by genjournal.doctime";
		pRstRaCash->Open (_bstr_t(strSQL),_variant_t((IDispatch*)pApp->pConnLocal), 
			adOpenKeyset, adLockOptimistic,adCmdText);
		if(pRstRaCash->GetRecordCount ()>0)
		{
			pRstRaCash->MoveFirst ();
			_variant_t vtFDoc=pRstRaCash->Fields->GetItem ("doctime")->Value;
			pRstRaCash->MoveLast();
			_variant_t vtLDoc=pRstRaCash->Fields->GetItem ("doctime")->Value ;
			m_dtFirstDocTime=(COleDateTime)vtFDoc;
			m_dtLastDocTime=(COleDateTime)vtLDoc;
			
		}
		else
		{
			CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
			m_dtFirstDocTime=pMainDoc->m_tmPointActual ;


		}
		
		pRstRaCash->Close ();
		TESTHR(pRstRgCash.CreateInstance (__uuidof(Recordset)));
		CString str2SQL="Select period,value from rgcash order by period";
		pRstRgCash->Open (_bstr_t(str2SQL),_variant_t((IDispatch*)pApp->pConnLocal), 
			adOpenKeyset, adLockOptimistic,adCmdText);
		if(pRstRgCash->GetRecordCount ()>0)
		{
		
			pRstRgCash->MoveLast();
			_variant_t vtLDoc=pRstRgCash->Fields->GetItem ("period")->Value ;
			
			m_dtActualTime=(COleDateTime)vtLDoc;
			m_dblActualSumma =pRstRgCash->Fields->GetItem ("value")->Value ;
			
		}
		else
		{
			m_dtActualTime=m_dtFirstDocTime.m_dt -1.0;
			m_dblActualSumma =0.0 ;
		}
		
		pRstRgCash->Close ();

	}
	catch (_com_error &e)
	{
		// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
		AfxMessageBox((LPCTSTR)e.Description ());
		
		return FALSE;
	}
	//TESTHR(pRstRaCash.CreateInstance (__uuidof(Recordset)));*/
	return TRUE;
}

CCashDoc::~CCashDoc()
{

}


BEGIN_MESSAGE_MAP(CCashDoc, CDocument)
	//{{AFX_MSG_MAP(CCashDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCashDoc diagnostics

#ifdef _DEBUG
void CCashDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCashDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCashDoc serialization

void CCashDoc::Serialize(CArchive& ar)
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
BOOL CCashDoc::CashDoActionIncome(LPCTSTR szDocId,float flSumma)
{

	//CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//
	//_RecordsetPtr pRst=NULL;
	//TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	////_variant_t v;
	//try
	//{
	//	pRst->Open (_bstr_t("racash"),_variant_t((IDispatch*)pApp->pConnLocal), 
	//		adOpenKeyset, adLockOptimistic,adCmdTable);
	//	TESTHR(pRst->AddNew ());
	//	pRst->Fields->GetItem("docid")->Value =_bstr_t(szDocId);
	//	pRst->Fields->GetItem("debcredit")->Value =0L;
	//	pRst->Fields->GetItem("value")->Value =_variant_t(flSumma );
	//	
	//	TESTHR(pRst->Update ());
	//	pRst->Close();
	//	return TRUE;
	//	
	//}
	//catch(_com_error &e)
	//{
	//	TRACE(_T("%s\n"),(LPCTSTR)e.Description ());
	//	AfxMessageBox(e.Description ());
	//	return FALSE;
	//	
	//}
	return TRUE;
}

BOOL CCashDoc::CashDoActionOutcome(LPCTSTR szDocId,float flSumma)
{
//CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
//	
//	_RecordsetPtr pRst=NULL;
//	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
//	//_variant_t v;
//	try
//	{
//		pRst->Open (_bstr_t("racash"),_variant_t((IDispatch*)pApp->pConnLocal), 
//			adOpenKeyset, adLockOptimistic,adCmdTable);
//		TESTHR(pRst->AddNew ());
//		pRst->Fields->GetItem("docid")->Value =_bstr_t(szDocId);
//		pRst->Fields->GetItem("debcredit")->Value =1L;
//		pRst->Fields->GetItem("value")->Value =_variant_t(flSumma );
//		
//		TESTHR(pRst->Update ());
//		pRst->Close();
//		return TRUE;
//		
//	}
//	catch(_com_error &e)
//	{
//		TRACE(_T("%s\n"),(LPCTSTR)e.Description ());
//		AfxMessageBox(e.Description 
//			());
//		return FALSE;
//		
//	}
	return TRUE;
}

BOOL CCashDoc::AddCashMoveDocument(LPCTSTR szDocId, LPCTSTR szCashId, LPCTSTR szPointId, LPCTSTR szCash2Id, LPCTSTR szPoint2Id, float flSumma)
{
	//CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//
	//CMainDocument *pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	////_variant_t v;
	//try
	//{
	//	pRstCashMove->Open (_bstr_t("dhcashmv"),_variant_t((IDispatch*)pApp->pConnLocal), 
	//		adOpenKeyset, adLockOptimistic,adCmdTable);
	//	TESTHR(pRstCashMove->AddNew ());
	//	pRstCashMove->Fields->GetItem("docid")->Value =_bstr_t(szDocId);
	//	pRstCashMove->Fields->GetItem("cashid")->Value =_bstr_t(szCashId);
	//	pRstCashMove->Fields->GetItem("pointid")->Value =_bstr_t(szPointId);
	//	pRstCashMove->Fields->GetItem("point2id")->Value =_bstr_t(szPoint2Id);
	//	pRstCashMove->Fields->GetItem("cash2id")->Value =_bstr_t(szCash2Id);
	//	pRstCashMove->Fields->GetItem("summa")->Value =double(flSumma);
	//	
	//	TESTHR(pRstCashMove->Update ());
	//	pMainDoc->UpdateNumerator (COleDateTime::GetCurrentTime ());
	//	pRstCashMove->Close();
	//	return TRUE;
	//	
	//}
	//catch(_com_error &e)
	//{
	//	TRACE(_T("%s\n"),(LPCTSTR)e.Description ());
	//	AfxMessageBox(e.Description ());
	//	return FALSE;
	//	
	//}
	return TRUE;

}

void CCashDoc::OnCloseDocument() 
{
	//// TODO: Add your specialized code here and/or call the base class
	//if((pRstCashMove!=NULL)&&(pRstCashMove->State ==adStateOpen))
	//{
	//	pRstCashMove->Close ();
	//}
	//
	//
	//if((pRstRaCash!=NULL)&&(pRstRaCash->State ==adStateOpen))
	//{
	//	pRstRaCash->Close ();
	//}
	//
	//if((pRstRgCash!=NULL)&&(pRstRgCash->State ==adStateOpen))
	//{
	//	pRstRgCash->Close ();
	//}
	//
	CDocument::OnCloseDocument();
}

BOOL CCashDoc::UpdateCashMove()
{
	//_RecordsetPtr pRst=NULL;
	//CString strSQL=_T("Select docid,cashid,pointid,summa,cash2id,point2id,docdate,doctime from HCAMOEXP where docid not in (select docid from dhcashmv) order by docdate,doctime");
	//try
	//{
	//	
	//	
	//	TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
	//	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//	
	//	HRESULT hr=pRst->Open (_bstr_t(strSQL),_variant_t((IDispatch*)pApp->pConnLocal),
	//		adOpenKeyset, adLockBatchOptimistic, adCmdText);
	//	if (hr!=S_OK)
	//	{
	//		AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
	//		return FALSE;
	//	}
	//	//pRst->MoveLast ();
	//	//pRst->MoveFirst ();
	//	long lRecordsCount=pRst->GetRecordCount ();
	//	if (lRecordsCount>0)
	//	{
	//		TESTHR(pRst->MoveFirst ());
	//		CMainDocument *pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	//		CString strCurPointId=pMainDoc->m_strPointId;
	//		CString strPointId=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("pointid")->Value );
	//		CString strPoint2Id=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("point2id")->Value );
	//		CString strCashId=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("cashid")->Value );
	//		CString strCash2Id=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("cash2id")->Value );
	//		strPointId.TrimRight ();
	//		strPoint2Id.TrimRight ();
	//		strCashId.TrimRight ();
	//		strCash2Id.TrimRight ();
	//		if((strPointId!=strCurPointId)&&(strPoint2Id!=strCurPointId))return FALSE;
	//		_variant_t vtDocDate=pRst->Fields->GetItem("docdate")->Value ;
	//		COleDateTime tmValue=vtDocDate;
	//		//pMainDoc->m_tmPointActual=(COleDateTime)(pRst->Fields->GetItem("docdate")->Value );
	//		pMainDoc->m_tmPointActual =tmValue;
	//		CString strTime=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("doctime")->Value );
	//		int nPos=0;
	//		int nDelta=3;
	//		int nTime[3];
	//		for(int i=0;i<3;i++)
	//		{
	//			nTime[i]=_ttoi(strTime.Mid (nPos,nDelta));
	//			nPos+=nDelta;
	//		}
	//		
	//		pMainDoc->m_tmPointActual.SetDateTime(pMainDoc->m_tmPointActual.GetYear(),
	//											pMainDoc->m_tmPointActual.GetMonth(),
	//											pMainDoc->m_tmPointActual.GetDay(),
	//											nTime[0],nTime[1],nTime[2]);
	//		//Add CashMove Documents In General Journal & DHCASHMV
	//		CString strDocType="CMV";
	//		while(!pRst->EndOfFile)
	//		{
	//			CString strDocId=(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("docid")->Value );
	//			_variant_t vtDocTime=pRst->Fields ->GetItem("doctime")->Value ;
	//			_variant_t vtDocDate=pRst->Fields->GetItem("docdate")->Value ;
	//			COleDateTime tmDocTime=vtDocTime;
	//			COleDateTime tmDocDate=vtDocDate;
	//			COleDateTime tmDocDateTime;

	//			tmDocDateTime.SetDateTime (tmDocDate.GetYear(),
	//								tmDocDate.GetMonth(),
	//								tmDocDate.GetDay(),
	//								tmDocTime.GetHour (),
	//								tmDocTime.GetMinute (),
	//								tmDocTime.GetSecond ()
	//								);
	//			float flSumma=(float)(double)(pRst->Fields ->GetItem("summa")->Value );
	//			if(!pMainDoc->AddNewDocInJournal (tmDocDateTime,strDocType,strDocId,flSumma))return FALSE;
	//			

	//		
	//			if(!AddCashMoveDocument (strDocId,strCashId,strPointId,strCash2Id,strPoint2Id,flSumma))return FALSE;
	//			
	//			if(strPoint2Id==pMainDoc->m_strPointId )
	//				CashDoActionIncome(strDocId,flSumma);
	//			else
	//				CashDoActionOutcome(strDocId,flSumma);
	//			pRst->MoveNext ();
	//		}
	//		double dSumm=0;
	//		CalculateCashRegisters(	pMainDoc->m_tmPointActual,COleDateTime::GetCurrentTime (),dSumm);
	//		pMainDoc->m_blIsDirty =FALSE;

	//	}
	//	TESTHR(pRst->Close());
	//	return TRUE;
	//}
	//catch (_com_error &e)
	//{
	//	// Notify the user of errors if any.
	//	// Pass a connection pointer accessed from the Recordset.
	//	_variant_t vtConnect = pRst->GetActiveConnection();
	//	
	//	// GetActiveConnection returns connect string if connection
	//	// is not open, else returns Connection object.
	//	switch(vtConnect.vt)
	//	{
	//	case VT_BSTR:
	//		PrintComError(e);
	//		break;
	//	case VT_DISPATCH:
	//		PrintProviderError(vtConnect);
	//		break;
	//	default:
	//		AfxMessageBox(_T("Errors occured."));
	//		break;
	//	}
	//	return FALSE;
	//}
	return TRUE;
}

BOOL CCashDoc::CalculateCashRegisters(COleDateTime tmStart,COleDateTime tmEnd,double& dblAggSumma)
{
	//ASSERT(pRstRaCash!=NULL);
	//	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//try
	//	{
	//	if(!m_blFlag)
	//{
	//	CString strDate=tmStart.Format (_T("%m/%d/%Y"));
	//	CString strSQL;
	//	strSQL.Format(_T("Select period from rgcash where period <= CONVERT(DATETIME, '%s', 101)"),strDate);
	//	_RecordsetPtr pRst=NULL;
	//	TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
	//	HRESULT hr=pRst->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConnLocal),
	//			adOpenKeyset, adLockOptimistic, adCmdText);
	//		if (hr!=S_OK)
	//		{
	//			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
	//			return FALSE;
	//		}
	//		if(pRst->GetRecordCount ()>0)
	//		{
	//			TESTHR(pRst->MoveLast ());
	//			_variant_t vtStart=pRst->Fields->GetItem ("period")->Value ;
	//			COleDateTime tmLastRecord=(COleDateTime)vtStart;
	//			strDate=tmLastRecord.Format (_T("%m/%d/%y"));
	//			tmStart=tmLastRecord;

	//		}
	//	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
	//	
	//	CString strExecute;
	//	strExecute.Format (_T("Delete from rgcash where period >CONVERT(DATETIME, '%s', 101)"),strDate);
	//	TESTHR(pApp->pConnLocal->Execute (_bstr_t(strExecute),&v,adOptionUnspecified));
	//	
	//	m_blFlag=TRUE;
	//}
	//if((tmEnd.m_dt -tmStart.m_dt )>10.0)
	//{
	//	COleDateTime tmpEnd=tmStart;
	//	tmpEnd.m_dt +=10.0;
	//	CString strStartDate=tmStart.Format (_T("%m/%d/%y"));
	//	CString strEndDate=tmpEnd.Format (_T("%m/%d/%y"));
	//	CString strSQL;
	//	strSQL.Format(_T("Select racash.docid,racash.debcredit as dc,racash.value as val,genjournal.docdate from racash inner join genjournal on racash.docid=genjournal.hdocid where genjournal.docdate between CONVERT(DATETIME, '%s', 101) and CONVERT(DATETIME, '%s', 101)"),strStartDate,strEndDate);
	//	
	//
	//		
	//		
	//		
	//	
	//		
	//		HRESULT hr=pRstRaCash->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConnLocal),
	//			adOpenKeyset, adLockBatchOptimistic, adCmdText);
	//		if (hr!=S_OK)
	//		{
	//			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
	//			return FALSE;
	//		}
	//		double dSumma=0;
	//		if(pRstRaCash->GetRecordCount ()>0)
	//		{ 
	//			
	//			
	//			
	//			TESTHR(pRstRaCash->MoveFirst());
	//			while(!pRstRaCash->EndOfFile)
	//			{	
	//				long lVal=pRstRaCash->Fields->GetItem ("dc")->Value ;
	//				double dVal=pRstRaCash->Fields->GetItem ("val")->Value;	
	//				if(lVal>0)
	//					dSumma-=dVal;
	//				else
	//					dSumma+=dVal;
	//				TESTHR(pRstRaCash->MoveNext());
	//				
	//			}
	//		}
	//		dblAggSumma +=dSumma;
	//		TESTHR(pRstRaCash->Close());
	//		ASSERT(pRstRgCash!=NULL);
	//		strSQL=_T("rgcash");
	//		//		CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//		hr=pRstRgCash->Open ((_bstr_t)("rgcash"),_variant_t((IDispatch*)pApp->pConnLocal),
	//			adOpenKeyset, adLockOptimistic, adCmdTable);
	//		if (hr!=S_OK)
	//		{
	//			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
	//			return FALSE;
	//		}
	//		TESTHR(pRstRgCash->AddNew ());
	//		pRstRgCash->Fields->GetItem ("period")->Value =(_variant_t)tmpEnd;
	//		pRstRgCash->Fields ->GetItem ("value")->Value =(_variant_t)dblAggSumma;
	//		TESTHR(pRstRgCash->Update ());
	//		TESTHR(pRstRgCash->Close());
	//		
	//		
	//		
	//		
	//		CalculateCashRegisters(tmpEnd,tmEnd,dblAggSumma);
	//		
	//	}}
	//	catch (_com_error &e)
	//	{
	//		// Notify the user of errors if any.
	//		// Pass a connection pointer accessed from the Recordset.
	//		AfxMessageBox((LPCTSTR)e.Description());
	//		return FALSE;
	//	}
	
	return TRUE;
}

double CCashDoc::CalculateCashBalance(COleDateTime &tmCurTime)
{
	
	CShtrihFRK Driver;
	double dblRes=0.0;
   // Driver.CreateDispatch(_T("Addin.DrvFR3"));
	Driver.GetContentOfCash (&dblRes);
	return dblRes;



}

CString& CCashDoc::GetMainCashId()
{

	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	return pMainDoc->m_strMainCashId;


}

CString& CCashDoc::GetCashId()
{

	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	return pMainDoc->m_strCashId;

}
