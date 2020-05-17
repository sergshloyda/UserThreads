// Barcode.cpp: implementation of the CBarcode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "userthreads.h"
#include "Barcode.h"
#include "NotyfyFndProduct.h"
#include <process.h>
#define WM_BARCODE_READ WM_USER+1
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HANDLE CBarcode::m_hComm =NULL;
BOOL CBarcode::m_bTerminated =FALSE;
CBarcode::CBarcode()
{
	strCommPort=_T("COM1");

}

CBarcode::~CBarcode()
{

}

BOOL CBarcode::InitComm()
{

	DCB dcb;
	//	m_hComm = CreateFile ("COM2", GENERIC_READ /*| GENERIC_WRITE*/,
	//                 0, NULL, OPEN_EXISTING, /*0*/FILE_FLAG_OVERLAPPED, NULL);
	m_hComm = CreateFile((LPCTSTR)strCommPort, GENERIC_READ| GENERIC_WRITE ,
		0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (m_hComm == INVALID_HANDLE_VALUE) 
	{
		//MessageBox(::GetActiveWindow(),"Невозможно открыть COM порт", "Ошибка!",MB_OK);
		MessageBox(::GetActiveWindow(),_T("Unable to open COM port!"), _T("Error!"),MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	FillMemory(&dcb, sizeof(dcb), 0);
	
	GetCommState(m_hComm,&dcb);
	SetupComm (m_hComm, 256, 256);       // allocate transmit & receive buffer
    //dcb.BaudRate = CBR_115200;
	dcb.BaudRate = CBR_9600;
	dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState (m_hComm, &dcb);
	SetCommMask(m_hComm,  EV_RXCHAR);
	
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout        = MAXDWORD;
	timeouts.ReadTotalTimeoutMultiplier    = 0;
	timeouts.ReadTotalTimeoutConstant    = 0;
	timeouts.WriteTotalTimeoutMultiplier    = 0;
	timeouts.WriteTotalTimeoutConstant    = 0;
	
	if (!SetCommTimeouts(m_hComm, &timeouts))
	{
		ASSERT(0);
		TRACE ( _T("CBarcode :  Error setting time-outs. %d"),GetLastError());
		return FALSE;
	}
	
	unsigned int ThreadId;
	
	m_bTerminated=FALSE;
	m_hReadData = (HANDLE)_beginthreadex(NULL, 0, ReadData,m_hWinReceiver, 0, &ThreadId);

	return TRUE;
}
CBarcode::CBarcode(HWND hWinReceiver,const CString& strPort)
{
	strCommPort=strPort;
	m_hWinReceiver=hWinReceiver;
	m_hReadData=NULL;
}
unsigned __stdcall  CBarcode::ReadData(LPVOID pParam)
{
	


	DWORD		dwEvtMask;
	DWORD		dwError;
	DWORD		dwBytes;
	COMSTAT		csStat;
	OVERLAPPED	o={0};
	
	
	HWND hWndReceiver =(HWND)(pParam);
	o.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	
	
	
	int			nCount;
	char*		strTemp=new char[128];
	memset(strTemp,0,128);
	nCount=0;
	char		szBuffer[256];
	memset(szBuffer,0,256);
	while (!m_bTerminated)
	{
		
	
		//TRACE("\nЖдем данных adress strTemp=%x m_hComm=%x",strTemp,m_hComm);
		BOOL abRet = ::WaitCommEvent(m_hComm,&dwEvtMask, &o) ;
        if ( !abRet )                                                                              
        {
			if (WaitForSingleObject(o.hEvent , 500) == WAIT_OBJECT_0)
			{
				GetOverlappedResult(m_hComm,&o,&dwBytes,FALSE);
				
				//TRACE(" !abRet");
				LPVOID lpMsgBuf;
				if (FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | 
					FORMAT_MESSAGE_IGNORE_INSERTS, NULL, 
					GetLastError(),                               //LastError
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),    // Default language
					(LPTSTR) &lpMsgBuf, 0, NULL)
					)
					TRACE((LPTSTR)lpMsgBuf);
				LocalFree( lpMsgBuf );
			
				if(m_bTerminated) break;
			
			}
			else
			{//WaitForSingleObject(o.hEvent , 500) == WAIT_TIMEOUT
				//TRACE(" !WAIT_TIMEOUT");
				LPVOID lpMsgBuf;
				if (FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | 
					FORMAT_MESSAGE_IGNORE_INSERTS, NULL, 
					GetLastError(),                               //LastError
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),    // Default language
					(LPTSTR) &lpMsgBuf, 0, NULL)
					)
					//TRACE((LPTSTR)lpMsgBuf);
				LocalFree( lpMsgBuf );
				if(!m_bTerminated) continue;
			}
        }
		
		
				if (GetCommMask(m_hComm,&dwEvtMask) )
                {
					//TRACE("Data sent");
					if ( dwEvtMask & EV_TXEMPTY )
					{
						
						ResetEvent ( o.hEvent );
						continue;
					}
					else if ( dwEvtMask & EV_BREAK )
					{
						
						ResetEvent ( o.hEvent );
						break ;
					}
					else if (dwEvtMask & EV_RXCHAR)
					{
						
						::Sleep(100);
						ClearCommError(m_hComm,&dwError, &csStat);
							if(m_bTerminated)
							 
								break;
						
						if (!ReadFile(m_hComm, szBuffer, (csStat.cbInQue>148)?148:csStat.cbInQue, &dwBytes, &o))
						{
							Sleep(50);
							ResetEvent(o.hEvent);
							break;
							//	if(kbhit())break;
						}
						if(m_bTerminated) break;
						memset(strTemp,0,128);
						//nCount=0;
						for (UINT i = 0; i < csStat.cbInQue; i++)
						{
							if(szBuffer[i]==13)
							{
								
								
							
								
								//TRACE("\nЭто %s from hWinReceiver=%x",strTemp,hWndReceiver);
							
								COPYDATASTRUCT MyCDS;
								memset((void*)&MyCDS,0,sizeof(MyCDS));
								MyCDS.dwData =0L;
								MyCDS.lpData =strTemp;
								MyCDS.cbData =128;
								
								//TRACE("\nЭто %s from pPass->hWinReceiver=%x",strTemp,hWndReceiver);
								if(::IsWindow (hWndReceiver ))
								{
									//TRACE("\nBefore SendMessage WM_COPYDATA");
									//::SendMessage(hWndReceiver ,WM_COPYDATA,NULL,(LPARAM) (LPVOID) &MyCDS);
									
									NMHDR hdr;
									hdr.code=FND_BY_BARCODE;
									hdr.hwndFrom=hWndReceiver;
									hdr.idFrom=0;
								
									CNotyfyFndProduct* pObject=new CNotyfyFndProduct(hdr,1,NULL,strTemp);
									PostMessageA(hWndReceiver,WM_NOTIFY,0,(LPARAM)&(pObject->m_hdrObject));
								}
								//memset(strTemp,0,128);
								nCount=0;
								break;
							}
							else
							{
								if (nCount>64) break;
								strTemp[nCount]=szBuffer[i];
								nCount++;
							}
						}
						if(nCount>64)
						{
							delete strTemp;
							nCount=0;
						}
						ResetEvent(o.hEvent);
						::PurgeComm (m_hComm,PURGE_RXCLEAR);
					}
				}
				
				
			
			}//GetCommMask
	
			delete strTemp;
			::CloseHandle(o.hEvent );
			
			return 0;
}
	
BOOL CBarcode::CloseCommPort()
{

	m_bTerminated=TRUE;
//на нет и суда нет
	if(m_hComm==NULL)return TRUE;
//если мы WaitCommEvent 
//принудительно выходим
	if (m_hComm != INVALID_HANDLE_VALUE)
	::SetCommMask (m_hComm,0);
	if(m_hReadData!=NULL){
		::WaitForSingleObject(m_hReadData,INFINITE);
		//	::MessageBox(0,_T("Поток окончен"), _T(""),MB_OK|MB_ICONSTOP);
		::CloseHandle (m_hReadData);}
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		//	::MessageBox(0,_T("Закроем СОМ порт"), _T(""),MB_OK|MB_ICONSTOP);
		::EscapeCommFunction(m_hComm, SETBREAK);
		
		::CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
	}
	else
	{	MessageBox(::GetActiveWindow(),_T("Unable to close COM port!"), _T("Error!"),MB_OK);
	return FALSE;
	}

	return TRUE;
}
