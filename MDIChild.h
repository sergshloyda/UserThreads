#if !defined(AFX_MDICHILD_H__1255B354_D67A_4244_B0EF_666FCFFEFBCE__INCLUDED_)
#define AFX_MDICHILD_H__1255B354_D67A_4244_B0EF_666FCFFEFBCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDIChild.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMDIChild frame

class CMDIChild : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMDIChild)
protected:
	CMDIChild();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void SetTitle(LPCTSTR strTitle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIChild)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMDIChild();

	// Generated message map functions
	//{{AFX_MSG(CMDIChild)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDICHILD_H__1255B354_D67A_4244_B0EF_666FCFFEFBCE__INCLUDED_)
