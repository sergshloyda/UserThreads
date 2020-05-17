#if !defined(AFX_REPORTVIEW_H__4FF3C415_C918_4BE7_B592_8B53C2464F6E__INCLUDED_)
#define AFX_REPORTVIEW_H__4FF3C415_C918_4BE7_B592_8B53C2464F6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportView view
#include "FolderFrame.h"
#include "ReportFrame.h"	// Added by ClassView
#include "InfoConsole.h"
class CReportView : public CFolderView
{
protected:
	CReportView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReportView)

// Attributes
public:

// Operations
public:
CDBDoc* GetDocument();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL
	virtual void OnChangedFolder(int iPage);
// Implementation
protected:
	CReport* pReport;

	virtual ~CReportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CReportView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int nVPos;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTVIEW_H__4FF3C415_C918_4BE7_B592_8B53C2464F6E__INCLUDED_)
