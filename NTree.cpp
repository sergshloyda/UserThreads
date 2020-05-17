// NTree1.cpp: implementation of the CNTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NTree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static void display(TreeItem& anItem)
{
	return;
}
CNTree::CNTree():root(NULL)
{

}

CNTree::~CNTree()
{
	DestroyTree(root);
}

CNTree::CNTree(TreeItem& item)
{
	root=new CTreeNode(item,NULL,NULL);

	if(root==NULL)	MessageBoxHelper::ShowError(_T("Not Enaught memory"));
}

bool CNTree::IsEmpty()
{
return(root==NULL);
}

void CNTree::SetRootData(TreeItem& item)
{
	if(!IsEmpty())
	root->item =item;
	else
	{
		root=new CTreeNode(item,NULL,NULL);
	}
}

TreeItem& CNTree::GetRootData() 
{
 return root->item ;
}

CTreeNode* CNTree::AttachFirstChild(TreeItem& item,CTreeNode* node)
{
	if(IsEmpty())
	{
		MessageBoxHelper::ShowError(_T("Tree Is Empty!!"));
		return NULL;
	}
	else if(node==NULL)
	{
			root->firstChild =new CTreeNode(item,NULL,NULL);
		return root->firstChild ;
	}
	else
	{
		node->firstChild =new CTreeNode(item,NULL,NULL);
		return node->firstChild ;
	}
	
}

CTreeNode* CNTree::AttachNextChild(TreeItem& item,CTreeNode* node)
{
	if(IsEmpty())
	{
	MessageBoxHelper::ShowError(_T("Tree Is Empty!!"));
	return NULL;
	}
	else if	(node==NULL)
	{
			root->nextChild =new CTreeNode(item,NULL,NULL);
		return root->nextChild ;
	}
	else
	{
		node->nextChild =new CTreeNode(item,NULL,NULL);
		return node->nextChild ;

	}
}

void CNTree::PreorderTraverse()
{
preorder(root,display);
}

void CNTree::DestroyTree(CTreeNode*& treePtr)
{
	if(treePtr!=NULL)
	{
		
		DestroyTree(treePtr->firstChild );
		DestroyTree(treePtr->nextChild );
		delete treePtr;
		treePtr=NULL;
		
	}
}

void CNTree::preorder(CTreeNode *treePtr, FunctionType display)
{
	if(treePtr!=NULL)
	{
		display(treePtr->item );
		
		preorder(treePtr->firstChild ,display);
		preorder(treePtr->nextChild ,display);
		
	}
}



CTreeNode* CNTree::GetRootNode()
{
return root;
}





CTreeNode* CNTree::AddChild(TreeItem& item,CTreeNode *ptrNode, BOOL IsOldChild)
{
	CTreeNode* pRetNode;
	if(IsOldChild)
		pRetNode=AttachFirstChild (item ,ptrNode);
	else 
		pRetNode=AttachNextChild(item ,ptrNode);
	return pRetNode;

}

void CNTree::SetRootNode(CTreeNode* ptrNode)
{
root=ptrNode;
}
