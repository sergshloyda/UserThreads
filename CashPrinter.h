// CashPrinter.h: interface for the CCashPrinter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CASHPRINTER_H__9B5F07ED_BD2B_49C2_8017_3D327A64DCE0__INCLUDED_)
#define AFX_CASHPRINTER_H__9B5F07ED_BD2B_49C2_8017_3D327A64DCE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define LF 10
#define ESC 27
#include "UserThreadsView.h"
class CCashPrinter  
{
public:

	BOOL PrintCheck();
	BOOL NewCheck(int nPort);
	//int nLeftMargin, int nSizeFont, int blBold, int nInt, BSTR bstrData
	void AddNewLine(int nLeftMargin,int nSizeFont, int nBold,int nInterval,LPCTSTR strData);
	CCashPrinter(CView* pView);
	virtual ~CCashPrinter();

private:
	CUserThreadsView* pView;
	BOOL WriteLPT();
	HANDLE m_hLPTPort;
	CString m_strData;
};

#endif // !defined(AFX_CASHPRINTER_H__9B5F07ED_BD2B_49C2_8017_3D327A64DCE0__INCLUDED_)
