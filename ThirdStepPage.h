#if !defined(AFX_THIRDSTEPPAGE_H__7558E72A_44D4_4DE3_961F_04387358E38D__INCLUDED_)
#define AFX_THIRDSTEPPAGE_H__7558E72A_44D4_4DE3_961F_04387358E38D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThirdStepPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThirdStepPage dialog

class CThirdStepPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CThirdStepPage)    

// Construction
public:
	CThirdStepPage();
	~CThirdStepPage();
   
// Dialog Data
	//{{AFX_DATA(CThirdStepPage)
	enum { IDD = IDD_THIRDSTEP };
	CLabel	m_lblSaler;
	CLabel	m_lblOstatok;
	CLabel	m_lblSdano;
	CLabel	m_lblZabral;
	CLabel	m_lblSalary;
	CLabel	m_lblCashValue;
	CLabel	m_lblEndAmount;
	CLabel	m_lblBegAmount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CThirdStepPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL TransactSalary();
	BOOL TransactCashMove();
	// Generated message map functions
	//{{AFX_MSG(CThirdStepPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()    

private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THIRDSTEPPAGE_H__7558E72A_44D4_4DE3_961F_04387358E38D__INCLUDED_)
