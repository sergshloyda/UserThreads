// Entity.h: interface for the CEntity class.
//
//////////////////////////////////////////////////////////////////////


#pragma once

#include <string>
#include <map>
#include <tuple>
#include <set>
#include <unordered_map>
#include <stdexcept>
#include <ostream>
#include <functional>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/find.hpp>
//**********************************************************************************************
#define DECLARE_TABLE_NAME(x) const static std::wstring getTableName(){return x;}
//**********************************************************************************************
#define BEGIN_FIELD_MAP(x) 	public:\
							typedef x _EntityClass;\
							const static  _MapRef* getFieldMap(){static const _MapRef MapRef[]={
//***********************************************************************************************
#define FIELD_MAP(x,y) {x,y},
//***********************************************************************************************
#define END_FIELD_MAP() {L"",L""}};\
						return MapRef;}
//*************************************************************************************************


enum HIERARCHY{YES,NO};
struct VariantType {};
struct StrType {};
template <class TYPE> class RefItemTraits;
template<>class RefItemTraits<VariantType>
{ 
public:
	typedef std::wstring str_type;
	typedef const std::wstring c_str_type;
	typedef c_str_type key_type;
	typedef _variant_t val_type;
	typedef VARIANT& ref_val_type;
	typedef const _variant_t& const_ref_val_type;
	static key_type getFolderFieldName()
	{

		return L"isfolder";
	}
	static key_type getParentFieldName()
	{

		return L"Parent";
	}
	static key_type getOwnerSuffix()
	{

		return L"_code";
	}
	typedef boost::shared_ptr<_Recordset> recordset_type;

};
template<>class RefItemTraits<StrType>
{
public:
	typedef std::wstring str_type;
	typedef const std::wstring c_str_type;
	typedef c_str_type key_type;
	typedef str_type val_type;
	typedef str_type& ref_val_type;
	typedef const str_type& const_ref_val_type;
	static str_type getFolderFieldName()
	{

		return L"isfolder";
	}

};
template<class T,class traits=class RefItemTraits<T> >class RefItemT
{

	typedef typename traits::key_type key_type_;
	typedef typename traits::val_type val_type_;
	typedef typename traits::ref_val_type ref_val_type;
	typedef typename traits::const_ref_val_type const_ref;
	typedef std::map<key_type_, val_type_> AttributeMap;
	typedef traits RIT;
public :
	class RefItemError :public std::runtime_error

	{

	public:
		RefItemError(const char *msg, std::ostream* ostreamptr = NULL) :std::runtime_error(msg), ostreamptr(ostreamptr) {
			OutputDebugString(msg);
		}
		std::ostream* ostreamptr;
	};
	std::wstring _code;
	std::wstring _descr;
	AttributeMap attributes;
	RIT rit;
	RefItemT() {}
	RefItemT(std::wstring code, std::wstring descr) :_code(code), _descr(descr) {}
	void setAttribute(key_type_ attrName, val_type_ attrValue)
	{

		const std::pair<key_type_, val_type_> p=std::make_pair(attrName, attrValue);
		attributes.insert(p);
	}
	const_ref getAttribute(key_type_ attrName) {
		AttributeMap::const_iterator it = attributes.find(attrName);
		USES_CONVERSION;
		
		std::string msg="Attribute ";
		msg+= W2A(attrName.c_str());
		msg+=" not found";
		if (it == attributes.end())throw RefItemT::RefItemError(msg.c_str());
		return it->second;
	}
	bool IsFolder()
	{
		const_ref isF=getAttribute(RIT::getFolderFieldName());
		return ((long)isF==1L);
	}
	
};
class RefItemV :public RefItemT<VariantType>
{
	typedef RefItemT<VariantType> VT;
	typedef const _variant_t& const_ref;
	typedef const std::wstring key_type_;
public:
	RefItemV(){}
	RefItemV(std::wstring code, std::wstring descr) :RefItemT<VariantType>(code,descr) {}
	
bool InFolder(RefItemV* ref)
	{
		const_ref inF=getAttribute(RIT::getParentFieldName());
		return (((key_type_)(_bstr_t)inF)==ref->_code);
	}


};
class RefItemS :public RefItemT<StrType>
{

};
//class RefItem 
//{
//	//definition for map
//	typedef std::map<std::wstring,_variant_t >  AttributeMap;
//	
//public:
//	//Обработчик ошибок
//	class RefItemError:public std::runtime_error
//
//	{
//
//	public:
//		RefItemError(const char *msg,std::ostream* ostreamptr=&std::cout):std::runtime_error(msg),ostreamptr(ostreamptr){}
//		std::ostream* ostreamptr;
//	};
//
//	//construct destruct
//	RefItem(){}
//	RefItem(std::wstring code,std::wstring descr):_code(code),_descr(descr){}
//
//	virtual ~RefItem(){}
//	/*********************************************************+*****
//	*************fields********************************************
//	****************************************************************/
//
//	std::wstring _code;
//	std::wstring _descr;
//	AttributeMap attributes;
//	
//	
//	/**************************************************************
//	****************methods*******************************
//	**************************************************************/
//	virtual std::wstring ToString(){
//		std::wstring strCode=L"code=";
//		return strCode.append(_code);
//	}
//	
//	void setAttribute(const std::wstring attrName,const _variant_t& attrValue)
//	{
//	/*AttributeMap::iterator it=attributes.find(attrName);
//		if(it== attributes.end())throw CEntity::EntityError("Attribute not find");
//		it->second=attrValue;*/
//attributes.insert(std::make_pair(attrName,attrValue));
//	}
//	
//	const _variant_t& getAttribute(const std::wstring attrName){
//	AttributeMap::const_iterator it=attributes.find(attrName);
//		if(it== attributes.end())throw RefItem::RefItemError("Attribute not find");
//		return it->second;
//}
//bool isFolder()
//{
//	_variant_t varFolder=getAttribute(L"isfolder");
//	return( varFolder.boolVal==VARIANT_TRUE);
//
//
//}
//int InFolder(RefItem* refItem)
//{
//_variant_t varParent=getAttribute(L"Parent");
//std::wstring ParentCode=varParent.bstrVal;
//if(refItem->_code!=ParentCode)
//return 0;
//else
//return 1;
//
//}
//
//};

struct _MapRef{std::wstring attr;std::wstring field;};
class Employee
{
public:
	Employee();
	Employee(std::wstring code,std::wstring firstname,std::wstring lastname,
		std::wstring address=L"Prostokvashino",std::wstring phone=L"(555)555-55-55",
std::wstring nickname=L"slave",std::wstring pointcode=L"123",std::wstring password=L"123"):
	_firstname(firstname),_lastname(lastname)
{
	
}
	virtual~Employee(){}
	std::wstring _firstname;
	std::wstring _lastname;
	std::wstring _address;
	std::wstring _phone;
	
	std::wstring _password;
	std::wstring _nickname;
	double _salary;
	double _premia;

	virtual const std::wstring ToString() const{
		std::wstring strEmpl;
		
		return strEmpl;

	}
	

};
class IReference{
public:
	struct ListOfAttr{
		static const std::wstring Code()
		{
			return L"code";
		}
		static const std::wstring Descr()
		{
			return L"descr";
		}
	};

	virtual const std::wstring getViewName()=0;
};
class IHReference:public IReference{
public:
	struct ListOfAttr{
		static const std::wstring IsFolder()
		{
			return L"isfolder";
		}
		
			static const std::wstring Parent()
		{
				return L"Parent";
		}
	
		
	};
	virtual int getLevel()=0;
};
template <class Master> class ISReference:public IReference{
public:
	struct ListOfAttr{
		static const std::wstring Owner()
		{
			return L"owner";
		}
		
	};
	virtual const std::wstring MasterReferenceView()=0;
};
// #EntityDefinitions
struct Contragents:public IHReference{

	DECLARE_TABLE_NAME(L"Contragents")
	BEGIN_FIELD_MAP(Contragents)
		FIELD_MAP(IReference::ListOfAttr::Code(),L"id")
		FIELD_MAP(L"descr",L"contrname")
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"Contragent";}
	int getLevel(){return 1;}
};

struct TypePrice:public IHReference{



	DECLARE_TABLE_NAME(L"TypePrice")
	BEGIN_FIELD_MAP(TypePrice)
		FIELD_MAP(IReference::ListOfAttr::Code(),L"code")
		FIELD_MAP(L"descr",L"descr")
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"TypePrice";}
	int getLevel(){return 1;}
};
struct Products:public IHReference{
	struct ListOfAttr{
		static const std::wstring BaseUnit()
		{
			return L"base_unit";
		}
		
	};
	
	DECLARE_TABLE_NAME(L"Products")
	BEGIN_FIELD_MAP(Products)
		FIELD_MAP(L"code",L"code")
		FIELD_MAP(L"descr",L"Name")
		FIELD_MAP(L"isfolder",L"IsFolder")
		FIELD_MAP(L"Parent",L"Parent_Code")
		FIELD_MAP(L"base_unit",L"Unit")
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"Product";}
	int getLevel(){return 1;}
};
struct Points:public IHReference{

	struct ListOfAttr{
		static const std::wstring Cash()
		{
			return L"cash";
		}
		static const std::wstring Stock()
		{
			return L"stock";
		}
	};

	DECLARE_TABLE_NAME(L"master")
	BEGIN_FIELD_MAP(Points)
		FIELD_MAP(L"code",L"pointid")
		FIELD_MAP(L"descr",L"pointname")
		FIELD_MAP(L"cash",L"cashid")
		FIELD_MAP(L"stock",L"stockid")
		FIELD_MAP(L"firma",L"firma")
		FIELD_MAP(L"inn",L"inn")
		FIELD_MAP(L"type_price",L"typeprice")
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"Point";}
	int getLevel(){return 1;}
};
struct Cashes:public IHReference{

	DECLARE_TABLE_NAME(L"Cashes")
	BEGIN_FIELD_MAP(Cashes)
		FIELD_MAP(L"code",L"cashid")
		FIELD_MAP(L"descr",L"cashname")
		
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"Cash";}
	int getLevel(){return 1;}
};
struct Stocks:public IHReference{

	DECLARE_TABLE_NAME(L"stocks")
	BEGIN_FIELD_MAP(Stocks)
		FIELD_MAP(L"code",L"stockid")
		FIELD_MAP(L"descr",L"stockname")
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"Stock";}
	int getLevel(){return 1;}
};
// #Employee_Definition
struct Employees:public ISReference<Points>{

	DECLARE_TABLE_NAME(L"Employee")
	BEGIN_FIELD_MAP(Employees)
		FIELD_MAP(L"code",L"emplid")
		FIELD_MAP(L"descr",L"emplname")
		FIELD_MAP(L"password",L"password")
		FIELD_MAP(L"nickname",L"nikname")
		FIELD_MAP(L"salary",L"salary")
		FIELD_MAP(L"premia",L"premia")
		FIELD_MAP(L"owner",L"pointid")
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"Employee";}
	static const bool IsHierarchy(){return false;}
	static const bool IsSlave(){return true;}
	const std::wstring MasterReferenceView(){
		Points m;
		return m.getViewName();}
};
struct Units:public ISReference<Products>{

	struct ListOfAttr{
		static const std::wstring Factor()
		{
			return L"factor";
		}
	
	};

	DECLARE_TABLE_NAME(L"Units")
	BEGIN_FIELD_MAP(Units)
		FIELD_MAP(L"code",L"barcode")
		FIELD_MAP(L"descr",L"NameUnit")
		FIELD_MAP(L"factor",L"Factor")
		FIELD_MAP(L"owner",L"Product_Code")
	END_FIELD_MAP()
	 const std::wstring getViewName(){return L"Unit";}
	static const bool IsHierarchy(){return false;}
	static const bool IsSlave(){return true;}
	const std::wstring MasterReferenceView(){
		Products m;
		return m.getViewName();}
};
struct Prices:public ISReference<Products>{

	struct ListOfAttr{
		static const std::wstring PriceValue()
		{
			return L"value";
		}
		static const std::wstring PriceType()
		{
			return L"type";
		}
	};
	DECLARE_TABLE_NAME(L"Prices")
	BEGIN_FIELD_MAP(Prices)
		FIELD_MAP(L"code",L"code")
		FIELD_MAP(L"descr",L"descr")
		FIELD_MAP(L"value",L"Price")
		FIELD_MAP(L"type",L"TypePrice")
		FIELD_MAP(L"owner",L"Parent_Code")
	END_FIELD_MAP()
	const std::wstring getViewName(){return L"Unit";}
	static const bool IsHierarchy(){return false;}
	static const bool IsSlave(){return true;}
	const std::wstring MasterReferenceView(){
		Products m;
		return m.getViewName();}
};
struct ProductsRestRegs{

	struct ListOfAttr{
		static const std::wstring Product()
		{
			return L"product";
		}
		static const std::wstring Stock()
		{
			return L"stock";
		}
	};
	DECLARE_TABLE_NAME(L"ProductRest")
	BEGIN_FIELD_MAP(ProductsRestRegs)
		FIELD_MAP(L"period",L"PERIOD")
		FIELD_MAP(L"product",L"product_code")
		FIELD_MAP(L"stock",L"stock_code")
		FIELD_MAP(L"resource",L"resource")
	END_FIELD_MAP()

};
template<class Entity>class Mapper{
	typedef std::map <std::wstring,std::wstring> _AttrMap;
private:
	static  _AttrMap mapAttributes;
	//static std::wstring TableName;
public:
	static const std::wstring getTableName()
	{
		return Entity::getTableName();
	}
	static const _AttrMap CreateMap();
	static  _AttrMap getFieldMap()
	{
		_AttrMap fldMap;
		const		_MapRef* map=Entity::getFieldMap();
		while(!map->attr.empty())
		{
			fldMap.insert(std::make_pair(map->attr,map->field));
			map++;
		}
		return fldMap;
	}
	static const bool IsHierarchy(){
return Entity::IsHierarchy();
};
	static const bool IsSlave(){
		return Entity::IsSlave();
	}
};



typedef boost::shared_ptr<RefItemV> RefItemPtr;

// #DataHolder
template <class T,int N=1> class DataHolder
{

public:
	typedef boost::shared_ptr<RefItemV> reference;
	typedef typename std::vector<boost::shared_ptr< RefItemV> >::const_iterator iterator_type;
	typedef std::vector<boost::shared_ptr<RefItemV> > container_type;
	typedef std::unordered_map<std::wstring,boost::shared_ptr<RefItemV>> hash_table_type;
	typedef std::multimap<std::wstring,std::wstring> owner_map_type;
private:
	container_type vector_;

public:

	bool AddItem(boost::shared_ptr<RefItemV> val)
	{
		vector_.push_back(val);

		return true;
	}

	const container_type& getDataContainer()  { return vector_; }

	void clear()
	{
		vector_.clear();

	}

};
template <class T> class  DataHolder<T,0>{

public:
	typedef boost::tuple< std::wstring,std::wstring,std::wstring,boost::shared_ptr<RefItemV> > reference;
	typedef std::vector<reference> container_type;
	typedef std::vector<boost::shared_ptr<RefItemV> > vector_type;
	container_type set_ ;
	vector_type vector_;
	bool AddItem(boost::shared_ptr<RefItemV> val) 
	{

		std::wstring key=val->_code;
		std::wstring descr=val->_descr;
		_variant_t var=val->getAttribute(ISReference<T>::ListOfAttr::Owner());
		std::wstring owner=(var.vt==VT_NULL?L"":(_bstr_t)var);
		boost::trim(key);
		boost::trim(owner);
		set_.push_back(boost::make_tuple(key,descr,owner,val));
		return true;
	}
	const vector_type& getDataContainer()  { return vector_; }
	const container_type& getHashTable(){return set_;}

	void clear()
	{
		vector_.clear();

	}
};
template <class T> class  DataHolder<T,2>{

public:
	typedef boost::tuple< std::wstring,std::wstring,bool,std::wstring,boost::shared_ptr<RefItemV> > reference;
	typedef std::vector<reference> container_type;
	typedef std::vector<boost::shared_ptr<RefItemV> > vector_type;

	container_type set_;
	vector_type vector_;
	bool AddItem(boost::shared_ptr<RefItemV> val) 
	{

		std::wstring key=val->_code;
		std::wstring descr=val->_descr;
		bool isfolder=val->IsFolder();
		_variant_t var=val->getAttribute(IHReference::ListOfAttr::Parent());
		std::wstring parent=(var.vt==VT_NULL?L"":(_bstr_t)var);
		boost::trim(key);
		boost::trim(parent);
		set_.push_back(boost::make_tuple(key,descr,isfolder,parent,val));
		return true;
	}
	const vector_type& getDataContainer()  { return vector_; }
	const container_type& getSet(){return set_;}

	void clear()
	{
		vector_.clear();

	}
};