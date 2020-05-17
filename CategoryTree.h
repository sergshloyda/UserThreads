#if !defined(AFX_KATEGORYTREE_H__8F343ACE_A11F_44E8_9D99_647F4DBCDD56__INCLUDED_)
#define AFX_KATEGORYTREE_H__8F343ACE_A11F_44E8_9D99_647F4DBCDD56__INCLUDED_

#include "SuperTree.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CategoryTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategoryTree view
class CTreeView;
class CTreeNode;
//class CUserThreadsDoc;
class CDBDoc;
class CCategoryTree : public CTreeView
{
protected:
	CCategoryTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCategoryTree)

// Attributes
public:

// Operations
public:
	CDBDoc* GetDocument();
	//void OnGetInfoFromNode(CTreeNode* pNode,BOOL blHasChild);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoryTree)
	public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCategoryTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCategoryTree)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnGetInfoFromNode(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CMainDocument* GetMainDocument();
	CSuperTree m_TreeCtrl;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KATEGORYTREE_H__8F343ACE_A11F_44E8_9D99_647F4DBCDD56__INCLUDED_)
