// 1CHelper.cpp: implementation of the C1CHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "userthreads.h"
#include "1CHelper.h"
#include <objbase.h>
#include <comdef.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C1CHelper::C1CHelper()
{
/*	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		AfxMessageBox("���������� ���������������� COM!");
	
	}*/
}

C1CHelper::~C1CHelper()
{
/*	if (pv77)
			pv77->Release();
		CoUninitialize();
		*/
}

BOOL C1CHelper::Open1C(BSTR bstrParam)
{
	
	//��� ������ �������������� COM
	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("���������� ���������������� COM!"));
		return FALSE;
	}
	
	/*
	������ �����, ��� ���������� ��������
	 ID ������� OLE Automation 1� �����������.
	*/
	CLSID   cls77;
	
	/*
	���������� ������������� ���� 1� ����������� 
	
	  ��������� ��. ��� � ���� � ��� ����������� ������������ 
		������ 1� � �� ����� ����������, ���� ��������� ������, 
		�� ����� ��������� ������. ��� ������� ������ ��������� ��������:
		
		  V1CEnterprise.Application - ������ ����������� ����;
		  V77.Application - ������ ��������� ����;
		  V77S.Application - ������ ��������� ����, SQL-������;
		  V77L.Application - ������ ��������� ����, ���������-������;
		  V77M.Application - ������ ��������� ����, �������-������.
	*/
	
	hr = CLSIDFromProgID(L"V77.Application", &cls77); 
	if(FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("�������������� 1� �����������!"));
		CoUninitialize();
		return FALSE;
	}
	
	//�������� ���������, �� ������� �� ����� "������"
	IDispatch *pv77;
	
	/*
	������ ��������� 1� �����������. 
	
	  CLSCTX_LOCAL_SERVER � ��� ������, ��� 1� ����������� 
	  ����� �������� � ���� ���������� �������� � �� ������� ��� �� �����.
	*/
	
	hr = CoCreateInstance(cls77, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&pv77);
	
	if(FAILED(hr)  ||  !pv77)
	{
		MessageBoxHelper::ShowError(_T("���������� ���������������� ��������� 1� �����������")); 
		CoUninitialize();
		return FALSE;
	}
	
	/*
	���� �� ���� ������� � ��������, ������ ���������� ��������� 
	  1� ������������� ��� ������� ���������� ������� Initialize. 
	  ����� ���� ������� �������� � VB �����������
	  
		V7.Initialize(V7.RMTrade,"D:\1C\�������� /N"+������������ ,"NO_SPLASH_SHOW");
		
		  - �� ����������� ��������, ��� �� ���������� ������.
		  �� ������������ �++ ���� �������������, ���������� �� ������. 
			 ��-������: �� ������ �������, ��� ��������� ���������� ����������� ����� ������
			 ��-������: �� ������ �������, ��� RMTrade - ��� ���� IDispatch ���������.. � ��� ������ ����� ��������.
	*/
	
	VARIANT       vRet;
	DISPID dispIDRmTrade, dispIDInitialize;
	DISPPARAMS args = {0, 0, 0, 0};
	VARIANT vars[3];  // ��������� ��� ������ Initialize
	
	//�� ������� IDispatch ��������� �� RMTrade ����� � vars[2]
	
	BSTR rmTrade = L"RMTrade";
	
	hr = pv77->GetIDsOfNames(IID_NULL, &rmTrade, 1, 0, &dispIDRmTrade);
	
	if (FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("���������� �������� ID �� RMTrade"));
		if (pv77)
			pv77->Release();
		CoUninitialize();
		return FALSE;
	}
	
	hr = pv77->Invoke(dispIDRmTrade, IID_NULL, 0, DISPATCH_PROPERTYGET, &args,
		&vars[2], NULL, NULL);
	
	if (FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("���������� �������� ��������� �� RMTrade"));
		if (pv77)
			pv77->Release();
		CoUninitialize();
		return FALSE;
	}
	
	//����� �������� ID ��� Initialize(..);
	BSTR init = L"Initialize";
	hr = pv77->GetIDsOfNames(IID_NULL, &init, 1, 0, &dispIDInitialize);
	if (FAILED(hr))
	{
		MessageBoxHelper::ShowError (_T("�� ������� �������� ID �� Initialize"));
		if (pv77)
			pv77->Release();
		CoUninitialize();
		return FALSE;
	}
	
	/*
	� ������ � ������� ���� ����� Initialize(..), 
	�� ������ ���������� ��������� ������ ���������� �������
	*/
	
	args.cArgs = 3;
	args.rgvarg = vars;
	vars[0] = _variant_t("NO_SPLASH_SHOW");
	vars[1] = _variant_t("/D C:\\TS\\DistrDB /N Test ");
	
	/*
	vars[2] � � ��� ��� ����, �� ��� �������� ��� ������� 
	���������� RMTrade � ������ ����������� Invoke
	*/
	
	hr = pv77->Invoke(dispIDInitialize, IID_NULL, 0, DISPATCH_PROPERTYGET, &args, 
		&vRet, NULL, NULL);
	
	if(FAILED(hr) ||  (vRet.vt ==  VT_BOOL && vRet.bstrVal == 0x00))
	{
		MessageBoxHelper::ShowError(_T("���������� ��������� 1� �����������"));
		return FALSE;
		
	}
	return TRUE;
}



BOOL C1CHelper::Open1CEx(const CString &strPath, const CString& strUser, const CString& strPassword)
{
	
	BYTE *parms;
		CString strSection       = "";
	CString strStringItem    = "1CProgID";
	
	 CString strProgID=	AfxGetApp()->GetProfileString (strSection,strStringItem,_T("V77S.Application"));
 
		if (drvApp.CreateDispatch(strProgID))
		{
			CString strRMTrade("RMTrade");     
			BSTR rmTrade = strRMTrade.AllocSysString() ;
			
			DISPID id_rmtrade=0;
			HRESULT hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&rmTrade,1,LOCALE_SYSTEM_DEFAULT,&id_rmtrade);
			::SysFreeString (rmTrade);
			if(hr!=S_OK || id_rmtrade==0 || id_rmtrade==-1)
			{
				AfxMessageBox(_T("������ 1C �� ������\n"),MB_ICONSTOP);
				return FALSE ;
			}
			// � �������� ��� ��������
			long RMTrade=0;
			drvApp.GetProperty(id_rmtrade,VT_I4,&RMTrade);
			
			// ������ ���� ������������������� 1�
			
			BOOL init;
			
			// ������� ID ������ Initialize
			CComBSTR name=_T("Initialize");
			DISPID id_init=0;
			hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_init);
			// ���� � ���� ������ 1�
			CString strCommand;
			strCommand.Format (_T("/D %s /N %s /P %s"),strPath,strUser,strPassword);
			// �������������� ��������, �������� NO_SPLASH_SHOW - �� ���������� �������� ��� �������� 1�
			CString strEmpty="NO_SPLASH_SHOW";
			// ��������� ������ ������ Initialize
			parms=(BYTE*)(VTS_I4 VTS_BSTR VTS_BSTR);
			drvApp.InvokeHelper(id_init,DISPATCH_METHOD,VT_BOOL,&init,parms,RMTrade,(void*)(LPCTSTR)strCommand,(void*)(LPCTSTR)strEmpty);
			if(init==FALSE)
			{
				AfxMessageBox(_T("���� �� ���������"),MB_ICONSTOP|MB_TOPMOST | MB_SETFOREGROUND | MB_OK);

				return FALSE;
			}
 

			return TRUE;
		}
		return FALSE;
	
}
/*������� ���������������������������(������,�������,��������,��������,�����������,�������������)
	����� ���,�����������,��������,�����������,�������������,���������,����,����������;
	
	���=�������������("XBase");
	�����������=�������������("��������.��������");
	
	���� �����������.�������������(������,�������)=0 �����
		
		��������=�������������("����������.�����");
		�����������=�������������("����������.���������");
		�������������=�������������("����������.�����������");
		���������=�������������("����������.������");
		���������������=�������������("����������.������������");
		����������=�������������("��������������");
		����=0;
		
		���� ��������.�����������(��������,0)=0 �����
			��������("����� � �����: "+ ��������+ "  �� �������","!!!");
			������� 0;
		���������;
		���� 	�����������.�����������(�����������,0)=0 �����
			��������("�������� � �����: "+ �����������+ "  �� ������","!!!");
			������� 0;
		���������;
		���� �������������.�����������(�������������,0)=0 �����
			��������("���������� � �����: "+ �������������+ "  �� ������","!!!");
			������� 0;
		���������; 
		���� ���������.�����������("810",0)=0 �����
			��������("������ � �����: 810  �� �������","!!!");
			������� 0;
		���������;
		
		����������.����������������("����",0);
		����������.����������������("������",0);
		����������.����������������("�������",0);
		�����������������(��������,":",����������);
		���=0;
		������=0;
		�������=0;
		���=����������.��������("����");
		������=����������.��������("������");
		�������=����������.��������("�������");
		
		���.�����������(���������+"\TZREPIMP.DBF");
		���� ���.�������()=0 �����
			��������������("�� ������� ������� ���� ������� ������� �� �����");
			������� 0;
		���������;
		���.���������������(0);
		���.������();
		���.�������������������(0);
		
		�����������.�����();
		�����������.��������=������;
		�����������.�������=�������;
		�����������.������������������();
		�����������.���������������(���,������,�������);
		�����������.�����=��������.��������������();
		�����������.��������=�����������.��������������();
		�����������.����������=�������������.��������������();
		�����������.������=���������.��������������(); 
		���������.����������������(�������);
		�����������.����=���������.����;
		�����������.������=��������.������;
		�����������.������������=1;
		�����������.�����������=1;
		�����������.�����������=0;
		�����������.����������=0;
		���� ���.������()=0 ����
			���� ���.docid=������ �����
				����=1;
				�����������.�����������();
				���� ���������������.�����������(���.nomenid,0)=1 �����
					�����������.������������=���������������.��������������();
					�����������.����������=���.qty;
					�����������.�����������=���������������.����������������;
					�����������.����=���.price;
					�����������.�����=���.qty*���.price;
					�����������.���������=���.checkid;
					�����������.���������=���.checktime;
					�����������.����������������������� = ���������������.�����������������������;
				    �����������.���������������=���������������.���������������;
					�����������.�������������������=����������������������();
				���������;
				//��������(�������);
				//��������(���.docid+ "  |  " + ���.checkid + "  |  " + ���.nomenid + "  |  "+ ������(���.qty) + "  |  "+ ������(���.price) + "  |  "+ ������(���.checkdate) + "  |  " + ������(���.checktime) );
				//��������(���.checktime);
			���������; 
			���.���������();
		����������;
		���� ����=1 �����
			�����������.��������();
		���������;
		���.�����������();
	�����
		��������("�������� � �������: "+ ������+ "  ����������","!!!");
		
	���������;
������������*/
BOOL C1CHelper::SaveZReportIn1C(const CString& strNumDoc,  const COleDateTime& tmTimeDoc,
								const CString& strNumPoint,const CString& strEmpl,
								const CString& strCust,    VARIANT* vtArray)
{
	//�� ��������!!!!
	
	
    // ������� ID ������ CreateObject
	BYTE *parms;
	
	
		CComBSTR name=_T("CreateObject");
		DISPID id_create=0;
		HRESULT    hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_create);
		
		// ��������� �� ������, ������� ���� ��������
		IDispatch *pZRT=NULL;
		// ��������� ������ ������ CreateObject
		parms=(BYTE*)(VTS_BSTR);
		// ��� �������
		CString strZRT="��������.��������";
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pZRT,parms,(void*)(LPCTSTR)strZRT);
		if(pZRT==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}
		
		COleDispatchDriver drvZRT;
		drvZRT.AttachDispatch(pZRT);
		// drvZRT - � ���� ��� �������� ��������
		//�����������=�������������("��������.��������");
		//���� �����������.�������������(������,�������)=0 �����
		//���� ��� ������ 0 ��� ������ �� ���� ���������
		COleDateTime tmNow=COleDateTime::GetCurrentTime();
		
		CString strExpr=_T("");
		strExpr.Format (_T("Date('01/01/%d')"),tmNow.GetYear ());
		name=_T("EvalExpr");
		DISPID id_Eval=0;
		hr=drvApp.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Eval);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR );
		CString pDate;
		drvApp.InvokeHelper(id_Eval,DISPATCH_METHOD,VT_BSTR,&pDate,parms,(void*)(LPCTSTR)strExpr);

		name="�������������";
		DISPID id_Find=0;
		hr=drvZRT.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Find);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR VTS_BSTR VTS_BSTR);
		BOOL  ret;

		drvZRT.InvokeHelper (id_Find,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strNumDoc,(void*)(LPCTSTR)pDate,_bstr_t(L"��������"));
		if(ret)
		{
			AfxMessageBox(_T("�������� � ����� ������� ��� ����������"),MB_ICONSTOP);
			return FALSE;
		}
		return TRUE;
	
}
/*******************************************    
������� ��������������(�����,�����,������,���������) 
	����� �����,������,����,���������,��������;

	����=�������������("����������.������������");
	���� ����.�������������������(���������������(),0)=1   ����� 
	������.�����=����.�������������;
	������.�����=����.��������������();
���������;

	��������=�������������("����������.�������������");
	���� ��������.�����������(�����,0)=1 ����� 
		������.�����=��������.��������������().�����;
		������.�����=��������.��������������().�������������;  
	���������;
	������=�������������("����������.������");
	���� ������.�������������������("���",0)=1  �����
		������.������=������.��������������();
		������.����=1;
		������.���������=1;
		������.��������=0;
	���������;
    ������.�����������=������������.������������������.���;
	������.������������=���������;
	������.������������=0;
	������.������=����������������������();
	������.������������=����������������������();
	������� 1;
������������ 

������� �������������(��������,���������,�����������)
	��� = 0;
	
	���������� = �������������("����������.�������");
	��������   = �������������("����������.������������");
	���� ����������.����������������("��������", ��������, 1) = 1 �����
		���������	= ����������.��������;
		�����������	= ����������.��������������();
		���         = 1;

	���������;	
    
	������� ���;
������������ // �������������()



��������� ������������()
	����� ������,���������,�����������;
     ��������= "9785845901224";
	������=�������������("��������.������");
	������� = ������������();
	������.�������������(�������);
	������.�����();

	��������������(1,"C0004",������,123456);
	
	������.�����������();
	���� �������������(������(��������), ���������, �����������) = 1 �����
			������.������������ = ���������;
			������.��������=��������;
			������.�������      = �����������;
			������.�����������  = �����������.�����������;
			������.����=140;
			������.�����=140;
			������.����������=1;
			������.��������();
            ������.��������();
		�����
			��������������("����� �� �����-����� "+������(��������)+" �� ������!", 60);
		
		���������


	
��������������
 *************************************************************************************/
BOOL C1CHelper::SaveCheckIn1C(const CString &strPointName, const CString &strUser, int nCheckNum,VARIANT* vtArray)
{
	//����������� ���
	AfxGetApp()->BeginWaitCursor ();
		BYTE *parms;
	//*������=�������������("��������.������");
		COleException e ;
  
  try {

		CComBSTR name=_T("CreateObject");
		DISPID id_create=0;
		HRESULT    hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_create);
		TESTHR(hr);
		// ��������� �� ������, ������� ���� ��������
		IDispatch *pDocCheck=NULL;
		// ��������� ������ ������ CreateObject
		parms=(BYTE*)(VTS_BSTR);
		// ��� �������CString strZRT="��������.��������";
		CString strDocCheck=_T("��������.������");
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pDocCheck,parms,(void*)(LPCTSTR)strDocCheck);
		
		if(pDocCheck==NULL)
		{
			TRACE0("������ �� ������\n");
			
			
			return FALSE;
		}
		COleDispatchDriver drvDocCheck;
		drvDocCheck.AttachDispatch(pDocCheck);
	
	//*������� = ������������()**********************************************************************
		name=_T("EvalExpr");
		DISPID id_Eval=0;
		hr=drvApp.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Eval);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR );
		CString strPrefixDoc;
		CString strExpr=_T("������������()");
		drvApp.InvokeHelper(id_Eval,DISPATCH_METHOD,VT_BSTR,&strPrefixDoc,parms,(void*)(LPCTSTR)strExpr);

	//** ������.�������������(�������)***************************************************************
		name=_T("�������������");
		DISPID id_Prefix=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Prefix);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR );
		CString strPrefixBefore;
		strPrefixDoc.TrimRight ();
		drvDocCheck.InvokeHelper(id_Prefix,DISPATCH_METHOD,VT_BSTR,&strPrefixBefore,parms,(void*)(LPCTSTR)strPrefixDoc);
//*  ������.����������������();****************************************************************************
		name=_T("����������������");
		DISPID id_AutoTime=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_AutoTime);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_AutoTime,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
    //*  ������.�����();****************************************************************************
		name=_T("�����");
		DISPID id_New=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_New);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_New,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);

	//***����=�������������("����������.������������");

		CString strUSR=_T("����������.������������");
		IDispatch *pUSR=NULL;
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pUSR,parms,(void*)(LPCTSTR)strUSR);
		
		if(pUSR==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}
	
		COleDispatchDriver drvUSR;
		drvUSR.AttachDispatch(pUSR);
	//**���� ����.�������������������(���������������(),0)=0   ����� �������;
		name=_T("�����������");
		DISPID id_FindByName=0;
		hr=drvUSR.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_FindByName);
		BOOL ret=FALSE;
		parms=(BYTE*)(VTS_BSTR VTS_I4);
		int nFlag=0;
		
		drvUSR.InvokeHelper(id_FindByName,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strUser,nFlag);
		if(!ret)
			return FALSE;

	//**������.�����=����.�������������;
		//������� ������� �������� ������������� � ����
		name=_T("�������������");
		DISPID id_BaseFirma=0;
		hr=drvUSR.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_BaseFirma);
	 	TESTHR(hr);
		IDispatch *pBaseFirma=NULL;//�������� ������������� � ����
		drvUSR.GetProperty(id_BaseFirma,VT_DISPATCH,(void*)&pBaseFirma);
		COleDispatchDriver drvFirma;
		drvFirma.AttachDispatch(pBaseFirma);
		//������ ��������� �������� ����� ��� ���������
		name=_T("�����");
		_variant_t vt;
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pBaseFirma;
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
		
		/*DISPID id_Firma=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Firma);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_Firma,VT_DISPATCH,(LPDISPATCH)drvFirma);//������.�����=����.�������������;
	*/
	//*������.�����=����.��������������();
			name=_T("��������������");

		DISPID id_current=0;
		hr=drvUSR.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_current);
		TESTHR(hr);
		// ��������� �� ������, ������� ���� ��������
		IDispatch *pCurUser=NULL;
	
		
		drvUSR.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurUser,NULL,NULL);
		
		if(pCurUser==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}
		name=_T("�����");
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pCurUser;

	/*	DISPID id_Avtor=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Avtor);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_Avtor,VT_DISPATCH,drvUSR.m_lpDispatch );//������.�����=����.��������������();
*/
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
			
	//*��������=�������������("����������.�������������");
		CString strPoints=_T("����������.�������������");
		IDispatch *pPoints=NULL;
		parms=(BYTE*)(VTS_BSTR );
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pPoints,parms,(void*)(LPCTSTR)strPoints);
		
		if(pPoints==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}
	
		COleDispatchDriver drvPoints;
		drvPoints.AttachDispatch(pPoints);

	
	//*���� ��������.�����������(�����,0)=1 �����
		name=_T("�������������������");
		DISPID id_FindByCode=0;
		hr=drvPoints.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_FindByCode);
		ret=FALSE;
		parms=(BYTE*)(VTS_BSTR VTS_I4);
		nFlag=0;
		CString		strPName=strPointName;
		strPName.TrimRight ();
		drvPoints.InvokeHelper(id_FindByCode,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strPName,nFlag);
		if(!ret)
			return FALSE;

	//*������.�����=��������.�����;
		//������� ������� �������� ����� � �����
		name=_T("�����");
		DISPID id_StockGet=0;
		hr=drvPoints.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_StockGet);
	 	TESTHR(hr);
		IDispatch *pStockProp=NULL;//�������� �������� ����� � �����
		drvPoints.GetProperty(id_StockGet,VT_DISPATCH,(void*)&pStockProp);
		//������ ��������� �������� ����� ��� ���������
		name=_T("�����");
		/*
		DISPID id_StockSet=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_StockSet);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_StockSet,VT_DISPATCH,pStockProp);//������.�����=��������.�����;
		*/
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pStockProp;
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
	//*������.�����=��������.�������������;  
		//������� ������� �������� ����� � �����
	
		name=_T("�������������");
		DISPID id_CashGet=0;
		hr=drvPoints.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CashGet);
	 	TESTHR(hr);
		IDispatch *pCashProp=NULL;//�������� ����� � �����
		drvPoints.GetProperty(id_CashGet,VT_DISPATCH,(void*)&pCashProp);
		//������ ��������� �������� ����� ��� ���������
		name=_T("�����");
		/*
		DISPID id_CashSet=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CashSet);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_CashSet,VT_DISPATCH,pCashProp);//������.�����=��������.�������������; 
*/
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pCashProp;
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
	
	//*������=�������������("����������.������");
		CString strCurr=_T("����������.������");
		IDispatch *pCurr=NULL;
		parms=(BYTE*)(VTS_BSTR );
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pCurr,parms,(void*)(LPCTSTR)strCurr);
		
		if(pCurr==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}
	
		COleDispatchDriver drvCurrs;
		drvCurrs.AttachDispatch(pCurr);

	
	//*���� ������.�������������������("���",0)=1
		name=_T("�������������������");
		DISPID id_CurrFindByName=0;
		hr=drvCurrs.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CurrFindByName);
		ret=FALSE;
		parms=(BYTE*)(VTS_BSTR VTS_I4);
		nFlag=0;
		CString strCurrName=_T("���");
		drvCurrs.InvokeHelper(id_FindByCode,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strCurrName,nFlag);
		if(!ret)
			return FALSE;

	//*������.������=������.��������������();

		name=_T("��������������");

		id_current=0;
		hr=drvCurrs.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_current);
		TESTHR(hr);
		// ��������� �� ������, ������� ���� ��������
		IDispatch *pCurValuta=NULL;
	
		
		drvCurrs.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurValuta,NULL,NULL);
		
		if(pCurValuta==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}

		name=_T("������");
		/*
		DISPID id_CurrSet=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CurrSet);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_CurrSet,VT_DISPATCH,drvCurrs.m_lpDispatch );//������.������=������.��������������();
*/
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pCurValuta;
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
	
	//*������.����=1;
		name=_T("����");
		DISPID id_Curs=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Curs);
	 	TESTHR(hr);
		int nKurs=1;
		drvDocCheck.SetProperty(id_Curs,VT_I4,nKurs );

	//*������.���������=1;
		name=_T("���������");
		DISPID id_Kratnost=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Kratnost);
	 	TESTHR(hr);
		int nKratnost=1;
		drvDocCheck.SetProperty(id_Kratnost,VT_I4,nKratnost );

	//*������.��������=0;
		name=_T("��������");
		DISPID id_Nal=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Nal);
	 	TESTHR(hr);
		double dblNal=0.0;
		drvDocCheck.SetProperty(id_Nal,VT_R8,dblNal );

	//*������.�����������=������������.������������������.���;
		_variant_t vtCheck;
		strExpr=_T("������������.������������������.���");
		parms=(BYTE*)(VTS_BSTR);
		drvApp.InvokeHelper(id_Eval,DISPATCH_METHOD,VT_VARIANT,&vtCheck,parms,(void*)(LPCTSTR)strExpr);

		name=_T("�����������");
		DISPID id_VidOper=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_VidOper);
	 	TESTHR(hr);
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vtCheck))
			return FALSE;

	//*������.������������=���������;
		name=_T("������������");
		DISPID id_NomCheck=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_NomCheck);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_NomCheck,VT_I4,nCheckNum);

	//*������.������������=0;
		name=_T("������������");
		DISPID id_CheckKKM=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CheckKKM);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_CheckKKM,VT_I4,0);

	
		//*���������� = �������������("����������.�������");
		CString strUnits=_T("����������.�������");
		parms=(BYTE*)(VTS_BSTR);
		IDispatch *pUnits=NULL;
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pUnits,parms,(void*)(LPCTSTR)strUnits);
		if(pUnits==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}
		COleDispatchDriver drvUnits;
		drvUnits.AttachDispatch(pUnits);

	//*	��������   = �������������("����������.������������");
		CString strTovary=_T("����������.������������");
		parms=(BYTE*)(VTS_BSTR);
		IDispatch *pGoods=NULL;
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pGoods,parms,(void*)(LPCTSTR)strTovary);
		if(pGoods==NULL)
		{
			TRACE0("������ �� ������\n");
			return FALSE;
		}
		COleDispatchDriver drvGoods;
		drvGoods.AttachDispatch(pGoods);

		//*����� �� ������� ���� �� ����

		COleSafeArray sa;
		sa.Attach (*vtArray);
		//sa.Attach (vtArray);
		long lNumRows;
		long lNumCols;
		sa.GetUBound(1, &lNumRows);
		sa.GetUBound(2, &lNumCols);
		
		//Display the elements in the SAFEARRAY.
		long index[2];
	
		
		//Determine upper bounds for both dimensions
		long r, c;
		sa.GetLBound(1, &r);
		sa.GetLBound(2, &c);
		
		for(;r <= lNumRows; r++ )
		{
			_variant_t val;
			CComBSTR bstrMethod;
			//*������.�����������();
			name=_T("�����������");
			DISPID id_NewLine=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_NewLine);
			TESTHR(hr);
			drvDocCheck.InvokeHelper(id_NewLine,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
			
			
			index[0]=r;
			index[1]=lNumCols;
			sa.GetElement(index, &val);//��� ������
			//*���� ��������.�����������(���, 0) = 1 �����
			bstrMethod=_T("�����������");
			DISPID id_FindByCode=0;
			HRESULT hr=drvGoods.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_FindByCode);
			BOOL ret=FALSE;
			BYTE* parms=(BYTE*)(VTS_BSTR VTS_I4);
			nFlag=0;
			CString		strCode=(LPCTSTR)(_bstr_t)val;
			strCode.TrimRight ();
			drvGoods.InvokeHelper(id_FindByCode,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strCode,nFlag);
			if(!ret)
			{
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				AfxThrowOleDispatchException(1001, 
					_T("�� ����� ����� �� ����"));
				
			}
			//::VariantClear(&val);//�� ���� ������

			//*������.������������ = ��������.��������������()
			bstrMethod=_T("��������������");

			DISPID id_current=0;
			hr=drvGoods.m_lpDispatch->GetIDsOfNames(IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_current);
			TESTHR(hr);
			// ��������� �� ������, ������� ���� ��������
			IDispatch *pCurGood=NULL;
			drvGoods.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurGood,NULL,NULL);
			if(pCurGood==NULL)
			{
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				TRACE0("������ �� ������\n");
				return FALSE;
			}
		
			bstrMethod=_T("������������");
			_variant_t vt;
			vt.vt =VT_DISPATCH;
			vt.pdispVal= pCurGood ;
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,bstrMethod,vt))
				return FALSE;

		//*������.��������=��������;
			CString strBarCode=_T("");
			index[1]=0L;
			sa.GetElement (index,&val);
			CComBSTR bstrBarcode;
			hr=::VarBstrFromR8(val.dblVal,LOCALE_SYSTEM_DEFAULT,LOCALE_NOUSEROVERRIDE,&bstrBarcode);
			if (hr)
				AfxThrowOleDispatchException(1001, 
				_T("Ytghfdbkmyj ds,hfy byltrc vfccbdb BarCode �� ������"));
			strBarCode=(LPCTSTR)(_bstr_t)bstrBarcode;
			int nPos=strBarCode.FindOneOf (_T(",."));
			if(nPos!=-1)
			{
			strBarCode.Remove ('.');
			strBarCode.Remove (',');
			}
			if(strBarCode.GetLength ()<13)
			{
				int append=13-strBarCode.GetLength ();
				for(int i=0;i<append;i++)
					strBarCode.Insert (i,_T("0"));
			}
			bstrMethod=_T("��������");
			DISPID id_BarCode=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_BarCode);
	 		TESTHR(hr);
			drvDocCheck.SetProperty(id_BarCode,VT_BSTR,(void*)(LPCTSTR)strBarCode );
		
		//*���� ����������.����������������("��������", ��������, 1) = 1 �����
			bstrMethod=_T("����������������");
			DISPID id_FindByAttribute=0;
			hr=drvUnits.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_FindByAttribute);
	 		if(hr!=S_OK)
			{		//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
					AfxThrowOleDispatchException(1001, 
					_T("����������������"));
			}
			ret=FALSE;
			parms=(BYTE*)(VTS_BSTR VTS_BSTR VTS_I4);
			nFlag=1;
			CString strParamether=_T("��������");
			strBarCode.TrimRight ();
			
			drvUnits.InvokeHelper(id_FindByAttribute,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strParamether,(void*)(LPCTSTR)strBarCode,nFlag);
			if(!ret)
			{
					//pCurGood->Release  ();
				CString msg;
				msg.Format (_T(" ����� �� ������� %d � ���������� %s �� ����� ������� ��������.\n������� ��� � ������������� ���."),r+1,strBarCode);
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				AfxThrowOleDispatchException(10010, 
				msg);
			}

			bstrMethod=_T("��������������");

			id_current=0;
			hr=drvUnits.m_lpDispatch->GetIDsOfNames(IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_current);
			TESTHR(hr);
			// ��������� �� ������, ������� ���� ��������
			IDispatch *pCurUnit=NULL;
			drvUnits.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurUnit,NULL,NULL);
			if(pCurUnit==NULL)
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
			AfxThrowOleDispatchException(1001, 
					_T("������ �� ������"));
			}
				
		
			/*COleDispatchDriver drvBaseUnit;
			drvBaseUnit.AttachDispatch(pBaseUnit);*/
			bstrMethod=_T("�������");
			vt.vt =VT_DISPATCH;
			vt.pdispVal= pCurUnit;
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,bstrMethod,vt))
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				AfxThrowOleDispatchException(1001, 
					_T("�����.�������������� �� �����������"));
			}

		//*������.�����������  = �����.��������������.�����������;
			bstrMethod=_T("�����������");
			DISPID id_Coeff=0;
			hr=pCurUnit ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Coeff);
	 		if(hr!=S_OK)
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
					AfxThrowOleDispatchException(1001, 
					_T("��������������.�����������;"));
			}
			int nCoeff=1;
			//drvBaseUnit.GetProperty(id_Coeff,VT_I4,(void*)&nCoeff);

			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Coeff);
	 		if(hr!=S_OK)
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
					AfxThrowOleDispatchException(1001, 
					_T("������.�����������;"));
			}
			drvDocCheck.SetProperty(id_Coeff,VT_I4,nCoeff);

		//*	������.����������=Kol;
			bstrMethod=_T("����������");
			DISPID id_Qty=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Qty);
	 		TESTHR(hr);
			double dblQty=0L;
			index[1]=4L;
			sa.GetElement(index, &val);
			dblQty=val.dblVal ;
			//::VariantClear(&val);
			drvDocCheck.SetProperty(id_Qty,VT_R8,dblQty);


		//*	������.����=140;
			double dblPrice=0.0;
			index[1]=2L;
			sa.GetElement(index, &val);
			dblPrice=val.dblVal;
			//::VariantClear(&val);
			bstrMethod=_T("����");
			DISPID id_Price=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Price);
	 		TESTHR(hr);
			drvDocCheck.SetProperty(id_Price,VT_R8,dblPrice);

		//*������.�����=140;
			double dblSumma=dblPrice*dblQty;
			
			bstrMethod=_T("�����");
			DISPID id_Summa=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Summa);
	 		TESTHR(hr);
			drvDocCheck.SetProperty(id_Summa,VT_R8,dblSumma);
		
			pCurGood->Release  ();
		}	

	//*������.��������();
		

		name=_T("��������");
		DISPID id_Save=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Save);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_Save,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
		
		/**/name=_T("��������");
		DISPID id_Transact=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Transact);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_Transact,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	//	pCurUnit->Release ();
		//pCurValuta->Release ();
		pCashProp->Release ();
		pStockProp->Release ();
		pCurUser->Release ();
		*vtArray=sa.Detach ();
		AfxGetApp()->EndWaitCursor ();
		return TRUE;
	}
   
  //Catch control-specific exceptions.
   catch (COleDispatchException * e) 
  {
    CString cStr;

    if (!e->m_strSource.IsEmpty())
      cStr = e->m_strSource + " - ";
    if (!e->m_strDescription.IsEmpty())
      cStr += e->m_strDescription;
    else
      cStr += "unknown error";

    AfxMessageBox(cStr, MB_OK, 
      (e->m_strHelpFile.IsEmpty())? 0:e->m_dwHelpContext);

    e->Delete();
	return FALSE;
  }
  //Catch all MFC exceptions, including COleExceptions.
  // OS exceptions will not be caught.
   catch (CException *e) 
  {
    TRACE(_T("%s(%d): OLE Execption caught: SCODE = %x"), 
      __FILE__, __LINE__, COleException::Process(e));
    e->Delete();
	return FALSE;
  }



}
BOOL C1CHelper::SetPropertyValue(IDispatch* pDisp,BSTR strPropertyName, VARIANT vtValue)
{
  
  if ( !pDisp )
    return FALSE;

  DISPID dispid = 0;
  HRESULT hr = NULL;
  OLECHAR* name = strPropertyName;
  _variant_t vtRetval;

  vtRetval.vt = VT_EMPTY;

  hr = pDisp->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
  if ( FAILED(hr) )
  {
    MessageBoxHelper::ShowError(_T("FAILED to get DISPID"));
    return FALSE;
  }


  CComVariant varResult;

  VariantClear(&varResult);
  DISPPARAMS disp = { NULL, NULL, 0, 0 };
  DISPID dispidNamed = DISPID_PROPERTYPUT;
  
  disp.cArgs = 1;
  disp.rgvarg = &vtValue;
  disp.cNamedArgs = 1;
  disp.rgdispidNamedArgs = &dispidNamed;


  hr = pDisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT | DISPATCH_METHOD, &disp, NULL, NULL, NULL);
  if ( FAILED(hr) )
  {
    MessageBoxHelper::ShowError(_T("FAILED to Invoke Method"));
    return FALSE;
  }  


  return TRUE;
}