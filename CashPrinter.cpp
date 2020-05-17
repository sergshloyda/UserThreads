// CashPrinter.cpp: implementation of the CCashPrinter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "userthreads.h"
#include "CashPrinter.h"
#include "CheckDoc.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCashPrinter::CCashPrinter(CView* pNewView)
{
pView=(CUserThreadsView*)pNewView;
}

CCashPrinter::~CCashPrinter()
{

}
//int nLeftMargin, int nSizeFont, int blBold, int nInt, BSTR bstrData
void CCashPrinter::AddNewLine(int nLeftMargin,int nSizeFont, int nBold,int nInterval,LPCTSTR strData)
{

	m_strData.Empty ();
	m_strData.Format(_T("%c%s%c"),ESC,"!",nSizeFont);
	WriteLPT();
	//Set interval 0-255
	m_strData.Empty ();
	m_strData.Format(_T("%c%c%c"),ESC,51,nInterval);
	WriteLPT();
	//Set Font Bold 1-Bold Font,0-Normal Font
	m_strData.Format(_T("%c%c%c"),ESC,69,nBold);
	/*sprintf((char *)m_szPrintData,"%c%c%c",ESC,69,0);*/
	WriteLPT();
		m_strData.Empty ();
	m_strData.Format(_T("%s%c"),strData,LF);
	
	WriteLPT();

	

}

BOOL CCashPrinter::NewCheck( int nPort)
{
	CString strPort;
	strPort.Empty ();
	strPort.Format (_T("LPT%d"),nPort);
	
	m_hLPTPort = ::CreateFile (strPort, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (m_hLPTPort == INVALID_HANDLE_VALUE) 
	{
	   MessageBox(NULL,_T("Unable to open LPT port!"), _T("Error!"),MB_OK|MB_ICONSTOP);
	   return FALSE;
	}
 return TRUE;
}

BOOL CCashPrinter::PrintCheck()
{
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	AddNewLine(25,10,1,12,pMainDoc->m_strFirma);
	//int nLeftMargin, int nSizeFont, int blBold, int nInt, BSTR bstrData
	AddNewLine(25,10,1,12,_T("Ñïàñèáî çà ïîêóïêó ! "));
	AddNewLine(25,14,0,12,_T("------------------------------"));
	IVSFlexGridPtr pGrid=pView->m_wndGrid.GetControlUnknown();
	CString strLine;
	for(long i=1;i<pGrid->GetRows();i++)
	{
		
		strLine.Format (_T("%.42s"),(char*)pGrid->GetTextMatrix (i,2));
		AddNewLine(25,10,1,12,strLine);
		strLine.Empty ();
		strLine.Format (_T("%.10s %.3s x %.20s =%s"),(char*)pGrid->GetTextMatrix (i,5),(char*)pGrid->GetTextMatrix (i,4),(char*)pGrid->GetTextMatrix (i,3),(char*)pGrid->GetTextMatrix (i,6));
		AddNewLine(45,9,0,12,strLine);
	}
	AddNewLine(25,14,0,12,_T("------------------------------"));
	CCheckDoc* pDoc=pView->GetDocument ();
	strLine.Format     (_T("ÈÒÎÃ            =%0.2f"),pDoc->GetCurSumma() );
	AddNewLine(25,20,1,12,strLine);
	strLine.Empty ();
	COleDateTime tmNow=COleDateTime::GetCurrentTime ();
	strLine.Format     (_T("#9406   %d-%d-%d     %d:%d 001"),tmNow.GetDay (),tmNow.GetMonth (),tmNow.GetYear (),tmNow.GetHour (),tmNow.GetMinute ());
	AddNewLine(25,10,1,12,strLine);
	strLine.Empty ();
	strLine.Format     (_T("ÈÍÍ               %.12s"),pMainDoc->m_strINN);
	AddNewLine(25,10,1,12,strLine);
	strLine.Empty ();
	strLine.Format     (_T("ÊÊÌ ñ ÔÏ              %.8s"),pMainDoc->m_strKKM );
	AddNewLine(25,10,1,12,strLine);
	strLine.Empty ();
	strLine.Format     (_T("               ÝÊËÇ %.10s"),pMainDoc->m_strEKLZ);
	AddNewLine(25,10,1,12,strLine);
	strLine.Empty ();
	strLine.Format     (_T("             00019803  #020965"));
	AddNewLine(25,10,1,12,strLine);
	m_strData.Empty ();
	m_strData.Format(_T("%c%c%c"),ESC,74,180);
	WriteLPT();
		if (m_hLPTPort==NULL)
		return TRUE;
	::CloseHandle(m_hLPTPort);
	::WaitForSingleObject (m_hLPTPort,INFINITE);

	return TRUE;
}

BOOL CCashPrinter::WriteLPT()
{

	DWORD dwBytes;
	int nLen,res;
	nLen = m_strData.GetLength ();
	char* buff=new char [nLen+1];

	::CharToOem(m_strData.GetBuffer (nLen),buff);
	res=::WriteFile(m_hLPTPort, buff, nLen, &dwBytes, NULL);
	m_strData.ReleaseBuffer ();
	delete [] buff;
	if (res)
		return TRUE;
	else
	{
		::Sleep (500);
		return WriteLPT();
	}
}

