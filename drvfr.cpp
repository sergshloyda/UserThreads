// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "drvfr.h"
#include <comutil.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define   DRV_RESCODE_WAIT_CONTINUE_PRINTING 88
#define MAX_STR_LENGHT 36

/////////////////////////////////////////////////////////////////////////////
// IDrvFR47 properties

/////////////////////////////////////////////////////////////////////////////
// IDrvFR47 operations
//implement our own conversion functions

//------------------------//
// Convert char * to BSTR //
//------------------------//
BSTR ConvertStringToBSTR(const char* pSrc)
{
    if(!pSrc) return NULL;

    DWORD cwch;

    BSTR wsOut(NULL);

    if(cwch = ::MultiByteToWideChar(CP_ACP, 0, pSrc, 
         -1, NULL, 0))//get size minus NULL terminator
    {
                cwch--;
            wsOut = ::SysAllocStringLen(NULL, cwch);

        if(wsOut)
        {
            if(!::MultiByteToWideChar(CP_ACP, 
                     0, pSrc, -1, wsOut, cwch))
            {
                if(ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
                    return wsOut;
                ::SysFreeString(wsOut);//must clean up
                wsOut = NULL;
            }
        }

    };

    return wsOut;
};

//------------------------//
// Convert BSTR to char * //
//------------------------//
 char* ConvertBSTRToString(BSTR pSrc)
{
    if(!pSrc) return NULL;

    //convert even embeded NULL
    DWORD cb,cwch = ::SysStringLen(pSrc);

    char *szOut = NULL;

    if(cb = ::WideCharToMultiByte(CP_ACP, 0, 
               pSrc, cwch + 1, NULL, 0, 0, 0))
    {
        szOut = new char[cb];
        if(szOut)
        {
            szOut[cb - 1]  = '\0';

            if(!::WideCharToMultiByte(CP_ACP, 0, 
                pSrc, cwch + 1, szOut, cb, 0, 0))
            {
                delete []szOut;//clean up if failed;
                szOut = NULL;
            }
        }
    }
//	delete []szOut;
    return szOut;
};
long CShtrihFRK::IDrvFR47::AddLD()
{
	long result;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Beep()
{
	long result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Buy()
{
	long result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::BuyEx()
{
	long result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CancelCheck()
{
	long result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CashIncome()
{
	long result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CashOutcome()
{
	long result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Charge()
{
	long result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CheckSubTotal()
{
	long result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CloseCheck()
{
	long result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ConfirmDate()
{
	long result;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Connect()
{
	long result;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ContinuePrint()
{
	long result;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Correction()
{
	long result;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CutCheck()
{
	long result;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::DampRequest()
{
	long result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::DeleteLD()
{
	long result;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Disconnect()
{
	long result;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Discount()
{
	long result;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::DozeOilCheck()
{
	long result;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Draw()
{
	long result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZDepartmentReportInDatesRange()
{
	long result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZDepartmentReportInSessionsRange()
{
	long result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZJournalOnSessionNumber()
{
	long result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZSessionReportInDatesRange()
{
	long result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZSessionReportInSessionsRange()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ExchangeBytes()
{
	long result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::FeedDocument()
{
	long result;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Fiscalization()
{
	long result;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::FiscalReportForDatesRange()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::FiscalReportForSessionRange()
{
	long result;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetActiveLD()
{
	long result;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EnumLD()
{
	long result;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCashReg()
{
	long result;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCountLD()
{
	long result;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetData()
{
	long result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetDeviceMetrics()
{
	long result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetECRStatus()
{
	long result;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetShortECRStatus()
{
	long result;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetExchangeParam()
{
	long result;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFieldStruct()
{
	long result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFiscalizationParameters()
{
	long result;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFMRecordsSum()
{
	long result;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetLastFMRecordDate()
{
	long result;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetLiterSumCounter()
{
	long result;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetOperationReg()
{
	long result;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetParamLD()
{
	long result;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetRangeDatesAndSessions()
{
	long result;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetRKStatus()
{
	long result;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetTableStruct()
{
	long result;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::InitFM()
{
	long result;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::InitTable()
{
	long result;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::InterruptDataStream()
{
	long result;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::InterruptFullReport()
{
	long result;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::InterruptTest()
{
	long result;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::LaunchRK()
{
	long result;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::LoadLineData()
{
	long result;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::OilSale()
{
	long result;
	InvokeHelper(0x3b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::OpenCheck()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::OpenDrawer()
{
	long result;
	InvokeHelper(0x3d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintBarCode()
{
	long result;
	InvokeHelper(0x3e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintDepartmentReport()
{
	long result;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintDocumentTitle()
{
	long result;
	InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintOperationReg()
{
	long result;
	InvokeHelper(0x41, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintReportWithCleaning()
{
	long result;
	InvokeHelper(0x42, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintReportWithoutCleaning()
{
	long result;
	InvokeHelper(0x43, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintString()
{
	long result;
	InvokeHelper(0x44, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintWideString()
{
	long result;
	InvokeHelper(0x45, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReadEKLZDocumentOnKPK()
{
	long result;
	InvokeHelper(0x46, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReadEKLZSessionTotal()
{
	long result;
	InvokeHelper(0x47, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReadLicense()
{
	long result;
	InvokeHelper(0x48, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReadTable()
{
	long result;
	InvokeHelper(0x49, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::RepeatDocument()
{
	long result;
	InvokeHelper(0x4a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ResetAllTRK()
{
	long result;
	InvokeHelper(0x4b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ResetRK()
{
	long result;
	InvokeHelper(0x4c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ResetSettings()
{
	long result;
	InvokeHelper(0x4d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ResetSummary()
{
	long result;
	InvokeHelper(0x4e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReturnBuy()
{
	long result;
	InvokeHelper(0x4f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReturnBuyEx()
{
	long result;
	InvokeHelper(0x50, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReturnSale()
{
	long result;
	InvokeHelper(0x51, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReturnSaleEx()
{
	long result;
	InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Sale()
{
	long result;
	InvokeHelper(0x53, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SaleEx()
{
	long result;
	InvokeHelper(0x54, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetActiveLD()
{
	long result;
	InvokeHelper(0x55, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetDate()
{
	long result;
	InvokeHelper(0x56, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetDozeInMilliliters()
{
	long result;
	InvokeHelper(0x57, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetDozeInMoney()
{
	long result;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetExchangeParam()
{
	long result;
	InvokeHelper(0x59, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetParamLD()
{
	long result;
	InvokeHelper(0x5a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetPointPosition()
{
	long result;
	InvokeHelper(0x5b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetRKParameters()
{
	long result;
	InvokeHelper(0x5c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetSerialNumber()
{
	long result;
	InvokeHelper(0x5d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetTime()
{
	long result;
	InvokeHelper(0x5e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ShowProperties()
{
	long result;
	InvokeHelper(0x5f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StopEKLZDocumentPrinting()
{
	long result;
	InvokeHelper(0x60, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StopRK()
{
	long result;
	InvokeHelper(0x61, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Storno()
{
	long result;
	InvokeHelper(0x62, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StornoEx()
{
	long result;
	InvokeHelper(0x63, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StornoCharge()
{
	long result;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StornoDiscount()
{
	long result;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SummOilCheck()
{
	long result;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SysAdminCancelCheck()
{
	long result;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Test()
{
	long result;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::WriteLicense()
{
	long result;
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::WriteTable()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetBarCode()
{
	CString result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetBarCode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetBatteryCondition()
{
	BOOL result;
	InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

double CShtrihFRK::IDrvFR47::GetBatteryVoltage()
{
	double result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetBaudRate()
{
	long result;
	InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetBaudRate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CY CShtrihFRK::IDrvFR47::GetChange()
{
	CY result;
	InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

CY CShtrihFRK::IDrvFR47::GetCheckResult()
{
	CY result;
	InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCheckResult(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CShtrihFRK::IDrvFR47::GetCheckType()
{
	long result;
	InvokeHelper(0x71, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCheckType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x71, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetComNumber()
{
	long result;
	InvokeHelper(0x72, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetComNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x72, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CY CShtrihFRK::IDrvFR47::GetContentsOfCashRegister()
{
	CY result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetContentsOfOperationRegister()
{
	long result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCurrentDozeInMilliliters()
{
	long result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCurrentDozeInMilliliters(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CY CShtrihFRK::IDrvFR47::GetCurrentDozeInMoney()
{
	CY result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCurrentDozeInMoney(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

BOOL CShtrihFRK::IDrvFR47::GetCutType()
{
	BOOL result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCutType(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CShtrihFRK::IDrvFR47::GetDataBlock()
{
	CString result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetDataBlockNumber()
{
	long result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

DATE CShtrihFRK::IDrvFR47::GetDate()
{
	DATE result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CShtrihFRK::IDrvFR47::GetDepartment()
{
	long result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDepartment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDeviceCode()
{
	long result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDeviceCode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetDeviceCodeDescription()
{
	CString result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

double CShtrihFRK::IDrvFR47::GetDiscountOnCheck()
{
	double result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheck(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString CShtrihFRK::IDrvFR47::GetDocumentName()
{
	CString result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDocumentName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetDocumentNumber()
{
	long result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDocumentNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDozeInMilliliters()
{
	long result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDozeInMilliliters(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x81, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CY CShtrihFRK::IDrvFR47::GetDozeInMoney()
{
	CY result;
	InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDozeInMoney(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long CShtrihFRK::IDrvFR47::GetDrawerNumber()
{
	long result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDrawerNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetECRAdvancedMode()
{
	long result;
	InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetECRAdvancedModeDescription()
{
	CString result;
	InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetECRBuild()
{
	long result;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetECRFlags()
{
	long result;
	InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetECRInput()
{
	CString result;
	InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetECRMode()
{
	long result;
	InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetECRMode8Status()
{
	long result;
	InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetECRModeDescription()
{
	CString result;
	InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetECROutput()
{
	CString result;
	InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

DATE CShtrihFRK::IDrvFR47::GetECRSoftDate()
{
	DATE result;
	InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetECRSoftVersion()
{
	CString result;
	InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetEKLZIsPresent()
{
	BOOL result;
	InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEmergencyStopCode()
{
	long result;
	InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetEmergencyStopCodeDescription()
{
	CString result;
	InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetFieldName()
{
	CString result;
	InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFieldNumber()
{
	long result;
	InvokeHelper(0x93, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFieldNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x93, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetFieldSize()
{
	long result;
	InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetFieldType()
{
	BOOL result;
	InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFirstLineNumber()
{
	long result;
	InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFirstLineNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE CShtrihFRK::IDrvFR47::GetFirstSessionDate()
{
	DATE result;
	InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFirstSessionDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CShtrihFRK::IDrvFR47::GetFirstSessionNumber()
{
	long result;
	InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFirstSessionNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x98, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetFM1IsPresent()
{
	BOOL result;
	InvokeHelper(0x99, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetFM2IsPresent()
{
	BOOL result;
	InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFMBuild()
{
	long result;
	InvokeHelper(0x9b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFMFlags()
{
	long result;
	InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetFMOverflow()
{
	BOOL result;
	InvokeHelper(0x9d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

DATE CShtrihFRK::IDrvFR47::GetFMSoftDate()
{
	DATE result;
	InvokeHelper(0x9e, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetFMSoftVersion()
{
	CString result;
	InvokeHelper(0x9f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFreeRecordInFM()
{
	long result;
	InvokeHelper(0xa0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFreeRegistration()
{
	long result;
	InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetInn()
{
	CString result;
	InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetInn(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xa2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetIsCheckClosed()
{
	BOOL result;
	InvokeHelper(0xa3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsCheckMadeOut()
{
	BOOL result;
	InvokeHelper(0xa4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsDrawerOpen()
{
	BOOL result;
	InvokeHelper(0xa5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetJournalRibbonIsPresent()
{
	BOOL result;
	InvokeHelper(0xa6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetJournalRibbonLever()
{
	BOOL result;
	InvokeHelper(0xa7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetJournalRibbonOpticalSensor()
{
	BOOL result;
	InvokeHelper(0xa8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetKPKNumber()
{
	long result;
	InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetKPKNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xaa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLastLineNumber()
{
	long result;
	InvokeHelper(0xab, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLastLineNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE CShtrihFRK::IDrvFR47::GetLastSessionDate()
{
	DATE result;
	InvokeHelper(0xac, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLastSessionDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0xac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CShtrihFRK::IDrvFR47::GetLastSessionNumber()
{
	long result;
	InvokeHelper(0xad, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLastSessionNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetLicense()
{
	CString result;
	InvokeHelper(0xae, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLicense(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetLicenseIsPresent()
{
	BOOL result;
	InvokeHelper(0xaf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetLidPositionSensor()
{
	BOOL result;
	InvokeHelper(0xb0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetLineData()
{
	CString result;
	InvokeHelper(0xb1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLineData(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetLineNumber()
{
	long result;
	InvokeHelper(0xb2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLineNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLogicalNumber()
{
	long result;
	InvokeHelper(0xb3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetMAXValueOfField()
{
	long result;
	InvokeHelper(0xb4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetMINValueOfField()
{
	long result;
	InvokeHelper(0xb5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetMotor()
{
	BOOL result;
	InvokeHelper(0xb6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetNameCashReg()
{
	CString result;
	InvokeHelper(0xb7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetNameOperationReg()
{
	CString result;
	InvokeHelper(0xb8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetNewPasswordTI()
{
	long result;
	InvokeHelper(0xb9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetNewPasswordTI(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetOpenDocumentNumber()
{
	long result;
	InvokeHelper(0xba, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetOperatorNumber()
{
	long result;
	InvokeHelper(0xbb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetPassword()
{
	long result;
	InvokeHelper(0xbc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPassword(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xbc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetPistol()
{
	BOOL result;
	InvokeHelper(0xbd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetPointPosition()
{
	BOOL result;
	InvokeHelper(0xbe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPointPosition(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xbe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetPortNumber()
{
	long result;
	InvokeHelper(0xbf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPortNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xbf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CY CShtrihFRK::IDrvFR47::GetPrice()
{
	CY result;
	InvokeHelper(0xc0, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPrice(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0xc0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double CShtrihFRK::IDrvFR47::GetQuantity()
{
	double result;
	InvokeHelper(0xc1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetQuantity(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xc1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CShtrihFRK::IDrvFR47::GetQuantityOfOperations()
{
	long result;
	InvokeHelper(0xc2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetReceiptRibbonIsPresent()
{
	BOOL result;
	InvokeHelper(0xc3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetReceiptRibbonLever()
{
	BOOL result;
	InvokeHelper(0xc4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetReceiptRibbonOpticalSensor()
{
	BOOL result;
	InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetRegisterNumber()
{
	long result;
	InvokeHelper(0xc6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRegisterNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetRegistrationNumber()
{
	long result;
	InvokeHelper(0xc7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRegistrationNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetReportType()
{
	BOOL result;
	InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetReportType(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetResultCode()
{
	long result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetResultCodeDescription()
{
	CString result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetRKNumber()
{
	long result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRKNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetRnm()
{
	CString result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRnm(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetRoughValve()
{
	BOOL result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetRowNumber()
{
	long result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRowNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetRunningPeriod()
{
	long result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRunningPeriod(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetSerialNumber()
{
	CString result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSerialNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetSessionNumber()
{
	long result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSessionNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetSlipDocumentIsMoving()
{
	BOOL result;
	InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetSlipDocumentIsPresent()
{
	BOOL result;
	InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetSlowingInMilliliters()
{
	long result;
	InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSlowingInMilliliters(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetSlowingValve()
{
	BOOL result;
	InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetStatusRK()
{
	long result;
	InvokeHelper(0xd6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetStatusRKDescription()
{
	CString result;
	InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetStringForPrinting()
{
	CString result;
	InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetStringForPrinting(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetStringQuantity()
{
	long result;
	InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetStringQuantity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CY CShtrihFRK::IDrvFR47::GetSumm1()
{
	CY result;
	InvokeHelper(0xda, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm1(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0xda, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CY CShtrihFRK::IDrvFR47::GetSumm2()
{
	CY result;
	InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm2(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0xdb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CY CShtrihFRK::IDrvFR47::GetSumm3()
{
	CY result;
	InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm3(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0xdc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CY CShtrihFRK::IDrvFR47::GetSumm4()
{
	CY result;
	InvokeHelper(0xdd, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm4(const CY& newValue)
{
	static BYTE parms[] =
		VTS_CY;
	InvokeHelper(0xdd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString CShtrihFRK::IDrvFR47::GetTableName()
{
	CString result;
	InvokeHelper(0xde, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetTableNumber()
{
	long result;
	InvokeHelper(0xdf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTableNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xdf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1()
{
	long result;
	InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2()
{
	long result;
	InvokeHelper(0xe1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3()
{
	long result;
	InvokeHelper(0xe2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4()
{
	long result;
	InvokeHelper(0xe3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

DATE CShtrihFRK::IDrvFR47::GetTime()
{
	DATE result;
	InvokeHelper(0xe4, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTime(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0xe4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CShtrihFRK::IDrvFR47::GetTimeout()
{
	long result;
	InvokeHelper(0xe5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetTimeStr()
{
	CString result;
	InvokeHelper(0xe6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTimeStr(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CShtrihFRK::IDrvFR47::GetTransferBytes()
{
	CString result;
	InvokeHelper(0xe7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTransferBytes(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetTRKNumber()
{
	long result;
	InvokeHelper(0xe8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTRKNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetTypeOfLastEntryFM()
{
	BOOL result;
	InvokeHelper(0xe9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetTypeOfSumOfEntriesFM()
{
	BOOL result;
	InvokeHelper(0xea, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTypeOfSumOfEntriesFM(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xea, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetUCodePage()
{
	long result;
	InvokeHelper(0xeb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetUDescription()
{
	CString result;
	InvokeHelper(0xec, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetUMajorProtocolVersion()
{
	long result;
	InvokeHelper(0xed, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetUMajorType()
{
	long result;
	InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetUMinorProtocolVersion()
{
	long result;
	InvokeHelper(0xef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetUMinorType()
{
	long result;
	InvokeHelper(0xf0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetUModel()
{
	long result;
	InvokeHelper(0xf1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetUseJournalRibbon()
{
	BOOL result;
	InvokeHelper(0xf2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetUseJournalRibbon(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetUseReceiptRibbon()
{
	BOOL result;
	InvokeHelper(0xf3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetUseReceiptRibbon(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetUseSlipDocument()
{
	BOOL result;
	InvokeHelper(0xf4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetUseSlipDocument(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetValueOfFieldInteger()
{
	long result;
	InvokeHelper(0xf5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetValueOfFieldInteger(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetValueOfFieldString()
{
	CString result;
	InvokeHelper(0xf6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetValueOfFieldString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::PrintStringWithFont()
{
	long result;
	InvokeHelper(0xa9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFontType()
{
	long result;
	InvokeHelper(0xf7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFontType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDBaudrate()
{
	long result;
	InvokeHelper(0xf8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDBaudrate(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDComNumber()
{
	long result;
	InvokeHelper(0xf9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDComNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDCount()
{
	long result;
	InvokeHelper(0xfa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetLDIndex()
{
	long result;
	InvokeHelper(0xfb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xfb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetLDName()
{
	CString result;
	InvokeHelper(0xfc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xfc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDNumber()
{
	long result;
	InvokeHelper(0xfd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xfd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetWaitPrintingTime()
{
	long result;
	InvokeHelper(0xfe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsPrinterLeftSensorFailure()
{
	BOOL result;
	InvokeHelper(0xff, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsPrinterRightSensorFailure()
{
	BOOL result;
	InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZActivizationResult()
{
	long result;
	InvokeHelper(0x101, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZActivization()
{
	long result;
	InvokeHelper(0x102, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CloseEKLZArchive()
{
	long result;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZSerialNumber()
{
	long result;
	InvokeHelper(0x104, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetEKLZNumber()
{
	CString result;
	InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::EKLZInterrupt()
{
	long result;
	InvokeHelper(0x106, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZCode1Report()
{
	long result;
	InvokeHelper(0x107, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CY CShtrihFRK::IDrvFR47::GetLastKPKDocumentResult()
{
	CY result;
	InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_CY, (void*)&result, NULL);
	return result;
}

DATE CShtrihFRK::IDrvFR47::GetLastKPKDate()
{
	DATE result;
	InvokeHelper(0x109, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

DATE CShtrihFRK::IDrvFR47::GetLastKPKTime()
{
	DATE result;
	InvokeHelper(0x10a, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetLastKPKNumber()
{
	long result;
	InvokeHelper(0x10b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZFlags()
{
	long result;
	InvokeHelper(0x10c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZCode2Report()
{
	long result;
	InvokeHelper(0x10d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::TestEKLZArchiveIntegrity()
{
	long result;
	InvokeHelper(0x10e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetTestNumber()
{
	long result;
	InvokeHelper(0x10f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTestNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::Get_EKLZVersion()
{
	CString result;
	InvokeHelper(0x110, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::Get_EKLZData()
{
	CString result;
	InvokeHelper(0x111, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZVersion()
{
	long result;
	InvokeHelper(0x112, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::InitEKLZArchive()
{
	long result;
	InvokeHelper(0x113, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZData()
{
	long result;
	InvokeHelper(0x114, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZJournal()
{
	long result;
	InvokeHelper(0x115, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZDocument()
{
	long result;
	InvokeHelper(0x116, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZDepartmentReportInDatesRange()
{
	long result;
	InvokeHelper(0x117, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZDepartmentReportInSessionsRange()
{
	long result;
	InvokeHelper(0x118, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZSessionReportInDatesRange()
{
	long result;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZSessionReportInSessionsRange()
{
	long result;
	InvokeHelper(0x11a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZSessionTotal()
{
	long result;
	InvokeHelper(0x11b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZActivizationResult()
{
	long result;
	InvokeHelper(0x11c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetEKLZResultCode()
{
	long result;
	InvokeHelper(0x11d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZResultCode()
{
	long result;
	InvokeHelper(0x11e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEKLZResultCode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetFMResultCode()
{
	long result;
	InvokeHelper(0x11f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

double CShtrihFRK::IDrvFR47::GetPowerSourceVoltage()
{
	double result;
	InvokeHelper(0x120, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsEKLZOverflow()
{
	BOOL result;
	InvokeHelper(0x121, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::OpenFiscalSlipDocument()
{
	long result;
	InvokeHelper(0x123, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::OpenStandardFiscalSlipDocument()
{
	long result;
	InvokeHelper(0x124, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::RegistrationOnSlipDocument()
{
	long result;
	InvokeHelper(0x125, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StandardRegistrationOnSlipDocument()
{
	long result;
	InvokeHelper(0x126, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ChargeOnSlipDocument()
{
	long result;
	InvokeHelper(0x127, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StandardChargeOnSlipDocument()
{
	long result;
	InvokeHelper(0x128, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CloseCheckOnSlipDocument()
{
	long result;
	InvokeHelper(0x129, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StandardCloseCheckOnSlipDocument()
{
	long result;
	InvokeHelper(0x12a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ConfigureSlipDocument()
{
	long result;
	InvokeHelper(0x12b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ConfigureStandardSlipDocument()
{
	long result;
	InvokeHelper(0x12c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::FillSlipDocumentWithUnfiscalInfo()
{
	long result;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ClearSlipDocumentBufferString()
{
	long result;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ClearSlipDocumentBuffer()
{
	long result;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintSlipDocument()
{
	long result;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCopyType()
{
	long result;
	InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCopyType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetNumberOfCopies()
{
	long result;
	InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetNumberOfCopies(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x133, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCopyOffset1()
{
	long result;
	InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCopyOffset1(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x134, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCopyOffset2()
{
	long result;
	InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCopyOffset2(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCopyOffset3()
{
	long result;
	InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCopyOffset3(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCopyOffset4()
{
	long result;
	InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCopyOffset4(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x137, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCopyOffset5()
{
	long result;
	InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCopyOffset5(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x138, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetClicheFont()
{
	long result;
	InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetClicheFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetHeaderFont()
{
	long result;
	InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetHeaderFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetEKLZFont()
{
	long result;
	InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEKLZFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetClicheStringNumber()
{
	long result;
	InvokeHelper(0x13c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetClicheStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetHeaderStringNumber()
{
	long result;
	InvokeHelper(0x13d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetHeaderStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetEKLZStringNumber()
{
	long result;
	InvokeHelper(0x13e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEKLZStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetFMStringNumber()
{
	long result;
	InvokeHelper(0x13f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFMStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetClicheOffset()
{
	long result;
	InvokeHelper(0x140, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetClicheOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x140, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetHeaderOffset()
{
	long result;
	InvokeHelper(0x141, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetHeaderOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x141, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetEKLZOffset()
{
	long result;
	InvokeHelper(0x142, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEKLZOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x142, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetKPKOffset()
{
	long result;
	InvokeHelper(0x143, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetKPKOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x143, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetFMOffset()
{
	long result;
	InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFMOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x144, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetOperationBlockFirstString()
{
	long result;
	InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetOperationBlockFirstString(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x145, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetQuantityFormat()
{
	long result;
	InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetQuantityFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x146, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetStringQuantityInOperation()
{
	long result;
	InvokeHelper(0x147, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetStringQuantityInOperation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x147, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTextStringNumber()
{
	long result;
	InvokeHelper(0x148, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTextStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x148, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetQuantityStringNumber()
{
	long result;
	InvokeHelper(0x149, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetQuantityStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x149, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSummStringNumber()
{
	long result;
	InvokeHelper(0x14a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSummStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDepartmentStringNumber()
{
	long result;
	InvokeHelper(0x14b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDepartmentStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTextFont()
{
	long result;
	InvokeHelper(0x14c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTextFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetQuantityFont()
{
	long result;
	InvokeHelper(0x14d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetQuantityFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetMultiplicationFont()
{
	long result;
	InvokeHelper(0x14e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetMultiplicationFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetPriceFont()
{
	long result;
	InvokeHelper(0x14f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPriceFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSummFont()
{
	long result;
	InvokeHelper(0x150, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSummFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x150, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDepartmentFont()
{
	long result;
	InvokeHelper(0x151, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDepartmentFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x151, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTextSymbolNumber()
{
	long result;
	InvokeHelper(0x152, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTextSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x152, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetQuantitySymbolNumber()
{
	long result;
	InvokeHelper(0x153, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetQuantitySymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x153, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetPriceSymbolNumber()
{
	long result;
	InvokeHelper(0x154, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPriceSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x154, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSummSymbolNumber()
{
	long result;
	InvokeHelper(0x155, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSummSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x155, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDepartmentSymbolNumber()
{
	long result;
	InvokeHelper(0x156, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDepartmentSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x156, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTextOffset()
{
	long result;
	InvokeHelper(0x157, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTextOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x157, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetQuantityOffset()
{
	long result;
	InvokeHelper(0x158, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetQuantityOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x158, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSummOffset()
{
	long result;
	InvokeHelper(0x159, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSummOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x159, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDepartmentOffset()
{
	long result;
	InvokeHelper(0x15a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDepartmentOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::DiscountOnSlipDocument()
{
	long result;
	InvokeHelper(0x15b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::StandardDiscountOnSlipDocument()
{
	long result;
	InvokeHelper(0x15c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsClearUnfiscalInfo()
{
	BOOL result;
	InvokeHelper(0x15d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetIsClearUnfiscalInfo(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetInfoType()
{
	long result;
	InvokeHelper(0x15e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetInfoType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetStringNumber()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::EjectSlipDocument()
{
	long result;
	InvokeHelper(0x122, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEjectDirection()
{
	long result;
	InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEjectDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::LoadLineDataEx()
{
	long result;
	InvokeHelper(0x15f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::DrawEx()
{
	long result;
	InvokeHelper(0x160, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ConfigureGeneralSlipDocument()
{
	long result;
	InvokeHelper(0x161, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetOperationNameStringNumber()
{
	long result;
	InvokeHelper(0x163, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetOperationNameStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x163, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetOperationNameFont()
{
	long result;
	InvokeHelper(0x164, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetOperationNameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x164, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetOperationNameOffset()
{
	long result;
	InvokeHelper(0x165, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetOperationNameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x165, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTotalStringNumber()
{
	long result;
	InvokeHelper(0x166, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTotalStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x166, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm1StringNumber()
{
	long result;
	InvokeHelper(0x167, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm1StringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x167, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm2StringNumber()
{
	long result;
	InvokeHelper(0x168, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm2StringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x168, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm3StringNumber()
{
	long result;
	InvokeHelper(0x169, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm3StringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x169, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm4StringNumber()
{
	long result;
	InvokeHelper(0x16a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm4StringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetChangeStringNumber()
{
	long result;
	InvokeHelper(0x16b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetChangeStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1TurnOverStringNumber()
{
	long result;
	InvokeHelper(0x16c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1TurnOverStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2TurnOverStringNumber()
{
	long result;
	InvokeHelper(0x16d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2TurnOverStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3TurnOverStringNumber()
{
	long result;
	InvokeHelper(0x16e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3TurnOverStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4TurnOverStringNumber()
{
	long result;
	InvokeHelper(0x16f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4TurnOverStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1SumStringNumber()
{
	long result;
	InvokeHelper(0x170, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1SumStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x170, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2SumStringNumber()
{
	long result;
	InvokeHelper(0x171, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2SumStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x171, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3SumStringNumber()
{
	long result;
	InvokeHelper(0x172, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3SumStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x172, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4SumStringNumber()
{
	long result;
	InvokeHelper(0x173, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4SumStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x173, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSubTotalStringNumber()
{
	long result;
	InvokeHelper(0x174, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSubTotalStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x174, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDiscountOnCheckStringNumber()
{
	long result;
	InvokeHelper(0x175, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheckStringNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x175, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTotalFont()
{
	long result;
	InvokeHelper(0x176, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTotalFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x176, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTotalSumFont()
{
	long result;
	InvokeHelper(0x177, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTotalSumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x177, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm1Font()
{
	long result;
	InvokeHelper(0x178, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm1Font(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x178, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm1NameFont()
{
	long result;
	InvokeHelper(0x179, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm1NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x179, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm2NameFont()
{
	long result;
	InvokeHelper(0x17a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm2NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm3NameFont()
{
	long result;
	InvokeHelper(0x17b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm3NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm4NameFont()
{
	long result;
	InvokeHelper(0x17c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm4NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm2Font()
{
	long result;
	InvokeHelper(0x17d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm2Font(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm3Font()
{
	long result;
	InvokeHelper(0x17e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm3Font(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm4Font()
{
	long result;
	InvokeHelper(0x17f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm4Font(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetChangeFont()
{
	long result;
	InvokeHelper(0x180, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetChangeFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x180, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetChangeSumFont()
{
	long result;
	InvokeHelper(0x181, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetChangeSumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x181, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1NameFont()
{
	long result;
	InvokeHelper(0x182, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x182, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2NameFont()
{
	long result;
	InvokeHelper(0x183, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x183, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3NameFont()
{
	long result;
	InvokeHelper(0x184, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x184, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4NameFont()
{
	long result;
	InvokeHelper(0x185, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4NameFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x185, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1TurnOverFont()
{
	long result;
	InvokeHelper(0x186, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1TurnOverFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x186, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2TurnOverFont()
{
	long result;
	InvokeHelper(0x187, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2TurnOverFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x187, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3TurnOverFont()
{
	long result;
	InvokeHelper(0x188, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3TurnOverFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x188, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4TurnOverFont()
{
	long result;
	InvokeHelper(0x189, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4TurnOverFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x189, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1RateFont()
{
	long result;
	InvokeHelper(0x18a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1RateFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2RateFont()
{
	long result;
	InvokeHelper(0x18b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2RateFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3RateFont()
{
	long result;
	InvokeHelper(0x18c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3RateFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4RateFont()
{
	long result;
	InvokeHelper(0x18d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4RateFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1SumFont()
{
	long result;
	InvokeHelper(0x18e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1SumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2SumFont()
{
	long result;
	InvokeHelper(0x18f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2SumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3SumFont()
{
	long result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3SumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x190, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4SumFont()
{
	long result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4SumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSubTotalFont()
{
	long result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSubTotalFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSubTotalSumFont()
{
	long result;
	InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSubTotalSumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDiscountOnCheckFont()
{
	long result;
	InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheckFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDiscountOnCheckSumFont()
{
	long result;
	InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheckSumFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTotalSymbolNumber()
{
	long result;
	InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTotalSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm1SymbolNumber()
{
	long result;
	InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm1SymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm2SymbolNumber()
{
	long result;
	InvokeHelper(0x198, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm2SymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x198, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm3SymbolNumber()
{
	long result;
	InvokeHelper(0x199, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm3SymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x199, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm4SymbolNumber()
{
	long result;
	InvokeHelper(0x19a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm4SymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetChangeSymbolNumber()
{
	long result;
	InvokeHelper(0x19b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetChangeSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1NameSymbolNumber()
{
	long result;
	InvokeHelper(0x19c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1NameSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1TurnOverSymbolNumber()
{
	long result;
	InvokeHelper(0x19d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1TurnOverSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1RateSymbolNumber()
{
	long result;
	InvokeHelper(0x19e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1RateSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1SumSymbolNumber()
{
	long result;
	InvokeHelper(0x19f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1SumSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x19f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2NameSymbolNumber()
{
	long result;
	InvokeHelper(0x1a0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2NameSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2TurnOverSymbolNumber()
{
	long result;
	InvokeHelper(0x1a1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2TurnOverSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2RateSymbolNumber()
{
	long result;
	InvokeHelper(0x1a2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2RateSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2SumSymbolNumber()
{
	long result;
	InvokeHelper(0x1a3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2SumSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3NameSymbolNumber()
{
	long result;
	InvokeHelper(0x1a4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3NameSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3TurnOverSymbolNumber()
{
	long result;
	InvokeHelper(0x1a5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3TurnOverSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3RateSymbolNumber()
{
	long result;
	InvokeHelper(0x1a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3RateSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3SumSymbolNumber()
{
	long result;
	InvokeHelper(0x1a7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3SumSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4NameSymbolNumber()
{
	long result;
	InvokeHelper(0x1a8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4NameSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4TurnOverSymbolNumber()
{
	long result;
	InvokeHelper(0x1a9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4TurnOverSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4RateSymbolNumber()
{
	long result;
	InvokeHelper(0x1aa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4RateSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1aa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4SumSymbolNumber()
{
	long result;
	InvokeHelper(0x1ab, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4SumSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSubTotalSymbolNumber()
{
	long result;
	InvokeHelper(0x1ac, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSubTotalSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDiscountOnCheckSymbolNumber()
{
	long result;
	InvokeHelper(0x1ad, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheckSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDiscountOnCheckSumSymbolNumber()
{
	long result;
	InvokeHelper(0x1ae, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheckSumSymbolNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTotalOffset()
{
	long result;
	InvokeHelper(0x1af, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTotalOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1af, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm1Offset()
{
	long result;
	InvokeHelper(0x1b0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm1Offset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTotalSumOffset()
{
	long result;
	InvokeHelper(0x1b1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTotalSumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm1NameOffset()
{
	long result;
	InvokeHelper(0x1b2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm1NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm2Offset()
{
	long result;
	InvokeHelper(0x1b3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm2Offset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm2NameOffset()
{
	long result;
	InvokeHelper(0x1b4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm2NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm3Offset()
{
	long result;
	InvokeHelper(0x1b5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm3Offset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm3NameOffset()
{
	long result;
	InvokeHelper(0x1b6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm3NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm4Offset()
{
	long result;
	InvokeHelper(0x1b7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm4Offset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSumm4NameOffset()
{
	long result;
	InvokeHelper(0x1b8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSumm4NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetChangeOffset()
{
	long result;
	InvokeHelper(0x1b9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetChangeOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetChangeSumOffset()
{
	long result;
	InvokeHelper(0x1ba, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetChangeSumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ba, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1NameOffset()
{
	long result;
	InvokeHelper(0x1bb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1bb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1TurnOverOffset()
{
	long result;
	InvokeHelper(0x1bc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1TurnOverOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1bc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1RateOffset()
{
	long result;
	InvokeHelper(0x1bd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1RateOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1bd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax1SumOffset()
{
	long result;
	InvokeHelper(0x1be, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax1SumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1be, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2NameOffset()
{
	long result;
	InvokeHelper(0x1bf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1bf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2TurnOverOffset()
{
	long result;
	InvokeHelper(0x1c0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2TurnOverOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2RateOffset()
{
	long result;
	InvokeHelper(0x1c1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2RateOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax2SumOffset()
{
	long result;
	InvokeHelper(0x1c2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax2SumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3NameOffset()
{
	long result;
	InvokeHelper(0x1c3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3TurnOverOffset()
{
	long result;
	InvokeHelper(0x1c4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3TurnOverOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3RateOffset()
{
	long result;
	InvokeHelper(0x1c5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3RateOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax3SumOffset()
{
	long result;
	InvokeHelper(0x1c6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax3SumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4NameOffset()
{
	long result;
	InvokeHelper(0x1c7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4NameOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4TurnOverOffset()
{
	long result;
	InvokeHelper(0x1c8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4TurnOverOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4RateOffset()
{
	long result;
	InvokeHelper(0x1c9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4RateOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1c9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTax4SumOffset()
{
	long result;
	InvokeHelper(0x1ca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTax4SumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSubTotalOffset()
{
	long result;
	InvokeHelper(0x1cb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSubTotalOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1cb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSubTotalSumOffset()
{
	long result;
	InvokeHelper(0x1cc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSubTotalSumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1cc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSlipDocumentWidth()
{
	long result;
	InvokeHelper(0x1cd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSlipDocumentWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1cd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetSlipDocumentLength()
{
	long result;
	InvokeHelper(0x1ce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSlipDocumentLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1ce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetPrintingAlignment()
{
	long result;
	InvokeHelper(0x1cf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPrintingAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1cf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetSlipStringIntervals()
{
	CString result;
	InvokeHelper(0x1d0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSlipStringIntervals(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetSlipEqualStringIntervals()
{
	long result;
	InvokeHelper(0x1d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSlipEqualStringIntervals(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetKPKFont()
{
	long result;
	InvokeHelper(0x162, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetKPKFont(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x162, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDiscountOnCheckOffset()
{
	long result;
	InvokeHelper(0x1d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheckOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetDiscountOnCheckSumOffset()
{
	long result;
	InvokeHelper(0x1d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetDiscountOnCheckSumOffset(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::WideLoadLineData()
{
	long result;
	InvokeHelper(0x1d4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintTaxReport()
{
	long result;
	InvokeHelper(0x1d5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetQuantityPointPosition()
{
	BOOL result;
	InvokeHelper(0x1d6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

unsigned long CShtrihFRK::IDrvFR47::GetFileVersionMS()
{
	unsigned long result;
	InvokeHelper(0x1d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CShtrihFRK::IDrvFR47::GetFileVersionLS()
{
	unsigned long result;
	InvokeHelper(0x1d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetLongSerialNumberAndLongRNM()
{
	long result;
	InvokeHelper(0x1d9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetLongSerialNumber()
{
	long result;
	InvokeHelper(0x1da, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::FiscalizationWithLongRNM()
{
	long result;
	InvokeHelper(0x1db, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsBatteryLow()
{
	BOOL result;
	InvokeHelper(0x1dc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsLastFMRecordCorrupted()
{
	BOOL result;
	InvokeHelper(0x1dd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsFMSessionOpen()
{
	BOOL result;
	InvokeHelper(0x1de, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetIsFM24HoursOver()
{
	BOOL result;
	InvokeHelper(0x1df, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::Connect2()
{
	long result;
	InvokeHelper(0x1e0, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetECRModeStatus()
{
	long result;
	InvokeHelper(0x1e1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetECRPrinterStatus()
{
	long result;
	InvokeHelper(0x1e2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetPrinterStatus()
{
	long result;
	InvokeHelper(0x1e3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetServerVersion()
{
	CString result;
	InvokeHelper(0x1e4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetLDComputerName()
{
	CString result;
	InvokeHelper(0x1e5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDComputerName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDTimeout()
{
	long result;
	InvokeHelper(0x1e6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1e6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetComputerName()
{
	CString result;
	InvokeHelper(0x1e7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetComputerName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::ServerConnect()
{
	long result;
	InvokeHelper(0x1e8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ServerDisconnect()
{
	long result;
	InvokeHelper(0x1e9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetServerConnected()
{
	BOOL result;
	InvokeHelper(0x1ea, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::LockPort()
{
	long result;
	InvokeHelper(0x1eb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::UnlockPort()
{
	long result;
	InvokeHelper(0x1ec, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetPortLocked()
{
	BOOL result;
	InvokeHelper(0x1ed, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::AdminUnlockPort()
{
	long result;
	InvokeHelper(0x1ee, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::AdminUnlockPorts()
{
	long result;
	InvokeHelper(0x1ef, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ServerCheckKey()
{
	long result;
	InvokeHelper(0x1f0, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFontMetrics()
{
	long result;
	InvokeHelper(0x1f1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetPrintWidth()
{
	long result;
	InvokeHelper(0x1f2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCharWidth()
{
	long result;
	InvokeHelper(0x1f3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCharHeight()
{
	long result;
	InvokeHelper(0x1f4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFontCount()
{
	long result;
	InvokeHelper(0x1f6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetFreeLDNumber()
{
	long result;
	InvokeHelper(0x1f5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetLogOn()
{
	BOOL result;
	InvokeHelper(0x1f7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLogOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CShtrihFRK::IDrvFR47::SetIsString(BOOL Value)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Value);
}

void CShtrihFRK::IDrvFR47::SetFieldSize(long Value)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Value);
}

long CShtrihFRK::IDrvFR47::ReadTable2()
{
	long result;
	InvokeHelper(0x1fa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::WriteTable2()
{
	long result;
	InvokeHelper(0x1fb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetFieldMinValue(long Value)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Value);
}

void CShtrihFRK::IDrvFR47::SetFieldMaxValue(long Value)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Value);
}

BOOL CShtrihFRK::IDrvFR47::GetCPLog()
{
	BOOL result;
	InvokeHelper(0x1fe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCPLog(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1fe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CShtrihFRK::IDrvFR47::GetCashControlHost()
{
	CString result;
	InvokeHelper(0x203, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCashControlHost(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x203, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CShtrihFRK::IDrvFR47::GetCashControlPort()
{
	CString result;
	InvokeHelper(0x204, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCashControlPort(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x204, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetCashControlEnabled()
{
	BOOL result;
	InvokeHelper(0x205, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCashControlEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x205, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetCashControlUseTCP()
{
	BOOL result;
	InvokeHelper(0x206, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCashControlUseTCP(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x206, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetCashControlPassword()
{
	long result;
	InvokeHelper(0x207, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCashControlPassword(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x207, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::CashControlOpen()
{
	long result;
	InvokeHelper(0x208, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CashControlClose()
{
	long result;
	InvokeHelper(0x209, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetConnectionType()
{
	long result;
	InvokeHelper(0x20a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetConnectionType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDConnectionType()
{
	long result;
	InvokeHelper(0x20b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDConnectionType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetTCPPort()
{
	long result;
	InvokeHelper(0x20c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTCPPort(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDTCPPort()
{
	long result;
	InvokeHelper(0x20d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDTCPPort(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x20d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetIPAddress()
{
	CString result;
	InvokeHelper(0x20e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetIPAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CShtrihFRK::IDrvFR47::GetLDIPAddress()
{
	CString result;
	InvokeHelper(0x20f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDIPAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetUseIPAddress()
{
	BOOL result;
	InvokeHelper(0x210, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetUseIPAddress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x210, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetLDUseIPAddress()
{
	BOOL result;
	InvokeHelper(0x211, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDUseIPAddress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x211, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::SaveParams()
{
	long result;
	InvokeHelper(0x212, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetCPLogFile()
{
	CString result;
	InvokeHelper(0x1ff, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCPLogFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CShtrihFRK::IDrvFR47::GetComLogFile()
{
	CString result;
	InvokeHelper(0x200, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetComLogFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x200, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CShtrihFRK::IDrvFR47::GetLineData2()
{
	CString result;
	InvokeHelper(0x201, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLineData2(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x201, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetSysAdminPassword()
{
	long result;
	InvokeHelper(0x202, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSysAdminPassword(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x202, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetRecoverError165()
{
	BOOL result;
	InvokeHelper(0x213, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRecoverError165(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x213, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetMaxRecoverCount()
{
	long result;
	InvokeHelper(0x214, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetMaxRecoverCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x214, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetEKLZCode1Status()
{
	long result;
	InvokeHelper(0x215, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetEKLZCode2Status()
{
	long result;
	InvokeHelper(0x216, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReadWriteFM()
{
	long result;
	InvokeHelper(0x217, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PrintHeader()
{
	long result;
	InvokeHelper(0x218, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CloseCheckWithResult()
{
	long result;
	InvokeHelper(0x219, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetOperationCode()
{
	long result;
	InvokeHelper(0x21a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetAccType()
{
	long result;
	InvokeHelper(0x21c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetAccType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetAddress()
{
	long result;
	InvokeHelper(0x21d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetAddress(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetWrittenByte()
{
	long result;
	InvokeHelper(0x21e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetWrittenByte(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetReadByte()
{
	long result;
	InvokeHelper(0x21f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetTransferByte()
{
	CString result;
	InvokeHelper(0x220, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTransferByte(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x220, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetOperationType()
{
	long result;
	InvokeHelper(0x222, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetOperationType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x222, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::AboutBox()
{
	long result;
	InvokeHelper(0x21b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetPresenterIn()
{
	BOOL result;
	InvokeHelper(0x223, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetPresenterOut()
{
	BOOL result;
	InvokeHelper(0x224, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PresenterKeep()
{
	long result;
	InvokeHelper(0x225, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::PresenterPush()
{
	long result;
	InvokeHelper(0x226, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::OpenScreen()
{
	long result;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CloseScreen()
{
	long result;
	InvokeHelper(0x228, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetComLogOnlyErrors()
{
	BOOL result;
	InvokeHelper(0x221, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetComLogOnlyErrors(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x221, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::SetSCPassword()
{
	long result;
	InvokeHelper(0x229, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetSCPassword()
{
	long result;
	InvokeHelper(0x22a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSCPassword(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x22a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetNewSCPassword()
{
	long result;
	InvokeHelper(0x22b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetNewSCPassword(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x22b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetLastKPKDateStr()
{
	CString result;
	InvokeHelper(0x22c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetLastKPKTimeStr()
{
	CString result;
	InvokeHelper(0x22d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::MethodSupported()
{
	BOOL result;
	InvokeHelper(0x22e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetMethodName()
{
	CString result;
	InvokeHelper(0x22f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetMethodName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x22f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CShtrihFRK::IDrvFR47::GetPropertyName()
{
	CString result;
	InvokeHelper(0x230, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPropertyName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x230, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CShtrihFRK::IDrvFR47::PropertySupported()
{
	BOOL result;
	InvokeHelper(0x231, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetLockTimeout()
{
	long result;
	InvokeHelper(0x233, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLockTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x233, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::LockPortTimeout()
{
	long result;
	InvokeHelper(0x232, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetSlipStringInterval()
{
	long result;
	InvokeHelper(0x234, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSlipStringInterval(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x234, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetIBMStatus()
{
	long result;
	InvokeHelper(0x235, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetShortIBMStatus()
{
	long result;
	InvokeHelper(0x236, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte1()
{
	long result;
	InvokeHelper(0x237, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte2()
{
	long result;
	InvokeHelper(0x238, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte3()
{
	long result;
	InvokeHelper(0x239, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte4()
{
	long result;
	InvokeHelper(0x23a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte5()
{
	long result;
	InvokeHelper(0x23b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte6()
{
	long result;
	InvokeHelper(0x23c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte7()
{
	long result;
	InvokeHelper(0x23d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMStatusByte8()
{
	long result;
	InvokeHelper(0x23e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMFlags()
{
	long result;
	InvokeHelper(0x23f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMDocumentNumber()
{
	long result;
	InvokeHelper(0x240, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMLastSaleReceiptNumber()
{
	long result;
	InvokeHelper(0x241, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMLastBuyReceiptNumber()
{
	long result;
	InvokeHelper(0x242, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMLastReturnSaleReceiptNumber()
{
	long result;
	InvokeHelper(0x243, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMLastReturnBuyReceiptNumber()
{
	long result;
	InvokeHelper(0x244, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMSessionDay()
{
	long result;
	InvokeHelper(0x245, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMSessionMonth()
{
	long result;
	InvokeHelper(0x247, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMSessionYear()
{
	long result;
	InvokeHelper(0x248, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMSessionHour()
{
	long result;
	InvokeHelper(0x249, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMSessionMin()
{
	long result;
	InvokeHelper(0x24a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIBMSessionSec()
{
	long result;
	InvokeHelper(0x24b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

DATE CShtrihFRK::IDrvFR47::GetIBMSessionDateTime()
{
	DATE result;
	InvokeHelper(0x24c, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetEscapeIP()
{
	CString result;
	InvokeHelper(0x246, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEscapeIP(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x246, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetEscapePort()
{
	long result;
	InvokeHelper(0x24d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEscapePort(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x24d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CShtrihFRK::IDrvFR47::GetLDEscapeIP()
{
	CString result;
	InvokeHelper(0x24e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDEscapeIP(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x24e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDEscapePort()
{
	long result;
	InvokeHelper(0x24f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDEscapePort(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x24f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetEscapeTimeout()
{
	long result;
	InvokeHelper(0x250, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetEscapeTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x250, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetLDEscapeTimeout()
{
	long result;
	InvokeHelper(0x251, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLDEscapeTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x251, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCommandTimeout()
{
	long result;
	InvokeHelper(0x252, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCommandTimeout(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x252, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetUseCommandTimeout()
{
	BOOL result;
	InvokeHelper(0x253, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetUseCommandTimeout(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x253, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetCommandCount()
{
	long result;
	InvokeHelper(0x254, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCommandIndex()
{
	long result;
	InvokeHelper(0x255, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCommandIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x255, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCommandParams()
{
	long result;
	InvokeHelper(0x256, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetCommandParams()
{
	long result;
	InvokeHelper(0x257, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SaveCommandParams()
{
	long result;
	InvokeHelper(0x258, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CString CShtrihFRK::IDrvFR47::GetCommandName()
{
	CString result;
	InvokeHelper(0x259, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCommandDefTimeout()
{
	long result;
	InvokeHelper(0x25a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetCommandCode()
{
	long result;
	InvokeHelper(0x25b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetAllCommandsParams()
{
	long result;
	InvokeHelper(0x25c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetTimeoutsUsing()
{
	long result;
	InvokeHelper(0x25d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetTimeoutsUsing(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x25d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::SetDefCommandsParams()
{
	long result;
	InvokeHelper(0x25e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetInterval()
{
	long result;
	InvokeHelper(0x25f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::OpenSession()
{
	long result;
	InvokeHelper(0x260, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ReprintSlipDocument()
{
	long result;
	InvokeHelper(0x261, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::SetInterval()
{
	long result;
	InvokeHelper(0x262, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ShowPayParams()
{
	long result;
	InvokeHelper(0x263, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::ShowTablesDlg()
{
	long result;
	InvokeHelper(0x264, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::WaitForPrinting()
{
	long result;
	InvokeHelper(0x265, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetIntervalNumber()
{
	long result;
	InvokeHelper(0x266, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetIntervalNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x266, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetIntervalValue()
{
	long result;
	InvokeHelper(0x267, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetIntervalValue(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x267, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetMobilePayEnabled()
{
	BOOL result;
	InvokeHelper(0x268, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetMobilePayEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x268, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetParamsPageIndex()
{
	long result;
	InvokeHelper(0x269, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetParamsPageIndex(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x269, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetParentWnd()
{
	long result;
	InvokeHelper(0x26a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetParentWnd(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x26a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetPayDepartment()
{
	long result;
	InvokeHelper(0x26b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetPayDepartment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x26b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetRealPayDepartment()
{
	long result;
	InvokeHelper(0x26c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetRealPayDepartment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x26c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetSaleError()
{
	BOOL result;
	InvokeHelper(0x26d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetSaleError(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x26d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::OutputReceipt()
{
	long result;
	InvokeHelper(0x26e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::GetReceiptOutputType()
{
	long result;
	InvokeHelper(0x26f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetReceiptOutputType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x26f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::Sale2()
{
	long result;
	InvokeHelper(0x270, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShtrihFRK::IDrvFR47::CardPayProperties()
{
	long result;
	InvokeHelper(0x272, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetCardPayEnabled()
{
	BOOL result;
	InvokeHelper(0x271, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCardPayEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x271, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetCardPayType()
{
	long result;
	InvokeHelper(0x274, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCardPayType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x274, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetCcUseTextAsWareName()
{
	BOOL result;
	InvokeHelper(0x273, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCcUseTextAsWareName(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x273, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CShtrihFRK::IDrvFR47::GetCcWareNameLineNumber()
{
	long result;
	InvokeHelper(0x275, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCcWareNameLineNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x275, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCcHeaderLineCount()
{
	long result;
	InvokeHelper(0x276, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCcHeaderLineCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x276, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::GetCcProtocol()
{
	long result;
	InvokeHelper(0x277, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetCcProtocol(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x277, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CShtrihFRK::IDrvFR47::PrintCliche()
{
	long result;
	InvokeHelper(0x278, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CShtrihFRK::IDrvFR47::GetLogCommands()
{
	BOOL result;
	InvokeHelper(0x279, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLogCommands(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x279, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CShtrihFRK::IDrvFR47::GetLogMethods()
{
	BOOL result;
	InvokeHelper(0x27a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CShtrihFRK::IDrvFR47::SetLogMethods(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x27a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}
CShtrihFRK::CShtrihFRK()
{
	::CoInitialize (NULL);
	CLSID clsid;
	CLSIDFromProgID(L"Addin.DrvFR3",&clsid);
	drv.CreateDispatch(clsid,NULL);

}

void CShtrihFRK::ShowProperties()
{
	drv.ShowProperties ();
}

CString CShtrihFRK::GetResultCodeDescription ()
{
	return drv.GetResultCodeDescription ();
}
long CShtrihFRK::ErrorProcessing()
{
	long res=0;
	long lResCode=drv.GetResultCode ();
	if (lResCode!=S_OK){
		m_strResultCodeDescription=GetResultCodeDescription ();
		if(lResCode==DRV_RESCODE_WAIT_CONTINUE_PRINTING){
			drv.ContinuePrint ();
		}
		res=1;
	}
	return res;
}

long CShtrihFRK::ErrorPrintProcessing()
{
	long result=0;
	long lResCode=drv.GetResultCode ();
	if (lResCode!=S_OK){
		m_strResultCodeDescription=GetResultCodeDescription ();
		if(lResCode==DRV_RESCODE_WAIT_CONTINUE_PRINTING){
			drv.ContinuePrint ();
			result= IDRETRY;
		}
		else{
			CString strMsg=_T("");
			strMsg.Format (_T("Ошибка ККМ: %s ."),GetResultCodeDescription ());
			result=AfxMessageBox(strMsg,MB_ICONSTOP|MB_RETRYCANCEL|MB_SETFOREGROUND);
		}
	}
		return result;
}

long CShtrihFRK::PrintString(LPCTSTR strPrint)
{
	long res=0;
	while(1)
	{
		drv.SetUseReceiptRibbon (true);
		drv.SetUseJournalRibbon (true);
		drv.SetStringForPrinting (strPrint);
		drv.PrintString ();
		res=ErrorPrintProcessing ();
		if(res==IDCANCEL){
			drv.CancelCheck ();
			res=0;
			break;
		}
		else if(res==0){
			res=1;
			break;
		}
		::Sleep(500);
	}
	return res;
	
}

long CShtrihFRK::PrintStringInMiddle(LPCTSTR strName, int lenght)
{
return PrintString(strName);
}

long CShtrihFRK::BreakStringAndPrint(LPCTSTR strName, int lenght)
{
	long res=0;
	CString strPrint=strName;
	strPrint.TrimRight ();
	int nLenght=strPrint.GetLength ();
	if(nLenght >MAX_STR_LENGHT){
		
		CString strPrint1=strPrint.Left (MAX_STR_LENGHT);
		res=PrintString (strPrint1);
		CString strPrint2=strPrint.Mid (strPrint1.GetLength (),MAX_STR_LENGHT);
		res=PrintString(strPrint2);

	}
	else
	res=PrintString (strPrint);
	strPrint.Empty ();
	return res;
}

long CShtrihFRK::ConnectFR(int nPassw)
{
	long res=0;
	drv.SetPassword (nPassw);
	drv.Connect ();
	res=ErrorProcessing();
	res=1;
	drv.Disconnect ();
	return res;
	
}

long CShtrihFRK::DisconnectFR()
{
	long res=0;
	drv.SetPassword (30);
	drv.Disconnect ();
	res=ErrorProcessing();
	res=1;
	return res;
}

long CShtrihFRK::ReturnSalePosition(const long nDepartment, const CY& cySumm, const double dblQty)
{
	long res=0;
	while(1)
	{
		drv.SetStringForPrinting (_T(""));
		drv.SetPrice (cySumm);
		drv.SetQuantity (dblQty);
		drv.SetDepartment (nDepartment);
		drv.ReturnSale ();
		res=ErrorPrintProcessing();
		if(res==IDCANCEL){
			drv.CancelCheck ();
			res=0;
			break;
		}
		else{
			res=1;
			break;
		}
		::Sleep(500);
	}
	
	return res;
}

long CShtrihFRK::CloseCheck(const CY &cySummCheck, const CY &cyCash)
{
	long res=0;

	COleCurrency cySumm1=cySummCheck;
	COleCurrency cySummCash=cyCash;

	while(1)
	{
		if(cySummCash>=cySumm1)
			drv.SetSumm1 (cySummCash);
		else
			drv.SetSumm1 (cySumm1);
		drv.CloseCheck ();
		res=ErrorPrintProcessing();
		if(res==IDCANCEL){
			drv.CancelCheck ();
			res=0;
			break;
		}
		else{
			res=1;
			break;
		}
		::Sleep(500);
	}
	
	return res;

}

long CShtrihFRK::SalePosition(const long nDepartment, const CY &cySumm, const double dblQty)
{
	long res=0;
	while(1)
	{
		drv.SetStringForPrinting (_T(""));
		drv.SetPrice (cySumm);
		drv.SetQuantity (dblQty);
		drv.SetDepartment (nDepartment);
		drv.Sale ();
		res=ErrorPrintProcessing();
		if(res==IDCANCEL){
			drv.CancelCheck ();
			res=0;
			break;
		}
		else{
			res=1;
			break;
		}
		::Sleep(500);
	}
	
	return res;
}

long CShtrihFRK::PrintCheck(CTableValue *tblGoods, CY &cySummCheck, CY &cySummCash, BOOL blIsReturn, long nDepartment, long *pNumCheck)
{
	CString strPrint;
	long lRegisterGoods=1;
	long res=0;
	while(1)
	{
		drv.SetPassword (1);
		drv.Connect ();
		res=ErrorPrintProcessing();
		if(res==IDCANCEL){
			drv.Disconnect ();
			res=0;
			return res;
		}
		else if(res==0){
			break;
		}
		::Sleep(500);
	}
	
	while(1)
	{
		
		drv.GetECRStatus ();
		res=ErrorPrintProcessing();
		if(res==IDCANCEL){
			drv.Disconnect ();
			res=0;
			return res;
		}
		else if(res==0){
			break;
		}
		::Sleep(500);
	}
	if(drv.GetECRAdvancedMode ()==3)
		drv.ContinuePrint ();
	while(1)
	{
		
		drv.GetECRStatus ();
		res=ErrorPrintProcessing();
		if(res==IDCANCEL){
			drv.Disconnect ();
			res=0;
			return res;
		}
		else if(res==0){
			break;
		}
		::Sleep(500);
	}
	if(blIsReturn)
		strPrint=_T("           ЧЕК ВОЗВРАТА");
	else
		strPrint=_T("           ЧЕК ПРОДАЖИ");
	if(PrintStringInMiddle(strPrint,MAX_STR_LENGHT)==0){
		res=0;
		return res;
	}
	ASSERT_VALID(tblGoods);
	POSITION pos=tblGoods->LoadRows ();
	ASSERT(pos!=NULL);
	do
	{
		strPrint=_T("----------------------------------------------------------------------------------------------");
		strPrint=strPrint.Left (MAX_STR_LENGHT);
		if(PrintString(strPrint)==0){
			res=0;
			return res;
		}
		CString strNumPos;
		COleVariant val;
		tblGoods->GetFieldValue (_T("pos"),&val);
		strNumPos.Format (_T("%d"),val.lVal );
		
		val.Clear ();
		tblGoods->GetFieldValue (_T("name"),&val);
		char* szName=ConvertBSTRToString(val.bstrVal );
		CString strName(szName);
		strPrint.Empty ();
		strPrint.Format (_T("%s . %s"),strNumPos,strName);
		strPrint.MakeUpper ();
		delete szName;
		if(BreakStringAndPrint(strPrint,MAX_STR_LENGHT)==0){
			res=0;
			return res;
		}
		CString strQtyPrice;
		CString strQty;
		CString strPrice;
		val.Clear ();
		tblGoods->GetFieldValue (_T("qty"),&val);
		strQty.Format (_T("%d  "),val.lVal );
		long lQty=val.lVal ;
		ASSERT(lQty>0);
		val.Clear ();
		tblGoods->GetFieldValue (_T("units"),&val);
		char* szUnits=ConvertBSTRToString(val.bstrVal );
		CString strUnits(szUnits);
		delete szUnits;

		val.Clear ();
		tblGoods->GetFieldValue (_T("price"),&val);
		COleCurrency cyPrice=val.cyVal ;
		strPrice=cyPrice.Format (0,MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), SORT_DEFAULT));
		COleCurrency cySummLine=cyPrice*lQty;
		CString strSummLine=cySummLine.Format (0,MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), SORT_DEFAULT));
		strPrint.Empty ();
		strPrint.Format (_T("%s%s X %s = %s"),strQty,strUnits,strPrice,strSummLine);
		if(BreakStringAndPrint(strPrint,MAX_STR_LENGHT)==0){
			res=0;
			return res;
		}
	}
	while(tblGoods->GetRow ());
	COleCurrency cySummTotal=cySummCheck;
	strPrint=_T("===========================================================================");
	strPrint=strPrint.Left (MAX_STR_LENGHT);
	if(PrintString(strPrint)==0){
		res=0;
		return res;
	}
	if(blIsReturn)	{
		if(ReturnSalePosition(nDepartment,cySummTotal,1)==0){
			res=0;
			return res;
		}
	}
	else{
		if(SalePosition(nDepartment,cySummCheck,1)==0){
			res=0;
			return res;
		}
	}
		COleCurrency cyCashTotal=cySummCash;
		COleCurrency cyZero;
		cyZero.SetCurrency(0,0);
		if((cyCashTotal>cyZero)&&(cyCashTotal>cySummTotal)){
			if(CloseCheck(cySummTotal,cyCashTotal)==0){
				res=0;
				return res;
			}
		}
		else{
			if(CloseCheck(cySummTotal,cyZero)==0){
				res=0;
				return res;
			}
		}
		if(ErrorProcessing()==0){
			drv.GetECRStatus();
			*pNumCheck=drv.GetOpenDocumentNumber()+1;
		}
		else{
			res=0;
			return res;
		}
		drv.Disconnect();
		res=1;
		return res;
	
}

long CShtrihFRK::CloseDay(int nPassw)
{
	long res=0;
	while(1)
	{
		drv.SetPassword (drv.GetPassword());
		drv.Connect ();
		res=ErrorPrintProcessing();
		if(res==IDCANCEL){
			drv.Disconnect ();
			res=0;
			return res;
		}
		else if(res==0){
			break;
		}
		::Sleep(500);
	}
	drv.GetECRStatus ();
	if(ErrorProcessing()==1){
		drv.Disconnect ();
		res=0;
		return res;
	}
	if(drv.GetECRAdvancedMode ()==3){
		drv.ContinuePrint ();
		drv.SetPassword (drv.GetPassword ());
		drv.GetECRStatus ();
		if(ErrorProcessing()==1){
			drv.Disconnect ();
			res=0;
			return res;
		}
	}
	if(drv.GetECRMode ()==4){
		AfxMessageBox(_T("ОБНУЛЕННАЯ КАССА!!!"),MB_OK|MB_SETFOREGROUND);
		drv.Disconnect ();
		res=0;
		return res;
	}
	int rescode=AfxMessageBox(_T("Вы действительно хотите снять суточный отчет с гашением?"),MB_YESNOCANCEL|MB_SETFOREGROUND);
	if(rescode!=IDYES){
		drv.Disconnect ();
		res=0;
		return res;
	}
	drv.PrintReportWithCleaning ();
	ErrorProcessing();
	drv.Disconnect ();
	res=1;
	return res;
}

long CShtrihFRK::GetContentOfCash(double *dblCash)
{ long res=0;
	drv.SetPassword(drv.GetPassword());
	drv.SetRegisterNumber (241);
	drv.GetCashReg ();
	COleCurrency curCash=drv.GetContentsOfCashRegister ();
	*dblCash=0.0;
	::VarR8FromCy (curCash.m_cur ,dblCash);
	return res;
}
