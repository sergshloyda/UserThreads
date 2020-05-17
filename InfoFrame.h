#if !defined(AFX_INFOFRAME_H__64CC6AA0_051C_4841_A411_504DEC3255E1__INCLUDED_)
#define AFX_INFOFRAME_H__64CC6AA0_051C_4841_A411_504DEC3255E1__INCLUDED_

#include "MDIClient.h"
#include "FontToolBar.h"
#include "ReportFrame.h"
#include "1CHelper.h"

	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoFrame frame

class CInfoFrame : public CMDIFrameWnd
{
	friend class CReport;
	DECLARE_DYNCREATE(CInfoFrame)
protected:
	           // protected constructor used by dynamic creation

// Attributes
public:
CInfoFrame();
void DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf);
// Operations
public:

	virtual ~CInfoFrame();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoFrame)
	public:
	virtual CDocument* GetActiveDocument();
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Open1C(BSTR param);
	CString m_strStatusBarInfoLang;
	CString m_strStatusBarInfoGrid;
	CMDIClient m_wndMDIClient;
	CMapStringToString m_mpFormCaption;
	HWND hwndForm;
	CStringList m_lsForms;
	CFontToolBar m_wndFontTB;
	CToolBar    m_wndToolBar;
	C1CHelper Help1C;
protected:
	CStatusBar m_wndStatusBar;


	// Generated message map functions
	//{{AFX_MSG(CInfoFrame)
	afx_msg void OnFileDictionary();
	afx_msg void OnUpdateFileDictionary(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileNaklad();
	afx_msg void OnUpdateFileNaklad(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnSetPeriod();
	afx_msg void OnUpdateSetPeriod(CCmdUI* pCmdUI);
	afx_msg void OnArchive();
	afx_msg void OnUpdateArchive(CCmdUI* pCmdUI);
	afx_msg void OnDearchive();
	afx_msg void OnUpdateDearchive(CCmdUI* pCmdUI);
	afx_msg void OnCustomize();
	afx_msg void OnUpdateCustomize(CCmdUI* pCmdUI);
	afx_msg void OnActivateApp(BOOL bActive, DWORD );
	//}}AFX_MSG
	afx_msg LRESULT OnFontChanged(WPARAM,LPARAM);
	afx_msg void OnUpdateRows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLanguage(CCmdUI *pCmdUI);
	afx_msg void OnToolbarDropDown(NMHDR* pnmhdr, LRESULT *plr);
	DECLARE_MESSAGE_MAP()
private:
	
	CString GetFormCaption(CString& strKey);
	void InitHashTable();
	void ShowForm(CString szName);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOFRAME_H__64CC6AA0_051C_4841_A411_504DEC3255E1__INCLUDED_)
