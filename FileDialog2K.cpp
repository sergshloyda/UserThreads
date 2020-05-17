// FileDialog2K.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "FileDialog2K.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDialog2K

IMPLEMENT_DYNAMIC(CFileDialog2K, CFileDialog)

CFileDialog2K::CFileDialog2K(BOOL bOpenFileDialog,
                LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
                DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
                CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName,
                            dwFlags, lpszFilter, pParentWnd)
{
        m_pofn2K = NULL;
}


BEGIN_MESSAGE_MAP(CFileDialog2K, CFileDialog)
        //{{AFX_MSG_MAP(CFileDialog2K)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CFileDialog2K::DoModal()
{
        ASSERT_VALID(this);
        ASSERT(m_ofn.Flags & OFN_ENABLEHOOK);
        ASSERT(m_ofn.lpfnHook != NULL); // can still be a user hook

        // zero out the file buffer for consistent parsing later
        ASSERT(AfxIsValidAddress(m_ofn.lpstrFile, m_ofn.nMaxFile));
        DWORD nOffset = lstrlen(m_ofn.lpstrFile)+1;
        ASSERT(nOffset <= m_ofn.nMaxFile);
        memset(m_ofn.lpstrFile+nOffset, 0, (m_ofn.nMaxFile-nOffset)*sizeof(TCHAR));

        // WINBUG: This is a special case for the file open/save dialog,
        //  which sometimes pumps while it is coming up but before it has
        //  disabled the main window.
        HWND hWndFocus = ::GetFocus();
        BOOL bEnableParent = FALSE;
        m_ofn.hwndOwner = PreModal();
        AfxUnhookWindowCreate();
        if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
        {
                bEnableParent = TRUE;
                ::EnableWindow(m_ofn.hwndOwner, FALSE);
        }

        _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
        ASSERT(pThreadState->m_pAlternateWndInit == NULL);

        if (m_ofn.Flags & OFN_EXPLORER)
                pThreadState->m_pAlternateWndInit = this;
        else
                AfxHookWindowCreate(this);

        // с этого места внесены добавления и исправления

        int nResult = -1;

        DWORD dwWinMajorVersion = GetVersion();

        if(dwWinMajorVersion > 2)
        {
                if(LOBYTE(LOWORD(dwWinMajorVersion) )> 4) // Windows 2000 и выше
                {
                        m_pofn2K = new OPENFILENAME_2K;

                        memset(m_pofn2K, 0, sizeof(OPENFILENAME_2K));
                        memcpy(m_pofn2K, &m_ofn, sizeof(OPENFILENAME));

                        m_pofn2K->ofn.lStructSize = sizeof(OPENFILENAME_2K);
                }

                if (m_bOpenFileDialog)
                        nResult = ::GetOpenFileName(m_pofn2K ?
                                    (LPOPENFILENAME) m_pofn2K : &m_ofn);
                else
                        nResult = ::GetSaveFileName(m_pofn2K ?
                                    (LPOPENFILENAME) m_pofn2K : &m_ofn);

                if(m_pofn2K)
                {
                        memcpy(&m_ofn, m_pofn2K, sizeof(m_ofn));
                        m_ofn.lStructSize = sizeof(m_ofn);

                        delete m_pofn2K;

                        m_pofn2K = NULL;
                }
        }

        // в этом месте добавления и исправления заканчиваются

        if (nResult)
                ASSERT(pThreadState->m_pAlternateWndInit == NULL);
        
        pThreadState->m_pAlternateWndInit = NULL;

        // WINBUG: Second part of special case for file open/save dialog
        if (bEnableParent)
                ::EnableWindow(m_ofn.hwndOwner, TRUE);
        if (::IsWindow(hWndFocus))
                ::SetFocus(hWndFocus);

        PostModal();
        return nResult ? nResult : IDCANCEL;
}

BOOL CFileDialog2K::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
        if(m_pofn2K != NULL)
        {
                memcpy(&m_ofn, &m_pofn2K->ofn, sizeof(m_ofn));
                m_ofn.lStructSize = sizeof(m_ofn);
        }

        return CFileDialog::OnNotify(wParam, lParam, pResult);
}



 
