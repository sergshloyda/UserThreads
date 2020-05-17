#if !defined(AFX_EMPTYVIEW_H__663FB17A_0449_4D4B_A98A_AFCAEAB59D9C__INCLUDED_)
#define AFX_EMPTYVIEW_H__663FB17A_0449_4D4B_A98A_AFCAEAB59D9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmptyView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmptyView view

class CEmptyView : public CView
{
protected:
	CEmptyView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEmptyView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmptyView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEmptyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CEmptyView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPTYVIEW_H__663FB17A_0449_4D4B_A98A_AFCAEAB59D9C__INCLUDED_)
