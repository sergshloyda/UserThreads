////////////////////////////////////////////////////////////////
// Microsoft Systems Journal -- October 1999
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
#include "stdafx.h"
#include "Splash.h"
#include "userthreads.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CSplashWnd, CWnd)
BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_COPYDATA()
	ON_WM_CLOSE( )
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////
// CSplashWnd : the splash window

CSplashWnd::CSplashWnd()
{
}

CSplashWnd::~CSplashWnd()
{
}

//////////////////
// Create splash window: load bitmap and create the window
//
BOOL CSplashWnd::Create(UINT nIDRes, UINT duration, WORD flags)
{
#ifdef NODIB
	// Code for ordinary bitmap (assumes m_bitmap is a CBitmap)
	if (!m_bitmap.LoadBitmap(nIDRes))
		return FALSE;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	CSize sz(bm.bmWidth, bm.bmHeight);
#else
	if (!m_dib.Load(nIDRes))
		return FALSE;
	CSize sz = m_dib.GetSize();
#endif

	m_duration = duration;
	m_flags = flags;
	CString MySplashWnd=AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	return CreateEx(0,MySplashWnd,
		_T("Загрузка Продажи 1.3"),
		WS_POPUP | WS_VISIBLE|WS_BORDER,
		0, 0, sz.cx, sz.cy,
		NULL, // parent wnd
		NULL
		);//no menu
}

//////////////////
// Splash window created: center it, move to foreground and set a timer
//
int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CenterWindow();
	CRect r;
	GetClientRect(&r);
	/*r.bottom -= 15;
	r.top = r.bottom - 25;
	r.right -= 140;
	r.left = r.right - 120;
	*/
	r.top+=25;
	r.left +=25;
	r.bottom =r.top+155;
	//r.right =r.left +140;
	m_wndLabel.Create (NULL,WS_VISIBLE|WS_CHILD,r,this,0);
	int res = m_Font.CreatePointFont(80, _T("MS Sans Serif"));
	if (!res)
	{
		TRACE0("Не могу создать MS Sans Serif шрифт!");
		_ASSERT(res);
	}
	m_wndLabel.SetColor (RGB(255,255,20));
	m_wndLabel.SetLabelFont(&m_Font); //
	CRect rcInfo;
	GetClientRect(&rcInfo);

	
	rcInfo.top = r.bottom + 55;
	rcInfo.bottom = rcInfo.top+20;
	//rcInfo.right -= 140;
	rcInfo.left += 25;

	m_wndLabelInfo.Create (NULL,WS_VISIBLE|WS_CHILD,rcInfo,this,1);
	m_wndLabelInfo.SetColor (RGB(255,255,200));
	m_wndLabelInfo.SetLabelFont(&m_Font); 

	ModifyStyleEx(0,WS_EX_CLIENTEDGE );
	UpdateWindow();
	SetForegroundWindow();
	if (m_duration!=-1)
		SetTimer(1, m_duration, NULL);
	return 0;
}

//////////////////
// The window has been destroyed: put main app in foreground
// and post a message to quit this thread.
//
void CSplashWnd::PostNcDestroy()
{
	CWinApp* pApp = AfxGetApp();
	CWnd* pMainWnd = pApp->m_pMainWnd;
	if (IsWindow(pMainWnd->GetSafeHwnd()))
		::SetForegroundWindow(pMainWnd->GetSafeHwnd());
	::DestroyWindow (m_wndLabel.m_hWnd );
	//m_wndLabelInfo.DestroyWindow ();
	delete this;
}

//////////////////
// Draw the bitmap.
//
void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);
#ifdef NODIB
	// Code for ordinary bitmap:
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
#else
	m_dib.Draw(dc);
#endif
}

//////////////////
// Timer expired: kill myself--unless the app has
// not created a main window yet.
//
//DEL void CSplashWnd::OnTimer(UINT nIDEvent)
//DEL {
//DEL 	CWinApp* pApp = AfxGetApp();
//DEL 	CWnd* pMainWnd = pApp->m_pMainWnd;
//DEL 	if ((m_flags & CSplash::NoWaitForMainWnd) ||
//DEL 		IsWindow(pMainWnd->GetSafeHwnd()))
//DEL 	{
//DEL 		
//DEL 		// have main window: OK to die
//DEL 		SendMessage(WM_CLOSE);
//DEL 	}
//DEL 	else
//DEL 		// no main window: keep splashing
//DEL 		SetTimer(1,100,NULL);
//DEL }

//////////////////
// Before translating keystroke or mouse: die
//
BOOL CSplashWnd::PreTranslateMessage(MSG* pMsg)
{
	if (m_flags & CSplash::KillOnClick) {
		UINT msg = pMsg->message;
		if (msg == WM_KEYDOWN ||
			 msg == WM_SYSKEYDOWN ||
			 msg == WM_LBUTTONDOWN ||
			 msg == WM_RBUTTONDOWN ||
			 msg == WM_MBUTTONDOWN)
		{
			PostMessage(WM_CLOSE); // post don't send, to let current msg process
			return TRUE;			  // (eat current message)
		}
	}
	return CWnd::PreTranslateMessage(pMsg);
}
BOOL CSplashWnd::OnCopyData( CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct )
{

	switch(pCopyDataStruct->dwData )
	{
	case 0:
		
		m_wndLabelInfo.SetText ((LPCTSTR)pCopyDataStruct->lpData );
		break;
	case 1:
		m_wndLabel.SetText((LPCTSTR)pCopyDataStruct->lpData);
		break;
	default:
		break;
	}
//	delete strText;
	return TRUE;
}

void CSplashWnd::OnClose()
{
	TRACE0("CSplashWnd::OnClose\n");
	CWnd::OnClose();
}
////////////////////////////////////////////////////////////////
// CSplash, a thread object

IMPLEMENT_DYNAMIC(CSplash, CWinThread)

//////////////////
// Create a new splash thread
//
CSplash::CSplash(UINT nIDRes, UINT duration, WORD flags, CSplash** ppBackPtr)
{
	m_ppBackPtr = ppBackPtr;
	m_nIDRes = nIDRes;
	m_duration = duration;
	m_flags = flags;
	g_hEvent=::CreateEvent(NULL,TRUE,FALSE,NULL);
	CreateThread();

}

/////////////////
// Destruction: Set caller's pointer to NULL, so he knows I'm gone.
//
CSplash::~CSplash()
{
	if (m_ppBackPtr)
		*m_ppBackPtr = NULL;
}

//////////////////
// Thread initialization.
// Returns TRUE to keep running, otherwise FALSE
// if I determine I'm not supposed to run the splash
//
BOOL CSplash::InitInstance()
{
	// Check for -nologo switch
	CWinApp* pApp = AfxGetApp();
	ASSERT(pApp);

	// Look for -nologo switch, or any others that MFC thinks should
	// prohibit a splash screen (such as OLE embedding, etc.)
	//

	
	if (!AfxOleGetUserCtrl())  // running without UI: to be safe
		return FALSE;

	// Create the splash window
	m_pMainWnd = OnCreateSplashWnd(m_nIDRes, m_duration, m_flags);
	::SetEvent(g_hEvent);
	return m_pMainWnd != NULL;
}

//////////////////
// Create the splash window. This is virtual so you can override to create
// somet other kind of window if you like. 
//
CWnd* CSplash::OnCreateSplashWnd(UINT nIDRes, UINT duration, WORD flags)
{
	CSplashWnd *pSplashWnd = new CSplashWnd;
	if (pSplashWnd)
		pSplashWnd->Create(nIDRes, duration, flags);
	return pSplashWnd;
}

//////////////////
// Kill the splash window. Could set a CEvent to
// terminate thread, but easier to post a close message.
//
void CSplash::Kill()
{
	//::Sleep(10000);
	if (m_pMainWnd)
		m_pMainWnd->PostMessage(WM_CLOSE);
}

void CSplash::SetText1(LPCTSTR strText)

{
CSplashWnd* pSplashWnd=(CSplashWnd*)m_pMainWnd;
pSplashWnd->SetText1 (strText);
}

void CSplashWnd::SetText1(LPCTSTR strText)
{
m_wndLabel.SetText(strText);
}
