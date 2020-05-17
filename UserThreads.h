 // UserThreads.h : main header file for the USERTHREADS application
//

#if !defined(AFX_USERTHREADS_H__B35DF4BD_4636_49B5_BC43_D307E0F62B29__INCLUDED_)
#define AFX_USERTHREADS_H__B35DF4BD_4636_49B5_BC43_D307E0F62B29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define MAX_LENGHT 256


#define _CRTDBG_MAP_ALLOC
#pragma warning(disable:4996)
#include <stdlib.h>
#include <crtdbg.h>


#include "resource.h"       // main symbols
#include "UserThreads_i.h"
#include "Splash.h"
#include "MainDocument.h"
#include "Register.h"
//#include "DbContext.h"
#include "boost\shared_ptr.hpp"
#include "MessageBoxHelper.h"
//#import "C:\VisualCStudy1\Dir1CServer\Dir1CServer.tlb" no_namespace,named_guids,raw_interfaces_only
//user messages
#define WM_VIEW_CLIENT_INFO     WM_USER + 2
#define WM_FONT_CHANGED         WM_USER + 3
#define WM_GETINFO_FROMNODE     WM_USER + 4
#define WM_DISCONNECTBASE       WM_USER + 5
#define WM_CONNECTBASE          WM_USER + 6
#define WM_SETFOCUSGRID         WM_USER + 7
#define WM_SPLASH_INFO          WM_USER + 8
#define WM_CHANGE_MULTIPLICATOR WM_USER + 9
#define WM_RECEIVED_BARCODE     WM_USER + 10
//#define GridPtr IVSFlexGridPtr
/////////////////////////////////////////////////////////////////////////////
void PrintProviderError(_ConnectionPtr pConnection);
void PrintComError(_com_error &e);
// CUserThreadsApp:
// See UserThreads.cpp for the implementation of this class
//
class CInfoConsole;
class CCashDoc;
class CCheckDoc;
class DbContext;
class CMainDocument;
class CUserThreadsApp : public CWinApp
{
public:
	
	BOOL DisconnectBase();
	

	HANDLE g_hEventBaseOccupied;
	HANDLE g_hEventFocus;
	HANDLE g_hCommPortOpen;
	DWORD m_dwCookie;
//	CComPtr<IDir1CServ> m_pDataProvider;
	void GetExePath(LPTSTR strPath);
	BOOL ConnectBase(CString &strConnString);

	CUserThreadsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserThreadsApp)
	public:
	virtual BOOL InitInstance();
	virtual void OnFinalRelease();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL
	HWND hwndInfoWnd;

	CInfoConsole* m_pInfoConsoleThread;
	_ConnectionPtr pConn/*,pConnLocal*/;
//	IProxiOneCObjectPtr m_pProxi;
	CSplash *pSplash;
// Implementation
	//{{AFX_MSG(CUserThreadsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnRefreshCatalog();

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
protected:
	template <class T> static void RegisterDocument()
	{
		CRuntimeClass* pNewDocClass;
		pNewDocClass = RUNTIME_CLASS(T);
		T* pMainDoc=static_cast <T*>(pNewDocClass->CreateObject ());

		pMainDoc->OnNewDocument ();
		CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
		POSITION posTempl=pApp->m_pDocManager->GetFirstDocTemplatePosition ();
		//we have the 1 DocTemplate
		CDocTemplate* pTempl=pApp->m_pDocManager->GetNextDocTemplate (posTempl);
		pTempl->AddDocument (pMainDoc);
	}
	
	//	long NomenclatureChanged();
	
private:
//CMemoryState oldMemState, newMemState, diffMemState;
	boost::shared_ptr<DbContext> dbCtxt_;
public:
	 template <class T> static T* GetDocument()
	{
		CUserThreadsApp* pApp=(CUserThreadsApp*)AfxGetApp();
		POSITION posTempl=pApp->m_pDocManager->GetFirstDocTemplatePosition ();
		//we have the 1 DocTemplate
		CDocTemplate* pTempl=pApp->m_pDocManager->GetNextDocTemplate (posTempl);
		POSITION posDoc=pTempl->GetFirstDocPosition ();
		CDocument *pDoc=NULL;
		while(posDoc)
		{
			pDoc=pTempl->GetNextDoc (posDoc);
			if(pDoc->IsKindOf (RUNTIME_CLASS(T)))
				break;
		}
		return (T*)pDoc;
	}
	 bool CreateDbContext(std::wstring const& connString,std::wstring const& user,std::wstring const& passw);
	 boost::shared_ptr<DbContext> GetDbContext()
	 {
		 if(dbCtxt_!=NULL)
			 return dbCtxt_;
		 else return nullptr;

	 }
//		CMultiDocTemplate* m_pMyDocTemplate;
	//BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERTHREADS_H__B35DF4BD_4636_49B5_BC43_D307E0F62B29__INCLUDED_)
