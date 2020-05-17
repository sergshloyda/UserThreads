// MainDocument.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "MainDocument.h"
#include "MainFrm.h"
#include "DocSetter.h"
//#include "BaseRepository.h"
#include "Repository.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDocument




IMPLEMENT_DYNCREATE(CMainDocument, CDocument)

CMainDocument::CMainDocument()
{
	blCatalogOpen=FALSE;
	m_blIsDirty=FALSE;
	m_blKKMOnLine=FALSE;
}

BOOL CMainDocument::OnNewDocument()
{
	EnableAutomation();
	try{
		if (!CDocument::OnNewDocument())
			return FALSE;
		WCHAR buffer[100]={0};
		DWORD size;
		size=sizeof(buffer);
		GetComputerNameW(buffer,&size);
		USES_CONVERSION;
		m_strMachineName =W2A(buffer);
		ReadFonts();
		ReadComPort();
		ReadSettings();
		SHFILEINFO info;
		memset((void*)&info,0,sizeof(SHFILEINFO));
		m_hSysImgLst=(HIMAGELIST)::SHGetFileInfo(_T("c:\\windows"),0,&info,sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX|SHGFI_SMALLICON);
		odslog(L"MainDocument Loaded");
		return TRUE;
	}
	catch(_com_error &err)
	{
		MessageBoxHelper::ShowError(err.Description ());
		return FALSE;
	}
	
}

CMainDocument::~CMainDocument()
{

	
}


BEGIN_MESSAGE_MAP(CMainDocument, CDocument)
	//{{AFX_MSG_MAP(CMainDocument)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()
BEGIN_DISPATCH_MAP(CMainDocument, CDocument)
END_DISPATCH_MAP( )
BEGIN_INTERFACE_MAP(CMainDocument, CDocument)
//INTERFACE_PART(CMainDocument, DIID__IProxiOneCObjectEvents, Dispatch)
END_INTERFACE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainDocument diagnostics

#ifdef _DEBUG
void CMainDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainDocument serialization

void CMainDocument::Serialize(CArchive& ar)
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
// CMainDocument commands

void CMainDocument::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	ImageList_RemoveAll(m_hSysImgLst);
	ImageList_Destroy(m_hSysImgLst);
	//SaveSettings ();
	FontMap::iterator it=m_FontMap.begin();

	for(it;it!=m_FontMap.end();++it){

		LOGFONT logFont;
		it->second->GetLogFont(&logFont);
		AfxGetApp()->WriteProfileBinary(_T("Font"),it->first,(BYTE*)&logFont,sizeof(LOGFONT));
	}
	CDocument::OnCloseDocument();
}



BOOL CMainDocument::SetEnvironmentPoint()
{
		try
    {
		CString strSection       = "Settings";
		CString strStringItem    = "Point";
		// #dlgLoginTask
		CString PointId=	AfxGetApp()->GetProfileString (strSection,strStringItem,_T(""));
		if(PointId.GetLength()==0)
		{
			// #Show_MessageBox_Error
			throw DbContext::DbContextError("В настройках не установлена точка");
		}
		CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
			
			Repository* pRepDoc=CUserThreadsApp::GetDocument<Repository>();
			boost::shared_ptr<Repository::PointsReference> refPoints=pRepDoc->getPoints();
			Repository::ReferenceItem point;
			if(refPoints->FindByAttribute(L"code",_bstr_t(PointId.AllocSysString()))>0)
			{
				point=refPoints->getCurrent();
				m_strCashId=(LPCTSTR)(_bstr_t)point->getAttribute(L"cash");
				m_strPointId=(LPCTSTR)(_bstr_t)point->getAttribute(L"code");
				m_strPointName=(LPCTSTR)(_bstr_t)point->getAttribute(L"descr");
				m_strStockId=(LPCTSTR)(_bstr_t)point->getAttribute(L"stock");
				m_strFirma=(LPCTSTR)(_bstr_t)point->getAttribute(L"firma");
				m_strINN=(LPCTSTR)(_bstr_t)point->getAttribute(L"inn");
				m_strTypePriceId=(LPCTSTR)(_bstr_t)point->getAttribute(L"type_price");
				std::string strCashName=(LPCTSTR)(_bstr_t)(point->getAttribute(L"descr"));
				int nPos=strCashName.find_first_of(" ");
				CString strPrefix=strCashName.substr(nPos+1,1).c_str();
				if(strPrefix==" ")
					throw  DbContext::DbContextError("Не могу расчитать префикс");
				m_strPrefix=strPrefix;
			}
			boost::shared_ptr<Repository::ContragentsReference> refContragents=pRepDoc->getContragents();
			Repository::ReferenceItem contragent;
			if(refContragents->FindByDescr(L"Частное")>0){
				contragent=refContragents->getCurrent();
				m_strContragId=contragent->getAttribute(L"code");
			}

				
		
	
		return TRUE;
			}
		
			catch(DbContext::DbContextError &err)
			{
				CString strMsg;
				strMsg.Format (_T("Error #%08x \nDescription %s \nFrom %s"),err.what(),"","DlgLogin InitInstance");
				MessageBoxHelper::ShowError(strMsg);
				return FALSE;
			}
	

}


void CMainDocument::ReadComPort()
{
 	int nComPort=0;
	TCHAR szComPortSection[] =_T("ComPort");
	TCHAR szComPort[]=_T("ComPort");
	nComPort = AfxGetApp()->GetProfileInt(szComPortSection, szComPort, 1);
	m_strComPort.Format (_T("COM%d"),nComPort);
}

void CMainDocument::SaveFont(LPCTSTR fntName,CFont* pFont)
{
	CString strSection       = "Font1";
	CString strStringItem    = "Font Name";
	CString strIntItem       = "Font Size";
	//CString szBuffer;
	//CMainFrame* pFrame=static_cast<CMainFrame*>(AfxGetMainWnd());
	//if(!IsWindow(pFrame->m_wndFontTB.m_hWnd )) return;
	//szBuffer=pFrame->m_wndFontTB.GetFontName ();
	//
	//int nSize=10;
	//
	//nSize=pFrame->m_wndFontTB.GetFontSize ();
	//
	//AfxGetApp()->WriteProfileString(strSection,strStringItem, szBuffer);
	//AfxGetApp()->WriteProfileInt (strSection,strIntItem,nSize);
}



void CMainDocument::ReadFonts()
{
	LOGFONT log_font;
	afxGlobalData.fontRegular.GetLogFont(&log_font);
	std::shared_ptr<CFont> spDeafaultFont(new CFont());
	spDeafaultFont->CreateFontIndirect(&log_font);
	m_FontMap.insert(std::make_pair(_T("Check"),spDeafaultFont));
	m_FontMap.insert(std::make_pair(_T("Reports"),spDeafaultFont));
	m_FontMap.insert(std::make_pair(_T("Return"),spDeafaultFont));
	std::shared_ptr<CFont> spDlgFont(new CFont());
	spDlgFont->CreateFontIndirect(&log_font);
	m_FontMap.insert(std::make_pair(_T("Dialogs"),spDlgFont));

	HKEY hKey;
	DWORD dwType=0;
	if(RegOpenKey(HKEY_CURRENT_USER,_T("Software\\RUSLAN\\Продажи 1.3\\Font"),&hKey)==ERROR_SUCCESS)
	{

		FontMap::iterator it=m_FontMap.begin();

		for(it;it!=m_FontMap.end();++it){
			DWORD dwSizeLF=sizeof(LOGFONT);
			BYTE* lpFontBynary=new BYTE[dwSizeLF];
			DWORD error=RegQueryValueEx(hKey,it->first,0,&dwType,(LPBYTE)lpFontBynary,&dwSizeLF);
			if (error==ERROR_SUCCESS)
			{
				LOGFONT* pLF=reinterpret_cast<LOGFONT*>(lpFontBynary);
				//CFont* font=new CFont();
				//font->CreateFontIndirect(pLF);
				std::shared_ptr<CFont> spFont(new CFont());
				spFont->CreateFontIndirect(pLF);
				it->second=spFont;
				//m_fntEdit.CreateFontIndirect(pLF);
				//	m_wndSampleText.SetFont(font_map[_T("Grid")].get());
				//delete pLF;

			}
			delete[] lpFontBynary;
		}
	}
	RegCloseKey(hKey);
	//LOGFONT lf;
	//m_FontMap[_T("Dialogs")]->GetLogFont(&lf);

}







//void CMainDocument::LoadCategoryTree()
//{
////	Sleep(2000);
////	HRESULT    hr = S_OK;
//    _RecordsetPtr    pRst  = NULL;
//
//    	//CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
////     int intCommand = 0;
//
//    // Temporary string variable for type conversion .
//    _bstr_t  bstrPartId;
//    _bstr_t  bstrPartName;
//	_bstr_t  bstrPartIdF;
//
//    try
//    {
//	//TESTHR(pApp->pConn.CreateInstance (__uuidof(Connection)));
//		//TESTHR(pApp->pConn->Open ("File Name=..\\data\\connstring.udl","","",adConnectUnspecified));
//			CNodeItem item;
//			_variant_t vtTemp;
//		
//			item.code=L"00000004";
//	
//			item.pcode=L"";
//		
//			item.text=L"Товары";
//			m_dataTree.SetRootData (item);
//		
//			Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
//			boost::shared_ptr<Repository::ProductsReference> prods=pRep->getProducts();
//			populatetree(m_dataTree.GetRootNode (),prods.get());
//
//		
//			
//			//TESTHR(pApp->pConn->Close());
//    }
//    catch (...)
//    {
//   
//    
//           MessageBoxHelper::ShowError(_T("Error occured!!LoadCategoryTree"));
//        
//    }
//
//}

//void CMainDocument::populatetree(CTreeNode *ptrNode,Repository::ProductsReference* pRef)
//{
//	// #populate
//	if(ptrNode!=NULL)
//	{
//
//		std::wstring  code;
//		static BOOL flag=TRUE;
//		CTreeNode* pNode=NULL;
//		_variant_t vtTemp;
//		_bstr_t    bstrTemp;
//		
//		code=ptrNode->item.code ;
//
//		
//		if(pRef->FindByCode(code)>0)
//		{
//			boost::shared_ptr<RefItemV> product,child_product;
//			product=pRef->getCurrent();
//			if(product->IsFolder())
//			{
//				
//				pRef->UseParent(product);
//				
//			
//				if(pRef->SelectItems()>0){
//
//					CWnd* pSplash=CWnd::FindWindow (NULL,_T("Загрузка Продажи 1.3"));
//					do 
//					{
//						
//					
//						child_product=pRef->getCurrent();
//						if(!child_product->IsFolder())continue;
//					
//						
//							CNodeItem item;
//							item.code=child_product->_code;
//							item.text=child_product->_descr;
//							item.pcode=product->_code;
//							if(flag)
//								pNode=m_dataTree.AttachFirstChild (item,ptrNode);
//							else
//								pNode=m_dataTree.AttachNextChild (item,pNode);
//							USES_CONVERSION;
//							LPCTSTR strTemp=W2A(child_product->_descr.c_str());
//							COPYDATASTRUCT MyCDS;
//							MyCDS.dwData =0L;
//							MyCDS.lpData =(PVOID)strTemp;
//							MyCDS.cbData =sizeof(TCHAR)*(_tcslen(strTemp)+1);
//
//
//							if(pSplash&&IsWindow(pSplash->m_hWnd ))
//								pSplash->SendMessage (WM_COPYDATA,NULL,(LPARAM) (LPVOID) &MyCDS);
//							flag=FALSE;
//						
//					} while (pRef->getNext());
//				}
//			}
//			//while(!pRstInt->EndOfFile )
//			//{
//			//	CNodeItem item;
//			//	CString strTemp=_T("");
//
//			//	bstrTemp=pRstInt->Fields ->Item ["CODE"]->Value;
//			//	strTemp=(TCHAR*)bstrTemp;
//			//	strTemp.TrimLeft();
//			//	strTemp.TrimRight ();
//			//	memset(item.code,0,sizeof(item.code ));
//			//	lstrcpy(item.code  ,/*(TCHAR*)b*/strTemp);
//			////	item.Id  =vtTemp.intVal ;
//			//	bstrTemp=pRstInt->Fields ->Item ["PCODE"]->Value;
//			//	strTemp=(TCHAR*)bstrTemp;
//			//	strTemp.TrimRight ();
//			//	strTemp.TrimLeft();
//			//	memset(item.pcode,0,sizeof(item.pcode));
//			//	_tcscpy(item.pcode  ,/*(TCHAR*)b*/strTemp);
//			//	//_tcscpy(item.pcode   ,(TCHAR*)bstrTemp);
//			//	bstrTemp=pRstInt->Fields ->Item ["NAME"]->Value;
//			//	strTemp=(TCHAR*)bstrTemp;
//			//	COPYDATASTRUCT MyCDS;
//			//	MyCDS.dwData =0L;
//			//	MyCDS.lpData =strTemp.GetBuffer (255);
//			//	MyCDS.cbData =255;
//
//
//			//	if(pSplash&&IsWindow(pSplash->m_hWnd ))
//			//	pSplash->SendMessage (WM_COPYDATA,NULL,(LPARAM) (LPVOID) &MyCDS);
//
//			//	strTemp.ReleaseBuffer ();
//			//	strTemp.TrimRight ();
//			//	strTemp.TrimLeft();
//			//	_tcscpy(item.text ,strTemp);
//
//
//			//	pRstInt->MoveNext ();
//			//}
//			//TESTHR(pRstInt->Close ());
//
//			flag=TRUE;
//			populatetree(ptrNode->firstChild,pRef );
//			populatetree(ptrNode->nextChild ,pRef);
//
//		}
//	}
//
//}













void CMainDocument::ReadSettings()

{
	m_blKKMOnLine =TRUE;
	CString strSection       = _T("Settings");
	CString strStringItem    = _T("QUEUEPATHNAME");
	
	m_strQueuePath=	AfxGetApp()->GetProfileString (strSection,strStringItem,_T("SERVER\\BasicQueue"));
	/*strStringItem.Empty();
	strStringItem=_T("cashid");
	m_strCashId=AfxGetApp()->GetProfileString (strSection,strStringItem,_T("300"));*/
		
}


BOOL CMainDocument::CreateQueue()
{
	CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
	CString strSection       = "Settings";
	CString strStringItem    = "QUEUEPATHNAME";
		
	m_strQueuePath=	AfxGetApp()->GetProfileString (strSection,strStringItem,_T("SERVER\\BasicQueue"));
	m_bQueueCreated=FALSE;
	USES_CONVERSION;
	HRESULT hr = S_OK;
	VARIANT varIsTransactional;
    VARIANT varIsWorldReadable;

	try
	{
		IMSMQQueueInfoPtr pQInfo("MSMQ.MSMQQueueInfo");
	//	_bstr_t bstrPath=".\\BasicQueue";
		pQInfo->PutPathName (m_strQueuePath.AllocSysString ());
		VariantInit(&varIsTransactional);
		varIsTransactional.vt = VT_BOOL;
		varIsTransactional.boolVal = MQ_TRANSACTIONAL_NONE;
		VariantInit(&varIsWorldReadable);
		varIsWorldReadable.vt = VT_BOOL;
		varIsWorldReadable.boolVal = TRUE;
		pQInfo->Create (&varIsTransactional,&varIsWorldReadable);
		CComBSTR FormatName;
		FormatName.Attach (pQInfo->GetFormatName ());
		TRACE1("Queue create with format name:%s\n",FormatName);
		m_bQueueCreated=TRUE;
	}
	catch(_com_error &comerr)
	{
	Register::ShowErrorMessage(comerr);
	m_bQueueCreated=FALSE;
	}
	return m_bQueueCreated;
}

BOOL CMainDocument::SendDocIn1CQueue(IUnknown *pDoc,LPCTSTR strLabel)
{
	OutputDebugString(_T("Message Sent 1\n"));
		_bstr_t MessageBody;
			CMainFrame* pMainWnd=(CMainFrame*)AfxGetApp()->GetMainWnd ();
		
	
		USES_CONVERSION;
	try
	{
		/*IMSMQQueueInfoPtr pQInfo("MSMQ.MSMQQueueInfo");
		pQInfo->PutPathName ((_bstr_t)(m_strQueuePath ));*/
		IMSMQQueuePtr pQueue/*=pQInfo->Open (MQ_SEND_ACCESS,MQ_DENY_NONE)*/;
		TESTHR(OpenMyQueue (OLE2W(m_strQueuePath.AllocSysString ()),MQ_SEND_ACCESS,MQ_DENY_NONE,pQueue));
		if(pQueue==NULL)
		{
			AfxMessageBox(_T("Queue not open Doc is not transacted!!!"),MB_ICONSTOP|MB_SETFOREGROUND);
			return FALSE;
		}
		if(strLabel==NULL)
		{
		static int s_cMessageNumber=0;
		WCHAR wcsLabel[MSGLABELSIZE];
		WCHAR buffer[100]={0};
		DWORD size;
		size=sizeof(buffer);
		GetComputerNameW(buffer,&size);
		swprintf(wcsLabel,L"%s_%d",buffer,++s_cMessageNumber);
		
	
		//CComVariant vtBody;
		//CString strMsg=wcsLabel;
		MessageBody=(LPOLESTR)wcsLabel;
		}
		else
		MessageBody=(LPOLESTR)strLabel;
		//vtBody.vt =VT_BSTR;
		//vtBody.bstrVal =BSTR(MessageBody);
		IMSMQMessagePtr pMsg("MSMQ.MSMQMessage");
		pMsg->PutLabel (MessageBody);
		/*IUnknown* pObjUnk;
		pDoc->QueryInterface (__uuidof(IUnknown),(void**)&pObjUnk);
		pMsg->PutBody (pObjUnk);*/
		CComQIPtr<DOC::IValue> spVal(pDoc);
		if(spVal)
		{
			CComBSTR bstrStream;
			spVal->SaveToString(&bstrStream);
			CComVariant val=bstrStream;
			pMsg->PutBody(val);
			OutputDebugString(OLE2A(bstrStream));
		}
		pMsg->Send (pQueue);
		//pObjUnk->Release ();
		OutputDebugString(_T("Message Sent\n"));
		

	return TRUE;
	}
	catch(_com_error &e)
	{
		Register::ShowErrorMessage(e); 
		return FALSE;
	}
	
}









HRESULT CMainDocument::OpenMyQueue(
                    WCHAR *wszPathName,
                    DWORD dwAccessMode,
                    DWORD dwShareMode,
                    IMSMQQueuePtr& pQueue
                    )
{
	USES_CONVERSION;
	// Validate the input string.
		if (wszPathName == NULL)
		{
			return MQ_ERROR_INVALID_PARAMETER;
		}
		
		
		DWORD dwFormatNameLength = 0;
		WCHAR *wszFormatName = NULL;
		
		dwFormatNameLength = wcslen(wszPathName) + 11;
		wszFormatName = new WCHAR[dwFormatNameLength];
		
		
	IMSMQQueueInfoPtr pInfo(L"MSMQ.MSMQQueueInfo");
	IMSMQQueryPtr pQuery("MSMQ.MSMQQuery"); 
    IMSMQQueueInfosPtr pInfos = NULL;
    IMSMQQueueInfoPtr pInfoCurrent = NULL;

   	_variant_t vtLabel(L"1CQueue");



    // Specify the queue label as the search criterion.
    pInfos = pQuery->LookupQueue(&vtMissing, &vtMissing, &vtLabel);
	pInfos->Reset();

    pInfoCurrent = pInfos->Next();

   /* while (pInfoCurrent)
    {
       
        pInfoCurrent = pInfos->Next();
	
    }  */
	pInfo=pInfoCurrent;
	
		
		
		// Create and set the format name of the queue.
		if (wszFormatName)
		{
			memset(wszFormatName, 0, dwFormatNameLength*sizeof(WCHAR));
			
			// ************************************
			// You must concatenate "DIRECT=OS" and wszPathName into the 
			// wszFormatName buffer.
			// wszFormatName = "DIRECT=OS" + wszPathName
			// If the format name is too long for the buffer. return FALSE.
			// ************************************
			CString strPath="DIRECT=OS:";
			strPath+=W2A(wszPathName);
			pInfo->FormatName = OLE2W(strPath.AllocSysString ());
			delete [] wszFormatName;
		}
	//	pInfo->PutPathName(wszPathName);
		
		// Open the queue and pass the smart pointer returned by reference.
		pQueue = pInfo->Open(dwAccessMode, dwShareMode);

	return S_OK;
}


HRESULT CMainDocument::CreateObjRefDispName(IUnknown *pUnk, BSTR *bsDN)
{
	   OutputDebugString(_T("Enter CreateObjRefDispName"));
	   HRESULT hr=S_OK;
	   HINSTANCE hDLL = LoadLibrary(_T("OLE32.DLL"));
	   BSTR bstrDispName;
	   IBindCtx* pbc=NULL; 
	   IMoniker* pmk=NULL;
	   if(NULL == hDLL)
	   {
		   // See Winerror.h for explanation of error code.
		   DWORD error = GetLastError();
		   OutputDebugString(_T("LoadLibrary() Failed with, error"));
		   return FALSE;
	   } 
	   pUnk->AddRef ();
	   LPFUNCCREATEOBJREFMONIKER pfnCreateObjrefMoniker=NULL;
	   pfnCreateObjrefMoniker=(LPFUNCCREATEOBJREFMONIKER)GetProcAddress(hDLL,"CreateObjrefMoniker");
	   OutputDebugString(_T("After GetProcAddress"));
	   if (pfnCreateObjrefMoniker==NULL)
	   {
		   hr=256L;
	   }
	   else
	   {
		   
		 
		   if SUCCEEDED(hr = pfnCreateObjrefMoniker(pUnk, &pmk))
		   {
			  OutputDebugString(_T("SUCCEEDED(hr = pfnCreateObjrefMoniker"));
			  
			   if SUCCEEDED(hr = CreateBindCtx(0, &pbc))
			   {
				   OutputDebugString(_T("SUCCEEDED CreateBindCtx(0, &pbc))"));
				   LPOLESTR pszDN=NULL;
				   hr = pmk->GetDisplayName(pbc,NULL,&pszDN);
				   if(hr==S_OK)
				   {
					   TCHAR szMessage[10024]={0};
					   wsprintf(szMessage,_T("SUCCEEDED GetDisplayName bsDN %ls"),pszDN);
					   bstrDispName=::SysAllocString (pszDN);
					   CoTaskMemFree (pszDN);
			
					   USES_CONVERSION;
					 
					   
					   
					   
					   OutputDebugString(szMessage );
				   }
			   }
		   }
	   }
	   if(pbc)
	   pbc->Release();
	   if(pmk)
	   {
		   
		   pmk->Release();
	   }

  *bsDN=bstrDispName;
OutputDebugString(_T("Leave CreateObjRefDispName" ));

	   return hr;
}





HRESULT CMainDocument::SendDataInQueue(BSTR bstrData, LPCTSTR strLabel)
{
	
	_bstr_t MessageBody;
	CMainFrame* pMainWnd=(CMainFrame*)AfxGetApp()->GetMainWnd ();
	OutputDebugString(_T("Message Sent 2\n"));
	
	USES_CONVERSION;

	/*IMSMQQueueInfoPtr pQInfo("MSMQ.MSMQQueueInfo");
		pQInfo->PutPathName ((_bstr_t)(m_strQueuePath ));*/
		IMSMQQueuePtr pQueue/*=pQInfo->Open (MQ_SEND_ACCESS,MQ_DENY_NONE)*/;
		TESTHR(OpenMyQueue (OLE2W(m_strQueuePath.AllocSysString ()),MQ_SEND_ACCESS,MQ_DENY_NONE,pQueue));
		if(pQueue==NULL)
		{
			AfxMessageBox(_T("Queue not open Doc is not transacted!!!"),MB_ICONSTOP|MB_SETFOREGROUND);
			return E_FAIL;
		}
		if(strLabel==NULL)
		{
			static int s_cMessageNumber=0;
			WCHAR wcsLabel[MSGLABELSIZE];
			WCHAR buffer[100]={0};
			DWORD size;
			size=sizeof(buffer);
			GetComputerNameW(buffer,&size);
			swprintf(wcsLabel,L"%s_%d",buffer,++s_cMessageNumber);
			
			
			//CComVariant vtBody;
			//CString strMsg=wcsLabel;
			MessageBody=(LPOLESTR)wcsLabel;
		}
		else
			MessageBody=(LPOLESTR)strLabel;
		//vtBody.vt =VT_BSTR;
		//vtBody.bstrVal =BSTR(MessageBody);
		IMSMQMessagePtr pMsg("MSMQ.MSMQMessage");
		pMsg->PutLabel (MessageBody);
		/*IUnknown* pObjUnk;
		pDoc->QueryInterface (__uuidof(IUnknown),(void**)&pObjUnk);
		pMsg->PutBody (pObjUnk);*/
			OutputDebugString(OLE2A(bstrData));
		CComVariant val=bstrData;
		pMsg->PutBody(val);
		
		pMsg->Send (pQueue);
		::SysFreeString(bstrData);
		//pObjUnk->Release ();
		OutputDebugString(_T("Message Sent\n"));

	
	
	return S_OK;
	
}
