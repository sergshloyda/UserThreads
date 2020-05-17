
#include "StdAfx.h"
#include "PointSettings.h"

IMPLEMENT_DYNAMIC(CPointSettings, CPropertySheet)

	CPointSettings::CPointSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

	//	pParent=static_cast<CView*>(pParentWnd);
}

CPointSettings::CPointSettings(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

	//pParent=static_cast<CView*>(pParentWnd);



}

CPointSettings::~CPointSettings()
{

	//	delete m_pgSelBarCode;
	//delete m_pgSelGood;
}


BOOL CPointSettings::OnInitDialog()
{
 BOOL bResult = CPropertySheet::OnInitDialog();
 return bResult;
}

BEGIN_MESSAGE_MAP(CPointSettings, CPropertySheet)
	//{{AFX_MSG_MAP(CPSDlgInsertGood)

	//}}AFX_MSG_MAP

END_MESSAGE_MAP()