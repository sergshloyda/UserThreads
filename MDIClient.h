#if !defined(AFX_MDICLIENT_H__1982F806_E14E_4EFB_9E09_107A331DBD92__INCLUDED_)
#define AFX_MDICLIENT_H__1982F806_E14E_4EFB_9E09_107A331DBD92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDIClient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMDIClient window
class CViewManager;
class CInfoFrame;
class CMDIClient : public CWnd
{
// Construction
public:
	CMDIClient();

// Attributes
public:

// Operations
public:
	CViewManager* GetViewManager() const  { return m_pViewManager; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIClient)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetViewManager(CMDIFrameWnd* pFrame);
	void SaveMainFrameState();
	void RestoreMainFrameState(UINT nCmdShow);
	BOOL SubclassMDIClient(CMDIFrameWnd* pMDIFrameWnd);
	virtual ~CMDIClient();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMDIClient)
	afx_msg void OnDestroy();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	afx_msg LRESULT OnMDICreate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMDIDestroy(WPARAM wParam, LPARAM lParam);	
	DECLARE_MESSAGE_MAP()
private:
	CInfoFrame* m_pMDIFrame;
	CViewManager* m_pViewManager;
	BOOL          m_bFirstTime;
	BOOL          m_bMaxChild;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDICLIENT_H__1982F806_E14E_4EFB_9E09_107A331DBD92__INCLUDED_)
