#if !defined(AFX_ZREPORTWIZARD_H__DE51A993_4FE5_40CF_96DB_17E4ED5E6CCD__INCLUDED_)
#define AFX_ZREPORTWIZARD_H__DE51A993_4FE5_40CF_96DB_17E4ED5E6CCD__INCLUDED_

#include "FirstStepPage.h"	// Added by ClassView
#include "SecondStepPage.h"
#include "ThirdStepPage.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZReportWizard.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// CZReportWizard
#include"1CHelper.h"
#include"ZReportDoc.h"
class CZReportWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CZReportWizard)

// Construction
public:
	CZReportWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CZReportWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
 
// Attributes
public:
   
// Operations     
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZReportWizard)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	float m_flSdano;
	float m_flZabral;
	float m_flSalaryBalance;
	float m_flItogo;
	CString m_strSalerName;
	CZReportDoc* pZReportDoc;
	float m_flPremia;
	float m_flSalary;
	CString m_strSalerId;
	
	virtual ~CZReportWizard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CZReportWizard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFirstStepPage m_FStepPage;
	CSecondStepPage m_SStepPage;
	CThirdStepPage m_TStepPage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZREPORTWIZARD_H__DE51A993_4FE5_40CF_96DB_17E4ED5E6CCD__INCLUDED_)
