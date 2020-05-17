#ifndef _REPORTFRAME_H__
#define _REPORTFRAME_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportFrame.h : header file
//
#include "FolderFrame.h"
#include "DBDoc.h"
//#include "ReportView.h"
/////////////////////////////////////////////////////////////////////////////
// CReportFrame frame

class CReport:public CWnd
{
	friend class CReportView;
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xd76d712e, 0x4a96, 0x11d3, { 0xbd, 0x95, 0xd2, 0x96, 0xdc, 0x2d, 0xd0, 0x72 } };
		return clsid;
	}

	 enum  {
    rprtPropertyView=0,
    rprtMoveView=1,
} ;
	BOOL ShowReport();

	CReport(BOOL IsDataSheet,CWnd* pParent)
	{
		m_blIsDataSheet=IsDataSheet;
		//m_pRst=NULL;
		m_strHead=_T("");
		m_strUnderGround =_T("");
		m_pParentWnd =pParent;
		blFirstTime=TRUE;
		nInstance++;
	
	}
	virtual void Head(){}
	virtual void Body(){}
	virtual void UnderGround(){}
	void SetPropertyQuery(CString strSQL){m_bstrPropertyQuery=(_bstr_t)strSQL;}
	void SetMoveQuery(CString strSQL){m_bstrMoveQuery=(_bstr_t)strSQL;}
	BOOL IsDataSheet(){ return m_blIsDataSheet;}
	void PrepareHeadString(CString& strHead){m_strHead=strHead;}
	void PrepareUnderGroundString(CString& strUnderGround){m_strUnderGround=strUnderGround;}
	BOOL CreateGrid(_bstr_t bstrFontName,int nFontSize);
protected:

	void Body(int* nCurRow,int nBeginRow=1);
	void Head(CString& lstStr,int* nCurRow,int nBeginRow=1);
	void UnderGround(CString& strUndGrnd,int nBeginRow=1);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

private:
	CString strMoveGridPath;
	void RestoreGrid();
	void SaveGrid();
	BOOL blFirstTime;
	void SetAutoSizeForGrid();
	_bstr_t m_bstrPropertyQuery,m_bstrMoveQuery;
	_bstr_t m_bstrFilter;
	CWnd* m_pParentWnd;
	CString m_strSQL;

	BOOL m_blIsDataSheet;
	CString m_strHead;
	CString m_strUnderGround;
	static int nInstance;
public:
	void LoadMove();
	_variant_t varArrMoveData;
	BOOL IsSubclassed();
	void GetGridSize(CSize* szGrid);
	void ShowReport(int nSettings);
		IVSFlexGridPtr  m_spGrid;
protected:
	void ShowMove(int* pCurRow,int nBeginRow);
	void ShowProperty(int* pCurRow,int nBeginRow);
	//{{AFX_MSG(CReport)
		afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
class CReportFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CReportFrame)
protected:
	CFolderFrame m_wndFolderFrame;
         // protected constructor used by dynamic creation

// Attributes
public:
	CReportFrame();  
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportFrame();

	// Generated message map functions
	//{{AFX_MSG(CReportFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif 