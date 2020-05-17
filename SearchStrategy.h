// SearchStrategy.h: interface for the CSearchStrategy class.
//
//////////////////////////////////////////////////////////////////////



#pragma once

#include "Entity.h"
#include "DbContext.h"
#include <boost/make_shared.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <map>

class RefItemV;

// #RefCreator
template <class T,int N=1> class RefCreator

{
public:
	typedef RefItemV val_type_;
	typedef boost::shared_ptr<_Recordset>	RecordsetSharedPtr;

	typedef DataHolder<T,N> container_type;

	// #LoadDataInReference
	static int LoadDataInReference(boost::shared_ptr<DbContext> dbContext_,std::wstring strSQL,container_type& container_){

		try{
			RecordsetSharedPtr spRst=dbContext_->Execute(strSQL);
			container_.clear();
			bool blNotEmptyRst=false;
			while(spRst->EndOfFile!=VARIANT_TRUE)
			{
				std::map<std::wstring,std::wstring> map=Mapper<T>::getFieldMap();

				std::wstring code=(wchar_t*)(_bstr_t)(spRst->Fields->Item[(_bstr_t)(map[L"code"].c_str())]->Value);
				std::wstring descr=(wchar_t*)(_bstr_t)(spRst->Fields->Item[(_bstr_t)(map[L"descr"].c_str())]->Value);
				boost::shared_ptr<RefItemV> spRef(new RefItemV(code,descr));
				typedef std::map<std::wstring,std::wstring>::iterator mapiterator;

				for(mapiterator it=map.begin();it!=map.end();it++)
				{

					_variant_t var=spRst->Fields->Item[(_bstr_t)(it->second.c_str())]->Value;
					spRef->setAttribute(it->first,var);
				}

				container_.AddItem(spRef);
				if(!blNotEmptyRst)blNotEmptyRst=true;
				spRst->MoveNext();
			}


			return (blNotEmptyRst?1:0);
		}
		catch(DbContext::DbContextError& err)
		{
			OutputDebugString(err.what());
			return -1;
		}



		catch(_com_error &e)
		{
			_bstr_t bstrSource(e.Source());
			_bstr_t bstrDescription(e.Description());
			OutputDebugStringW(bstrSource);
			OutputDebugStringW(bstrDescription);

		}
	}
};


template<class Entity,class mapper= Mapper<Entity> > 
class EntityMapper
{
	typedef typename mapper entitymapper_;
	typedef std::wstring str_type;

	std::wstring tablename_;
	std::wstring parent_filter_;
	const std::wstring SelectClause(){return L"SELECT ";} 
	const std::wstring FromClause(){return L" FROM ";}
	const std::wstring WhereClause(){return L" WHERE ";}
	const std::wstring AndClause(){return L" AND ";}

	typedef std::map <std::wstring,std::wstring> _FieldMap,_ExtraFilterMap;
	const std::wstring getParentFilter(const bool flagAND=true){
		std::wstring filter_expr;
		if(!parent_filter_.empty())
			if(flagAND)
				filter_expr=L" "+AndClause()+L" ("+fldMap[IHReference::ListOfAttr::Parent()]+L"='"+parent_filter_+L"')";
			else
				filter_expr=L"("+fldMap[IHReference::ListOfAttr::Parent()]+L"='"+parent_filter_+L"')";
		return filter_expr;

	}
	const std::wstring getOwnerFilter(const std::wstring& filter){
		std::wstring filter_expr;
		filter_expr=L"("+fldMap[L"owner"]+L"='"+filter+L"')";
		return filter_expr;

	}
public:
	entitymapper_ entitymapper;
	_FieldMap fldMap;
	_ExtraFilterMap extraMap;
	EntityMapper()
	{
		tablename_=mapper::getTableName();
		fldMap=mapper::getFieldMap();
	}
	bool IsHierarchy(){
		Entity e;
		return (e.getLevel()>0);
	}
	bool IsSlave()
	{
		Entity e;
		return (!e.MasterReferenceView().empty()>0);
	}
	const std::wstring getStrFields(_FieldMap map)
	{
		std::wstringstream ostrFields;
		_FieldMap::iterator iter;
		//outer::FieldMap* fldmap=outer::FieldMap::GetFieldMap();
		//_AttrMap map=outer::FieldMap()();
		for(iter=map.begin();iter!=map.end();++iter)
		{
			ostrFields<<(*iter).second<<",";

		}
		std::wstring strFields=ostrFields.str();
		boost::trim_right_if(strFields,boost::is_any_of(std::wstring(L",",1)) );
		return strFields;
	}
	const std::wstring getPredicat(const int flag,  _FieldMap map, const std::wstring& key,const std::wstring& filter)
	{
		std::wstringstream ostrPredicat;
		if(flag==1)
			ostrPredicat<<WhereClause()<<"("<<map[key]<<L"='"<<filter<<L"')";
		else
			ostrPredicat<<WhereClause()<<map[key]<<L" LIKE'%"<<filter<<L"%'";
		return ostrPredicat.str();
	}
	const std::wstring SelectStmt()
	{
		std::wstringstream ostr;
		ostr<<SelectClause()<<getStrFields(fldMap)<<FromClause()<<tablename_;

		return ostr.str();
	}
	std::wstring FindFromCodeStmt(const int code)
	{
		_FieldMap map=fldMap;
		std::wstringstream ostr;
		std::wstring strFields= getStrFields(fldMap);
		ostr<<WhereClause()<<"("<<map[L"code"]<<L"="<<code<<L")";

		return ostr.str();
	}
	const std::wstring FindFromCodeStmt(const std::wstring code)
	{
		std::wstringstream ostr;
		ostr<<getPredicat(1,fldMap,L"code",code)<<getParentFilter();

		return ostr.str();
	}


	const std::wstring FindFromDescStmt(const std::wstring descr,const int flag=0)
	{
		std::wstringstream ostr;
		ostr<<getPredicat(flag,fldMap,L"descr",descr)<<getParentFilter();

		return ostr.str();
	}



	const std::wstring FindFromAttrStmt(const std::wstring& attr,const _variant_t& attrVal,const int flag=0)
	{
		std::wstringstream ostr;
		std::wstring filtrValue;
		if (attrVal.vt==VT_BSTR){
			filtrValue=(_bstr_t)attrVal;
			ostr<<getPredicat(flag,fldMap,attr,filtrValue)<<getParentFilter();
		}
		return ostr.str();


	}
	void set_parent(const std::wstring& parent_code)
	{
		parent_filter_=parent_code;
	}
	const std::wstring SelectChildFromParentStmt(const std::wstring& code)
	{
		std::wstringstream ostr;
		set_parent(code);
		ostr<<WhereClause()<<getParentFilter(false);

		return ostr.str();
	}
	const std::wstring SelectFromOwnerStmt(const std::wstring& code)
	{
		std::wstringstream ostr;
		ostr<<WhereClause()<<getOwnerFilter(code);

		return ostr.str();
	}
	bool AddExtraFilter( const std::wstring& key,const std::wstring& filter)
	{

		std::pair<_ExtraFilterMap::iterator,bool> ret;
		ret=extraMap.insert(std::make_pair(key,filter));
		return ret.second;
	}
	bool SetExtraFilter( const std::wstring& key,const std::wstring& filter)
	{

		_ExtraFilterMap::iterator it=extraMap.find(key);
		if(it==extraMap.end())
			return false;
		else
		{
			it->second=filter;
			return true;
		}

	}
	const std::wstring GetExtraFilterStmt()
	{

		std::wstringstream ostr;
		for(_ExtraFilterMap::iterator it=extraMap.begin();it!=extraMap.end();++it)
			ostr<<AndClause()<<fldMap[it->first]<<L" LIKE'%"<<it->second<<L"%'";
		return ostr.str();
	}
	void CleanParentFilter()
	{
		parent_filter_=L"";
	}


};
// #SQLSearchStartegy	
#pragma warning(disable:4482)
template <class Entity,class creator=RefCreator<Entity,HIERARCHY::NO> > 
class SQLSearchStrategy
{
public:
	class SQLSearchStrategyError:public std::runtime_error

	{

	public:
		SQLSearchStrategyError(const char *msg,ostream* ostreamptr=nullptr):std::runtime_error(msg),ostreamptr(ostreamptr){}
		ostream* ostreamptr;
	};
public :


	typedef typename creator::container_type DataHolderType;

	typedef typename creator::val_type_ val_type;

	typedef Entity EntityType;
	typedef EntityMapper<Entity> EM;

	typedef DataHolderType container_type;
private:
	boost::shared_ptr<DbContext> dbContext_;

	std::wstring curSQLStatement_;
	bool blUseExtra_;

public:
	SQLSearchStrategy(){}
	SQLSearchStrategy(boost::shared_ptr<DbContext> dbContext):
	  dbContext_(dbContext)
	  {
		  curSQLStatement_=entityMapper_.SelectStmt();

	  }

	  EM entityMapper_;

	  static SQLSearchStrategy* CreateObject(boost::shared_ptr<DbContext> dbContext)
	  {
		  SQLSearchStrategy* p=new SQLSearchStrategy(dbContext);
		  return p;
	  }
	  int FindByCode(const std::wstring code,container_type& out_container){

		  curSQLStatement_=entityMapper_.SelectStmt();
		  curSQLStatement_+=entityMapper_.FindFromCodeStmt(code);
		  int retVal=0;
		  retVal=creator::LoadDataInReference(dbContext_,curSQLStatement_,out_container);
		  return retVal;

	  }
	  int FindByDescr(const std::wstring& descr,container_type& out_container,const int flag=0)
	  {
		  curSQLStatement_=entityMapper_.SelectStmt();
		  curSQLStatement_+=entityMapper_.FindFromDescStmt(descr,flag);
		  int retVal=0;
		  retVal=creator::LoadDataInReference(dbContext_,curSQLStatement_,out_container);
		  return retVal;
	  }
	  // #FindByAttribure
	  int FindByAttribute(const std::wstring& attribute,const _variant_t& attrValue,container_type& out_container,const int flag=0)
	  {
		  curSQLStatement_=entityMapper_.SelectStmt();
		  curSQLStatement_+=entityMapper_.FindFromAttrStmt(attribute,attrValue,flag);
		  int retVal=0;
		  retVal=creator::LoadDataInReference(dbContext_,curSQLStatement_,out_container);
		  return retVal;
	  }

	  void UseParent(boost::shared_ptr<val_type> parent){
		  blUseExtra_=true;
		  if(!entityMapper_.IsHierarchy()){ throw SQLSearchStrategyError("Not hierarchy dictionary");}
		  if(!parent) { throw SQLSearchStrategyError("No parent element");}
		  if(parent->_code.empty()) { throw SQLSearchStrategyError("No parent element code");}
		  if(!parent->IsFolder()){ throw SQLSearchStrategyError("It`s not group element");}
		  curSQLStatement_=entityMapper_.SelectStmt();
		  curSQLStatement_+=entityMapper_.SelectChildFromParentStmt(parent->_code);
	  }
	  void UseOwner(boost::shared_ptr<val_type> owner){
		  blUseExtra_=true;
		  Entity e;
		  if(!e.IsSlave()){ throw SQLSearchStrategyError("Not Slave dictionary");}
		  if(!owner) { throw SQLSearchStrategyError("No owner element");}
		  if(owner->_code.empty()) { throw SQLSearchStrategyError("No owner element code");}
		  curSQLStatement_=entityMapper_.SelectStmt();
		  curSQLStatement_+=entityMapper_.SelectFromOwnerStmt(owner->_code);
	  }

	  int SelectItems(container_type& out_container)
	  {
		  int retVal=0;
		  retVal=creator::LoadDataInReference(dbContext_,curSQLStatement_,out_container);
		  entityMapper_.CleanParentFilter();
		  blUseExtra_=false;
		  return retVal;
	  }
	  int SelectItemsByAttribute(const std::wstring& attr,const std::wstring& attrVal,container_type& out_container)
	  {

		  if(blUseExtra_)
			  curSQLStatement_+=entityMapper_.AddExtraFilterStmt(attr,attrVal);
		  else
			  curSQLStatement_+=entityMapper_.FindFromAttrStmt(attr,_variant_t(_bstr_t(attrVal.c_str())));
		  int retVal=0;
		  retVal=creator::LoadDataInReference(dbContext_,curSQLStatement_,out_container);
		  entityMapper_.CleanParentFilter();
		  blUseExtra_=false;
		  return retVal;
	  }

};