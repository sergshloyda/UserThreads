#if !defined(AFX_FONTCOMBO_H__A1B64CEB_8602_403E_9406_C9E239A0BD06__INCLUDED_)
#define AFX_FONTCOMBO_H__A1B64CEB_8602_403E_9406_C9E239A0BD06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFontCombo window

class CFontCombo : public CComboBox
{
// Construction
public:
	CFontCombo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontCombo)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	//CStringList m_lstFontNames;
	//CFont m_font;
	void PopulFontSize();
	void PopulateFont();
	virtual ~CFontCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFontCombo)
	afx_msg void OnSelchange();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTCOMBO_H__A1B64CEB_8602_403E_9406_C9E239A0BD06__INCLUDED_)
