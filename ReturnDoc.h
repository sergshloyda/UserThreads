#if !defined(AFX_RETURNDOC_H__5BC825E0_3F57_469F_85D8_2DC735B18C5C__INCLUDED_)
#define AFX_RETURNDOC_H__5BC825E0_3F57_469F_85D8_2DC735B18C5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReturnDoc.h : header file
//
#include "ReturnView.h"
/////////////////////////////////////////////////////////////////////////////
// CReturnDoc document

class CReturnDoc : public CDocument
{
		friend class CReturnView;
		friend class CZReportView;
protected:
	CReturnDoc();                  // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CReturnDoc)

// Attributes
public:
enum
{UpdateAll=0,
UpdateDocs=1,
UpdateGoods=2,
UpdateSelectGoods=3
};
// Operations
public:

protected:
	BOOL LoadAllChecksOnDate(_Recordset** pRs);
	BOOL LoadEntryDoc(LPCTSTR szDocId, _Recordset **ppRst);
	BOOL LoadAllSalesOnDate( _Recordset** pRs);
	BOOL LoadAllReturns(const COleDateTime& tmDateTime, _Recordset** pRs);
	BOOL TransactReturn(VARIANT* vtArray);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReturnDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnCloseDocument();
	virtual BOOL OnNewDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_blLoadDocs;
	void SetDate(COleDateTime *pNewDate);
	BOOL LoadReturnDocIn1C(_variant_t &vtArray);
	static CReturnDoc* GetReturnDoc();
	BOOL EditSales(COleDateTime&,LPCTSTR szDocId);
	float m_flCurSumma;
	_variant_t m_vtArray;
	CString m_strBaseDocId;
	CString m_strBaseCheckId;
	CString m_strDocId;   
	COleDateTime m_tmDateView;
	virtual ~CReturnDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	BOOL SaveTableReturn(_variant_t& vtArray,LPCTSTR szDocId);
	BOOL SaveHeadReturn(COleDateTime& tmDocTime,LPCTSTR szDocId);
	//{{AFX_MSG(CReturnDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PrepareEntryDocSQLStatement(LPCTSTR szDocId,BSTR* bstrSQLStatement);
	BOOL CheckReturnRow(LPCTSTR strCode,LPCTSTR strCheckId);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RETURNDOC_H__5BC825E0_3F57_469F_85D8_2DC735B18C5C__INCLUDED_)
