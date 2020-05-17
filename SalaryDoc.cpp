// SalaryDoc.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "SalaryDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSalaryDoc

IMPLEMENT_DYNCREATE(CSalaryDoc, CDocument)

CSalaryDoc::CSalaryDoc()
{
}

BOOL CSalaryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSalaryDoc::~CSalaryDoc()
{
	m_flBaseSalary=0.0;

	m_flCalcSalary=0.0;
}


BEGIN_MESSAGE_MAP(CSalaryDoc, CDocument)
	//{{AFX_MSG_MAP(CSalaryDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSalaryDoc diagnostics

#ifdef _DEBUG
void CSalaryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSalaryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSalaryDoc serialization

void CSalaryDoc::Serialize(CArchive& ar)
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
// CSalaryDoc commands

BOOL CSalaryDoc::GetProductSalePremia(LPCTSTR strCode, float *pflPremia)
{//получить значение премиального процента с продажи для указанного товара
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	float flPremia=0.0;
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
	try
	{
		CString strSQL;
		strSQL.Format(_T("Select price , zprice from catalog  where code='%s'"),strCode);
		HRESULT hr=pRst->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
			adOpenStatic, adLockBatchOptimistic, adCmdText);
		if (hr!=S_OK)
		{
			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
			return FALSE;
		}
		
		if(pRst->GetRecordCount ()<=0)
			return FALSE;
		pRst->MoveFirst ();
		double dPrice=pRst->Fields->GetItem ("price")->Value;
		double dZPrice=pRst->Fields->GetItem ("zprice")->Value;
		double delta=((dPrice-dZPrice)/dZPrice)*100;
		if (delta<0) return FALSE;
		if(delta<=75)
			flPremia=5.0;
		if((delta >75) && (delta<=100))
			flPremia=6.0;
		if(delta>100)
			flPremia=7.0;
		*pflPremia=flPremia;
		pRst->Close();
		return TRUE;
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
		MessageBoxHelper::ShowError(_T("Errors occured.CSalaryDoc::GetSalaryBalance"));
			break;
		}
		return FALSE;
	}
	
 
}

BOOL CSalaryDoc::AddPremiaToEmployer(LPCTSTR strEmplId, float flValue)
{//Начислить премию работнику
 return FALSE;
}

BOOL CSalaryDoc::DeductFromSalary(LPCTSTR strEmplId, float flValue)
{//вычесть из зарплатного счета работника
 return FALSE;
}
float CSalaryDoc::GetSalaryBalance(LPCTSTR strEmplId, COleDateTime tmDate)
{//получить состояние счета работника на указанный момент
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	COleDateTime tmCurTime=COleDateTime::GetCurrentTime ();
	CString strCurDate=tmCurTime.Format (_T("%m/%d/%y"));
	CString strDate=tmDate.Format(_T("%m/%d/%y"));
	float flBalance=0.0;
	_RecordsetPtr pRstEndPointDate=NULL;
	TESTHR(pRstEndPointDate.CreateInstance(__uuidof(Recordset)));
	try
	{
	//находим точку последнего вычисленного значения, далее будем делать вычисления
	//позже этой точки (точка актуальности итогов)
		
		CString strSQL;
		strSQL.Format(_T("Select value , period ")
			_T("from rgsalary  where rgsalary.period < {%s} and rgsalary.emplid='%s' order by rgsalary.period"),strDate,strEmplId);
		HRESULT hr=pRstEndPointDate->Open ((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn),
			adOpenKeyset, adLockBatchOptimistic, adCmdText);
		if (hr!=S_OK)
		{
			AfxMessageBox(_T("Error in Open Recordset"),MB_OK|MB_ICONSTOP);
			return 0.0;
		}
		
		if(pRstEndPointDate->GetRecordCount ()<=0)
			return 0.0; 
		TESTHR(pRstEndPointDate->MoveLast());
		COleDateTime tmLastPoint=(COleDateTime)pRstEndPointDate->Fields ->GetItem("period")->Value;	
		CString strLastPointDate=tmLastPoint.Format (_T("%m/%d/%y"));
		double dblLastPointValue=pRstEndPointDate->Fields ->GetItem("value")->Value;
		TESTHR(pRstEndPointDate->Close());

		_RecordsetPtr pRstDebet=NULL;
		TESTHR(pRstDebet.CreateInstance(__uuidof(Recordset)));
		strSQL.Empty ();
		strSQL.Format(_T("SELECT rasalary.summa as val from rasalary inner join genjournal on rasalary.docid=genjournal.hdocid ")
					_T("where rasalary.debcredit=0 and rasalary.emplid='%s' and (genjournal.doctime between {%s} and {%s})"),strEmplId,strLastPointDate,strDate);

		hr=pRstDebet->Open((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn ),adOpenKeyset, adLockBatchOptimistic, adCmdText);
		
		TESTHR(hr);
		if(pRstDebet->GetRecordCount ()<=0) return 0.0;
		pRstDebet->MoveFirst ();
		double dblDebet=0.0;
		while(!pRstDebet->EndOfFile )
		{	
			
			double dVal=pRstDebet->Fields->GetItem ("val")->Value;	
			
			dblDebet+=dVal;
			TESTHR(pRstDebet->MoveNext());
			
		}
		TESTHR(pRstDebet->Close());

		_RecordsetPtr pRstCredit=NULL;
		TESTHR(pRstCredit.CreateInstance(__uuidof(Recordset)));
		strSQL.Empty ();
		strSQL.Format(_T("SELECT rasalary.summa as val from rasalary inner join genjournal on rasalary.docid=genjournal.hdocid ")
					_T("where rasalary.debcredit=1 and rasalary.emplid='%s' and (genjournal.doctime between {%s} and {%s})"),strEmplId,strLastPointDate,strDate);

		hr=pRstCredit->Open((_bstr_t)strSQL,_variant_t((IDispatch*)pApp->pConn ),adOpenKeyset, adLockBatchOptimistic, adCmdText);
		
		TESTHR(hr);
		if(pRstCredit->GetRecordCount ()<=0) return 0.0;
		pRstCredit->MoveFirst ();
		double dblCredit=0.0;
		while(!pRstCredit->EndOfFile )
		{	
			
			double dVal=pRstCredit->Fields->GetItem ("val")->Value;	
			
			dblCredit+=dVal;
			TESTHR(pRstCredit->MoveNext());
			
		}
		TESTHR(pRstCredit->Close());
		flBalance=(float)dblLastPointValue+(float)dblDebet-(float)dblCredit;

		return flBalance;
		
	}
	catch (_com_error &e)
	{
		// Notify the user of errors if any.
		// Pass a connection pointer accessed from the Recordset.
		_variant_t vtConnect = pRstEndPointDate->GetActiveConnection();
		
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
		MessageBoxHelper::ShowError(_T("Errors occured.CSalaryDoc::GetSalaryBalance"));
			break;
		}
	}
return 0.0;
}

CSalaryDoc* CSalaryDoc::GetSalaryDoc()
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
		if(pDoc->IsKindOf (RUNTIME_CLASS(CSalaryDoc)))
			break;
	}
	return (CSalaryDoc*)pDoc;
}

BOOL CSalaryDoc::TransactSalary(LPCTSTR strBaseDocId,_variant_t& vt)
{

	///добавляем данные в dhsalary.dbf
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
//	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();

	COleDateTime tmDocTime=COleDateTime::GetCurrentTime ();
	//CString strDocId ;
	int nDayNumber=0;
//	pMainDoc->CalculateDocId(pMainDoc->m_strPointId ,m_strDocId,&nDayNumber);//расчитываем номер документа

	m_strEmplId=pMainDoc->m_strUserId;
	m_strBaseDocId=strBaseDocId;
	
	GetBaseSalary(m_strEmplId,&m_flBaseSalary);
	
	CalculateAmountSalary(vt,&m_flCalcSalary);//расчитываем премию за продажи

	AccountingSalaryToEmpl(m_strEmplId,m_flCalcSalary+m_flBaseSalary);//начисляем зарплату 
	

	
	return TRUE;


}

BOOL CSalaryDoc::WithdrawFromEmplAccount(LPCTSTR strEmpId, float flValue)
{//снятие ден средств работником 
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();

	
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	try
	{
HRESULT		hr=pRst->Open (_bstr_t("rasalary"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);


		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(m_strDocId);
		pRst->Fields->GetItem("debcredit")->Value =1L;;
		pRst->Fields->GetItem("emplid")->Value =_bstr_t(strEmpId);
		pRst->Fields->GetItem("summa")->Value =(double)flValue  ;
		TESTHR(pRst->Update ());

		pRst->Close();
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE1("%s\n",(LPCTSTR)e.Description ());
		MessageBoxHelper::ShowError(e.Description ());
		
		return FALSE;
	}
 
}

BOOL CSalaryDoc::AccountingSalaryToEmpl(LPCTSTR strEmplId, float flValue)
{
	//начисление ден средств на счет работника
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	COleDateTime tmDocTime=COleDateTime::GetCurrentTime ();
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	try
	{
		HRESULT hr=pRst->Open (_bstr_t("dhsalary"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);
		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(m_strDocId);
		pRst->Fields->GetItem("period")->Value =(_variant_t)tmDocTime;;
		pRst->Fields->GetItem("emplid")->Value =_bstr_t(strEmplId);
		pRst->Fields->GetItem("summa")->Value =(double)flValue ;//сколько начислено
		pRst->Fields->GetItem("basedoc")->Value =_bstr_t(m_strBaseDocId );//базовый отчет по кассе
		TESTHR(pRst->Update ());
		pRst->Close();



			//добавляем запись в журнал документов genjournal.dbf
	//if(!pMainDoc->AddNewDocInJournal(tmDocTime,_T("SLR"),m_strDocId,flValue))return FALSE;
	//if(!pMainDoc->UpdateNumerator (tmDocTime))return FALSE;
	///добавляем данные в оборотный регистр оплаты труда rasalary.dbf
	//pRst=NULL;
	
		hr=pRst->Open (_bstr_t("rasalary"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);

		TESTHR(pRst->AddNew ());
		pRst->Fields->GetItem("docid")->Value =_bstr_t(m_strDocId);
		pRst->Fields->GetItem("debcredit")->Value =0L;;
		pRst->Fields->GetItem("emplid")->Value =_bstr_t(strEmplId);
		pRst->Fields->GetItem("summa")->Value =(double)flValue  ;
		TESTHR(pRst->Update ());

		

		pRst->Close();
	

		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE1("%s\n",(LPCTSTR)e.Description ());
		MessageBoxHelper::ShowError(e.Description ());
		
		return FALSE;
	}

}

BOOL CSalaryDoc::CalculateAmountSalary(_variant_t &vt,float* pfCalcSalary)
{
	ASSERT(vt.vt ==(VT_ARRAY | VT_VARIANT));
//	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	

	//_variant_t v;
	try
	{
		
		COleSafeArray sa(vt);
		long lNumRows;
		long lNumCols;
		sa.GetUBound(2, &lNumRows);
		sa.GetUBound(1, &lNumCols);
		
		//Display the elements in the SAFEARRAY.
		long index[2];
		_variant_t val;
		float flCurSumma=0.0;
		
		//Determine upper bounds for both dimensions
		long r, c;
		sa.GetLBound(1, &r);
		sa.GetLBound(2, &c);
		
		for(;r <=lNumRows; r++ )
		{

			index[0]=1L;
			index[1]=r;
			sa.GetElement(index, &val);// код товара
			
			CString strCode=(LPCTSTR)(_bstr_t)val;
			strCode.TrimRight ();
			float flPremia=0.0;
			if(!GetProductSalePremia(strCode,&flPremia)) return FALSE;
		
			long lQty=0L;
			index[0]=2L;
			sa.GetElement(index, &val);
			lQty=val.lVal ;
			
			double dPrice=0.0;
			index[0]=3L;
			sa.GetElement(index, &val);
			dPrice=(double)val;
			
			
			flCurSumma+=(flPremia*lQty*(float)dPrice/100);
			
		}
		*pfCalcSalary=flCurSumma;
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE1("%s\n",(LPCTSTR)e.Description ());
		MessageBoxHelper::ShowError(e.Description ());
		return FALSE;
	}
}

BOOL CSalaryDoc::RecalculateSalaryRegisters(const COleDateTime &tmValue)
{
//проверяем и если нет записей или разница с последней записью > 30 дней записываем
	//значение в регистр остатков зарплаты rgsalary.dbf
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();

	COleDateTime tmDocTime=tmValue;
	_RecordsetPtr pRst=NULL;
	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	try
	{
		BOOL blFlag1,blFlag2;
		blFlag1=blFlag2=FALSE;
		HRESULT hr=pRst->Open (_bstr_t("rgsalary"),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdTable);
		TESTHR(hr);

		if(pRst->GetRecordCount ()<=0) 
		{
			blFlag1=TRUE;
		}
		else
		{
			pRst->Sort="period ASC";
			TESTHR(pRst->MoveLast());
			COleDateTime tmLastDate=pRst->Fields ->GetItem("period")->Value;
			if(((double)tmDocTime-(double)tmLastDate)>30) blFlag2=TRUE;
		}

	
	if(blFlag1||blFlag2)
		{
			TESTHR(pRst->AddNew ());
			pRst->Fields->GetItem("period")->Value =(_variant_t)tmDocTime;
			pRst->Fields->GetItem("emplid")->Value =_bstr_t(m_strEmplId);
			pRst->Fields->GetItem("value")->Value =GetSalaryBalance (m_strEmplId ,tmDocTime) ;
			TESTHR(pRst->Update ());
		}

		pRst->Close();
	return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE1("%s\n",(LPCTSTR)e.Description ());
		MessageBoxHelper::ShowError(e.Description ());
		
		return FALSE;
	}

}

BOOL CSalaryDoc::GetBaseSalary(LPCTSTR strEmplId, float *pfBaseSalary)
{
	CString strSQL;
	
	double dblSalary;
	double dblPremia;
	strSQL.Format(_T("Select emplname,salary,premia from employee where emplid='%s'"),strEmplId );
	try
    {
		CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		_RecordsetPtr pRst=NULL;
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		
		HRESULT hResult=pRst->Open(_bstr_t(strSQL),_variant_t((IDispatch*)pApp->pConn), 
			adOpenKeyset, adLockOptimistic,adCmdText);
		if(hResult!=S_OK)return FALSE;
		if(pRst->GetRecordCount ()<=0) return FALSE;
		pRst->MoveFirst();
		
		dblSalary=pRst->Fields ->GetItem("salary")->Value ;
		dblPremia =pRst->Fields->GetItem("premia")->Value ;
	
		pRst->Close ();
		*pfBaseSalary=(float)dblSalary;
		return TRUE;
		
	}
	catch(_com_error &e)
	{ 
		MessageBoxHelper::ShowError(e.Description() );
		return FALSE ;
	}
}

BOOL CSalaryDoc::CalculateAmountSalary(_RecordsetPtr pRst, float *pfCalcSalary)
{
	float flCurSumma=0.0;
	ASSERT(pRst!=NULL);
	try
    {
		pRst->MoveFirst ();
		while(!pRst->EndOfFile )
		{	
			CString strCode=(LPCTSTR)(_bstr_t)pRst->Fields->GetItem ("code")->Value;	
			float flPremia=0.0;
			strCode.TrimRight ();
			if(!GetProductSalePremia(strCode,&flPremia)) return FALSE;
			
			long lQty=pRst->Fields->GetItem ("qty")->Value;
			
			double dPrice=pRst->Fields->GetItem ("price")->Value;
			
			
			flCurSumma+=(flPremia*lQty*(float)dPrice/100);
			
			TESTHR(pRst->MoveNext());
		}
		TESTHR(pRst->Close());
		
		*pfCalcSalary=flCurSumma;
		return TRUE;
	}
	catch(_com_error &e)
	{
		TRACE1("%s\n",(LPCTSTR)e.Description ());
		MessageBoxHelper::ShowError(e.Description ());
		return FALSE;
	}
}
