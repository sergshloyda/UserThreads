#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "DbContext.h"
#include <boost/make_shared.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <map>
 class RegsValCreator

{
public:
	typedef _variant_t val_type_;
	typedef boost::shared_ptr<_Recordset>	RecordsetSharedPtr;
	// #LoadDataInReference
	static int GetValueFromRegs(boost::shared_ptr<DbContext> dbContext_,std::wstring strSQL,val_type_& ret_value){

		USES_CONVERSION;
		try{
			RecordsetSharedPtr spRst=dbContext_->Execute(strSQL);
			bool blNotEmptyRst=false;
			if(spRst->EndOfFile!=VARIANT_TRUE)
			{
			blNotEmptyRst=true;
			spRst->MoveFirst();
			ret_value=spRst->Fields->Item[L"Resource"]->Value;

			}


			return (blNotEmptyRst?1:0);
		}
		



		catch(_com_error &e)
		{
			
			_bstr_t bstrSource(e.Source());
			_bstr_t bstrDescription(e.Description());
			std::wstringstream ss;
			ss<<bstrSource<<bstrDescription<<std::endl;
			
			throw new DbContext::DbContextError("jkfndfnajksnfjkl");
			/*std::wcout<<bstrSource<<bstrDescription<<std::endl;
			OutputDebugStringW(bstrSource);
			OutputDebugStringW(bstrDescription);*/

		}
	}
};
template <class Entity > 
class SQLStrategy
{

public:
	class SQLStrategyError:public std::runtime_error

	{

	public:
		SQLStrategyError(const char *msg,ostream* ostreamptr=&std::cerr):std::runtime_error(msg),ostreamptr(ostreamptr){}
		ostream* ostreamptr;
	};

public :


	typedef Entity EntityType;
	typedef EntityMapper<Entity> EM;
	typedef  RegsValCreator creator_;


	protected:
	boost::shared_ptr<DbContext> dbContext_;

	std::wstring curSQLStatement_,initialSQLStatement_;
	bool blUseExtra_;
	EM entityMapper_;
public:

	SQLStrategy(){}
	SQLStrategy(boost::shared_ptr<DbContext> dbContext):
	dbContext_(dbContext)
	{
			std::wstringstream ss;
			ss<<L"SELECT RESOURCE FROM "<<Mapper<Entity>::getTableName();
			COleDateTime now=COleDateTime::GetCurrentTime();
			
			ss<<L" WHERE PERIOD='01-"<<now.GetMonth()<<L"-"<<now.GetYear()<<L"'";
			initialSQLStatement_=ss.str();

	}


int SetFilterValue(std::wstring filter,std::wstring value)
	{
		//std::wstring::size_type n=curSQLStatement_.find(filter);
		//if(n==std::wstring::npos)
		if(!entityMapper_.AddExtraFilter(filter,value))
			entityMapper_.SetExtraFilter(filter,value);

		return 1;
	}
int  GetRest(_variant_t &value)
{
	curSQLStatement_=initialSQLStatement_+entityMapper_.GetExtraFilterStmt();
		SQLStrategy::creator_::GetValueFromRegs(dbContext_,curSQLStatement_,value);
	return 1;
}

};
template <class Entity,template<class> class Strategy=SQLStrategy >
class RestRegistry:public Strategy<Entity>
{
public:

	RestRegistry(boost::shared_ptr<DbContext> dbContext):Strategy<Entity>(dbContext){}
	int GetRest(_variant_t& value)
	{
		return Strategy<Entity>::GetRest(value);
	}
	
	~RestRegistry(void)
	{
	}
};

