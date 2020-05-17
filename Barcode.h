// Barcode.h: interface for the CBarcode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BARCODE_H__0A9DC4C9_F99B_46E8_93F9_4BB34BC45238__INCLUDED_)
#define AFX_BARCODE_H__0A9DC4C9_F99B_46E8_93F9_4BB34BC45238__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBarcode  
{
public:

	BOOL CloseCommPort();
	BOOL InitComm();
	CBarcode();
	CBarcode(HWND hWinReceiver,const CString& strPort=_T("COM1"));
	virtual ~CBarcode();

private:
	static	unsigned   __stdcall ReadData(LPVOID pParam);
	static	HANDLE m_hComm;
	CString strCommPort;
	static	BOOL m_bTerminated;
	HANDLE m_hReadData;
	HWND m_hWinReceiver;
};

#endif // !defined(AFX_BARCODE_H__0A9DC4C9_F99B_46E8_93F9_4BB34BC45238__INCLUDED_)
