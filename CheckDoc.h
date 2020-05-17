#if !defined(AFX_CHECKDOC_H__58F03A27_4F96_4BD9_9871_4F0747B606B0__INCLUDED_)
#define AFX_CHECKDOC_H__58F03A27_4F96_4BD9_9871_4F0747B606B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckDoc document

class CCheckDoc : public CDocument
{
protected:
	CCheckDoc();           // protected constructor used by dynamic creation
	
	DECLARE_DYNCREATE(CCheckDoc)
	
// Attributes    
public:
	typedef struct{
		int line_no;
		std::wstring barcode;
		std::wstring code;
		std::wstring descr;
		std::wstring unit;
		int qty;
		double price;
	} SalesItemLine;
	typedef std::list<SalesItemLine> SalesLineItemsType;
	//typedef boost::tuple<int/*line_no(0)*/,
	//					std::wstring/*barcode(1)*/,
	//					std::wstring/*descr(2)*/,
	//					std::wstring/*unit(3)*/,
	//					std::wstring /*code(4)*/,
	//					int/*qty(5)*/,
	//					double/*price(6)*/> SalesItem;
	void AddLine(const SalesItemLine& line);
	
	float GetCurSumma() const { 
		float flSumma=0.0;
		if(SalesLineItems.size()>0){
		std::for_each(SalesLineItems.begin(),SalesLineItems.end(),[&flSumma](SalesItemLine line)
			{
		flSumma+=(float)(line.qty*line.price);
			});
		}
		return flSumma;
	}
	


	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	const SalesLineItemsType& GetSalesLineItems()  { return SalesLineItems; }
	
	int GetUnitsQty() const { return m_nUnitsQty; }
	void SetUnitsQty(int val) { m_nUnitsQty = val; }
	int GetLineNoQty() const { return m_nLineNo; }
	void SetLineNoQty(int val) { m_nLineNo = val; }
	// Operations
public:
	BOOL TransactCheck();
	BOOL SaveHeadCheck(const COleDateTime &tmCheckTime,LPCTSTR szDocId);
	BOOL SaveTableCheck(VARIANT* vt ,LPCTSTR szDocId);
	BOOL GetCheckInfo(LPCTSTR strDocId, 
							 TCHAR* strPointId, 
							 TCHAR* strSalerId, 
							 TCHAR* strContragId,
							 size_t szStrId,
							 COleDateTime &tmCheckDate);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void OnCloseDocument();
	virtual BOOL OnNewDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_str1CNum;
	BOOL DeleteCheck(LPCTSTR szDocId);
	void DeleteLineNo(int line);
	CString m_strDocId;
	virtual ~CCheckDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
private:
	
	SalesLineItemsType SalesLineItems;
//		CMemoryState oldMemState, newMemState, diffMemState;
	float m_flCurSumma;
	int m_nUnitsQty;
	int m_nLineNo;
	int m_nMultiplicator;
public:
	afx_msg void OnMultbutHolder();
	afx_msg void OnUpdateMultbutHolder(CCmdUI *pCmdUI);
	void ClearCheck()
	{
		SalesLineItems.clear();
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKDOC_H__58F03A27_4F96_4BD9_9871_4F0747B606B0__INCLUDED_)
