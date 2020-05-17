// NTree1.h: interface for the CNTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_NTREE1_H__)
#define _NTREE1_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TreeNode.h"
typedef void(*FunctionType)(TreeItem& anItem);

class CNTree  
{
public:
	void SetRootNode(CTreeNode* ptrNode);
	CTreeNode* AddChild(TreeItem& item,CTreeNode* ptrNode,BOOL IsOldChild);
	CTreeNode* GetRootNode();

	void PreorderTraverse();
	CTreeNode* AttachNextChild(TreeItem& item,CTreeNode* node);
	CTreeNode* AttachFirstChild(TreeItem& item,CTreeNode* node);
	TreeItem& GetRootData();
	void SetRootData(TreeItem& item);
	bool IsEmpty();
	CNTree(TreeItem& item);
	CNTree();
	virtual ~CNTree();

private:

	void preorder(CTreeNode* treePtr,FunctionType display);
	CTreeNode* root;
protected:
	void DestroyTree(CTreeNode*& treePtr);
};

#endif // !defined_NTREE1_H__)
