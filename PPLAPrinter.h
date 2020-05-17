// PPLAPrinter.h: interface for the CPPLAPrinter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PPLAPRINTER_H__30539F63_E9BC_4B66_8B09_CB78B68F6836__INCLUDED_)
#define AFX_PPLAPRINTER_H__30539F63_E9BC_4B66_8B09_CB78B68F6836__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UserThreadsView.h"
class CPPLAPrinter  
{
public:
	BOOL Feeding();
	BOOL PrintCheck();
	BOOL NewCheck(int nLPTPort);
	CPPLAPrinter(CView* pView);
	virtual ~CPPLAPrinter();
private:
	CDC dc;
	DWORD GetPrinterDC();
	CUserThreadsView* pView;
	HINSTANCE hPPLA;
typedef int (_stdcall *pfnA_Bar2d_Maxi)(int x,int y,long int primary,int secondary,int country,
								int service,char mode,int numeric,LPCTSTR data);
typedef int (_stdcall *pfnA_Bar2d_Maxi_Ori)(int x,int y,int ori,long int primary,int secondary,int country,
								int service,char mode,int numeric,LPCTSTR data);
typedef int (_stdcall *pfnA_Bar2d_PDF417)(int x,int y,int narrow,int width,char normal,int security,
					int aspect,int row,int column,char mode,int numeric,LPCTSTR data);
typedef int (_stdcall *pfnA_Bar2d_PDF417_Ori)(int x,int y,int ori,int narrow,int width,char normal,
					int security,int aspect,int row,int column,char mode,int numeric,LPCTSTR data);
typedef int (_stdcall *pfnA_Bar2d_DataMatrix)(int x, int y,int rotation,int hor_mul,int ver_mul,
						int ECC,int data_format,int num_rows,int num_col,char mode,int numeric,LPCTSTR data);
typedef void (_stdcall *pfnA_Clear_Memory)(void);
typedef void (_stdcall *pfnA_ClosePrn)(void);
typedef int (_stdcall *pfnA_CreatePrn)(int selection, LPCTSTR filename);
typedef int (_stdcall *pfnA_Del_Graphic)(int mem_mode,char graphic[10]);
typedef int (_stdcall *pfnA_Draw_Box)(char mode,int x,int y,int width,int height,int top,int side);
typedef int (_stdcall *pfnA_Draw_Line)(char mode,int x,int y,int width,int height);
typedef void (_stdcall *pfnA_Feed_Label)(void);
typedef LPTSTR (_stdcall *pfnA_Get_DLL_Version)(int nShowMessage);
typedef int (_stdcall *pfnA_Get_DLL_VersionA)(int nShowMessage);
typedef int (_stdcall *pfnA_Get_Graphic)(int x,int y,int mem_mode,char format,LPCTSTR filename);
typedef int (_stdcall *pfnA_Get_Graphic_ColorBMP)(int x,int y,int mem_mode,char format,LPCTSTR filename);
typedef int (_stdcall *pfnA_Initial_Setting)(int Type,LPCTSTR Source);
typedef int (_stdcall *pfnA_Load_Graphic)(int x,int y,char graphic_name[10]);
typedef int (_stdcall *pfnA_Open_ChineseFont)(char* path);
typedef int (_stdcall *pfnA_Print_Form)(int width,int height,int copies,int amount,LPTSTR form_name);
typedef int (_stdcall *pfnA_Print_Out)(int width,int height,int copies,int amount);
typedef int (_stdcall *pfnA_Prn_Barcode)(int x,int y,int ori,char type,int narrow,int width,
                        int height,char mode,int numeric,LPTSTR data);
typedef int (_stdcall *pfnA_Prn_Text)(int x,int y,int ori,int font,int type,int hor_factor,
                     int ver_factor,char mode,int numeric,LPCTSTR data);
typedef int (_stdcall *pfnA_Prn_Text_Chinese)(int x,int y,int fonttype,LPCTSTR id_name,LPCTSTR data,int mem_mode);
typedef int (_stdcall *pfnA_Prn_Text_TrueType)(int x,int y,int FSize,LPCTSTR FType,int Fspin,
						      int FWeight,int FItalic,int FUnline,int FStrikeOut,
					          LPCTSTR id_name,LPCTSTR data,int mem_mode);
typedef int (_stdcall *pfnA_Prn_Text_TrueType_W)(int x, int y, int FHeight, int FWidth, LPCTSTR FType,
						int Fspin, int FWeight, int FItalic, int FUnline,
						int FStrikeOut, LPCTSTR id_name, LPCTSTR data, int mem_mode);
typedef int (_stdcall *pfnA_Set_Backfeed)(int back);
typedef int (_stdcall *pfnA_Set_BMPSave)(int nSave, char* pstrBMPFName);
typedef int (_stdcall *pfnA_Set_Cutting)(int cutting);
typedef int (_stdcall *pfnA_Set_Darkness)(int heat);
typedef int (_stdcall *pfnA_Set_DebugDialog)(int nEnable);
typedef int (_stdcall *pfnA_Set_Feed)(char rate);
typedef int (_stdcall *pfnA_Set_Form)(LPCTSTR formfile,LPCTSTR form_name,int mem_mode);
typedef int (_stdcall *pfnA_Set_Margin)(int position,int margin);
typedef int (_stdcall *pfnA_Set_Prncomport)(int baud, int parity, int data, int stop);
typedef int (_stdcall *pfnA_Set_Prncomport_PC)(int nBaudRate, int nByteSize, int nParity,
					int nStopBits, int nDsr, int nCts, int nXonXoff);
typedef int (_stdcall *pfnA_Set_Sensor_Mode)(char type,int continuous);
typedef int (_stdcall *pfnA_Set_Speed)(char speed);
typedef int (_stdcall *pfnA_Set_Syssetting)(int transfer,int cut_peel,int length,int zero,int pause);
typedef int (_stdcall *pfnA_Set_Unit)(char unit);
typedef int (_stdcall *pfnA_Set_Logic)(int logic);
typedef int (_stdcall *pfnA_Set_ProcessDlg)(int nShow);
typedef int (_stdcall *pfnA_Set_LabelVer)(int centiInch);
typedef int (_stdcall *pfnA_GetUSBBufferLen)(void);
typedef int (_stdcall *pfnA_EnumUSB)(char *buf);
typedef int (_stdcall *pfnA_CreateUSBPort)(int nPort);
typedef int (_stdcall *pfnA_CreatePort)(int nPortType, int nPort, LPCTSTR filename);
	pfnA_Bar2d_Maxi				A_Bar2d_Maxi		;
	pfnA_Bar2d_Maxi_Ori			A_Bar2d_Maxi_Ori		;
	pfnA_Bar2d_PDF417			A_Bar2d_PDF417		;
	pfnA_Bar2d_PDF417_Ori		A_Bar2d_PDF417_Ori	;
	pfnA_Bar2d_DataMatrix		A_Bar2d_DataMatrix	;
	pfnA_Clear_Memory			A_Clear_Memory		;
	pfnA_ClosePrn				A_ClosePrn			;
	pfnA_CreatePrn				A_CreatePrn			;
	pfnA_Del_Graphic			A_Del_Graphic	;
	pfnA_Draw_Box				A_Draw_Box			; 
	pfnA_Draw_Line				A_Draw_Line			;
	pfnA_Feed_Label				A_Feed_Label		;
	pfnA_Get_DLL_Version		A_Get_DLL_Version	;
	pfnA_Get_DLL_VersionA		A_Get_DLL_VersionA		;
	pfnA_Get_Graphic			A_Get_Graphic			;
	pfnA_Get_Graphic_ColorBMP	A_Get_Graphic_ColorBMP	;
	pfnA_Initial_Setting		A_Initial_Setting		;
	pfnA_Load_Graphic			A_Load_Graphic		;
	pfnA_Open_ChineseFont		A_Open_ChineseFont	;
	pfnA_Print_Form				A_Print_Form			;
	pfnA_Print_Out				A_Print_Out				;
	pfnA_Prn_Barcode			A_Prn_Barcode			;
	pfnA_Prn_Text				A_Prn_Text			;
	pfnA_Prn_Text_Chinese		A_Prn_Text_Chinese	;
	pfnA_Prn_Text_TrueType		A_Prn_Text_TrueType		;
	pfnA_Prn_Text_TrueType_W	A_Prn_Text_TrueType_W;
	pfnA_Set_Backfeed			A_Set_Backfeed			;
	pfnA_Set_BMPSave			A_Set_BMPSave			;
	pfnA_Set_Cutting			A_Set_Cutting			;
	pfnA_Set_Darkness			A_Set_Darkness			;
	pfnA_Set_DebugDialog		A_Set_DebugDialog		;
	pfnA_Set_Feed				A_Set_Feed				;
	pfnA_Set_Form				A_Set_Form				;
	pfnA_Set_Margin				A_Set_Margin			;
	pfnA_Set_Prncomport			A_Set_Prncomport		;
	pfnA_Set_Prncomport_PC		A_Set_Prncomport_PC		;
	pfnA_Set_Sensor_Mode		A_Set_Sensor_Mode		;
	pfnA_Set_Speed				A_Set_Speed				;
	pfnA_Set_Syssetting			A_Set_Syssetting		;
	pfnA_Set_Unit				A_Set_Unit				;
	pfnA_Set_Logic				A_Set_Logic				;
	pfnA_Set_ProcessDlg			A_Set_ProcessDlg		;
	pfnA_Set_LabelVer			A_Set_LabelVer			;
	pfnA_GetUSBBufferLen		A_GetUSBBufferLen		;
	pfnA_EnumUSB				A_EnumUSB				;
	pfnA_CreateUSBPort			A_CreateUSBPort		;
	pfnA_CreatePort				A_CreatePort			;

};

#endif // !defined(AFX_PPLAPRINTER_H__30539F63_E9BC_4B66_8B09_CB78B68F6836__INCLUDED_)
