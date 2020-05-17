#if !defined(AFX_CASHDOC_H__7A4C2372_C51E_4872_A20D_9D3B532F9E20__INCLUDED_)
#define AFX_CASHDOC_H__7A4C2372_C51E_4872_A20D_9D3B532F9E20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CashDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCashDoc document
class CUserThreadsApp;
class CCashDoc : public CDocument
{
protected:      
	CCashDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCashDoc)
 
// Attributes
public:
private:
	BOOL m_blFlag;
// Operations
public:
BOOL CashDoActionIncome(LPCTSTR szDocId,float flSumma);
BOOL CashDoActionOutcome(LPCTSTR szDocId,float flSumma);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCashDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL
 
// Implementation
public:
	CString& GetCashId();
	CString& GetMainCashId();     
	double CalculateCashBalance(COleDateTime& tmCurTime);
	double m_dblActualSumma;
	COleDateTime m_dtActualTime;
	COleDateTime m_dtLastDocTime;
	COleDateTime m_dtFirstDocTime;
	BOOL CalculateCashRegisters(COleDateTime tmStart,COleDateTime tmEnd,double& dAggrSumma);
	BOOL UpdateCashMove(); 
	//_RecordsetPtr pRstCashMove;
	//_RecordsetPtr pRstRaCash;
	//_RecordsetPtr pRstRgCash;
	BOOL AddCashMoveDocument(LPCTSTR szDocId,LPCTSTR szCashId,LPCTSTR szPointId,LPCTSTR szCash2Id,LPCTSTR szPoint2Id,float flSumma);
	virtual ~CCashDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCashDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CASHDOC_H__7A4C2372_C51E_4872_A20D_9D3B532F9E20__INCLUDED_)
