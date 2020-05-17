//{{AFX_INCLUDES()
#include "dtpicker.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLGSETPERIOD_H__CB066F3F_0E65_47A8_B2DE_D4EDF86DB340__INCLUDED_)
#define AFX_DLGSETPERIOD_H__CB066F3F_0E65_47A8_B2DE_D4EDF86DB340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetPeriod.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetPeriod dialog

class CDlgSetPeriod : public CDialog
{
// Construction
public:
	CDlgSetPeriod(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetPeriod)
	enum { IDD = IDD_SET_PERIOD };
	CDTPicker	m_dateStart;
	CDTPicker	m_dateEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetPeriod)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetPeriod)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETPERIOD_H__CB066F3F_0E65_47A8_B2DE_D4EDF86DB340__INCLUDED_)
