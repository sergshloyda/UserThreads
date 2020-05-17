#if !defined(AFX_BARCODEEDIT_H__2A4FBA92_06C2_40E7_A2AB_6022D09AE057__INCLUDED_)
#define AFX_BARCODEEDIT_H__2A4FBA92_06C2_40E7_A2AB_6022D09AE057__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BarcodeEdit.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// CBarcodeEdit window

class CBarcodeEdit : public CEdit
{
// Construction
public:
	CBarcodeEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarcodeEdit)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CBarcodeEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBarcodeEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CString m_strText;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARCODEEDIT_H__2A4FBA92_06C2_40E7_A2AB_6022D09AE057__INCLUDED_)
