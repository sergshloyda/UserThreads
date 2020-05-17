#if !defined(AFX_SECONDSTEPPAGE_H__7668D85E_D3F2_4005_8F8E_ABB2481ABD33__INCLUDED_)
#define AFX_SECONDSTEPPAGE_H__7668D85E_D3F2_4005_8F8E_ABB2481ABD33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SecondStepPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSecondStepPage dialog
#include "Label.h"
#include "WntRetEdit.h"
class CSecondStepPage : public CPropertyPage
{
 	DECLARE_DYNCREATE(CSecondStepPage)
	HACCEL m_hAccel;
// Construction 
public:
	CSecondStepPage();
	~CSecondStepPage();

// Dialog Data
	//{{AFX_DATA(CSecondStepPage)
	enum { IDD = IDD_SECONDSTEP };
	CLabel	m_lblCashMove;
	CLabel	m_lblOstKassa;
	CEdit	m_edSdanaKassa;
	CLabel	m_lblCashNow;
	CLabel	m_lblBalans;
	CWntRetEdit	m_edZabral;
	CLabel	m_lblZabral;
	CLabel	m_lblZarplata;
	CLabel	m_lblOstBegin;
	CLabel	m_lblSaler;
	float	m_flZabral;
	float	m_flSdano;
	//}}AFX_DATA
   

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSecondStepPage)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation      
protected:
	// Generated message map functions
	//{{AFX_MSG(CSecondStepPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdzabral();
	afx_msg void OnChangeSdano();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM wp, LPARAM lp);
	afx_msg void OnReturn();
	afx_msg BOOL OnNextPrevField(UINT nCmdID);
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_blFirstTime;
	BOOL LoadInfo();
	CFont m_Font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECONDSTEPPAGE_H__7668D85E_D3F2_4005_8F8E_ABB2481ABD33__INCLUDED_)
