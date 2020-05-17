#if !defined(AFX_ZREPORTDOC_H__2CAF94D8_4BD5_4E50_8D25_81B605632275__INCLUDED_)
#define AFX_ZREPORTDOC_H__2CAF94D8_4BD5_4E50_8D25_81B605632275__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZReportDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZReportDoc document

class CZReportDoc : public CDocument
{
protected:
	CZReportDoc();            // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CZReportDoc)

// Attributes
public:
	float m_flCurSummSale;
	float m_flCurSummReturn;
	float m_flOstatok;
	CString m_strDocId;    
	COleDateTime m_tmDocTime;
// Operations  
public:
	BOOL TransactZReport(_variant_t& vtArray);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZReportDoc)    
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	static	long m_lRowsCount;
	_RecordsetPtr GetZReportRecordset();
	_RecordsetPtr m_pRstZReport;
	COleDateTime m_tmLastZReportTime;
	double CalculateDaySales(); 
	static CZReportDoc* GetZReportDoc();
	virtual ~CZReportDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CZReportDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()    
private:
	BOOL SetCheckMarked(LPCTSTR strDocId);
	BOOL SaveTableZReport(LPUNKNOWN pRst,double* dblSumma);
	BOOL SaveHeadZReport();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZREPORTDOC_H__2CAF94D8_4BD5_4E50_8D25_81B605632275__INCLUDED_)
