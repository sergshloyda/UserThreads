#if !defined(AFX_FIRSTSTEPPAGE_H__754A5FC8_0E9D_4BD5_AAD5_2EC6C5B5E33C__INCLUDED_)
#define AFX_FIRSTSTEPPAGE_H__754A5FC8_0E9D_4BD5_AAD5_2EC6C5B5E33C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FirstStepPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirstStepPage dialog
#include "Label.h"
class CFirstStepPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFirstStepPage)

// Construction 
public:
	BOOL LoadCashInfo();
	CFirstStepPage();
	~CFirstStepPage();
 
// Dialog Data
	//{{AFX_DATA(CFirstStepPage)
	enum { IDD = IDD_FIRSTSTEP };
	CLabel	m_lblCash;
	CLabel	m_lblItogo;
	CLabel	m_lblPremia;
	CLabel	m_lblKassa;
	CLabel	m_lblEndAmount;
	CLabel	m_lblBegAmount;
	CLabel	m_lblSaler;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFirstStepPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFirstStepPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	double m_dblSalary;
	BOOL LoadSalerInfo();         
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTSTEPPAGE_H__754A5FC8_0E9D_4BD5_AAD5_2EC6C5B5E33C__INCLUDED_)
