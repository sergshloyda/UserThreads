// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__22E46340_12E0_4461_9A0C_4CD085175093__INCLUDED_)
#define AFX_STDAFX_H__22E46340_12E0_4461_9A0C_4CD085175093__INCLUDED_
# define WINVER 0x0500
#define _WIN32_DCOM
#define _ATL_APARTMENT_THREADED
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning( disable : 4100 )
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <afxcview.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <AFXPRIV.H>
#include<ole2.h>
#pragma warning( push ) 
#endif // 
#pragma warning( disable : 4146 )
#import "c:\Program Files\Common Files\System\ADO\msado15.dll" 	no_namespace rename("EOF","EndOfFile")

//#import "libid:{00000205-0000-0010-8000-00aa006d2ea4}" auto_rename
#pragma warning( pop )
#import "C:\VisualCStudy\UserThreads\DLL\MSDATSRC.TLB" no_namespace
#import "C:\VisualCStudy\UserThreads\DLL\vsflex7.ocx" no_namespace

//#import "C:\VisualCStudy1\Dir1CServer\ReleaseUMinDependency\Dir1CServer.exe" no_namespace ,named_guids rename("GetUserName","GetUserNameX")

//#import "C:\VisualCStudy1\ProxiOneC\ReleaseUMinDependency\ProxiOneC.exe" no_namespace,named_guids

//#include <atlbase.h>

#include <AFXCTL.H> 
#include <afxcoll.h>

  //#include <adoid.h>
   //#include <adoint.h>
   //#include <comdef.h>
#import "mqoa.dll" named_guids
using namespace MSMQ;
typedef LONG (*LPFUNCCREATEOBJREFMONIKER)( LPUNKNOWN , LPMONIKER * );
inline void TESTHR(HRESULT x){if FAILED(x) _com_issue_error(x);};

inline void _raise_error(HRESULT hr,BSTR strDescription,BSTR strSource)
{
		CComPtr<ICreateErrorInfo> pCER;
			CreateErrorInfo(&pCER);
		
			pCER->SetDescription (strDescription);
			pCER->SetSource (strSource);
			CComQIPtr<IErrorInfo> pEI=pCER;
			SetErrorInfo(0,pEI);
		//	::SysFreeString (strDescription);
		//	::SysFreeString (strSource);
			_com_raise_error(hr,pEI);
}
#include "MessageBoxHelper.h"
#include <iosfwd>
#include <strstream>
#define odslog(msg) {std::wstringstream ss;ss<<msg;OutputDebugStringW(ss.str().c_str());}
#define OutputDebugString_ENABLED
//for AfxConnectionAdvise/Unadvise
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
/*class CUserThreadsModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};
extern CUserThreadsModule _Module;*/
//#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
/*typedef enum EditableSettings {
    flexEDNone,
    flexEDKbd,
    flexEDKbdMouse,
} #include <afxcontrolbars.h>
EditableSettings;

typedef enum RedrawSettings {
    flexRDNone,
    flexRDDirect,
    flexRDBuffered,
} RedrawSettings;

typedef enum AppearanceSettings {
    flexFlat,
    flex3D,
    flex3DLight,
} AppearanceSettings;

typedef enum BorderStyleSettings {
    flexBorderNone,
    flexBorderFlat,
} BorderStyleSettings;

typedef enum MousePointerSettings {
    flexDefault,
    flexArrow,
    flexCross,
    flexIBeam,
    flexIcon,
    flexSize,
    flexSizeNESW,
    flexSizeNS,
    flexSizeNWSE,
    flexSizeEW,
    flexUpArrow,
    flexHourglass,
    flexNoDrop,
    flexArrowHourGlass,
    flexArrowQuestion,
    flexSizeAll,
    flexPointerCopy = 50,
    flexPointerMove = 51,
    flexSizeHorz    = 52,
    flexSizeVert    = 53,
    flexHand        = 54,
    flexCustom      = 99,
} MousePointerSettings;

typedef enum RowStatusSettings {
	flexrsNew,
	flexrsUpdated,
	flexrsModified,
	flexrsDeleted,
} RowStatusSettings;

typedef enum CellPropertySettings {
	flexcpText,
	flexcpTextStyle,
	flexcpAlignment,
	flexcpPicture,
	flexcpPictureAlignment,
	flexcpChecked,
	flexcpBackColor,
	flexcpForeColor,
	flexcpFloodPercent,
	flexcpFloodColor,
	flexcpFont,
	flexcpFontName,
	flexcpFontSize,
	flexcpFontBold,
	flexcpFontItalic,
	flexcpFontUnderline,
	flexcpFontStrikethru,
	flexcpFontWidth,
	flexcpValue,
	flexcpTextDisplay,
	flexcpData,
	flexcpCustomFormat,
	flexcpLeft,
	flexcpTop,
	flexcpWidth,
	flexcpHeight,
	flexcpVariantValue,
	flexcpRefresh,
	flexcpSort,
} CellPropertySettings;

typedef enum ExplorerBarSettings {
	flexExNone            = 0,
	flexExSort            = 1,
	flexExMove            = 2,
	flexExSortAndMove     = 3,
	flexExSortShow        = 5,
	flexExSortShowAndMove = 7,
	flexExMoveRows        = 8,
} ExplorerBarSettings;

typedef enum AutoSearchSettings {
	flexSearchNone,
	flexSearchFromTop,
	flexSearchFromCursor,
} AutoSearchSettings;

typedef enum ComboSearchSettings {
	flexCmbSearchNone,
	flexCmbSearchLists,
	flexCmbSearchCombos,
	flexCmbSearchAll,
} ComboSearchSettings;

typedef enum MergeCompareSettings {
	flexMCExact,
	flexMCNoCase,
	flexMCTrimNoCase,
} MergeCompareSettings;

typedef enum EllipsisSettings {
	flexNoEllipsis,
	flexEllipsisEnd,
	flexEllipsisPath,
} EllipsisSettings;

typedef enum CellCheckedSettings {
	flexNoCheckbox,
	flexChecked,
	flexUnchecked,
	flexTSChecked,
	flexTSUnchecked,
	flexTSGrayed,
} CellCheckedSettings;

typedef enum TabBehaviorSettings {
    flexTabControls,
    flexTabCells,
} TabBehaviorSettings;

typedef enum SaveLoadSettings {
    flexFileAll,
    flexFileData,
    flexFileFormat,
    flexFileCommaText,
    flexFileTabText,
    flexFileCustomText,
} SaveLoadSettings;

typedef enum ArchiveSettings {
	arcAdd,
	arcStore,
	arcExtract,
	arcDelete,
} ArchiveSettings;

typedef enum ArchiveInfoSettings {
	arcFileCount,
	arcFileName,
	arcFileSize,
	arcFileCompressedSize,
	arcFileDate
} ArchiveInfoSettings;

typedef enum OLEDragModeSettings {
    flexOLEDragManual,
    flexOLEDragAutomatic,
} OLEDragModeSettings;

typedef enum OLEDropModeSettings {
    flexOLEDropNone,
    flexOLEDropManual,
    flexOLEDropAutomatic,
} OLEDropModeSettings;

typedef enum DataModeSettings {
    flexDMFree,
    flexDMBound,
    flexDMBoundBatch,
    flexDMBoundImmediate,
} DataModeSettings;

typedef enum OwnerDrawSettings {
    flexODNone,
    flexODOver,
    flexODContent,
    flexODComplete,
    flexODOverFixed,
    flexODContentFixed,
    flexODCompleteFixed,
} OwnerDrawSettings;

typedef enum DataTypeSettings {
	flexDTEmpty    = 0,
	flexDTNull     = 1,
	flexDTShort    = 2,
	flexDTLong     = 3,
	flexDTSingle   = 4,
	flexDTDouble   = 5,
	flexDTCurrency = 6,
	flexDTDate     = 7,
	flexDTString   = 8,
	flexDTDispatch = 9,
	flexDTError    = 10,
	flexDTBoolean  = 11,
	flexDTVariant  = 12,
	flexDTUnknown  = 13,
	flexDTDecimal  = 14,
	flexDTLong8    = 20,
	flexDTStringC  = 30,
	flexDTStringW  = 31,
} DataTypeSettings;

typedef enum AutoSizeSettings {
    flexAutoSizeColWidth,
    flexAutoSizeRowHeight,
} AutoSizeSettings;

typedef enum CollapsedSettings {
    flexOutlineExpanded,
    flexOutlineSubtotals,
    flexOutlineCollapsed,
} CollapsedSettings;

typedef enum OutlineBarSettings {
    flexOutlineBarNone,
    flexOutlineBarComplete,
    flexOutlineBarSimple,
    flexOutlineBarSymbols,
    flexOutlineBarCompleteLeaf,
    flexOutlineBarSimpleLeaf,
    flexOutlineBarSymbolsLeaf,
} OutlineBarSettings;

typedef enum SubtotalSettings {
    flexSTNone,
    flexSTClear,
    flexSTSum,
    flexSTPercent,
    flexSTCount,
    flexSTAverage,
    flexSTMax,
    flexSTMin,
    flexSTStd,
    flexSTVar,
} SubtotalSettings;

typedef enum SortSettings {
    flexSortNone,
    flexSortGenericAscending,
    flexSortGenericDescending,
    flexSortNumericAscending,
    flexSortNumericDescending,
    flexSortStringNoCaseAscending,
    flexSortStringNoCaseDescending,
    flexSortStringAscending,
    flexSortStringDescending,
    flexSortCustom,
    flexSortUseColSort,
} SortSettings;

typedef enum FocusRectSettings {
    flexFocusNone,
    flexFocusLight,
    flexFocusHeavy,
    flexFocusSolid,
    flexFocusRaised,
    flexFocusInset,
} FocusRectSettings;

typedef enum ShowSelSettings {
    flexHighlightNever,
    flexHighlightAlways,
    flexHighlightWithFocus,
} ShowSelSettings;

typedef enum ScrollBarsSettings {
    flexScrollBarNone,
    flexScrollBarHorizontal,
    flexScrollBarVertical,
    flexScrollBarBoth,
} ScrollBarsSettings;

typedef enum TextStyleSettings { 
    flexTextFlat,
    flexTextRaised,
    flexTextInset,
    flexTextRaisedLight,
    flexTextInsetLight,
} TextStyleSettings;

typedef enum FillStyleSettings {
    flexFillSingle,
    flexFillRepeat,
} FillStyleSettings;

typedef enum GridStyleSettings {
    flexGridNone,
    flexGridFlat,
    flexGridInset,
    flexGridRaised,
    flexGridFlatHorz,
    flexGridInsetHorz,
    flexGridRaisedHorz,
    flexGridSkipHorz,
    flexGridFlatVert,
    flexGridInsetVert,
    flexGridRaisedVert,
    flexGridSkipVert,
    flexGridExplorer,
    flexGridExcel,
} GridStyleSettings;

typedef enum SelModeSettings {
    flexSelectionFree,
    flexSelectionByRow,
    flexSelectionByColumn,
    flexSelectionListBox,
} SelModeSettings;

typedef enum MergeSettings {
    flexMergeNever,
    flexMergeFree,
    flexMergeRestrictRows,
    flexMergeRestrictColumns,
    flexMergeRestrictAll,
    flexMergeFixedOnly,
    flexMergeSpill,
    flexMergeOutline,
} MergeSettings;

typedef enum PictureTypeSettings {
    flexPictureColor,
    flexPictureMonochrome,
} PictureTypeSettings;

typedef enum AllowUserResizeSettings {
    flexResizeNone,
    flexResizeColumns,
    flexResizeRows,
    flexResizeBoth,
    flexResizeBothUniform,
} AllowUserResizeSettings;

typedef enum AllowUserFreezeSettings {
    flexFreezeNone,
    flexFreezeColumns,
    flexFreezeRows,
    flexFreezeBoth,
} AllowUserFreezeSettings;

typedef enum SubtotalPositionSettings {
    flexSTBelow,
    flexSTAbove,
} SubtotalPositionSettings;

typedef enum AlignmentSettings {
    flexAlignLeftTop,
    flexAlignLeftCenter,
    flexAlignLeftBottom,
    flexAlignCenterTop,
    flexAlignCenterCenter,
    flexAlignCenterBottom,
    flexAlignRightTop,
    flexAlignRightCenter,
    flexAlignRightBottom,
    flexAlignGeneral,
} AlignmentSettings;

typedef enum PictureAlignmentSettings {
    flexPicAlignLeftTop,
    flexPicAlignLeftCenter,
    flexPicAlignLeftBottom,
    flexPicAlignCenterTop,
    flexPicAlignCenterCenter,
    flexPicAlignCenterBottom,
    flexPicAlignRightTop,
    flexPicAlignRightCenter,
    flexPicAlignRightBottom,
    flexPicAlignStretch,
    flexPicAlignTile,
} PictureAlignmentSettings;

typedef enum NodeMoveSettings {
    flexNMIn,
    flexNMOut,
    flexNMUp,
    flexNMDown,
    flexNMFirst,
    flexNMLast,
    flexNMChildOf,
} NodeMoveSettings;

typedef enum NodeTypeSettings {
	flexNTRoot,
	flexNTParent,
	flexNTFirstChild,
	flexNTLastChild,
	flexNTFirstSibling,
	flexNTLastSibling,
	flexNTNextSibling,
	flexNTPreviousSibling,
} NodeTypeSettings;*/
// !defined(AFX_STDAFX_H__22E46340_12E0_4461_9A0C_4CD085175093__INCLUDED_)
