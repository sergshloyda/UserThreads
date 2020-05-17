// BarCodeReader.h : Declaration of the CBarCodeReader

/*#ifndef __BARCODEREADER_H_
#define __BARCODEREADER_H_
#import ".\DLL\BarCode5.dll"  no_namespace
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBarCodeReader
class ATL_NO_VTABLE CBarCodeReader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBarCodeReader, &CLSID_BarCodeReader>,
	public IDispEventImpl<0, CBarCodeReader, &DIID__IReaderEvents,&LIBID_BARCODE5Lib, 1, 0>
{
public:
	CBarCodeReader()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BARCODEREADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBarCodeReader)
	COM_INTERFACE_ENTRY(IBarCodeReader)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IID(DIID__IReaderEvents, CBarCodeReader)
END_COM_MAP()

// IBarCodeReader
public:
};

#endif //__BARCODEREADER_H_
*/