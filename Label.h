#if !defined(AFX_LABEL_H__0367F49B_3933_4EAB_AC5F_41A932FB4F85__INCLUDED_)
#define AFX_LABEL_H__0367F49B_3933_4EAB_AC5F_41A932FB4F85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Label.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLabel window

class CLabel : public CStatic
{
// Construction
public:
	CLabel();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabel)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetText(const CString& szText);
	void SetColor(COLORREF newColor);
	void SetLabelFont(CFont* pNewFont);
	void SetLabelFont(LPCTSTR szFontName,int nSize);

	virtual ~CLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLabel)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	void UpdateControl();
	DECLARE_MESSAGE_MAP()
private:

	COLORREF m_clrText;
	CBrush m_brBackGrndBrush;
	COLORREF m_clrRed;
	COLORREF m_clrGreen;
	COLORREF m_clrBlue;
	COLORREF m_clrBlack;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABEL_H__0367F49B_3933_4EAB_AC5F_41A932FB4F85__INCLUDED_)
