// PSDlgInsertGood.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "PSDlgInsertGood.h"
#include "DlgSetQuantity.h"
#include "MainDocument.h"
#include "NotyfyFndProduct.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSDlgInsertGood
TCHAR CPSDlgInsertGood::s_profileHeading[] =_T("PropertySheetSize");
TCHAR CPSDlgInsertGood::s_profileRect[] =_T("Rect");
TCHAR CPSDlgInsertGood::s_profilePage[]=_T("Page");

IMPLEMENT_DYNAMIC(CPSDlgInsertGood, CPropertySheet)

CPSDlgInsertGood::CPSDlgInsertGood(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

//	pParent=static_cast<CView*>(pParentWnd);
}

CPSDlgInsertGood::CPSDlgInsertGood(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage), m_bNeedInit(TRUE)	 , m_nMinCX(0)	 , m_nMinCY(0)
{

	//pParent=static_cast<CView*>(pParentWnd);
	
	m_pgSelBarCode=NULL;
	m_pgSelGood=NULL;
	m_bFirstTime=TRUE;
	
}

CPSDlgInsertGood::~CPSDlgInsertGood()
{

//	delete m_pgSelBarCode;
	//delete m_pgSelGood;
}


BEGIN_MESSAGE_MAP(CPSDlgInsertGood, CPropertySheet)
	//{{AFX_MSG_MAP(CPSDlgInsertGood)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_RESIZEPAGE, OnResizePage)
    ON_COMMAND (ID_APPLY_NOW, OnApplyNow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSDlgInsertGood message handlers

void CPSDlgInsertGood::SetPageTitle(int nPage,LPTSTR pszText)
{
	CTabCtrl* pTab = GetTabControl();
    ASSERT (pTab);
	
    TC_ITEM ti;
    ti.mask = TCIF_TEXT;
    ti.pszText = pszText;
    VERIFY (pTab->SetItem (nPage, &ti));


}



BOOL CPSDlgInsertGood::SetPageIcon(int nPage,int nIcon)
{
	CTabCtrl* pTab = GetTabControl();
    ASSERT (pTab);
	
    TC_ITEM ti;
	ti.mask=TCIF_IMAGE;
	ti.iImage=nIcon;
	VERIFY (pTab->SetItem (nPage, &ti));
	//pTab->Invalidate ();
	return TRUE;
}
// Create and associate a tooltip control to the tab control of 
// CMyPropertySheet.  CMyPropertySheet is a CPropertySheet-derived
// class.
BOOL CPSDlgInsertGood::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();

	CreateTipWindow (IDC_TIPWND,this);//для отображения полного наименования

	CWnd* pOKButton = GetDlgItem (IDOK);
	ASSERT (pOKButton);
	pOKButton->ShowWindow (SW_HIDE);//скроем ОК кнопку

	CWnd* pCancelBtn = GetDlgItem (IDCANCEL);
	ASSERT (pCancelBtn);
	CString txtBtn;
	pCancelBtn->SetWindowText(_T("Закрыть(Esc)"));
    CRect rcCancel;
	pCancelBtn->GetWindowRect (&rcCancel);
	ScreenToClient(&rcCancel);
	//rcCancel.right +=20;
	rcCancel.left -=10;
	rcCancel.bottom  +=3;
	pCancelBtn->MoveWindow (&rcCancel);

	
	m_pgSelGood=(CDlgSelectGood*)GetPage(0);
	m_pgSelBarCode=(CDlgInsert*)GetPage(1);
	
	SetPageTitle(0,_T("Выбор из под&Каталогов "));
	SetPageTitle(1,_T("Выбор по &Штрихкоду "));
	SetPageTitle(2,_T("&Поиск "));


	
	// Associate the tooltip control to the tab control
	// of CMyPropertySheet.
	CTabCtrl* tab = GetTabControl();
	
	
	CSize szImage(32,32);
	CSize szMargin(6,6);
	HICON hIcon[3];
	int n;
	m_ImageList.Create (szImage.cx ,szImage.cy ,ILC_COLOR8|ILC_MASK,2,2);
	hIcon[0]=AfxGetApp()->LoadIcon (IDI_FOLDERSFILE);
	hIcon[1]=AfxGetApp()->LoadIcon (IDI_BARCODE);
	hIcon[2]=AfxGetApp()->LoadIcon (IDI_FIND);
	for(n=0;n<3;n++)
		m_ImageList.Add (hIcon[n]);
	tab->SetImageList (&m_ImageList);
	
	CSize szItem=szImage+szMargin;
	CRect rcTabRect;

	//мы сделали вкладки выше  для больших икон, самое время
	//уменьшить высоту страницы(Page)

	tab->GetWindowRect(rcTabRect);
	CPropertyPage* pPage = GetActivePage ();
	ASSERT (pPage);
	CRect rcPageRect;
	// store page size in rcPageRect
	pPage->GetWindowRect (&rcPageRect);

	int nOldTabHeight= rcPageRect.top-rcTabRect.top ;
	rcPageRect.top+=(szItem.cy - nOldTabHeight);
	//rcPageRect.DeflateRect (0,szItem.cy -nOldTabHeight);
	ScreenToClient(&rcPageRect);
	pPage->MoveWindow (rcPageRect);

	SetActivePage (0);
	// Get the bounding rectangle of each tab in the tab control of the
	// property sheet. Use this rectangle when registering a tool with 
	// the tool tip control.  IDS_FIRST_TOOLTIP is the first ID string 
	// resource that contains the text for the tool.
	int count = tab->GetItemCount();
	int id = IDS_FIRST_TOOLTIP;

	for (int i = 0; i < count; i++)
	{
		id += i;
		CRect r;
		tab->GetItemRect(i, &r);
	
		
		SetPageIcon(i,i);
	}

	
	/* Subclass the tab control. */ 
	m_myTabCtrl.SubclassWindow(GetTabControl()->m_hWnd);
	
	/* Make it owner drawn. for change fonts*/ 
	m_myTabCtrl.ModifyStyle(0,TCS_OWNERDRAWFIXED);

	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();	
	LOGFONT logFont;
	pDoc->m_FontMap[_T("Dialogs")]->GetLogFont(&logFont);
	long szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));
	CString strFontName(logFont.lfFaceName);
	m_myTabCtrl.SetFont(szFont,strFontName);
	
	// Activate the tooltip control.

	RestorePropertyPage ();
	

	tab->SetMinTabWidth (rcPageRect.Width ()/3);//set tabwidth equal
// Init m_nMinCX/Y
	 CRect r;  GetWindowRect(&r);
   m_nMinCX = r.Width();
   m_nMinCY = r.Height();
   // After this point we allow resize code to kick in
   m_bNeedInit = FALSE;
   GetClientRect(&m_rCrt);

	return bResult;
}

// Override PreTranslateMessage() so RelayEvent() can be 
// called to pass a mouse message to CMyPropertySheet's 
// tooltip control for processing.
BOOL CPSDlgInsertGood::PreTranslateMessage(MSG* pMsg) 
{

	if (pMsg->message == WM_SYSKEYDOWN)
    {
        switch (pMsg->wParam)
        {
		case 'R' :
			SetActivePage(0);
			break;
			
		case 'I' :
			SetActivePage(1);
			break;
		case 'G' :
			SetActivePage(2);
		break;	
            // ... case statements for each key being trapped
			
		default :  // unhandled keystroke
			return CPropertySheet::PreTranslateMessage(pMsg);
			break;
        }
		
        return TRUE;  // msg is processed

    }
	else if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST&&pMsg->hwnd==m_hWnd)
	{
		switch (pMsg->wParam)
        {
		case VK_ESCAPE:
			PressButton(PSBTN_CANCEL);   
			break;
		default:
			return CPropertySheet::PreTranslateMessage(pMsg);
			break;
		}
		return TRUE;
	}
	
	return CPropertySheet::PreTranslateMessage(pMsg);
}






void CPSDlgInsertGood::OnSelectGood(const CString &strCode)
{
	//ASSERT(pParent);
	USES_CONVERSION;
	CDlgSetQuantity dlg(strCode,NULL);
	//	CString strItem;
	int ret=dlg.DoModal ();
	if (ret==IDOK)
	{
		int nQty=dlg.m_nQty;
		CFrameWnd* pParentFrame=GetParentFrame();
		HWND hMain=pParentFrame->GetSafeHwnd();
		NMHDR hdr;
		hdr.code=FND_BY_CODE;
		hdr.hwndFrom=hMain;
		hdr.idFrom=0;
		Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
		boost::shared_ptr<Repository::UnitsReference> refUnits=pRep->getUnits();
		CString strBarCode=_T("");
		if(refUnits->SelectItemsByAttribute(ISReference<Products>::ListOfAttr::Owner(),A2W(strCode)))
		{
			Repository::ReferenceItem unit=refUnits->getCurrent();
			strBarCode=W2A(unit->_code.c_str());
		}
		CNotyfyFndProduct* pObject=new CNotyfyFndProduct(hdr,nQty,strCode,strBarCode);
		pParentFrame->PostMessageA(WM_NOTIFY,0,(LPARAM)&(pObject->m_hdrObject));
	}

}

BOOL CPSDlgInsertGood::CreateTipWindow(UINT nID, CWnd *pParent)
{
	const int nBorder=4;
	CRect rcOK;
	GetDlgItem(IDOK)->GetWindowRect(&rcOK);
	ScreenToClient(&rcOK);
	CRect rc;
	GetClientRect(&rc);
	rc.right  =rcOK.left ;
//	rc.InflateRect (-nBorder,-nBorder);
	rc.top =rcOK.top ;
//	rc.bottom =rcOK.bottom+5;
	m_wndTip.Create (NULL,WS_VISIBLE|WS_CHILD,rc,pParent,nID);
	m_wndTip.SetColor(RGB(0,0,200));
	m_wndTip.SetText (_T("Полное наименование"));
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	m_wndTip.SetFont (pMainDoc->m_FontMap[_T("Dialogs")].get());


	return TRUE;

}

void CPSDlgInsertGood::SetTipText(LPCTSTR strText)
{
	m_wndTip.SetText (strText);

}

BOOL CPSDlgInsertGood::DestroyWindow() 
{
	/*CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	pMainDoc->pRstCatalog=pRstCatalog;
	pMainDoc->pRstCatalog->Requery(adCmdUnknown);*/
	CRect rcWndPos;
	GetWindowRect(&rcWndPos);
	CString strText;
	strText.Format(_T("%04d %04d %04d %04d"),rcWndPos.left ,rcWndPos.top,rcWndPos.right,rcWndPos.bottom);
	AfxGetApp()->WriteProfileString (s_profileHeading,s_profileRect,strText);
	AfxGetApp()->WriteProfileInt (s_profileHeading,s_profilePage,GetActiveIndex ());
	return CPropertySheet::DestroyWindow();
}

HBRUSH CPSDlgInsertGood::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return (HBRUSH)GetStockObject (WHITE_BRUSH);
}

int CALLBACK CPSDlgInsertGood::XmnPropSheetCallback(HWND hWnd,
                                        UINT message, LPARAM lParam)
{
   extern int CALLBACK AfxPropSheetCallback(HWND, UINT message, LPARAM lParam);
   // XMN: Вызывает MFC-шный callback
   int nRes = AfxPropSheetCallback(hWnd, message, lParam);

   switch (message)
   {
   case PSCB_PRECREATE:
      // Устанавливаем наши собственные стили окна
      ((LPDLGTEMPLATE)lParam)->style |= (DS_3DLOOK | DS_SETFONT
         | WS_THICKFRAME | WS_SYSMENU | WS_POPUP | WS_VISIBLE | WS_CAPTION);
      break;
   }
   return nRes;
}

int CPSDlgInsertGood::DoModal() 
{
	PROPSHEETHEADER* psh = &m_psh;;
   psh->dwFlags |= PSH_USECALLBACK;
   psh->pfnCallback = XmnPropSheetCallback;
   return CPropertySheet::DoModal();
}

void CPSDlgInsertGood::OnSize(UINT nType, int cx, int cy) 
{
	CRect r1; 
   CPropertySheet::OnSize(nType, cx, cy);

   if (m_bNeedInit)
      return;

   CTabCtrl *pTab = GetTabControl();
   ASSERT(NULL != pTab && IsWindow(pTab->m_hWnd));
    
   int dx = cx - m_rCrt.Width();
   int dy = cy - m_rCrt.Height();
   GetClientRect(&m_rCrt);

   HDWP hDWP = ::BeginDeferWindowPos(5);

   pTab->GetClientRect(&r1); 
   r1.right += dx; r1.bottom += dy;
   ::DeferWindowPos(hDWP, pTab->m_hWnd, NULL,
                    0, 0, r1.Width(), r1.Height(),
                    SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);

   // Move all buttons with the lower right sides
   for (CWnd *pChild = GetWindow(GW_CHILD);
        pChild != NULL;
        pChild = pChild->GetWindow(GW_HWNDNEXT))
   {
      if (pChild->SendMessage(WM_GETDLGCODE) & DLGC_BUTTON)
      {
         pChild->GetWindowRect(&r1); ScreenToClient(&r1); 
         r1.top += dy; r1.bottom += dy; r1.left+= dx; r1.right += dx;
         ::DeferWindowPos(hDWP, pChild->m_hWnd, NULL,
                          r1.left, r1.top, 0, 0,
                          SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
      }
	  else if (pChild->SendMessage(WM_GETDLGCODE) & DLGC_STATIC)
      {
         pChild->GetWindowRect(&r1); ScreenToClient(&r1); 
         r1.top += dy; r1.bottom += dy; /*r1.left+= dx;*/ r1.right += dx;
         ::DeferWindowPos(hDWP, pChild->m_hWnd, NULL,
                          r1.left, r1.top, 0, 0,
                          SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
      }
      // Resize everything else...
      else 
      {
         pChild->GetClientRect(&r1); 
	 r1.right += dx; r1.bottom += dy;
	 ::DeferWindowPos(hDWP, pChild->m_hWnd, NULL, 0, 0, r1.Width(), r1.Height(),SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
      }

   }

   ::EndDeferWindowPos(hDWP);
	
}

void CPSDlgInsertGood::RestorePropertyPage()
{
	CRect rectNew,rc;
	
	
	CString strText;
	int nActivePage=0;
	if(m_bFirstTime)
	{
		m_bFirstTime=FALSE;
		strText=AfxGetApp()->GetProfileString (s_profileHeading,s_profileRect);
		nActivePage=AfxGetApp()->GetProfileInt (s_profileHeading,s_profilePage,0);
		if(!strText.IsEmpty())
		{
			rectNew.left=_ttoi((const TCHAR*)strText);
			rectNew.top=_ttoi((const TCHAR*)strText+5);
			rectNew.right=_ttoi((const TCHAR*)strText+10);
			rectNew.bottom=_ttoi((const TCHAR*)strText+15);
			
			SetActivePage (nActivePage);
			
			GetWindowRect (&rc);
			CSize szDelta(rectNew.Width() -rc.Width() ,rectNew.Height () -rc.Height () );
            MoveWindow (&rectNew);
			//resize Esc button
			CWnd* pWnd = GetDlgItem(IDCANCEL);
			pWnd->GetWindowRect(&rc);
			rc.left +=szDelta.cx ;
			rc.top += szDelta.cy;
			rc.right +=szDelta.cx ;
			rc.bottom += szDelta.cy;
			
			ScreenToClient(&rc);
			pWnd->MoveWindow(&rc);
			//resize tip window
			m_wndTip.GetWindowRect(&rc);
			rc.left =rectNew.left+10;
			rc.top += szDelta.cy;
			rc.right +=szDelta.cx ;
			rc.bottom += szDelta.cy;
			
			ScreenToClient(&rc);
			m_wndTip.MoveWindow(&rc);
			// resize the CTabCtrl
			CTabCtrl* pTab = GetTabControl ();
			ASSERT (pTab);
			pTab->GetWindowRect (&rc);
			ScreenToClient (&rc);
			rc.right += szDelta.cx ;
			rc.bottom += szDelta.cy;
			pTab->MoveWindow (&rc);
			// resize the page
			CPropertyPage* pPage = GetActivePage ();
			ASSERT (pPage);
			// store page size in m_PageRect
			pPage->GetWindowRect (&m_PageRect);
			ScreenToClient (&m_PageRect);
			m_PageRect.right += szDelta.cx ;
			m_PageRect.bottom += szDelta.cy;
			pPage->MoveWindow (&m_PageRect);
		}
	}
}
LRESULT CPSDlgInsertGood::OnResizePage(WPARAM, LPARAM)
 {
     // resize the page using m_PageRect which was set in OnInitDialog()
     CPropertyPage* pPage = GetActivePage ();
	 if(pPage->IsKindOf(RUNTIME_CLASS(CDlgSelectGood)))
	 {
		 NMHDR hdr;
		 hdr.code=FND_BY_CODE;
		 hdr.hwndFrom=m_hWnd;
		 hdr.idFrom=0;
		 CNotyfyFndProduct* pObject=new CNotyfyFndProduct(hdr,0,m_strSelectProduct,_T(""));
		 pPage->PostMessageA(WM_NOTIFY,0,(LPARAM)&(pObject->m_hdrObject));
	 }
     ASSERT (pPage);
     pPage->MoveWindow (&m_PageRect);

     return 0L;
 }

 BOOL CPSDlgInsertGood::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
 {
     NMHDR* pnmh = (LPNMHDR) lParam;

     // the sheet resizes the page whenever it is activated
     // so we need to resize it to what we want
     if (TCN_SELCHANGE == pnmh->code)
	 {
         // user-defined message needs to be posted because page must
         // be resized after TCN_SELCHANGE has been processed
		 // CPropertyPage* pPage = GetActivePage ();
		// AfxMessageBox(pPage->GetPSP().pszTitle);
         PostMessage (WM_RESIZEPAGE);
		*pResult=0;
	 }
     return CPropertySheet::OnNotify(wParam, lParam, pResult);
 }

 void CPSDlgInsertGood::OnApplyNow()
 {
     // the sheet resizes the page whenever the Apply button is clicked
     // so we need to resize it to what we want
     PostMessage (WM_RESIZEPAGE);
 }