// CheckDoc.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "CheckDoc.h"
#include "CashDoc.h"
#include "UserThreadsView.h"
#include "DocSetter.h"
#include "NotyfyFndProduct.h"
#include "Repository.h"
#include "MultButtonEx.h"
#include "MainFrm.h"
#include "DlgSetQuantity.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckDoc


IMPLEMENT_DYNCREATE(CCheckDoc,CDocument)

CCheckDoc::CCheckDoc()
{
		m_strDocId="";
		m_flCurSumma=0.0;
		m_nLineNo=0;
		m_nMultiplicator=1;
}

BOOL CCheckDoc::OnNewDocument()
{

	if (!CDocument::OnNewDocument())
		return FALSE;
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	int nDayNumber=0;
//	pMainDoc->CalculateDocId(pMainDoc->m_strPointId ,m_strDocId,&nDayNumber);
		CMDIFrameWnd* pMainWnd = (CMDIFrameWnd*)AfxGetMainWnd();
		// Get the active MDI child window.
		CMDIChildWnd* pChild = (CMDIChildWnd*)pMainWnd->MDIGetActive();
		
	CString strTitle="";
	
	strTitle.Format (_T("Товарный чек №-%s"),m_strDocId);
	AfxSetWindowText(pChild->m_hWnd ,strTitle);
	
	SalesLineItems.clear();
	if(SalesLineItems.size()>0)
		AfxMessageBox(_T("size not 0"));
	odslog(L"CheckDock loaded");
	return TRUE;
}

CCheckDoc::~CCheckDoc()
{
}


BEGIN_MESSAGE_MAP(CCheckDoc, CDocument)
	//{{AFX_MSG_MAP(CCheckDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_MULTBUT_HOLDER, &CCheckDoc::OnMultbutHolder)
	ON_UPDATE_COMMAND_UI(ID_MULTBUT_HOLDER, &CCheckDoc::OnUpdateMultbutHolder)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CCheckDoc,CDocument)
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckDoc diagnostics

#ifdef _DEBUG
void CCheckDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCheckDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCheckDoc serialization

void CCheckDoc::Serialize(CArchive& ar)
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
// CCheckDoc commands

void CCheckDoc::OnCloseDocument() 
{
	
	if(GetCurSumma()!=0.0)
	{
		int nRes=AfxMessageBox(_T("Документ не пуст.Провести документ ?"),
			MB_YESNO|MB_ICONEXCLAMATION);
		if (nRes==IDYES)
		{
			CMDIFrameWnd* pMainWnd = (CMDIFrameWnd*)AfxGetMainWnd();
			// Get the active MDI child window.
			CMDIChildWnd* pChild = (CMDIChildWnd*)pMainWnd->MDIGetActive();
			// Get the active view attached to the active MDI child window.
			CUserThreadsView* pActiveView = (CUserThreadsView*)pChild->GetActiveView();
			pActiveView->TransactCheck ();
			
			
		}
	}
	
	CDocument::OnCloseDocument();
	
}

void CCheckDoc::AddLine(const SalesItemLine& line)
{
	CCheckDoc::SalesLineItemsType::iterator it=std::find_if(SalesLineItems.begin(),
		SalesLineItems.end(),[&line](SalesItemLine l){
			return l.code==line.code;	
	});
	if(it!=SalesLineItems.end())
	{
		it->qty+=line.qty;
	}
	else
		SalesLineItems.push_back(line);

}

BOOL CCheckDoc::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if(HIWORD(nCode)==WM_NOTIFY)
	{
		WORD wCode=LOWORD(nCode);
		AFX_NOTIFY* notify=reinterpret_cast<AFX_NOTIFY*>(pExtra);
		if(wCode==FND_BY_CODE)
		{
			USES_CONVERSION;
			LPNMFNDPRODUCT lpnmhdr=reinterpret_cast<LPNMFNDPRODUCT>(notify->pNMHDR);
			CNotyfyFndProduct* pObject=lpnmhdr->pObject;
			Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
			boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
			std::wstring code=A2W(pObject->GetCode());
			std::wstring descr=L"";
			std::wstring unit=L"";
			std::wstring barcode=L"";
			double price=0.0;
			
			if(refProducts->FindByCode(code)>0)
			{

				Repository::ReferenceItem prodRoot=refProducts->getCurrent();
				descr=prodRoot->_descr;
				unit=(_bstr_t)prodRoot->getAttribute(Products::ListOfAttr::BaseUnit());
				boost::shared_ptr<Repository::TypePriceReference> refTypePrice=pRep->getType_price();
				refTypePrice->FindByCode(A2W(CUserThreadsApp::GetDocument<CMainDocument>()->m_strTypePriceId));
				Repository::ReferenceItem curTypePrice=refTypePrice->getCurrent();
				boost::shared_ptr<Repository::PricesReference> refPrice=pRep->getPrices();
				std::wstring typePrice=curTypePrice->_code;
				std::wstring prod_code=prodRoot->_code;
				std::wstring price_code=prod_code+typePrice;
				
				if(refPrice->FindByCode(price_code)){
					//refPrice->SelectItemsByAttribute(IReference::ListOfAttr::Descr(),L"Домоде");

					Repository::ReferenceItem curPrice=refPrice->getCurrent();
					if(curPrice!=nullptr)
					{
						_variant_t var=curPrice->getAttribute(Prices::ListOfAttr::PriceValue());
						if(var.vt==VT_NULL)
							price=0.0;
						else
							price=(double)var;;
					}
				}
				
			}

			SalesItemLine sl;
			memset((void*)&sl,0,sizeof(SalesItemLine));
			sl.line_no=++m_nLineNo;
			sl.barcode=A2W(pObject->GetBarCode());
			sl.descr=descr;
			sl.code=code;
			sl.unit=unit;
			sl.qty=pObject->GetQty()*m_nMultiplicator;
			sl.price=price;
			AddLine(sl);
			m_nMultiplicator=1;	
			OnUpdateMultbutHolder(NULL);
			UpdateAllViews(NULL,0,this);
			delete pObject;
			*(notify->pResult)=1;
			return TRUE;
		}
		if(wCode==FND_BY_BARCODE)
		{
			USES_CONVERSION;
			LPNMFNDPRODUCT lpnmhdr=reinterpret_cast<LPNMFNDPRODUCT>(notify->pNMHDR);
			CNotyfyFndProduct* pObject=lpnmhdr->pObject;
			Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
			boost::shared_ptr<Repository::UnitsReference> refUnits=pRep->getUnits();
			CString strBarCode=pObject->GetBarCode();
			if(refUnits->FindByCode(A2W(strBarCode)))
			{
				boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
				Repository::ReferenceItem curUnit=refUnits->getCurrent();
				std::wstring code=(_bstr_t)curUnit->getAttribute(ISReference<Products>::ListOfAttr::Owner());
				boost::trim(code);
				std::wstring descr=L"";
				std::wstring unit=L"";
				std::wstring barcode=L"";
				double price=0.0;

				if(refProducts->FindByCode(code)>0)
				{

					Repository::ReferenceItem prodRoot=refProducts->getCurrent();
					descr=prodRoot->_descr;
					unit=(_bstr_t)prodRoot->getAttribute(Products::ListOfAttr::BaseUnit());
					boost::shared_ptr<Repository::TypePriceReference> refTypePrice=pRep->getType_price();
					refTypePrice->FindByCode(A2W(CUserThreadsApp::GetDocument<CMainDocument>()->m_strTypePriceId));
					Repository::ReferenceItem curTypePrice=refTypePrice->getCurrent();
					boost::shared_ptr<Repository::PricesReference> refPrice=pRep->getPrices();
					std::wstring typePrice=curTypePrice->_code;
					std::wstring prod_code=prodRoot->_code;
					std::wstring price_code=prod_code+typePrice;

					if(refPrice->FindByCode(price_code)){
						//refPrice->SelectItemsByAttribute(IReference::ListOfAttr::Descr(),L"Домоде");

						Repository::ReferenceItem curPrice=refPrice->getCurrent();
						if(curPrice!=nullptr)
						{
							_variant_t var=curPrice->getAttribute(Prices::ListOfAttr::PriceValue());
							if(var.vt==VT_NULL)
								price=0.0;
							else
								price=(double)var;;
						}
					}

				}

				SalesItemLine sl;
				memset((void*)&sl,0,sizeof(SalesItemLine));
				sl.line_no=++m_nLineNo;
				sl.barcode=A2W(pObject->GetBarCode());
				sl.descr=descr;
				sl.code=code;
				sl.unit=unit;
				sl.qty=pObject->GetQty()*m_nMultiplicator;
				sl.price=price;
				AddLine(sl);
				//SalesLineItems.push_back(sl);
				m_nMultiplicator=1;	
				OnUpdateMultbutHolder(NULL);
				UpdateAllViews(NULL,0,this);
				delete pObject;
				*(notify->pResult)=1;
				return TRUE;
			}
			delete pObject;
		}
	}
return CDocument::OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
}

BOOL CCheckDoc::TransactCheck()

{	
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	
	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	CCashDoc* pCashDoc=CUserThreadsApp::GetDocument<CCashDoc> ();
	COleDateTime tmCheckTime=COleDateTime::GetCurrentTime ();
	int nDayNumber=0;
	m_strDocId=_T("00001");
	CComBSTR bstrNumDoc=m_strDocId;
	int NumDoc=0;
	::VarI4FromStr (bstrNumDoc,LOCALE_SYSTEM_DEFAULT,LOCALE_NOUSEROVERRIDE,(long*)&NumDoc);
	USES_CONVERSION;
	CheckBuilder* pCheckBuilder=new CheckBuilder();
	CCheckContainer* pCheck=new CCheckContainer(pCheckBuilder);
	pCheck->Init();
	pCheck->SetNumber (_T("007"));
	
	pCheck->SetAuthor (pMainDoc->m_strUserNick);
	pCheck->SetDescription (_T("Very very important document; can't  lousing anybody data"));
	pCheck->SetPointCode(pMainDoc->m_strPointName);
	pCheck->SetPrefix(pMainDoc->m_strPrefix);
	odslog(L"Document #:"<<OLE2W(bstrNumDoc)<<L" Author:"<<A2W(pMainDoc->m_strUserNick)<<L" Point:"<<A2W(pMainDoc->m_strPointName)<<std::endl);
	for(SalesLineItemsType::const_iterator it=SalesLineItems.cbegin();it!=SalesLineItems.cend();++it)
		{
			TESTHR(pCheck->AddNewLine ());
			std::wstring code=it->code;
			boost::trim(code);
			TESTHR(pCheck->SetNomenclatureCode(W2T(code.c_str())));
			std::wstring barcode=it->barcode;
			boost::trim(barcode);
			CString strBarCode=W2A(barcode.c_str());
			TESTHR(pCheck->SetBarCode(strBarCode));
			TESTHR(pCheck->SetQty(it->qty));
			TESTHR(pCheck->SetPrice(it->price));
			odslog(L"Code:"<<it->code<<L" BarCode:"<<it->barcode<<L" Qty:"<<it->qty<<L" Price:"<<it->price<<std::endl);
			odslog(L"Descr:"<<it->descr<<std::endl);
		}
		TRACE(_T("\nCheck save in 1C"));
		BSTR bstrData;
		pCheck->SaveToString(&bstrData);
		delete pCheck;
		pMainDoc->SendDataInQueue(bstrData);
		CMDIFrameWnd* pMainWnd = (CMDIFrameWnd*)AfxGetMainWnd();
		// Get the active MDI child window.
		CMDIChildWnd* pChild = (CMDIChildWnd*)pMainWnd->MDIGetActive();
		
		CString strTitle="";
		
		strTitle.Format (_T("Товарный чек №-%s"),m_strDocId);
		AfxSetWindowText(pChild->m_hWnd ,strTitle);

		//SalesLineItems.clear();
		return TRUE;


}
BOOL CCheckDoc::SaveHeadCheck(const COleDateTime &tmCheckTime,LPCTSTR szDocId)
{
	//CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	//CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//
	//_RecordsetPtr pRst=NULL;
	//TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
	////_variant_t v;
	//try
	//{
	//	pRst->Open (_bstr_t("headcheck"),_variant_t((IDispatch*)pApp->pConnLocal), 
	//		adOpenKeyset, adLockOptimistic,adCmdTable);
	//	TESTHR(pRst->AddNew ());
	//	pRst->Fields->GetItem("docid")->Value =_bstr_t(szDocId);
	//	pRst->Fields->GetItem("pointid")->Value =_bstr_t(pMainDoc->m_strPointId);
	//	pRst->Fields->GetItem("contragid")->Value =_bstr_t(pMainDoc->m_strContragId);
	//	pRst->Fields->GetItem("salerid")->Value =_bstr_t(pMainDoc->m_strUserId);
	//	pRst->Fields->GetItem("checkdate")->Value =_bstr_t(tmCheckTime.Format (VAR_DATEVALUEONLY));
	//	pRst->Fields->GetItem("checktime")->Value =_bstr_t(tmCheckTime.Format (VAR_TIMEVALUEONLY));
	//	pRst->Fields->GetItem("descript")->Value =_bstr_t("Здесь могла быть ваша реклама");
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

BOOL CCheckDoc::SaveTableCheck(VARIANT* vt,LPCTSTR szDocId )
{
//if (V_VT(vt) != (VT_ARRAY | VT_VARIANT))
//      AfxThrowOleDispatchException(1001, 
//         _T("Type Mismatch in Parameter. Pass a variant array by reference"));
//	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
//	
//	_RecordsetPtr pRst;
//	TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
//	//_variant_t v;
//	try
//	{
//		ASSERT(pApp->pConnLocal->State ==adStateOpen);
//		pRst->Open (_bstr_t("tablecheck"),_variant_t((IDispatch*)pApp->pConnLocal), 
//			adOpenKeyset, adLockOptimistic,adCmdTable);
//		COleSafeArray sa(vt);
//		//sa.Attach (*vt);
//		long lNumRows;
//		long lNumCols;
//		sa.GetUBound(1, &lNumRows);
//		sa.GetUBound(2, &lNumCols);
//		
//		//Display the elements in the SAFEARRAY.
//		long index[2];
//		_variant_t val;
//		m_flCurSumma=0.0;
//		
//		//Determine upper bounds for both dimensions
//		long r, c;
//		sa.GetLBound(1, &r);
//		sa.GetLBound(2, &c);
//		
//		for(;r <= lNumRows; r++ )
//		{
//			TESTHR(pRst->AddNew ());
//			pRst->Fields->GetItem("docid")->Value =_bstr_t(szDocId);
//			long numpos=r+1;
//			_variant_t varNumPos(numpos);
//			pRst->Fields->GetItem("numpos")->Value =varNumPos;
//			index[0]=r;
//			index[1]=lNumCols;
//			sa.GetElement(index, &val);
//			pRst->Fields->GetItem("nomenid")->Value=val ;
//			::VariantClear(&val);
//			double dblQty=0.0;
//			index[1]=4L;
//			sa.GetElement(index, &val);
//			::VarR8FromStr (val.bstrVal,LOCALE_USER_DEFAULT,LOCALE_NOUSEROVERRIDE,&dblQty);
//			long lQty=(long)dblQty ;
//			pRst->Fields->GetItem("qty")->Value =lQty;
//			::VariantClear(&val);
//			double dblPrice=0.0;
//			index[1]=2L;
//			sa.GetElement(index, &val);
//			::VarR8FromStr (val.bstrVal,LOCALE_USER_DEFAULT,LOCALE_NOUSEROVERRIDE,&dblPrice);
//			
//			pRst->Fields->GetItem("price")->Value =dblPrice;	
//			m_flCurSumma+=(float)(lQty*dblPrice);
//			::VariantClear(&val);
//			
//		}
//		TESTHR(pRst->UpdateBatch (adAffectAll));
//		pRst->Close();
//	//*vt=sa.Detach ();
//		return TRUE;
//	}
//	catch(_com_error &e)
//	{
//		TRACE(_T("%s\n"),(LPCTSTR)e.Description ());
//		AfxMessageBox(e.Description ());
//		return FALSE;
//	}
//
	return TRUE;

}


BOOL CCheckDoc::DeleteCheck(LPCTSTR szDocId)
{

////	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
//	CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
//	_variant_t v(DISP_E_PARAMNOTFOUND , VT_ERROR);//vtMissing
//	try
//	{
//		pApp->pConnLocal->BeginTrans();
//		CString strSQL=_T("delete from tablecheck where docid='");
//		strSQL+=szDocId;
//		strSQL+="'";
//		pApp->pConnLocal->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
//		strSQL.Empty ();
//
//		strSQL=_T("delete from headcheck where docid='");
//		strSQL+=szDocId;
//		strSQL+="'";
//		pApp->pConnLocal->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
//		strSQL.Empty ();
//
//		strSQL=_T("delete from genjournal where hdocid='");
//		strSQL+=szDocId;
//		strSQL+="'";
//		pApp->pConnLocal->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
//		strSQL.Empty ();
//	
//		strSQL=_T("delete from racash where docid='");
//		strSQL+=szDocId;
//		strSQL+="'";
//		pApp->pConnLocal->Execute ((_bstr_t)strSQL,&v,adOptionUnspecified);
//		strSQL.Empty ();
//		pApp->pConnLocal->CommitTrans ();
//		return TRUE;
//		
//	}
//	catch(_com_error &e)
//	{
//		pApp->pConnLocal->RollbackTrans ();
//		TRACE(_T("%s\n"),(LPCTSTR)e.Description ());
//		AfxMessageBox(e.Description ());
//		return FALSE;
//		
//	}
	return FALSE;
}

void CCheckDoc::DeleteLineNo(int line)
{
	int del_line=line;
SalesLineItems.remove_if([del_line](SalesItemLine line)
{
return line.line_no==del_line;
});
}

BOOL CCheckDoc::GetCheckInfo(LPCTSTR strDocId, 
							 TCHAR* strPointId, 
							 TCHAR* strSalerId, 
							 TCHAR* strContragId,
							 size_t szStrId,
							 COleDateTime &tmCheckDate)

{
	//CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
	//_RecordsetPtr pRst=NULL;
	//pRst.CreateInstance (__uuidof(Recordset));
	//try
	//{
	//	pRst->Open (_bstr_t("headcheck"),_variant_t((IDispatch*)pApp->pConnLocal), 
	//			adOpenStatic, adLockOptimistic,adCmdTable);
	//	CString strCriteria;
	//	strCriteria.Format(_T("[docid]='%s'"),strDocId);
	//	
	//	HRESULT hr=pRst->MoveFirst ();
	//	TESTHR(hr);
	//	TESTHR(pRst->Find ((bstr_t)strCriteria,0,adSearchForward,""));
	//	if(!pRst->EndOfFile )
	//		{
	//			_tcsncpy(strPointId,(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("pointid")->Value ),szStrId);
	//			_tcsncpy(strSalerId,(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("salerid")->Value ),szStrId);
	//			_tcsncpy(strContragId,(LPCTSTR)(_bstr_t)(pRst->Fields->GetItem("contragid")->Value ),szStrId);
	//			tmCheckDate =(COleDateTime)(pRst->Fields->GetItem("checkdate")->Value);
	//		
	//		
	//		}

	//	pRst->Close();
	//	return TRUE;
	//}
	//catch(_com_error &e)
	//{
	//	TRACE(_T("%s\n"),(LPCTSTR)e.Description ());
	//	AfxMessageBox(e.Description ());
	//	return FALSE;

	//}
	return FALSE;
}

BOOL CCheckDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	int nRes=AfxMessageBox(_T("Документ не пуст.Провести документ?"),
		MB_YESNO|MB_ICONEXCLAMATION);
	if (nRes==IDYES)
	{
		CMDIFrameWnd* pMainWnd = (CMDIFrameWnd*)AfxGetMainWnd();
		// Get the active MDI child window.
		CMDIChildWnd* pChild = (CMDIChildWnd*)pMainWnd->MDIGetActive();
		// Get the active view attached to the active MDI child window.
		CUserThreadsView* pActiveView = (CUserThreadsView*)pChild->GetActiveView();
		pActiveView->TransactCheck ();
		return TRUE;
		
	}
	
	
	else
		return FALSE;
}


void CCheckDoc::OnMultbutHolder()
{
	// TODO: Add your command handler code here
	CDlgSetQuantity dlg;
	dlg.DoModal();
	m_nMultiplicator=dlg.m_nQty;
	OnUpdateMultbutHolder(NULL);
#ifdef OutputDebugString_ENABLED
	OutputDebugString(_T("CCheckDoc::OnMultbutHolder\n"));
#endif
		
}


void CCheckDoc::OnUpdateMultbutHolder(CCmdUI *pCmdUI)
{
		CMainFrame *pMainFrame=static_cast<CMainFrame*>(AfxGetMainWnd());
		const CObList &buttons=pMainFrame->m_wndMultToolBar.GetAllButtons();
		for(POSITION pos=buttons.GetHeadPosition();pos!=nullptr;)
		{
			CMFCToolBarButton* button=DYNAMIC_DOWNCAST(CMFCToolBarButton,buttons.GetNext(pos));
			if(button&&button->m_nID==ID_MULTBUT_HOLDER)
			{
				MultButtonEx* pBtn=DYNAMIC_DOWNCAST(MultButtonEx,button);
				if(pBtn!=NULL){
					CString str;
					str.Format(_T("x%d"),m_nMultiplicator);
					pBtn->SetText(str);
					pBtn->GetParentWnd()->RedrawWindow();
				}
			}
		}
}
