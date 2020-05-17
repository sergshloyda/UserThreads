// UserThreadsDoc.h : interface of the CUserThreadsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERTHREADSDOC_H__713E19BE_64BB_4735_9F80_07AF1BD85B10__INCLUDED_)
#define AFX_USERTHREADSDOC_H__713E19BE_64BB_4735_9F80_07AF1BD85B10__INCLUDED_

#include "NTree.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*class CRowEntry
{
public:
	CRowEntry(CString strCode,int nQty,float fPrice):code(strCode),Qty(nQty),Price(fPrice){}
	

	CString code;
	int Qty;
	float Price;
};

*/
     
class CUserThreadsDoc : public CDocument
{
protected: // create from serialization only

	DECLARE_DYNCREATE(CUserThreadsDoc)

// Attributes
public:
	CUserThreadsDoc();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserThreadsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL LoadEntryDoc(LPCTSTR szDocId,_Recordset** ppRst);
	CPtrList m_lsCheckRows;
	BOOL AddNewCheckInJournal(COleDateTime& tmCheckTime);
	BOOL TransactCheck(_variant_t&  vtArray);
	BOOL CashDoActionOutcome();
	BOOL CashDoActionIncome();
	CString m_strCurDocId;
	int m_nCurMaxDocNum;
	CString m_strPointId;
	CString m_strUserId;
	CString m_strUserName;
	CString m_strContragId;
	float m_flCurSumma;
	BOOL CloseAllRecordsets();
	BOOL OpenRecordsetList();
	void DisconnectBase();
	BOOL blCatalogOpen;
	CMapStringToPtr m_MapRst;
	_RecordsetPtr pRstCatalog;
//	_RecordsetPtr pRstMaster;
	void ReadComPort();
	void SaveFont();
	void ReadFont();
	void SetFont(CFont& newFont);
	void SetPointFont(LPCTSTR szName,int nSize);
	void SetLogFont(LOGFONT* lf);
	CNTree& GetCategoryTree();
	CNTree m_dataTree;
	CString& GetFontName(){return m_szFontName;}
	CFont* GetFont(){return &m_font;}
	int GetFontSize(){return m_nFontSize;}
	virtual ~CUserThreadsDoc();
	CString& GetComPort(){return m_strComPort;}
	BOOL LoadAllChecksOnDate(COleDateTime tmDate, _Recordset** pRst);
	BOOL LoadAllSalesOnDate(COleDateTime tmDate, _Recordset** pRs);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void LoadCategoryTree();
	void populatetree(CTreeNode* ptrNode);
// Generated message map functions
protected:
	BOOL UpdateNumerator(COleDateTime& tmCheckTime);
	BOOL SaveTableCheck(_variant_t& vt);
	BOOL SaveHeadCheck(COleDateTime& tmTimeCheck);
	BOOL CalculateDocId(CString strPointId,CString &strDocId,int* pDayNumber);

	//{{AFX_MSG(CUserThreadsDoc)
	afx_msg void OnFontBold();
	afx_msg void OnFontItalic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strComPort;
	int m_nFontSize;
	CFont m_font;
	CString m_szFontName;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERTHREADSDOC_H__713E19BE_64BB_4735_9F80_07AF1BD85B10__INCLUDED_)
