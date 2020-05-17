// MDIClient.cpp : implementation file
//

#include "stdafx.h"
//#include "MDIForms.h"
#include "MDIClient.h"
#include "ViewManager.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ID_VIEW_VIEWTAB                 32771
/////////////////////////////////////////////////////////////////////////////
// CMDIClient
static TCHAR szSection[]     = _T("Settings");
static TCHAR szChildWinPos[] = _T("TVChildWinState");
static TCHAR szLogoFont[]    = _T("TVLogoFont");
static TCHAR szLogoColor[]   = _T("TVLogoColor");
static TCHAR szWindowPos[]   = _T("TVWindowPos");
static TCHAR szDispType[]    = _T("TVDispType");
static TCHAR szFileName[]    = _T("TVFileName");
static TCHAR szBackColor[]   = _T("TVBackColor");
static TCHAR szBkBitmap[]    = _T("TVBkBitmap");
static TCHAR szFormat[]      = _T("%u,%u,%d,%d,%d,%d,%d,%d,%d,%d");

static BOOL ReadWindowPlacement(LPWINDOWPLACEMENT pwp)
{
	CString strBuffer = AfxGetApp()->GetProfileString(szSection, szWindowPos);
	if (strBuffer.IsEmpty())
		return FALSE;
	
	WINDOWPLACEMENT wp;
	
	int nRead = _stscanf(strBuffer, szFormat,
		&wp.flags, &wp.showCmd,
		&wp.ptMinPosition.x, &wp.ptMinPosition.y,
		&wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
		&wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
		&wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);
	
	if (nRead != 10)
		return FALSE;
	
	wp.length = sizeof(WINDOWPLACEMENT);
	*pwp = wp;
	return TRUE;
}

static void WriteWindowPlacement(LPWINDOWPLACEMENT pwp)
	// write a window placement to settings section of app's ini file
{
	TCHAR szBuffer[sizeof("-32767")*8 + sizeof("65535")*2];
	
	wsprintf(szBuffer, szFormat,
		pwp->flags, pwp->showCmd,
		pwp->ptMinPosition.x, pwp->ptMinPosition.y,
		pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
		pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
		pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);
	AfxGetApp()->WriteProfileString(szSection, szWindowPos, szBuffer);
}

CMDIClient::CMDIClient()
{
	m_pMDIFrame           = NULL;
	m_pViewManager        = NULL;
	m_bFirstTime          = TRUE;
	m_bMaxChild           = FALSE;
}

CMDIClient::~CMDIClient()
{
}


BEGIN_MESSAGE_MAP(CMDIClient, CWnd)
	//{{AFX_MSG_MAP(CMDIClient)
	ON_WM_DESTROY()
	ON_WM_MDIACTIVATE()
	ON_MESSAGE(WM_MDICREATE, OnMDICreate)
	ON_MESSAGE(WM_MDIDESTROY, OnMDIDestroy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LRESULT CMDIClient::OnMDICreate(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd  = reinterpret_cast<HWND>(DefWindowProc(WM_MDICREATE, wParam, lParam));
	ASSERT(hWnd != NULL);
	CMDIChildWnd *pChild = static_cast<CMDIChildWnd*>(FromHandle(hWnd));
	if (pChild == NULL)
		return NULL;
	
	if (m_pViewManager->GetWindowNum() > 0)
	{
		CMDIChildWnd* pActiveChild = m_pMDIFrame->MDIGetActive();
		DWORD dwStyle = ::GetWindowLong(pActiveChild->m_hWnd, GWL_STYLE);
		m_bMaxChild   = (dwStyle & WS_MAXIMIZE) ? TRUE : FALSE;
	
	}


	// TODO-bug shows even if the document does not exits!!!
	if (m_bFirstTime && m_bMaxChild)
		m_pMDIFrame->MDIMaximize(pChild);
	else if (m_bMaxChild && m_pViewManager->GetWindowNum() == 0)
		m_pMDIFrame->MDIMaximize(pChild);
	
	m_pViewManager->AddView(_T(""), pChild);
	return (LRESULT) hWnd;
}

LRESULT CMDIClient::OnMDIDestroy(WPARAM wParam, LPARAM lParam)
{
	CMDIChildWnd* pChild = 
		static_cast<CMDIChildWnd*>(FromHandle(reinterpret_cast<HWND>(wParam)));
	ASSERT(pChild != NULL);
	
	// It will be useful to save the state of the last child window closed and
	// use this for displaying the next window...

	
	m_pViewManager->RemoveView(pChild);
	return DefWindowProc(WM_MDIDESTROY,  wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIClient message handlers

void CMDIClient::OnDestroy() 
{
	CWnd::OnDestroy();
	
	if (m_pViewManager != NULL)
	{
		delete m_pViewManager;
		m_pViewManager = NULL;
	}	
}

BOOL CMDIClient::SubclassMDIClient(CMDIFrameWnd *pMDIFrameWnd)
{
	// Subclass the MDI client window
    VERIFY(this->SubclassWindow(pMDIFrameWnd->m_hWndMDIClient));


	m_pMDIFrame    = reinterpret_cast<CInfoFrame*>(pMDIFrameWnd); // TODO
	//m_pMDIFrame->LoadBarState(AfxGetApp()->m_pszProfileName);
	return TRUE;
}

void CMDIClient::RestoreMainFrameState(UINT nCmdShow)
{
		WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	if (!ReadWindowPlacement(&wp))
	{
		m_pMDIFrame->ShowWindow(nCmdShow);
		return;
	}
	if (nCmdShow != SW_SHOWNORMAL)
		wp.showCmd = nCmdShow;
	m_pMDIFrame->SetWindowPlacement(&wp);
	m_pMDIFrame->ShowWindow(wp.showCmd);

	m_bMaxChild=(BOOL)(AfxGetApp()->GetProfileInt(szSection, szChildWinPos, 0));

}

void CMDIClient::SaveMainFrameState()
{
	CMDIChildWnd* pChild = m_pMDIFrame->MDIGetActive();
	if (pChild)
	{
		// It will be useful to save the state of the last child window closed and
		// use this for displaying the next window...
		DWORD dwStyle = ::GetWindowLong(pChild->m_hWnd, GWL_STYLE);
		// Save the necessary options for later restoration process
		m_bMaxChild  =(dwStyle & WS_MAXIMIZE) ? TRUE : FALSE;
		AfxGetApp()->WriteProfileInt(szSection, szChildWinPos, m_bMaxChild);
	}
	
	// before it is destroyed, save the position of the window
	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	if (m_pMDIFrame->GetWindowPlacement(&wp))
	{
		wp.flags = 0;
		if (m_pMDIFrame->IsZoomed())
			wp.flags |= WPF_RESTORETOMAXIMIZED;
		// and write it to the registry
		WriteWindowPlacement(&wp);
	}
	m_pMDIFrame->SaveBarState(AfxGetApp()->m_pszProfileName);
}

void CMDIClient::SetViewManager(CMDIFrameWnd* pMDIFrameWnd)
{

	if(m_pViewManager==NULL)
			{
				m_pViewManager = new CViewManager;

				m_pViewManager->CreateViewManager(pMDIFrameWnd, ID_VIEW_VIEWTAB);
				m_pViewManager->m_ViewTabCtrl.SetTabStyle(TRUE, FALSE);//Set Tab Style TCS_BUTTONS
				
				//m_pMDIFrame->LoadBarState(AfxGetApp()->m_pszProfileName);		
	}

}

void CMDIClient::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
	
}


