// DbContext.h: interface for the DbContext class.
//
//////////////////////////////////////////////////////////////////////


#pragma once

#pragma warning( push )
#pragma warning( disable : 4146 )
#import "c:\Program Files\Common Files\System\ADO\msado15.dll" 	no_namespace rename("EOF","EndOfFile")
#include <string>
#include "boost\shared_ptr.hpp"
#include "boost\bind.hpp"
#include "boost\function.hpp"
#include <stdexcept>
#include <stdlib.h>
#include <iosfwd>



using std::string;
using std::wstring;
using std::ostream;

class DbContext  
{
public:
 typedef boost::shared_ptr<_Connection>	ConnectionSharedPtr;
 typedef boost::shared_ptr<_Recordset>	RecordsetSharedPtr;

	static void TESTHR(HRESULT x){if FAILED(x) _com_issue_error(x);};
	class DbContextError:public std::runtime_error
		
	{
		
	public:
		DbContextError(const char *msg,ostream* ostreamptr=NULL):std::runtime_error(msg),ostreamptr(ostreamptr){
			OutputDebugString(msg);
		}
		ostream* ostreamptr;
	};

	 class ConnectionDeleter{
	
	 public:
		
		void operator()(_Connection* pConn)
		{
			try{
				DbContext::TESTHR(pConn->Close());
				OutputDebugString("Connection close\n");
				pConn->Release();
			}
			catch(_com_error)
			{
				abort();
			}
		}
	};

	 class RecordsetDeleter{
	 public:
		 RecordsetDeleter()
		 {}
		 void operator()(_Recordset* pRst)
		 {
			 pRst->Close();
				OutputDebugString("Recordset close\n");
			 pRst->Release();
		 }
		 ConnectionSharedPtr conn;
		 _CommandPtr cmd;
	 };
	const bool& IsConnected() const
	{
		return isConnected;
	}

	DbContext(wstring const& connstring,wstring const& user=L"",wstring const& pwd=L""):connection(DbContext::CreateConnection(connstring,user,pwd),DbContext::ConnectionDeleter())
		{
		
				isConnected=true;

		
			
	
		}
	static _Connection* CreateConnection(wstring const& connstring,wstring const& user,wstring const& pwd)
	{
		_ConnectionPtr pConn=NULL;
			try
			{
				if(pConn ==NULL)
					TESTHR(pConn.CreateInstance (__uuidof(Connection)));
				if(pConn==NULL)throw DbContextError("Не установлена ADO");
			
				pConn->Open (connstring.c_str(),user.c_str(),pwd.c_str(),adConnectUnspecified);
				pConn->CursorLocation = adUseClient;
				return pConn.Detach();

			}
			catch(_com_error &e)
			{

			throw DbContextError(e.Description());
			return NULL;

			}

	}
	RecordsetSharedPtr Execute(const wstring& strQuery)const
	{
		_CommandPtr pCmd=NULL;
		_RecordsetPtr pRst=NULL;
		try{
			TESTHR(pCmd.CreateInstance (__uuidof(Command)));
			pCmd->CommandText=strQuery.c_str();
			pCmd->CommandType = adCmdText;
			pCmd->ActiveConnection = connection.get();
			TESTHR(pRst.CreateInstance (__uuidof(Recordset)));
			pRst = pCmd->Execute(NULL,NULL,adCmdText);
			return RecordsetSharedPtr(pRst.Detach(),DbContext::RecordsetDeleter());

		}
		catch(_com_error &e)
			{

			throw DbContextError(e.Description());
			

			}

	}
	virtual ~DbContext(){}
	DbContext::ConnectionSharedPtr getConnection() const { return connection; }
	void setConnection(DbContext::ConnectionSharedPtr val) { connection = val; }
private:
	
	ConnectionSharedPtr connection;
	bool isConnected;

};


