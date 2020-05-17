// SuperTree.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "SuperTree.h"
#include "CategoryTree.h"
//#include "UserThreadsDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperTree

CSuperTree::CSuperTree()
{
	/*HICON hIcon[3];
	int n;
	m_ImageList.Create (16,16,ILC_COLOR8|ILC_MASK,2,2);
	hIcon[0]=AfxGetApp()->LoadIcon (IDI_CLOSEFOLDER);
	hIcon[1]=AfxGetApp()->LoadIcon (IDI_CLOSEFOLDER);
	hIcon[2]=AfxGetApp()->LoadIcon (IDI_OPENFOLDERS);
	for(n=0;n<3;n++)
		m_ImageList.Add (hIcon[n]);
	


*/
	
	

}

BOOL CSuperTree::PreCreateWindow(CREATESTRUCT& cs)
{
	::SetWindowLongW(m_hWnd,GWL_STYLE,
		::GetWindowLongW(m_hWnd,GWL_STYLE)
		|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT|TVS_SHOWSELALWAYS);
	return TRUE;
}

CSuperTree::~CSuperTree()
{

	
}


BEGIN_MESSAGE_MAP(CSuperTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CSuperTree)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_GETDLGCODE()
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CSuperTree::OnTvnItemexpanded)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperTree message handlers

void CSuperTree::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	std::wstring str;
	HTREEITEM	hSelected=GetSelectedItem();
	if(hSelected!=NULL)
	{
		str=(LPWSTR)GetItemData(hSelected);

	}
	NMFLDR_DBL_CLK nm;
	nm.nmHdr.code=DBL_CLICK_FOLDER;
	nm.nmHdr.hwndFrom=m_hWnd;
	nm.nmHdr.idFrom=GetDlgCtrlID();
	USES_CONVERSION;

	wcscpy(nm.code,str.c_str());

	// TODO: Add your control notification handler code here
//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//CSuperTree* pTree = this;
	
	//HTREEITEM	hSelected=GetSelectedItem();
	//if(hSelected!=NULL)
	//{
	//	TCHAR text[256];
	//	TV_ITEM item;
	//	item.mask=TVIF_HANDLE|TVIF_TEXT|TVIF_PARAM;
	//	item.hItem=hSelected;
	//	item.pszText=text;
	//	item.cchTextMax=255; 
	//	
	//	VERIFY(GetItem (&item));
	//	//CategoryName=text;
	//
	//		ASSERT(item.lParam);
	//		CTreeNode* pNode=reinterpret_cast<CTreeNode*>(item.lParam);
	//		CWnd* pParentView=GetParent();
	//		pParentView->PostMessage (WM_GETINFO_FROMNODE,(WPARAM)pNode,(LPARAM)item.hItem);
	//		
	//
	//}
	
	//this->Invalidate(TRUE);
	CWnd* pParent=GetParent();
	pParent->SendMessageA(WM_NOTIFY,nm.nmHdr.idFrom,(LPARAM)&(nm.nmHdr));
	*pResult = 0;
}

UINT CSuperTree::OnGetDlgCode() 
{
	// TODO: Add your message handler code here and/or call default
	return (DLGC_WANTALLKEYS|DLGC_WANTARROWS);
}

void CSuperTree::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	//// TODO: Add your control notification handler code here
	//HTREEITEM hSelected = GetSelectedItem ();
	//if(pTVKeyDown->wVKey!=VK_RIGHT&&pTVKeyDown->wVKey!=VK_LEFT)
	//{
	//	*pResult=0;
	//	return;
	//}
	//if(hSelected!=NULL)
	//{
	//	hItem=hSelected;
	//	TCHAR text[_MAX_PATH];
	//	TV_ITEM item;
	//	item.mask=TVIF_HANDLE|TVIF_TEXT|TVIF_PARAM;
	//	item.hItem=hSelected;
	//	item.pszText=text;
	//	item.cchTextMax=255; 
	//	
	//	VERIFY(GetItem (&item));
	//	
	//	
	//	ASSERT(item.lParam);
	//	CTreeNode* pNode=reinterpret_cast<CTreeNode*>(item.lParam);
	//	CWnd* pParentView=GetParent();
	//	pParentView->PostMessage (WM_GETINFO_FROMNODE,(WPARAM)pNode,(LPARAM)item.cChildren);
	//		
	//}
	*pResult = 0;
}

void CSuperTree::Init()
{

	CClientDC dcClient(this); 
	CMainDocument* pUTDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	//int nFontHeight =  -((dcClient.GetDeviceCaps(LOGPIXELSY) * pUTDoc->GetFontSize ()) / 72);//in TWIPS
	//m_font.CreateFont(nFontHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, 
	//	DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, 
	//	DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pUTDoc->GetFontName ());
	SetFont(pUTDoc->m_FontMap[_T("Dialogs")].get());
	Repository *pRep=CUserThreadsApp::GetDocument<Repository>();
	boost::shared_ptr<Repository::ProductsReference> products=pRep->getProducts();
	if(products->SelectItems(true))
	{
		do 
		{
			boost::shared_ptr<RefItemV> ref_item_=products->getCurrent();
			std::wstring parent=(_bstr_t)ref_item_->getAttribute(IHReference::ListOfAttr::Parent());
			boost::trim(parent);
			data_reference item=boost::make_tuple(boost::trim_copy(ref_item_->_code),boost::trim_copy(ref_item_->_descr));
			_data_map.insert(std::make_pair(parent,item));
		} while (products->getNext());


	}

	HIMAGELIST prevImgLst=TreeView_SetImageList(m_hWnd,pUTDoc->m_hSysImgLst,TVSIL_NORMAL);
	//BOOL res=pNewImgList->Attach(hImgLst);
	//HIMAGELIST hil=pList->Detach();
	//CImageList* previousImageList=GetImageList(TVSIL_NORMAL);
	//if(previousImageList==NULL)
	//SetImageList(pNewImgList,TVSIL_NORMAL);
	
	
	PreorderTraverse(TVI_ROOT,L"");
	
}

void CSuperTree::Clear()
{
//	CImageList *pImgList=GetImageList(TVSIL_NORMAL);
//	ASSERT_NULL_OR_POINTER(pImgList,CImageList);
//if(pImgList)	{
//	pImgList->DeleteImageList();
//	
//}


	CTreeCtrl& tree=*(this);
	std::for_each(_tree_map.cbegin(),_tree_map.cend(),[&tree](std::pair<std::wstring,HTREEITEM> item){
		void* data=(void*)tree.GetItemData(item.second);
		delete data;
	});
//	delete pImgList;
	DeleteAllItems();
}

void CSuperTree::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
OnDblclk(pNMHDR,pResult);	
	*pResult = 0;
}
void CSuperTree::PreorderTraverse(HTREEITEM hParent,const std::wstring& code)
{
	SHFILEINFO Info;
	::SHGetFileInfo(_T("c:\\windows"),0,&Info,sizeof(SHFILEINFO),SHGFI_ICON|SHGFI_SMALLICON);
	int id=Info.iIcon;
	::SHGetFileInfo(_T("c:\\windows"),0,&Info,sizeof(SHFILEINFO),
		SHGFI_ICON|SHGFI_OPENICON|SHGFI_SMALLICON);
	int idsel=Info.iIcon;
	//OutputDebugString(L"LoadTreeCtrl\n");
	//OutputDebugStringW(code.c_str());
	USES_CONVERSION;
	for(auto pos=_data_map.lower_bound(code);pos!=_data_map.upper_bound(code);++pos)
	{
		TVINSERTSTRUCT gtv;
		gtv.hParent=hParent;
		gtv.hInsertAfter=TVI_LAST;
		gtv.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
		gtv.item.iImage=id;
		gtv.item.iSelectedImage=idsel;
		gtv.item.pszText=W2A(pos->second.get<1>().c_str());
		gtv.item.lParam=(long)_wcsdup(pos->second.get<0>().c_str());
		HTREEITEM hItem= InsertItem(&gtv);
		_tree_map.insert(std::make_pair(pos->second.get<0>(),hItem));
		multi_map::size_type i=_data_map.count(pos->second.get<0>());

		if(i!=0)
		{
			gtv.item.pszText=_T("");
			gtv.hParent=hItem;
			InsertItem(&gtv);
		}
	}
}



void CSuperTree::SetFont(CFont *pFont)
{

	CTreeCtrl::SetFont (pFont);

}

void CSuperTree::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{	   
	/*UINT nFlag = 0;
	CPoint cursorPoint(0, 0); 
	GetCursorPos(&cursorPoint); 
	ScreenToClient ( &cursorPoint );  


	HTREEITEM hSelected = HitTest(cursorPoint, &nFlag);
	if(hSelected==hItem)
	{
	*pResult=0;
	return;
	}
	if(hSelected!=NULL)
	{
	hItem=hSelected;
	TCHAR text[_MAX_PATH];
	TV_ITEM item;
	item.mask=TVIF_HANDLE|TVIF_TEXT|TVIF_PARAM;
	item.hItem=hSelected;
	item.pszText=text;
	item.cchTextMax=255; 

	VERIFY(GetItem (&item));


	ASSERT(item.lParam);
	CTreeNode* pNode=reinterpret_cast<CTreeNode*>(item.lParam);
	CWnd* pParentView=GetParent();*/
		//pParentView->PostMessage (WM_GETINFO_FROMNODE,(WPARAM)pNode,(LPARAM)item.cChildren);
	
		//CCategoryTree* pTreeView=static_cast<CCategoryTree*>(GetParent());
		//pTreeView->OnGetInfoFromNode (pNode,ItemHasChildren(hItem));
			
	//}
	*pResult = 0;
}

void CSuperTree::GetFullPath(HTREEITEM hItem)
{
	/*HTREEITEM hCurItem=hItem;
	strFullPath="";
	CString strDelimiter;

	do{
		CTreeNode* pNode;
		TCHAR text[255];
		TV_ITEM item;
		item.mask=TVIF_HANDLE|TVIF_TEXT|TVIF_PARAM;
		item.hItem=hCurItem;
		item.pszText=text;
		item.cchTextMax=255; 
		
		VERIFY(GetItem (&item));
		pNode=(CTreeNode*)item.lParam;
		hCurItem=GetParentItem(hCurItem);
		if(strFullPath=="")
			strDelimiter="";
		else
			strDelimiter="/";
		CString strTxt=pNode->item.text.c_str(); 
		strFullPath= strTxt +strDelimiter+strFullPath;
		
	}	while(hCurItem!=NULL);*/

}

void CSuperTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hSelected=pNMTreeView->itemNew.hItem;
//	GetFullPath (hSelected);
	*pResult = 0;
}


void CSuperTree::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	if((pNMTreeView->itemNew.state&TVIS_EXPANDED)){

		HTREEITEM hCur=pNMTreeView->itemNew.hItem;

		HTREEITEM hTmp=GetChildItem(hCur);
		if(GetItemText(hTmp)==_T(""))
		{
			//void* data=(void*)m_Tree.GetItemData(hTmp);
			DeleteItem(hTmp);
			//delete data;

			std::wstring str=(LPWSTR)GetItemData(hCur);
			PreorderTraverse(hCur,str);

		}


	}

	*pResult = 0;
}
