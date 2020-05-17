#if !defined(AFX_INFOCONSOLE_H__507B352E_5E61_4467_A17F_7406C54F1853__INCLUDED_)
#define AFX_INFOCONSOLE_H__507B352E_5E61_4467_A17F_7406C54F1853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoConsole.h : header file
//
//#include "UserThreadsDoc.h"
#include "DialogView.h"
#include "InfoFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogView

/////////////////////////////////////////////////////////////////////////////
// CInfoConsole thread
class CMainDocument;
class CInfoConsole : public CWinThread
{
	DECLARE_DYNCREATE(CInfoConsole)
protected:
	           // protected constructor used by dynamic creation
	CInfoConsole();
// Attributes
public:
CInfoConsole(HWND hwndView,HWND hwndFrame);
virtual ~CInfoConsole();
// Operations
public:
	void CloseAll();
	void SetDocument(CDocument* pDoc);
	CMainDocument* m_pDocument;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoConsole)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CInfoFrame* pMainFrame;


	// Generated message map functions
	//{{AFX_MSG(CInfoConsole)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bConnOpen;
	BOOL DisconnectBase();
	BOOL ConnectBase(CString strConn);
	_ConnectionPtr pConn;
	HWND m_hwndView;

	CWnd* m_pFrame;
	CWnd* m_pView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOCONSOLE_H__507B352E_5E61_4467_A17F_7406C54F1853__INCLUDED_)
