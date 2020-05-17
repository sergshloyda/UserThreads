// Register.cpp: implementation of the Register class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "userthreads.h"
#include "Register.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMapStringToString Register::repository;

Register::Register()
{

}

Register::~Register()
{

}

void Register::ShowErrorMessage(_com_error &ce)
{
	CString adoStr,msgStr,tempStr;
		
		
		// Trace COM error information.
		// 
		adoStr=_T("");
		TRACE0( "\nCom Exception Information\n-----------------------------------------------\n" );
		TRACE1( "Description : %s\n",   (char*) ce.Description()  );
		TRACE1( "Message     : %s\n",   (char*) ce.ErrorMessage() );
		TRACE1( "HRESULT     : 0x%08x\n", ce.Error() );
		// 
		// Trace ADO exception information only if connection is not null.
		// 
		CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
		/*if ( NULL != pApp->pConn )
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
		}*/
		msgStr.Format(_T("Com Exception :\n===============\nDescription : %s\nMessage     : %s\nSource       :%s\n%s"),(char*) ce.Description(),(char*) ce.ErrorMessage(),(char*)ce.Source(), (LPCTSTR) adoStr);  
		AfxMessageBox(msgStr, MB_OK|MB_TOPMOST|MB_ICONSTOP);
}

void Register::SetValue(LPCTSTR strKey,LPCTSTR strValue)
{
	repository[strKey]=strValue;

}

LPCTSTR Register::GetValue(LPCTSTR strKey)
{
	CString string;
	if(!repository.Lookup(strKey,string))
		_raise_error(E_FAIL,_bstr_t("Not value for this key"),_bstr_t("Register::GetValue"));
	return string.GetBuffer(1);;
}
