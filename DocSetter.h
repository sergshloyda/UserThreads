// DocSetter.h: interface for the CDocSetter class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DOCSETTER_H__
#define __DOCSETTER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#import "./DLL/DocOneCHolder2.dll"  rename_namespace("DOC") rename("Fields","FieldsX") rename("Field","FieldX")
//#include "..\doconecholder2.h"
//#include "..\doconecholder2_i.c"
#include <vector>
#include <algorithm>
#include <string>
#include<memory>

class CDocBuilder  
{
public:
	CDocBuilder(){
		spDoc = NULL;
	}
	CDocBuilder(LPCTSTR strProgId)
	{
	bstrProgId.Append(strProgId);
	}
	HRESULT CreateInstance(LPCTSTR strProgId) {
		bstrProgId.Append(strProgId);
		if (spDoc == NULL)
			return spDoc.CoCreateInstance(bstrProgId);
		else
			return E_FAIL;
		
	}
	virtual BOOL CreateHead(){
		return FALSE;
	}
	virtual BOOL CreateTable(){
		return FALSE;
	}
	HRESULT GetDocPtr(DOC::IDocOneC** ppDoc){
		if (spDoc)
			return spDoc.CopyTo(ppDoc);
		else
			return E_FAIL;
	}
	protected:
		CComPtr<DOC::IDocOneC> spDoc;
	CComBSTR bstrProgId;
	

};
class CheckBuilder :public CDocBuilder
{
public:
	CheckBuilder() :CDocBuilder(){};
	CheckBuilder(LPCTSTR strProgId) :CDocBuilder(strProgId){}
	BOOL CreateHead()
	{
		CComPtr<IDispatch> spDisp = NULL;
		HRESULT hr=spDoc->get_Head(&spDisp);
		if (FAILED(hr))return FALSE;
		CComQIPtr<DOC::IHead> spHead = spDisp;
		spDisp.Release();
		hr=spHead->AddAttrName((bstr_t)(L"Point"));
		if (FAILED(hr))return FALSE;
		hr=spHead->AddAttrName((bstr_t)(L"BaseDoc"));
		if (FAILED(hr))return FALSE;
		hr=spHead->AddAttrName((bstr_t)(L"Prefix"));
		if (FAILED(hr))return FALSE;
		return TRUE;

	}
	BOOL CreateTable()
	{
		try{
			CComPtr<IDispatch> spDisp = NULL;
			TESTHR(spDoc->get_Table(&spDisp));
			CComQIPtr<DOC::ITable> spTable = spDisp;
			TESTHR(spTable->AddField(_bstr_t("code")));
			TESTHR(spTable->AddField(_bstr_t("barcode")));
			TESTHR(spTable->AddField(_bstr_t("qty")));
			TESTHR(spTable->AddField(_bstr_t("price")));
			return TRUE;
		}
		catch (...)
		{
			::MessageBox(NULL, _T("Error in CheckBuilder"), _T("Error!!!"), MB_OK | MB_ICONSTOP);
			return FALSE;
		}
		
	}
};
class CCheckContainer
{
	private:
		HRESULT SetFieldValue(LPCTSTR strFName,const VARIANT& varValue)
		{
			try
			{
				CComPtr<IDispatch> spDisp=NULL;
				spDoc->get_Table (&spDisp);
				CComQIPtr<DOC::ITable> spTable=spDisp;
				spTable->FieldsX ->Item (_bstr_t(strFName))->Value =varValue;
				return S_OK;
			} 
			catch(...)
			{
				return E_FAIL;
			}
		}
		HRESULT SetAttribute(LPCTSTR strAttr,const VARIANT& varAttrValue)
		{
			CComBSTR bstrAttr(strAttr);

			try
			{
				CComPtr<IDispatch> spDisp=NULL;
				TESTHR(spDoc->get_Head (&spDisp));
				CComQIPtr<DOC::IHead> spHead=spDisp;
				CComVariant varVal(varAttrValue);
				TESTHR(spHead->put_Attribute ((_bstr_t)bstrAttr,varVal));
				return S_OK;
			} 
			catch(...)
			{
				return E_FAIL;
			}
		}
public:
	HRESULT SetDescription(LPCTSTR strDescr)
	{
		CComBSTR bstrDescr(strDescr);

		try
		{
			return spDoc->put_Description(bstrDescr);

		} 
		catch(...)
		{
			return E_FAIL;
		}
	}
	HRESULT SetAuthor(LPCTSTR strAuthor)
	{
		CComBSTR bstrAuthor(strAuthor);
		try
		{
			return spDoc->put_Author(bstrAuthor);
			//return S_OK;
		} 
		catch(...)
		{
			return E_FAIL;
		}
	}

	HRESULT SetNumber(LPCTSTR strNum)
	{
		CComBSTR bstrNum(strNum);
		try
		{
			return spDoc->put_Number(bstrNum);
			//return S_OK;
		} 
		catch(...)
		{
			return E_FAIL;
		}
	}
	
	HRESULT SaveToString(BSTR* bstrStr)
	{
		CComQIPtr<DOC::IValue> spVal=spDoc;
		return spVal->SaveToString(bstrStr);
	}

	HRESULT AddNewLine()
	{
		CComPtr<IDispatch> spDisp=NULL;
		spDoc->get_Table (&spDisp);
		CComQIPtr<DOC::ITable> spTable=spDisp;
		return	spTable->AddNewLine ();	
	}

	HRESULT SetPrice(double dblPrice)
	{
		if(dblPrice<=0.0) return E_FAIL;
		CComVariant varPrice(dblPrice);
		return SetFieldValue (_T("price"),varPrice);

	}
	HRESULT SetQty(int nQty)
	{
		if(nQty<=0) return E_FAIL;
		CComVariant varQty((long)nQty);
		return SetFieldValue (_T("qty"),varQty);

	}
	HRESULT SetBarCode(LPCTSTR _strBarCode)
	{

		std::string strBarCode((char*)_strBarCode);
		if(strBarCode.length ()>13)
		{
		_raise_error(E_INVALIDARG,_bstr_t("Length BarCode>13"),_bstr_t("CheckContainer"));
			return E_INVALIDARG;
		}
		CComBSTR strFName=_T("barcode");
		CComVariant varBarCode(strBarCode.c_str());


		try
		{
			CComPtr<IDispatch> spDisp=NULL;
			spDoc->get_Table (&spDisp);
			CComQIPtr<DOC::ITable> spTable=spDisp;
			spTable->FieldsX ->Item (_bstr_t(strFName))->Value =varBarCode;
			return S_OK;
		} 
		catch(...)
		{
			return E_FAIL;
		}
	}
	HRESULT SetNomenclatureCode(LPCTSTR strNomCode)
	{

		CComVariant varNomCode(strNomCode);
		return SetFieldValue (_T("code"),varNomCode);

	}
	HRESULT SetPointCode(LPCTSTR strPointCode)
	{

		CComVariant varPointCode(strPointCode);
		return SetAttribute (_T("Point"),varPointCode);

	}
		HRESULT SetBaseDocNumber(LPCTSTR strBaseDoc)
	{

		CComVariant varBDN(strBaseDoc);
		return SetAttribute (_T("BaseDoc"),varBDN);

	}
	HRESULT SetPrefix(LPCTSTR strPrefix)
	{

		CComVariant varPrefix(strPrefix);
		return SetAttribute (_T("Prefix"),varPrefix);

	}
	CCheckContainer(CDocBuilder* pBuilder)
	{
		m_pBuilder= pBuilder;

	}
	~CCheckContainer()
	{
	if(m_pBuilder!=NULL)
		delete m_pBuilder;
	}

	HRESULT Init(BOOL blIsReturn=FALSE)
	{
		try
		{
			m_pBuilder->CreateInstance(_T("DocOneCHolder2.DocOneC"));
			m_pBuilder->CreateHead();
			m_pBuilder->CreateTable();
			m_pBuilder->GetDocPtr(&spDoc);
			if(blIsReturn)
			spDoc->ViewName = (_bstr_t)(_T("¬ÓÁ‚‡Ú"));
			else
			spDoc->ViewName = (_bstr_t)(_T("◊ÂÍ  Ã"));
			return S_OK;
		}
		catch (...)
		{
			return E_INVALIDARG;
		}

	}
	HRESULT GetDocPtr(DOC::IDocOneC** ppDoc){
		if (spDoc)
			return spDoc.CopyTo(ppDoc);
		else
			return E_FAIL;
	}
	private:


	CDocBuilder* m_pBuilder;
	CComPtr<DOC::IDocOneC> spDoc;
	
};


#endif // !defined(__DOCSETTER_H__)
