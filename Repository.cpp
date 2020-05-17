// Repository.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "Repository.h"


// Repository

IMPLEMENT_DYNCREATE(Repository, CDocument)

Repository::Repository()
{
}

BOOL Repository::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
	setContragents(boost::make_shared<ContragentsReference>(pApp->GetDbContext()));
	setPoints(boost::make_shared<PointsReference>(pApp->GetDbContext()));
	setEmployees(boost::make_shared<Repository::EmployeesReference>(pApp->GetDbContext()));
	setType_price(boost::make_shared<Repository::TypePriceReference>(pApp->GetDbContext()));
	setProductRest(boost::make_shared<Repository::ProductRest>(pApp->GetDbContext()));
	products.reset(ProductsReference::CreateReference(pApp->GetDbContext()));

	OutputDebugStringW(L"\nLoad Products\n");

	units.reset(UnitsReference::CreateReference(pApp->GetDbContext()));
	prices.reset(PricesReference::CreateReference(pApp->GetDbContext()));
	odslog(L"Load.Repository");
	return TRUE;
}

Repository::~Repository()
{
}


BEGIN_MESSAGE_MAP(Repository, CDocument)
END_MESSAGE_MAP()


// Repository diagnostics

#ifdef _DEBUG
void Repository::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void Repository::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// Repository serialization

void Repository::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif


// Repository commands
