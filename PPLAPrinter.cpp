// PPLAPrinter.cpp: implementation of the CPPLAPrinter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "userthreads.h"
#include "PPLAPrinter.h"
#include "CheckDoc.h"
#include "Winspool.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPPLAPrinter::CPPLAPrinter(CView* pView)
{
	
	
	A_Bar2d_Maxi			= NULL;
	A_Bar2d_Maxi_Ori		= NULL;
	A_Bar2d_PDF417			= NULL;
	A_Bar2d_PDF417_Ori		= NULL;
	A_Bar2d_DataMatrix		= NULL;
	A_Clear_Memory			= NULL;
	A_ClosePrn				= NULL;
	A_CreatePrn				= NULL;
	A_Del_Graphic			= NULL;
	A_Draw_Box				= NULL; 
	A_Draw_Line				= NULL;
	A_Feed_Label			= NULL;
	A_Get_DLL_Version		= NULL;
	A_Get_DLL_VersionA		= NULL;
	A_Get_Graphic			= NULL;
	A_Get_Graphic_ColorBMP	= NULL;
	A_Initial_Setting		= NULL;
	A_Load_Graphic			= NULL;
	A_Open_ChineseFont		= NULL;
	A_Print_Form			= NULL;
	A_Print_Out				= NULL;
	A_Prn_Barcode			= NULL;
	A_Prn_Text				= NULL;
	A_Prn_Text_Chinese		= NULL;
	A_Prn_Text_TrueType		= NULL;
	A_Prn_Text_TrueType_W	= NULL;
	A_Set_Backfeed			= NULL;
	A_Set_BMPSave			= NULL;
	A_Set_Cutting			= NULL;
	A_Set_Darkness			= NULL;
	A_Set_DebugDialog		= NULL;
	A_Set_Feed				= NULL;
	A_Set_Form				= NULL;
	A_Set_Margin			= NULL;
	A_Set_Prncomport		= NULL;
	A_Set_Prncomport_PC		= NULL;
	A_Set_Sensor_Mode		= NULL;
	A_Set_Speed				= NULL;
	A_Set_Syssetting		= NULL;
	A_Set_Unit				= NULL;
	A_Set_Logic				= NULL;
	A_Set_ProcessDlg		= NULL;
	A_Set_LabelVer			= NULL;
	A_GetUSBBufferLen		= NULL;
	A_EnumUSB				= NULL;
	A_CreateUSBPort			= NULL;
	A_CreatePort			= NULL;
	
	VERIFY(hPPLA = ::LoadLibrary(_T("..\\DLL\\Winppla.dll")));
//	AfxMessageBox("After LoadLibrary");
	VERIFY(A_Bar2d_Maxi = (pfnA_Bar2d_Maxi) ::GetProcAddress(hPPLA,"A_Bar2d_Maxi"));
	VERIFY(A_Bar2d_Maxi_Ori = (pfnA_Bar2d_Maxi_Ori) ::GetProcAddress(hPPLA,"A_Bar2d_Maxi_Ori"));
	VERIFY(A_Bar2d_PDF417 = (pfnA_Bar2d_PDF417) ::GetProcAddress(hPPLA,"A_Bar2d_PDF417"));
	VERIFY(A_Bar2d_PDF417_Ori = (pfnA_Bar2d_PDF417_Ori) ::GetProcAddress(hPPLA,"A_Bar2d_PDF417_Ori"));
	VERIFY(A_Bar2d_DataMatrix = (pfnA_Bar2d_DataMatrix) ::GetProcAddress(hPPLA,"A_Bar2d_DataMatrix"));
	VERIFY(A_Clear_Memory = (pfnA_Clear_Memory) ::GetProcAddress(hPPLA,"A_Clear_Memory"));
	VERIFY(A_ClosePrn = (pfnA_ClosePrn) ::GetProcAddress(hPPLA,"A_ClosePrn"));
	VERIFY(A_CreatePrn = (pfnA_CreatePrn) ::GetProcAddress(hPPLA,"A_CreatePrn"));
	VERIFY(A_Del_Graphic = (pfnA_Del_Graphic) ::GetProcAddress(hPPLA,"A_Del_Graphic"));
	VERIFY(A_Draw_Box = (pfnA_Draw_Box) ::GetProcAddress(hPPLA,"A_Draw_Box"));
	VERIFY(A_Draw_Line = (pfnA_Draw_Line) ::GetProcAddress(hPPLA,"A_Draw_Line"));
	VERIFY(A_Feed_Label = (pfnA_Feed_Label) ::GetProcAddress(hPPLA,"A_Feed_Label"));
	VERIFY(A_Get_DLL_Version = (pfnA_Get_DLL_Version) ::GetProcAddress(hPPLA,"A_Get_DLL_Version"));
	VERIFY(A_Get_DLL_VersionA = (pfnA_Get_DLL_VersionA) ::GetProcAddress(hPPLA,"A_Get_DLL_VersionA"));
	VERIFY(A_Get_Graphic = (pfnA_Get_Graphic) ::GetProcAddress(hPPLA,"A_Get_Graphic"));
	VERIFY(A_Get_Graphic_ColorBMP = (pfnA_Get_Graphic_ColorBMP) ::GetProcAddress(hPPLA,"A_Get_Graphic_ColorBMP"));
	VERIFY(A_Initial_Setting = (pfnA_Initial_Setting) ::GetProcAddress(hPPLA,"A_Initial_Setting"));
	VERIFY(A_Load_Graphic = (pfnA_Load_Graphic) ::GetProcAddress(hPPLA,"A_Load_Graphic"));
	VERIFY(A_Open_ChineseFont = (pfnA_Open_ChineseFont) ::GetProcAddress(hPPLA,"A_Open_ChineseFont"));
	VERIFY(A_Print_Form = (pfnA_Print_Form) ::GetProcAddress(hPPLA,"A_Print_Form"));
	VERIFY(A_Print_Out = (pfnA_Print_Out) ::GetProcAddress(hPPLA,"A_Print_Out"));
	VERIFY(A_Prn_Barcode = (pfnA_Prn_Barcode) ::GetProcAddress(hPPLA,"A_Prn_Barcode"));
	VERIFY(A_Prn_Text = (pfnA_Prn_Text) ::GetProcAddress(hPPLA,"A_Prn_Text"));
	VERIFY(A_Prn_Text_Chinese = (pfnA_Prn_Text_Chinese) ::GetProcAddress(hPPLA,"A_Prn_Text_Chinese"));
	VERIFY(A_Prn_Text_TrueType = (pfnA_Prn_Text_TrueType) ::GetProcAddress(hPPLA,"A_Prn_Text_TrueType"));
	VERIFY(A_Prn_Text_TrueType_W = (pfnA_Prn_Text_TrueType_W) ::GetProcAddress(hPPLA,"A_Prn_Text_TrueType_W"));
	VERIFY(A_Set_Backfeed = (pfnA_Set_Backfeed) ::GetProcAddress(hPPLA,"A_Set_Backfeed"));
	VERIFY(A_Set_BMPSave = (pfnA_Set_BMPSave) ::GetProcAddress(hPPLA,"A_Set_BMPSave"));
	VERIFY(A_Set_Cutting = (pfnA_Set_Cutting) ::GetProcAddress(hPPLA,"A_Set_Cutting"));
	VERIFY(A_Set_Darkness = (pfnA_Set_Darkness) ::GetProcAddress(hPPLA,"A_Set_Darkness"));
	VERIFY(A_Set_Feed = (pfnA_Set_Feed) ::GetProcAddress(hPPLA,"A_Set_Feed"));
	VERIFY(A_Set_Form = (pfnA_Set_Form) ::GetProcAddress(hPPLA,"A_Set_Form"));
	VERIFY(A_Set_Margin = (pfnA_Set_Margin) ::GetProcAddress(hPPLA,"A_Set_Margin"));
	VERIFY(A_Set_Prncomport = (pfnA_Set_Prncomport) ::GetProcAddress(hPPLA,"A_Set_Prncomport"));
	VERIFY(A_Set_Prncomport_PC = (pfnA_Set_Prncomport_PC) ::GetProcAddress(hPPLA,"A_Set_Prncomport_PC"));
	VERIFY(A_Set_Sensor_Mode = (pfnA_Set_Sensor_Mode) ::GetProcAddress(hPPLA,"A_Set_Sensor_Mode"));
	VERIFY(A_Set_Speed = (pfnA_Set_Speed) ::GetProcAddress(hPPLA,"A_Set_Speed"));
	VERIFY(A_Set_Syssetting = (pfnA_Set_Syssetting) ::GetProcAddress(hPPLA,"A_Set_Syssetting"));
	VERIFY(A_Set_Unit = (pfnA_Set_Unit) ::GetProcAddress(hPPLA,"A_Set_Unit"));
	VERIFY(A_Set_Logic = (pfnA_Set_Logic) ::GetProcAddress(hPPLA,"A_Set_Logic"));
	VERIFY(A_Set_ProcessDlg = (pfnA_Set_ProcessDlg) ::GetProcAddress(hPPLA,"A_Set_ProcessDlg"));
	VERIFY(A_Set_LabelVer = (pfnA_Set_LabelVer) ::GetProcAddress(hPPLA,"A_Set_LabelVer"));
	VERIFY(A_GetUSBBufferLen = (pfnA_GetUSBBufferLen) ::GetProcAddress(hPPLA,"A_GetUSBBufferLen"));
	VERIFY(A_EnumUSB = (pfnA_EnumUSB) ::GetProcAddress(hPPLA,"A_EnumUSB"));
	VERIFY(A_CreateUSBPort = (pfnA_CreateUSBPort) ::GetProcAddress(hPPLA,"A_CreateUSBPort"));
	VERIFY(A_CreatePort = (pfnA_CreatePort) ::GetProcAddress(hPPLA, "A_CreatePort"));
	this->pView=(CUserThreadsView*)pView;
}

CPPLAPrinter::~CPPLAPrinter()
{
	::FreeLibrary(hPPLA);
	hPPLA					= NULL;
	A_Bar2d_Maxi			= NULL;
	A_Bar2d_Maxi_Ori		= NULL;
	A_Bar2d_PDF417			= NULL;
	A_Bar2d_PDF417_Ori		= NULL;
	A_Bar2d_DataMatrix		= NULL;
	A_Clear_Memory			= NULL;
	A_ClosePrn				= NULL;
	A_CreatePrn				= NULL;
	A_Del_Graphic			= NULL;
	A_Draw_Box				= NULL; 
	A_Draw_Line				= NULL;
	A_Feed_Label			= NULL;
	A_Get_DLL_Version		= NULL;
	A_Get_DLL_VersionA		= NULL;
	A_Get_Graphic			= NULL;
	A_Get_Graphic_ColorBMP	= NULL;
	A_Initial_Setting		= NULL;
	A_Load_Graphic			= NULL;
	A_Open_ChineseFont		= NULL;
	A_Print_Form			= NULL;
	A_Print_Out				= NULL;
	A_Prn_Barcode			= NULL;
	A_Prn_Text				= NULL;
	A_Prn_Text_Chinese		= NULL;
	A_Prn_Text_TrueType		= NULL;
	A_Prn_Text_TrueType_W	= NULL;
	A_Set_Backfeed			= NULL;
	A_Set_BMPSave			= NULL;
	A_Set_Cutting			= NULL;
	A_Set_Darkness			= NULL;
	A_Set_DebugDialog		= NULL;
	A_Set_Feed				= NULL;
	A_Set_Form				= NULL;
	A_Set_Margin			= NULL;
	A_Set_Prncomport		= NULL;
	A_Set_Prncomport_PC		= NULL;
	A_Set_Sensor_Mode		= NULL;
	A_Set_Speed				= NULL;
	A_Set_Syssetting		= NULL;
	A_Set_Unit				= NULL;
	A_Set_Logic				= NULL;
	A_Set_ProcessDlg		= NULL;
	A_Set_LabelVer			= NULL;
	A_GetUSBBufferLen		= NULL;
	A_EnumUSB				= NULL;
	A_CreateUSBPort			= NULL;
	A_CreatePort			= NULL;
}

BOOL CPPLAPrinter::NewCheck(int nLPTPort)
{
	//	AfxMessageBox("Before A_CreatePrn");
	int res=A_CreatePrn(nLPTPort,NULL);
	
	return (res==0);
}

BOOL CPPLAPrinter::PrintCheck()
{
	//AfxMessageBox("Before Print Check");
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	IVSFlexGridPtr pGrid=pView->m_wndGrid.GetControlUnknown();
	CCheckDoc* pDoc=pView->GetDocument ();
	A_Clear_Memory();

	A_Set_Darkness(8);

	A_Set_Unit('m'); 
	A_Set_Syssetting(2,9,1200,1,2);
	A_Set_Sensor_Mode('c',100);

	
	CSize nRetVal;
	GetPrinterDC ();
	//AfxMessageBox("After GetPrinterDC()");
	dc.SetMapMode (MM_LOMETRIC);
	nRetVal.cx = dc.GetDeviceCaps(HORZSIZE);
	nRetVal.cy = dc.GetDeviceCaps(VERTSIZE);
	const int nGap=2;
	int nWidth=nRetVal.cx *10;
	CString strLine;


	strLine.Empty ();
	strLine.Format (_T("ИТОГО:%.2f"),pDoc->GetCurSumma() );
	A_Prn_Text_TrueType(0,0,70,_T("Monotype Corsiva"),1,400,1,0,0,_T("AB"),strLine,1);
	A_Draw_Line('n',0,72,nWidth,4);
	int j=0;
for(long i=pGrid->GetRows()-1;i>0;i--)
	{

	
		CString strIndex;
		strLine.Empty ();
		strIndex.Empty ();
		strIndex.Format (_T("A%d"),j);
		CString strName=(LPCTSTR)pGrid->GetTextMatrix (i,2);
		strName.TrimRight ();
	

		strLine.Format (_T("%.28s"),strName);
		//strLine.MakeUpper ();
		CFont font;
		font.CreatePointFont (20,_T("Microsoft Sans Serif"));
		CFont* pFont=dc.SelectObject (&font);
		CSize szText=dc.GetTextExtent (strLine,23);
		dc.SelectObject (pFont);
		A_Prn_Text_TrueType(0,72+j*30,20,_T("Microsoft Sans Serif"),1,200,0,0,0,strIndex,strLine,1);

		strLine.Empty ();
		strIndex.Empty ();
		strIndex.Format (_T("B%d"),j);
		strLine.Format (_T("%.3s"),(char*)pGrid->GetTextMatrix (i,5));
		A_Prn_Text_TrueType(350,72+j*30,20,_T("Arial"),1,200,0,0,0,strIndex,strLine,1);

		strLine.Empty ();
		strIndex.Empty ();
		strIndex.Format (_T("C%d"),j);
		strLine.Format (_T("%.6s"),(char*)pGrid->GetTextMatrix (i,3));
		A_Prn_Text_TrueType(400,72+j*30,20,_T("Arial"),1,200,0,0,0,strIndex,strLine,1);

		strIndex.Format (_T("D%d"),j);
		strLine.Format (_T("%.6s"),(char*)pGrid->GetTextMatrix (i,6));
		A_Prn_Text_TrueType(450,72+j*30,20,_T("Arial"),1,200,0,0,0,strIndex,strLine,1);

	
		j++;
	

		
		/*strLine.Empty ();
		strLine.Format ("%.10s %.3s x %.20s =%s",(char*)pGrid->GetTextMatrix (i,5),(char*)pGrid->GetTextMatrix (i,4),
		(char*)pGrid->GetTextMatrix (i,3),(char*)pGrid->GetTextMatrix (i,6));
		AddNewLine(45,9,0,12,strLine);*/
	}
	A_Draw_Line('n',0,72+j*30+2,nWidth,2);
	A_Prn_Text_TrueType(0,72+j*30+4,20,_T("Arial"),1,400,0,0,0,_T("AE"),_T("Наименование                                 Кол   Цена Сумма"),1);
	A_Draw_Line('n',0,72+j*30+4+30,nWidth,4);


	strLine.Empty ();
	COleDateTime tmNow=COleDateTime::GetCurrentTime ();
	strLine.Format     (_T("Дата:%.2d/%.2d/%.2d         Время:%.2d:%.2d:%.2d"),tmNow.GetDay (),tmNow.GetMonth (),tmNow.GetYear (),tmNow.GetHour (),tmNow.GetMinute (),tmNow.GetSecond ());
	A_Prn_Text_TrueType(0,72+j*30+4+60,30,_T("Arial"),1,300,0,0,0,_T("AD"),strLine,1);
	strLine.Format (_T("Товарный чек №     %s"),pDoc->m_str1CNum   );
	A_Prn_Text_TrueType(25,72+j*30+4+90,30,_T("Arial"),1,300,0,0,0,_T("AC"),strLine,1);
	strLine.Format (_T("%s   ИНН%s"),pMainDoc->m_strFirma,pMainDoc->m_strINN );
	A_Prn_Text_TrueType(0,72+j*30+4+120,30,_T("Monotype Corsiva"),1,300,1,0,0,_T("AA"), strLine,1);
	A_Prn_Text_TrueType(100,72+j*30+4+170,30,_T("Monotype Corsiva"),1,300,1,0,0,_T("AI"), _T("СПАСИБО ЗА ПОКУПКУ!!!"),1);
/*	strLine.Format ("%s   ИНН%s",pMainDoc->m_strFirma,pMainDoc->m_strINN );
	A_Prn_Text_TrueType(0,30,30,"Monotype Corsiva",3,300,1,0,0,"AA", strLine,1);
	strLine.Format ("Товарный чек №     %s",pDoc->m_str1CNum   );
	A_Prn_Text_TrueType(25,60,30,"Arial",3,300,0,0,0,"AC",strLine,1);
	strLine.Empty ();
	COleDateTime tmNow=COleDateTime::GetCurrentTime ();
	strLine.Format     ("Дата:%d/%d/%d         Время:%d:%d:%d",tmNow.GetDay (),tmNow.GetMonth (),tmNow.GetYear (),tmNow.GetHour (),tmNow.GetMinute (),tmNow.GetSecond ());
	A_Prn_Text_TrueType(0,90,30,"Arial",3,300,0,0,0,"AD",strLine,1);
	
	
	
	
	TRACE("cx=%d  cy=%d\n",nRetVal.cx ,nRetVal.cy );
	
	A_Draw_Line('n',0,130,nWidth,2);
	A_Prn_Text_TrueType(0,130,20,"Arial",3,200,0,0,0,"AE","Наименование              Кол   Цена Сумма",1);
	A_Draw_Line('n',0,160,nWidth,2);
	strLine.Empty ();
	
	A_Draw_Line('n',70,130,3,300);
	A_Draw_Line('n',140,130,3,300);
	A_Draw_Line('n',190,130,3,300);
*/
	A_Prn_Text_TrueType(100,102+j*30+4+170+30,30,_T("Arial"),1,300,0,0,0,_T("AZ"),_T("Сохраняйте чек 14 дней"),1);
	A_Prn_Text_TrueType(100,132+j*30+4+170+30*2,30,_T("Arial"),1,300,0,0,0,_T("AY"),_T("Ярмарка у м.Домодедовская"),1);
	A_Prn_Text_TrueType(100,162+j*30+4+170+30*3,30,_T("Arial"),1,300,0,0,0,_T("AX"),_T("Ореховый б-р д.14 стр.3"),1);
	A_Prn_Text_TrueType(200,192+j*30+4+170+30*4,30,_T("Arial"),1,300,0,0,0,_T("AW"),_T("г.МОСКВА"),1);
	A_Print_Out(1,1,1,1);

	dc.DeleteDC();
		
			
	A_ClosePrn();
return TRUE;
	
}

DWORD CPPLAPrinter::GetPrinterDC()
{
/*
PRINTER_INFO_5* ppinfo5;
DWORD dwNeeded,dwReturned;
BOOL bErr;
::EnumPrinters(PRINTER_ENUM_LOCAL,NULL,5,(LPBYTE)_T(""),0,&dwNeeded,&dwReturned);
ppinfo5=(PRINTER_INFO_5*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,dwNeeded);
if(ppinfo5)
bErr=EnumPrinters(PRINTER_ENUM_LOCAL,NULL,5,(LPBYTE)ppinfo5,dwNeeded,&dwNeeded,&dwReturned);
CString strPrinterName;
for(int i=0;i<(int)dwReturned;i++)
{
strPrinterName.Empty ();
strPrinterName=ppinfo5->pPrinterName ;
strPrinterName.Left(5);
if(strPrinterName.CompareNoCase ("label")==0)
break;
ppinfo5++;
}
hDC=CreateDC(NULL,ppinfo5->pPrinterName ,NULL,NULL);
return 0;
	*/
	
	
	PRINTDLG FAR * pPrintDlg = new PRINTDLG;
	BOOL bRet = FALSE;
	
	// Получаем текущие установки принтера.
	
	if(AfxGetApp()->GetPrinterDeviceDefaults(pPrintDlg))
	{
		
		// Получаем указатели на две структуры с установками.
		
		DEVNAMES FAR *lpDevNames =
			(DEVNAMES FAR *)::GlobalLock(pPrintDlg->hDevNames);
		
		DEVMODE FAR *lpDevMode =
			(DEVMODE FAR *)::GlobalLock(pPrintDlg->hDevMode);
		
		// Получаем информацию о драйвере.
		
		CString szDriver((LPTSTR)lpDevNames +
			lpDevNames->wDriverOffset);
		CString szDevice((LPTSTR)lpDevNames +
			lpDevNames->wDeviceOffset);
		CString szOutput((LPTSTR)lpDevNames +
			lpDevNames->wOutputOffset);
		
		// Создаём объект CDC согласно текущим настройкам.
		
		dc.CreateDC(szDriver, szDevice, szOutput, lpDevMode);
	}
	::GlobalUnlock(pPrintDlg->hDevNames);
	::GlobalUnlock(pPrintDlg->hDevMode);
	
	

delete pPrintDlg;

return 0;
}

BOOL CPPLAPrinter::Feeding()
{
A_CreatePrn(1,NULL);
		
	//	A_Feed_Label();
		A_Print_Out(1,1,1,1);
	A_ClosePrn();

	return TRUE;
}
