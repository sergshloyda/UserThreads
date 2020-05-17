// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "barcode5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// _IReaderEvents properties

/////////////////////////////////////////////////////////////////////////////
// _IReaderEvents operations


/////////////////////////////////////////////////////////////////////////////
// IReader properties

/////////////////////////////////////////////////////////////////////////////
// IReader operations

void IReader::OpenCommPort(LPCTSTR CommPort)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 CommPort);
}

void IReader::CloseCommPort()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IReader::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// _IReaderEvents properties

/////////////////////////////////////////////////////////////////////////////
// _IReaderEvents operations


/////////////////////////////////////////////////////////////////////////////
// IReader properties

/////////////////////////////////////////////////////////////////////////////
// IReader operations

void IReader::OpenCommPort(LPCTSTR CommPort)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 CommPort);
}

void IReader::CloseCommPort()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IReader::Execute()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
