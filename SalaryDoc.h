#if !defined(AFX_SALARYDOC_H__C8FAAF64_D981_4CE4_8BEC_52B4EE480E43__INCLUDED_)
#define AFX_SALARYDOC_H__C8FAAF64_D981_4CE4_8BEC_52B4EE480E43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SalaryDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSalaryDoc document

class CSalaryDoc : public CDocument
{
	friend class CUserThreadsApp;
protected:
	CSalaryDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSalaryDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSalaryDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL CalculateAmountSalary(_RecordsetPtr pRst,float* pflCalcSalary);
	float m_flCalcSalary;
	float m_flBaseSalary;
	BOOL GetBaseSalary(LPCTSTR strEmplId,float* pfBaseSalary);
	CString m_strEmplId;
	BOOL RecalculateSalaryRegisters(const COleDateTime& tmValue);
	BOOL CalculateAmountSalary(_variant_t& vt,float* flCalcSalary);
	CString m_strBaseDocId;
	CString m_strDocId;
	BOOL AccountingSalaryToEmpl(LPCTSTR strEmplId,float flValue);
	BOOL WithdrawFromEmplAccount(LPCTSTR strEmpId,float flValue);
	static CSalaryDoc* GetSalaryDoc();
	BOOL DeductFromSalary(LPCTSTR strEmplId,float flValue);
	BOOL AddPremiaToEmployer(LPCTSTR strEmplId,float flValue);
	BOOL GetProductSalePremia(LPCTSTR strCode,float* pflPremia);
	float GetSalaryBalance(LPCTSTR strEmplId,COleDateTime tmDate);
	BOOL TransactSalary(LPCTSTR strBaseDocId,_variant_t& vt);
	virtual ~CSalaryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSalaryDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SALARYDOC_H__C8FAAF64_D981_4CE4_8BEC_52B4EE480E43__INCLUDED_)
