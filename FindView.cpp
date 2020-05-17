// FindView.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "InfoConsole.h"
#include "FindView.h"
//#include "UserThreadsDoc.h"
#include "ExplorerDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindView

IMPLEMENT_DYNCREATE(CFindView, CFormView)

CFindView::CFindView()
	: CFormView(CFindView::IDD)
{
	//{{AFX_DATA_INIT(CFindView)
	m_radio = -1;
	m_strName = _T("");
	//}}AFX_DATA_INIT
	m_strExplorer="Îבחמנ...";
	m_strSQL="";
}

CFindView::~CFindView()
{
}

void CFindView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindView)
	DDX_Control(pDX, IDC_STATIC2, m_wndStaticEx);
	DDX_Control(pDX, IDC_FIND, m_wndEdit);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_radio);
	DDX_Text(pDX, IDC_FIND, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindView, CFormView)
	//{{AFX_MSG_MAP(CFindView)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, OnRadioCustom)
	ON_BN_CLICKED(IDC_RADIO_ALL, OnRadioAll)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBOEX, OnSelchangeComboex)
	ON_BN_CLICKED(IDC_FINDBTN, OnFindbtn)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
		ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipNotify)
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindView diagnostics

#ifdef _DEBUG
void CFindView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFindView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFindView message handlers

void CFindView::OnRadioCustom() 
{
	CComboBoxEx * m_comboEx = (CComboBoxEx*)GetDlgItem(IDC_COMBOEX);
	m_wndStaticEx.ShowWindow(SW_SHOW);
	m_comboEx->ShowWindow(SW_SHOW);
	InitComboBoxEx ();
}

void CFindView::OnRadioAll() 
{
	CComboBoxEx * m_comboEx = (CComboBoxEx*)GetDlgItem(IDC_COMBOEX);
	m_wndStaticEx.ShowWindow(SW_HIDE);
	m_comboEx->ShowWindow(SW_HIDE);	
}

int CFindView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_radio=0;	
	//m_wndEdit.SetFocus();

	return 0;
}

void  CFindView::InitComboBoxEx()
{
	CComboBoxEx * m_comboEx = (CComboBoxEx*)GetDlgItem(IDC_COMBOEX);
	if (m_comboEx->GetImageList()==NULL)
	{
		CTreeNode* root=NULL;
		CTreeNode *Node=NULL;

		CInfoConsole* pThread=static_cast<CInfoConsole*>(AfxGetThread());
		ASSERT(pThread!=NULL);
		m_il.Create(16, 16, ILC_COLOR8|ILC_MASK, 2, 2);
		HICON hIcon1=AfxGetApp()->LoadIcon (IDI_CLOSEFOLDER);
		m_il.Add(hIcon1);
		HICON hIcon2=AfxGetApp()->LoadIcon (IDI_OPENFOLDERS);
		m_il.Add(hIcon2);//
		
	
		m_comboEx->SendMessage(CBEM_SETIMAGELIST, 0, (LPARAM)m_il.Detach());
		CMainDocument* pUTDoc=static_cast<CMainDocument*>(pThread->m_pDocument);
		//root=pUTDoc->GetCategoryTree ().GetRootNode ();
		Node=/*root->firstChild*/ NULL;
		int i=0;
		while(Node!=NULL)
		{
			COMBOBOXEXITEM     cbi;
			CString            str;
			int                nItem;
			str=Node->item.text.c_str();
			cbi.mask = CBEIF_IMAGE |  
                        CBEIF_SELECTEDIMAGE | CBEIF_TEXT | CBEIF_LPARAM;;
			
			cbi.iItem = i;
			cbi.pszText = (LPTSTR)(LPCTSTR) str;
			cbi.cchTextMax = str.GetLength();
			cbi.iSelectedImage=1;
			cbi.iImage = 0;
			cbi.lParam=(LPARAM)Node;  
		
			
			nItem = m_comboEx->InsertItem(&cbi);
			
			Node=Node->nextChild ;
			i++;
		}
		COMBOBOXEXITEM     cbi;
	
		int                nItem;
		
		cbi.mask =  CBEIF_TEXT | CBEIF_LPARAM;
		
		cbi.iItem = i;
		cbi.pszText = (LPTSTR)(LPCTSTR) m_strExplorer;
		cbi.cchTextMax = m_strExplorer.GetLength();
		nItem = m_comboEx->InsertItem(&cbi);

		m_comboEx ->SetCurSel (0);	
	}
}

void CFindView::OnSelchangeComboex() 
{
	// TODO: Add your control notification handler code here IDS_QUERY_GOODS_FROM_PARTID
	CComboBoxEx * pComboEx = (CComboBoxEx*)GetDlgItem(IDC_COMBOEX);
	TCHAR szText[256];
	CTreeNode* pNode=NULL;
	COMBOBOXEXITEM     cbi;
	memset(&cbi,0,sizeof(cbi));
	cbi.mask =  CBEIF_TEXT | CBEIF_LPARAM;
	cbi.iItem = pComboEx->GetCurSel();
	cbi.pszText = szText;
	cbi.cchTextMax = 256;
	ASSERT(pComboEx->GetItem(&cbi));
	ASSERT(cbi.lParam);
	pNode=reinterpret_cast<CTreeNode*>(cbi.lParam);
		
	if(m_strExplorer.Compare(szText)==0)

	{
		CExplorerDlg dlg(this);
		if(dlg.DoModal ()==IDOK)
		{
			pNode=dlg.m_pNode ;
			COMBOBOXEXITEM     cbi;
			CString            str;
			int nItem=pComboEx->GetCount ();
			str=pNode->item.text.c_str();
			cbi.mask = CBEIF_IMAGE |  
                        CBEIF_SELECTEDIMAGE | CBEIF_TEXT | CBEIF_LPARAM;
			cbi.iItem =nItem; 
			cbi.pszText = (LPTSTR)(LPCTSTR) str;
			cbi.cchTextMax = str.GetLength();
			cbi.iSelectedImage=1;
			cbi.iImage = 0;
		 cbi.lParam=(LPARAM)pNode;
					
		    pComboEx->InsertItem(&cbi);
			pComboEx->SetCurSel (nItem);
		}
		else

		pComboEx->SetCurSel (0);
	}

}

void CFindView::EnumerateChildNodes(CTreeNode *pNode,int* pLevel)
{

	if((pNode!=NULL)&&(*pLevel>=0))
	{
		
		if((pNode->firstChild==NULL))
		{
			CString strAddText;
			strAddText.Format (_T("PCODE='%s' "),pNode->item.code  );
			
			m_lstPredicates.AddTail(strAddText );
		}
		(*pLevel)++;
		EnumerateChildNodes(pNode->firstChild,pLevel );
		EnumerateChildNodes(pNode->nextChild,pLevel);
		
	}
	else
	{
		(*pLevel)--;
		
	}

}


void CFindView::OnFindbtn() 
{
	
	Find();
}


CDBDoc* CFindView::GetDocument()
{
	CSplitterWnd* pWnd=static_cast<CSplitterWnd*>(GetParent());
	CDialogView* pView=static_cast<CDialogView*>(pWnd->GetPane (0,1));
	CDBDoc* pDoc=pView->GetDocument();
	return (CDBDoc*)pDoc;
}







void CFindView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFormView::OnShowWindow(bShow, nStatus);
	EnableToolTips (bShow);
	// TODO: Add your message handler code here
	if(bShow)m_wndEdit.SetFocus();
}



void CFindView::Find()
{
		// TODO: Add your control notification handler code here
	UpdateData (TRUE);//retrieve m_radio and m_strName

	m_lstPredicates.RemoveAll();
	if (m_radio!=0)//Find in selected categories
	{
		CComboBoxEx * pComboEx = (CComboBoxEx*)GetDlgItem(IDC_COMBOEX);
		TCHAR szText[256];
		CTreeNode* pNode=NULL;
		COMBOBOXEXITEM     cbi;
		memset(&cbi,0,sizeof(cbi));
		cbi.mask =  CBEIF_TEXT | CBEIF_LPARAM;
		cbi.iItem = pComboEx->GetCurSel();
		cbi.pszText = szText;
		cbi.cchTextMax = 256;
		ASSERT(pComboEx->GetItem(&cbi));
		ASSERT(cbi.lParam);
		pNode=reinterpret_cast<CTreeNode*>(cbi.lParam);
		ASSERT(pNode!=NULL);
		CInfoConsole* pThread=(CInfoConsole*)AfxGetThread();
		CMainDocument* pMainDoc= (CMainDocument*)pThread->m_pDocument;
		CTreeNode* pRootNode=/*pMainDoc->GetCategoryTree ().GetRootNode ()*/NULL;
	
		if((pNode!=pRootNode))
		{
			
			int nLevel=0;
			EnumerateChildNodes (pNode->firstChild,&nLevel );
		}
	}
	CString strFields,strCondition,strDiffCondition;
	strFields.LoadString(IDS_QUERY_GOODS_FROM_PARTID);
	UpdateData(TRUE);
	CString strName2;
	strName2=m_strName;
	strName2.MakeLower ();
	CString strFL=strName2.Left (1);
	strFL.MakeUpper ();
	
	strName2.SetAt (0,*strFL.GetBuffer(1));
	strFL.ReleaseBuffer ();
	strCondition.Format(_T(" WHERE catalog.Name LIKE '%%%s%%' AND catalog.ISFOLDER=0"),m_strName);
	strDiffCondition.Format(_T(" WHERE (Name LIKE UPPER(%c%%%s%%%c) OR Name LIKE LOWER(%c%%%s%%%c)  OR Name LIKE (%c%%%s%%%c))  AND ISFOLDER=0"),34,m_strName,34,34,m_strName,34,34,strName2,34);
	POSITION pos = m_lstPredicates.GetHeadPosition();
	int i=0;
	while( pos != NULL )
	{
		CString strTmp = static_cast<CString>(m_lstPredicates.GetNext( pos ));
		if(i<253){
			
	//	strTmp=strTmp;
		if (i==0)
		strCondition+="AND (" + strTmp;
		else
		strCondition+=" OR " + strTmp;
	
		}
		else if (i==253)
		strDiffCondition+="AND (" + strTmp;
		else if (i>253)
		strDiffCondition+=" OR " + strTmp;
		i++;
		
	}
	TRACE(_T("FieldCount=%d\n"),i );
	CDBDoc* pDoc=(CDBDoc*)GetDocument();
	pDoc->m_strSQL="";
	pDoc->m_strDiffSQL="";
	pDoc->m_strSQL=(i>0?strFields+strCondition +")":strFields+strCondition);
	if (i>=253)
	pDoc->m_strDiffSQL=strFields+strDiffCondition +")";
	//AfxMessageBox(pDoc->m_strSQL);
	pDoc->UpdateAllViews (this,0,NULL);	
}


BOOL CFindView::OnToolTipNotify(UINT id, NMHDR *pNMHDR,LRESULT *pResult)
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
	}
	
	if (nID != 0) // will be zero on a separator
	{
		
		
		strTipText.LoadString(nID);
	}
	
	if (pNMHDR->code == TTN_NEEDTEXTA)
#ifdef _UNICODE
		lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
#else
lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
#endif
/*	else
		_mbstowcsz(pTTTW->szText,strTipText, sizeof(pTTTW->szText));*/
	*pResult = 0;
	
	return TRUE;    // message was handled
	
}




BOOL CFindView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::DestroyWindow();
}

void CFindView::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnClose();
}
