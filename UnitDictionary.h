#pragma once
#include "baserepository.h"
class RefItemV;
template <> class RefCreator<Units>

{
public:
	typedef RefItemV val_type_;
	typedef boost::shared_ptr<_Recordset>	RecordsetSharedPtr;
	typedef std::vector<boost::shared_ptr< RefItemV> > container_type;
	typedef std::vector<boost::shared_ptr< RefItemV> >::const_iterator cont_iter;
	cont_iter currIter_;

	static int LoadDataInReference(boost::shared_ptr<DbContext> dbContext_,std::wstring strSQL,container_type& container_){

		try{
			OutputDebugStringW(strSQL.c_str());
			OutputDebugString("\n");
			RecordsetSharedPtr spRst=dbContext_->Execute(strSQL);
			container_.clear();
			bool blNotEmptyRst=false;
			while(spRst->EndOfFile!=VARIANT_TRUE)
			{
				std::map<std::wstring,std::wstring> map=Mapper<Units>::getFieldMap();

				std::wstring code=(wchar_t*)(_bstr_t)(spRst->Fields->Item[(_bstr_t)(map[L"code"].c_str())]->Value);
				std::wstring descr=(wchar_t*)(_bstr_t)(spRst->Fields->Item[(_bstr_t)(map[L"descr"].c_str())]->Value);
				//RefItemV* pRef=new RefItemV(code,descr);
				boost::shared_ptr<RefItemV> spRef(new RefItemV(code,descr));
				typedef std::map<std::wstring,std::wstring>::iterator mapiterator;

				for(mapiterator it=map.begin();it!=map.end();it++)
				{
					spRef->setAttribute(it->first,spRst->Fields->Item[(_bstr_t)(it->second.c_str())]->Value);
				}

				container_.push_back(spRef);
				if(!blNotEmptyRst)blNotEmptyRst=true;
				spRst->MoveNext();
			}
			//currIter_=container_.begin();

			return (blNotEmptyRst?1:0);
		}
		catch(DbContext::DbContextError& err)
		{
			_raise_error(S_FALSE,_bstr_t(err.what()),L"LoadDataInReference");
			//std::cout<<err.what()<<std::endl;
			return -1;
		}

	}

};
class UnitDictionary :
	public Dictionary<Units>
{
	typedef boost::shared_ptr<_Recordset>	RecordsetSharedPtr;
	typedef std::vector<boost::shared_ptr< RefItemV> > container_type;
	typedef std::vector<boost::shared_ptr< RefItemV> >::const_iterator cont_iter;
	typedef  EntityMapper<Units,Mapper<Units>> EM;
	typedef  RefCreator<Units>::val_type_ val_type;

	EM entityMapper_;
	boost::shared_ptr<DbContext> dbContext_;
	container_type container_;
	cont_iter currIter_;
	std::wstring curSQLStatement_;
	bool blUseExtra_;
	UnitDictionary(boost::shared_ptr<DbContext> dbContext):Dictionary<Units>(dbContext)
	{

	}
public:
	static UnitDictionary* CreateObject(boost::shared_ptr<DbContext> dbContext)
	{
		UnitDictionary* p=new UnitDictionary(dbContext);
		
		p->SelectItems();
		return p;
	}
	~UnitDictionary(void)
	{
	}
};

