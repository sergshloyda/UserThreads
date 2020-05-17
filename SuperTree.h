#if !defined(AFX_SUPERTREE_H__A2674592_90E0_459B_9610_C8E61CC9F8F7__INCLUDED_)
#define AFX_SUPERTREE_H__A2674592_90E0_459B_9610_C8E61CC9F8F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SuperTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuperTree window
#include "NTree.h"
#include "Repository.h"
enum { DBL_CLICK_FOLDER = 1 };				 // notification: tab changed

typedef struct tag_NMFLDR_DBL_CLK {		 // notification struct
	NMHDR nmHdr;										 // item index 
	 wchar_t code[15];					 // ptr to data, if any
}NMFLDR_DBL_CLK;

typedef NMFLDR_DBL_CLK* LPNMFLDR_DBL_CLK;

class CSuperTree : public CTreeCtrl
{
	typedef HierarchyReference<Products> ProductsReference;
	typedef boost::tuple<std::wstring,std::wstring> data_reference;
	typedef std::multimap<std::wstring,data_reference> multi_map;
	typedef std::map<std::wstring,HTREEITEM> tree_map;

	multi_map _data_map;
	tree_map _tree_map;
// Construction
public:
	CSuperTree();


	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString strFullPath;
	void GetFullPath(HTREEITEM hCurItem);
	void SetFont(CFont* pFont);
	void Init();
	void Clear();
	void SetAssociatedView(CWnd* pNewView){pView=(CView*)pNewView;}
	CView* GetAssociatedView(){return pView;}
	virtual ~CSuperTree();
private:
	CView* pView;

	
	CFont m_font;

	// Generated message map functions
protected:
	//{{AFX_MSG(CSuperTree)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	void PreorderTraverse(HTREEITEM hParent,const std::wstring& code);
	//void preorder(CTreeNode* treePtr,HTREEITEM hParent,HTREEITEM hInsertAfter);


public:
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERTREE_H__A2674592_90E0_459B_9610_C8E61CC9F8F7__INCLUDED_)
