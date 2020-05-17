#pragma once
#include "BaseRepository.h"
#include "RestRegistry.h"
// Repository document

class Repository : public CDocument
{
	DECLARE_DYNCREATE(Repository)
	

public:
	Repository();
	virtual ~Repository();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

typedef boost::shared_ptr<RefItemV> ReferenceItem;

typedef Reference<Points> PointsReference;
typedef Reference<Contragents> ContragentsReference;
typedef Reference<Employees> EmployeesReference;
typedef Reference<TypePrice> TypePriceReference;
typedef HierarchyReference<Products > ProductsReference;
typedef SlaveReference<Units,Products> UnitsReference;
typedef SlaveReference<Prices,Products> PricesReference;
typedef RestRegistry<ProductsRestRegs> ProductRest;




boost::shared_ptr<Repository::TypePriceReference> getType_price() const { return type_price; }
void setType_price(boost::shared_ptr<Repository::TypePriceReference> val) { type_price = val; }
public:
	virtual BOOL OnNewDocument();
public:
	boost::shared_ptr<Repository::PointsReference> getPoints() const { return points; }
	void setPoints(boost::shared_ptr<Repository::PointsReference> val) { points = val; }
	boost::shared_ptr<Repository::ContragentsReference> getContragents() const { return contragents; }
	void setContragents(boost::shared_ptr<Repository::ContragentsReference> val) { contragents = val; }
	boost::shared_ptr<Repository::EmployeesReference> getEmployees() const { return employees; }
	void setEmployees(boost::shared_ptr<Repository::EmployeesReference> val) { employees = val; }
	boost::shared_ptr<Repository::ProductsReference> getProducts() const {
		boost::shared_ptr<Repository::ProductsReference> clone(new Repository::ProductsReference(*products.get()));
		return clone; }
	boost::shared_ptr<Repository::UnitsReference> getUnits() const {
		boost::shared_ptr<Repository::UnitsReference> clone(new Repository::UnitsReference(*units.get()));
		return clone;}
	boost::shared_ptr<Repository::PricesReference> getPrices() const {
		boost::shared_ptr<Repository::PricesReference> clone(new Repository::PricesReference(*prices.get()));
	return clone;}
	void setProductRest(boost::shared_ptr<Repository::ProductRest> val) { product_rest = val; }
	boost::shared_ptr<Repository::ProductRest> getProductRest() const { return product_rest; }
	DECLARE_MESSAGE_MAP()
private:
	boost::shared_ptr <PointsReference> points;
	boost::shared_ptr<ContragentsReference> contragents;
	boost::shared_ptr<EmployeesReference> employees;
	boost::shared_ptr<ProductsReference> products;
	boost::shared_ptr<UnitsReference> units;
	boost::shared_ptr<PricesReference> prices;
	boost::shared_ptr<TypePriceReference> type_price;
	boost::shared_ptr<ProductRest> product_rest;
};
