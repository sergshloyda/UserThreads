#if !defined(AFX_DBDOC_H__52132518_AB76_498B_B5F2_FCEEA22C4855__INCLUDED_)
#define AFX_DBDOC_H__52132518_AB76_498B_B5F2_FCEEA22C4855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBDoc document

class CDBDoc : public CDocument
{
protected:
	CDBDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDBDoc)

// Attributes
public:   

// Operations
public:
	BOOL UpdateCashMove();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveComPort();
	void ReadComPort();
	CString m_strDiffSQL;
	CString m_strSQL;
	int m_nComPort;
	COleDateTime m_dtEnd;
	COleDateTime m_dtStart;
	CString m_strPropertyQuery;
	CString m_strMoveQuery;
	CString m_strHead;
	CString m_strBarCode;
	CFont& GetFont();
	CFont m_font;
	void SetPointFont(CString szName,int nSize);
	virtual ~CDBDoc();
	int GetFontSize(){return m_nFontSize;}
	CString& GetFontName(){return m_szFontName;}
	inline void GetFontName(LPTSTR szBuff){_tcscpy(szBuff,m_szFontName);}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void SavePeriod();
	void SaveFont();
	void ReadFont();
	void ReadPeriod();
	//{{AFX_MSG(CDBDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	int m_nFontSize;
	CString m_szFontName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBDOC_H__52132518_AB76_498B_B5F2_FCEEA22C4855__INCLUDED_)
