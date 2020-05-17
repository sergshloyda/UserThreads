// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__299F4469_132C_4BED_A137_2A782F8BA3C2__INCLUDED_)
#define AFX_MAINFRM_H__299F4469_132C_4BED_A137_2A782F8BA3C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InfoConsole.h"
#include "FontCombo.h"
#include "FontToolBar.h"
#include "MultButton.h"
#include "OutputWnd.h"
#define WM_KILL_THREAD  WM_USER + 1
#define NM_FONTCHANGED NM_FIRST-23

enum eView 
{
	CHECK=1,
	ZREPORT=2,
	RETURN=4,
	RECICLING=3
};

class CMainFrame : public CMDIFrameWndEx
{
static LPCTSTR s_winClassName;	
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CMainFrame)

// Attributes

public:
CMainFrame();
void DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strErrorMsg;
	BOOL m_bUserActivated;
	BOOL SwitchView(CRuntimeClass* pViewRuntimeClass);
	CMFCStatusBar  m_wndStatusBar;
	COutputWnd  m_wndOutput;
	eView m_nCurView;
	CMFCToolBar    m_wndMultToolBar;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
protected:  // control bar embedded members

	CMFCToolBar    m_wndToolBar;
	

// Generated message map functions
protected:

	
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnUpdateViewInfoconsole(CCmdUI* pCmdUI);
	afx_msg void OnCheckView();
	afx_msg void OnUpdateCheckView(CCmdUI* pCmdUI);
	afx_msg void OnZReport();
	afx_msg void OnUpdateZReport(CCmdUI* pCmdUI);
	afx_msg void OnRecicling();
	afx_msg void OnUpdateRecicling(CCmdUI* pCmdUI);
	afx_msg void OnSetup();
	afx_msg void OnUpdateSetup(CCmdUI* pCmdUI);
	afx_msg void OnReturn();
	afx_msg void OnUpdateReturn(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaneComPort(CCmdUI* pCmdUI);
	afx_msg void OnActivateApp(BOOL bActive, DWORD);
	//}}AFX_MSG
	afx_msg void OnUpdatePointActual(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaneKKM(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaneKKMError(CCmdUI* pCmdUI);
	afx_msg void OnInfoConsole();
	afx_msg LRESULT OnKillThread(WPARAM,LPARAM);
	afx_msg LRESULT OnFontChanged(WPARAM,LPARAM);
	afx_msg LRESULT OnDisconnectBase(WPARAM,LPARAM);
	afx_msg LRESULT OnConnectBase(WPARAM,LPARAM);
	afx_msg LRESULT OnChangeMultiplicator(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	BOOL CreateMainToolBar();
	int m_nQtyMultiplicator;
	CFont m_NCFont;
	CRect m_rcQtyView;
	BOOL m_bActive;
	CMultButton m_wndMultButton;
	HACCEL  m_hAccelTable;
protected:
	afx_msg LRESULT OnResetToolbar(WPARAM wParam, LPARAM lParam);
public:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__299F4469_132C_4BED_A137_2A782F8BA3C2__INCLUDED_)
