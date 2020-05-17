// TreeNode.h: interface for the CTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TREENODE_H_)
#define _TREENODE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
typedef struct CNodeItem  
{
	std::wstring code;
	std::wstring text;
	std::wstring pcode;
} TreeItem;

class CTreeNode  
{
public:
	//constructors
	CTreeNode();
	CTreeNode(TreeItem& nodeItem,
		CTreeNode* first=NULL,
		CTreeNode* next=NULL):
		item(nodeItem),
		firstChild(first),
		nextChild(next){}
//destructor
	virtual ~CTreeNode();
	//attributes
	TreeItem item;
	CTreeNode* firstChild;
	CTreeNode* nextChild;
	UINT hParent;

};

#endif // !defined(_TREENODE_H_)
