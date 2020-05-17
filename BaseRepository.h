// BaseRepository.h: interface for the CBaseRepository class.
//
//////////////////////////////////////////////////////////////////////


#pragma once
#include "searchstrategy.h"
template <class Entity, class SearchStrategy=SQLSearchStrategy<Entity>  >
class Reference :
public SearchStrategy
	
{
	typedef  SearchStrategy  SearchStrategyClass;
	typedef typename SearchStrategyClass::EntityType Entity;
	typedef typename SearchStrategyClass::container_type container_type;
	//typedef typename DataHolder<Entity>::iterator_type cont_iter;
	typedef typename SearchStrategyClass::val_type val_type;
	typedef typename container_type::reference cont_ref;
	typedef std::vector<boost::shared_ptr< RefItemV> > internal_container_type;
	internal_container_type internal_container_;
	typedef typename internal_container_type::const_iterator internal_cont_iterator;
	internal_cont_iterator currIter_;
	container_type container_;


protected:
	
	internal_cont_iterator InsertData(cont_ref val )
	{
		internal_container_.push_back(val);
		currIter_=internal_container_.begin();
		return currIter_;

	}
	void ClearInternalContainer()
	{
		internal_container_.clear();
	}
	internal_cont_iterator BeginInternalContainer()
	{
		return internal_container_.begin();

	}

public:
	Reference(){}
	Reference(boost::shared_ptr<DbContext> dbContext):Reference::SearchStrategyClass(dbContext){}

	
	int FindByCode(std::wstring code)
	{
		if(SearchStrategyClass::FindByCode(code,container_))
		{
			internal_container_=container_.getDataContainer();
			currIter_=internal_container_.begin();
			return internal_container_.size();
		}
		else
			return 0;
	}
	int FindByDescr(const std::wstring& descr,const int flag=0)
	{
		if(SearchStrategyClass::FindByDescr(descr,container_,flag))
		{
			internal_container_=container_.getDataContainer();
			currIter_=internal_container_.begin();
			return internal_container_.size();
		}
		else
			return 0;
	}
	// #FindByAttribure
	int FindByAttribute(const std::wstring& attribute,const _variant_t& attrValue,const int flag=0)
	{
		if(SearchStrategyClass::FindByAttribute(attribute,attrValue,container_,flag))
		{
			internal_container_=container_.getDataContainer();
			currIter_=internal_container_.begin();
			return internal_container_.size();
		}
		else
			return 0;
	}
	int getNext()
	{
		currIter_++;
		if(currIter_!=internal_container_.end())
			return 1;
		else
			return 0;

	}
	boost::shared_ptr<val_type> getCurrent()
	{
		if(currIter_!=internal_container_.end())
			return *currIter_;
		else
			return boost::make_shared<val_type>();

	}
	void UseParent(boost::shared_ptr<val_type> parent){
		SearchStrategyClass::UseParent(parent);
	}
	void UseOwner(boost::shared_ptr<val_type> owner){
		SearchStrategyClass::UseOwner(owner);
	}

	int SelectItems()
	{
		container_.clear();
		if(SearchStrategyClass::SelectItems(container_))
		{
			internal_container_=container_.getDataContainer();
			currIter_=internal_container_.begin();
			return internal_container_.size();
		}
		else
			return 0;
	}
	int SelectItemsByAttribute(const std::wstring& attr,const std::wstring& attrVal)
	{
		container_.clear();
		if(SearchStrategyClass::SelectItemsByAttribute(attr,attrVal,container_))
		{
			internal_container_=container_.getDataContainer();
			currIter_=internal_container_.begin();
			return internal_container_.size();
		}
		else
			return 0;
	}
};

template <class T,class Master>class SlaveReference:protected Reference<T>
{
	typedef RefItemV val_type;
	typedef DataHolder<T,0> DataHolder_;
	typedef typename DataHolder_::container_type set_type;
	set_type set_;
	boost::shared_ptr<DbContext> dbContext_;
	bool blUseExtra_;
	boost::shared_ptr<val_type> owner_;

	SlaveReference(boost::shared_ptr<DbContext> dbContext):Reference(dbContext),dbContext_(dbContext),blUseExtra_(false){}
	

	void LoadData(SlaveReference* pRef)
	{
		
		DataHolder_ ud;
		EntityMapper<T> em;
		RefCreator<T,0>::LoadDataInReference(dbContext_,em.SelectStmt(),ud);
		set_=ud.getHashTable();
		
	}
public:	
	SlaveReference(const SlaveReference &hr)
	{
		set_=hr.set_;
		dbContext_=hr.dbContext_;
		blUseExtra_=false;
	}
	SlaveReference& operator=(const SlaveReference& hr)
	{
		set_=hr.set_;
		dbContext_=hr.dbContext_;
		blUseExtra_=false;
		return *this;
	}
	static SlaveReference* CreateReference(boost::shared_ptr<DbContext> dbContext)
	{
		SlaveReference*pRef=new SlaveReference(dbContext);
		pRef->LoadData(pRef);
		
		return pRef;

	}
	
	int FindByCode(std::wstring code)
	{
	ClearInternalContainer();
		set_type::const_iterator it=set_.cbegin(),end=set_.cend();
		it=std::find_if(it,end,[code](DataHolder_::reference val)
			{
			return val.get<0>()==code;
			});
	
		if(it!=end)
		{
		auto cur=(*it);
		InsertData(cur.get<3>());
		return 1;
		}


	else return 0;
	}
	int FindByDescription(std::wstring descr)
	{
	ClearInternalContainer();
		set_type::const_iterator it=set_.cbegin(),end=set_.cend();
		it=std::find_if(it,end,
			[descr](DataHolder_::reference val)->bool	{
				std::wstring cur_attr=val.get<1>();
				std::size_t found=cur_attr.find(descr);
				return (found!=std::wstring::npos);
		});
		if(it!=end)
		{
			auto cur=(*it);
			InsertData(cur.get<3>());
			return 1;
		}


		else return 0;
	}
	int SelectItems()
	{
			ClearInternalContainer();
		int count_records=0;
		typedef typename DataHolder_::reference value_type;
		set_type temp_set=set_;
			if(blUseExtra_)
			{
				if(owner_==nullptr)
					throw std::runtime_error("Not set owner filter");
				std::wstring parent_filter=owner_->_code;
				temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
				[parent_filter](DataHolder_::reference val){return val.get<2>()!=parent_filter;}),
				temp_set.end());
				
			}
		for(set_type::const_iterator it=temp_set.begin();it!=temp_set.end();++it)
				{
			count_records++;
			InsertData(it->get<3>());
				}
		

		return count_records;
	}
	  int SelectItemsByAttribute(const std::wstring& attr,const std::wstring& attrVal,int match=0)
	  {
			ClearInternalContainer();
			int count_records=0;
			typedef typename DataHolder_::reference value_type;
			set_type temp_set=set_;
			//auto exactly=	[attrVal,attr](DataHolder_::reference ref)->bool
			//{
			//	boost::shared_ptr<val_type> val=ref.get<3>();
			//	std::wstring cur_attr=(_bstr_t)val->getAttribute(attr);
			//	boost::trim(cur_attr);
			//	return (cur_attr!=attrVal);
			//};
			//auto likely=	[attrVal,attr](DataHolder_::reference ref)->bool
			//{
			//	boost::shared_ptr<val_type> val=ref.get<3>();
			//	std::wstring cur_attr=(_bstr_t)val->getAttribute(attr);
			//	std::size_t found=cur_attr.find(attrVal);
			//	return (found==std::wstring::npos);
			//};
			if(blUseExtra_)
			{
				if(owner_==nullptr)
					throw std::runtime_error("Not set parent filter");
				std::wstring parent_filter=owner_->_code;
				temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
				[parent_filter](DataHolder_::reference val){return val.get<2>()!=parent_filter;}),
				temp_set.end());
				
			}
				if(match==0){
				/*temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),likely),
				temp_set.end());*/
				temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
				[attrVal,attr](value_type item_refer)->bool
			{
				boost::shared_ptr<val_type> val=item_refer.get<3>();
				std::wstring cur_attr=(_bstr_t)val->getAttribute(attr);
				return (std::search(cur_attr.begin(),cur_attr.end(),attrVal.begin(),attrVal.end(),
					[](wchar_t ch1,wchar_t ch2)
				{
					return std::toupper(ch1,std::locale())==std::toupper(ch2,std::locale());
				})==cur_attr.end());
				/*std::size_t found=cur_attr.find(attrVal);
				return (found==std::wstring::npos);*/
			}),
				temp_set.end());
			}

		for(set_type::const_iterator it=temp_set.begin();it!=temp_set.end();++it)
				{
					count_records++;
					InsertData(it->get<3>());
				}
		blUseExtra_=false;
		return count_records;
    }


	void UseOwner(boost::shared_ptr<val_type> owner){
		blUseExtra_=true;
		owner_=owner;
	
	}
	boost::shared_ptr<val_type> getCurrent()
	{
		
			return Reference::getCurrent();

	}
	int getNext()
	{
		
			return Reference::getNext();

	}

};
// #HierarchyReference
/*

*/
template <class T>class HierarchyReference:protected Reference<T>
{
	typedef RefItemV val_type;
	typedef DataHolder<T,2> DataHolder_;
	typedef typename DataHolder_::container_type set_type;
	set_type set_;
	boost::shared_ptr<DbContext> dbContext_;
	bool blUseExtra_;
	boost::shared_ptr<val_type> parent_;

	HierarchyReference(){}

	 HierarchyReference(boost::shared_ptr<DbContext> dbContext):Reference(dbContext),dbContext_(dbContext),blUseExtra_(false){}
	
/****
«агружает данные в контейнер справочника
****/
	void LoadData( HierarchyReference* pRef) 
	{
		
		DataHolder_ ud;
		EntityMapper<T> em;
		RefCreator<T,2>::LoadDataInReference(dbContext_,em.SelectStmt(),ud);
		set_=ud.getSet();
		
	}
public:	

	static HierarchyReference* CreateReference(boost::shared_ptr<DbContext> dbContext)
	{
		HierarchyReference*pRef=new HierarchyReference(dbContext);
		pRef->LoadData(pRef);
		
		return pRef;

	}
	HierarchyReference(const HierarchyReference &hr)
	{
		set_=hr.set_;
		dbContext_=hr.dbContext_;
		blUseExtra_=false;
	}
	HierarchyReference& operator=(const HierarchyReference& hr)
	{
		set_=hr.set_;
		dbContext_=hr.dbContext_;
		blUseExtra_=false;
		return *this;
	}
// #HierarchyReferenceFindByCode
	int FindByCode(std::wstring code)
	{
	ClearInternalContainer();
		//auto f=[](){return }
	set_type::const_iterator it=set_.cbegin(),end=set_.cend();
	/*for(it=set_.cbegin();
		end!=(*/it=std::find_if(it,end,[code](DataHolder_::reference val)
			{
			return val.get<0>()==code;
			});
		//it!=end;
		//++it)
	if(it!=end)
		{
		auto cur=(*it);
		InsertData(cur.get<4>());
		return 1;
		}


	else return 0;
	}
int FindByDescription(std::wstring descr,bool use_folder)
	{
		ClearInternalContainer();
		int count_records=0;
		typedef typename DataHolder_::reference value_type;
		set_type temp_set=set_;
		
			temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
				[use_folder](DataHolder_::reference val){return val.get<2>()!=use_folder;}),
				temp_set.end());
		
	set_type::const_iterator it=temp_set.cbegin(),end=temp_set.cend();
	it=std::find_if(it,end,
			[descr](DataHolder_::reference val)->bool	{
						std::wstring cur_attr=val.get<1>();
						return (std::search(cur_attr.begin(),cur_attr.end(),descr.begin(),descr.end(),
							[](wchar_t ch1,wchar_t ch2)
						{
							return std::toupper(ch1,std::locale())==std::toupper(ch2,std::locale());
						})!=cur_attr.end());
						//boost::iterator_range<std::wstring::iterator> rng=boost::ifind_first(val.get<1>(),descr);
    					//std::size_t found=cur_attr.find(descr);
						//return (found!=std::wstring::npos);
						//return (rng.begin()!=rng.end() );
					});
		if(it!=end)
		{
		auto cur=(*it);
		InsertData(cur.get<4>());
		return 1;
		}


	else return 0;
	}
	int SelectItems(const bool use_folder=false)
	{
		ClearInternalContainer();
		int count_records=0;
	typedef typename DataHolder_::reference value_type;
	set_type temp_set=set_;
		if(use_folder)
			{
		temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
			[](DataHolder_::reference val){return val.get<2>()!=true;}),
			temp_set.end());
			}
			if(blUseExtra_)
			{
				if(parent_==nullptr)
					throw std::runtime_error("Not set parent filter");
				std::wstring parent_filter=parent_->_code;
				temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
				[parent_filter](DataHolder_::reference val){return val.get<3>()!=parent_filter;}),
				temp_set.end());
				
			}
			set_type::const_iterator it,it_begin,it_end;
			it_begin=temp_set.begin();
			it_end=temp_set.end();
			for(it=it_begin;it!=it_end;++it)
				{
			count_records++;
			InsertData(it->get<4>());
				}
		
			blUseExtra_=false;
		return count_records;
	}
	  int SelectItemsByAttribute(const std::wstring& attr,const std::wstring& attrVal,int match=0,bool use_folder=false)
	  {
			ClearInternalContainer();
			int count_records=0;
			typedef typename DataHolder_::reference value_type;
			set_type temp_set=set_;
			//auto exactly=	[attrVal,attr](DataHolder_::reference ref)->bool
			//{
			//	boost::shared_ptr<val_type> val=ref.get<4>();
			//	std::wstring cur_attr=(_bstr_t)val->getAttribute(attr);
			//	boost::trim(cur_attr);
			//	return (cur_attr!=attrVal);
			//};
			//auto likely=[attrVal,attr](DataHolder_::reference ref)->bool
			//{
			//	boost::shared_ptr<val_type> val=ref.get<4>();
			//	std::wstring cur_attr=(_bstr_t)val->getAttribute(attr);
			//	return (std::search(cur_attr.begin(),cur_attr.end(),attrVal.begin(),attrVal.end(),
			//		[](wchar_t ch1,wchar_t ch2)
			//	{
			//		return std::toupper(ch1,std::locale())==std::toupper(ch2,std::locale());
			//	})==cur_attr.end());
			//	/*std::size_t found=cur_attr.find(attrVal);
			//	return (found==std::wstring::npos);*/
			//};
			if(use_folder)
			{
				temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
					[](DataHolder_::reference val){return val.get<2>()!=true;}),
					temp_set.end());
			}
			if(blUseExtra_)
			{
				if(parent_==nullptr)
					throw std::runtime_error("Not set parent filter");
				std::wstring parent_filter=parent_->_code;
				temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
				[parent_filter](DataHolder_::reference val){return val.get<3>()!=parent_filter;}),
				temp_set.end());
				
			}
			if(match==0){
				/*temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),likely),
				temp_set.end());*/
				temp_set.erase(std::remove_if(temp_set.begin(),temp_set.end(),
				[attrVal,attr](value_type item_refer)->bool
			{
				boost::shared_ptr<val_type> val=item_refer.get<4>();
				std::wstring cur_attr=(_bstr_t)val->getAttribute(attr);
				return (std::search(cur_attr.begin(),cur_attr.end(),attrVal.begin(),attrVal.end(),
					[](wchar_t ch1,wchar_t ch2)
				{
					return std::toupper(ch1,std::locale())==std::toupper(ch2,std::locale());
				})==cur_attr.end());
				/*std::size_t found=cur_attr.find(attrVal);
				return (found==std::wstring::npos);*/
			}),
				temp_set.end());
			}
			/*	else
			{
			temp_set.erase(
			std::remove_if
			(temp_set.begin(),temp_set.end(),
			[attrVal,attr](value_type item_refer)->bool
			{
			boost::shared_ptr<val_type> val=item_refer.get<4>();
			std::wstring cur_attr=(_bstr_t)val->getAttribute(attr);
			boost::trim(cur_attr);
			return cur_attr!=attrVal;
			}),
			temp_set.end());
			}*/


		for(set_type::const_iterator it=temp_set.begin();it!=temp_set.end();++it)
				{
			count_records++;
			InsertData(it->get<4>());
				}
		
		blUseExtra_=false;
		return count_records;
	 }


	void UseParent(boost::shared_ptr<val_type> parent){
		blUseExtra_=true;
		parent_=parent;
	
	}
	boost::shared_ptr<val_type> getCurrent()
	{
		
			return Reference::getCurrent();

	}
	int getNext()
	{
		
			return Reference::getNext();

	}

};

