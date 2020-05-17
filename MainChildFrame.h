#if !defined(AFX_MAINCHILDFRAME_H__7B643A35_7386_4A3D_9396_D7D449AE70DC__INCLUDED_)
#define AFX_MAINCHILDFRAME_H__7B643A35_7386_4A3D_9396_D7D449AE70DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainChildFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainChildFrame frame

class CMainChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMainChildFrame)
protected:
	         // protected constructor used by dynamic creation

// Attributes
public:
	CMainChildFrame();

	virtual ~CMainChildFrame(); 
// Operations
public:
	CToolBar* GetToolBar(UINT nID); 
BOOL ReplaceView(CRuntimeClass * pViewClass);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainChildFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBar m_wndToolBar;


	// Generated message map functions
	//{{AFX_MSG(CMainChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINCHILDFRAME_H__7B643A35_7386_4A3D_9396_D7D449AE70DC__INCLUDED_)
