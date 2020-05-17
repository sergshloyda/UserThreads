# Microsoft Developer Studio Project File - Name="UserThreads" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UserThreads - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UserThreads.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UserThreads.mak" CFG="UserThreads - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UserThreads - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UserThreads - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "UserThreads - Win32 ReleaseU" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/UserThreads", WBAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UserThreads - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /map /debug /debugtype:both /machine:I386 /OPT:REF
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "UserThreads - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "UserThreads - Win32 ReleaseU"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "UserThreads___Win32_ReleaseU"
# PROP BASE Intermediate_Dir "UserThreads___Win32_ReleaseU"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "UserThreads___Win32_ReleaseU"
# PROP Intermediate_Dir "UserThreads___Win32_ReleaseU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /map /debug /debugtype:both /machine:I386 /OPT:REF
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /map /debug /debugtype:both /machine:I386 /OPT:REF
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "UserThreads - Win32 Release"
# Name "UserThreads - Win32 Debug"
# Name "UserThreads - Win32 ReleaseU"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\1CHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\Barcode.cpp
# End Source File
# Begin Source File

SOURCE=.\BarcodeEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CashDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CashPrinter.cpp
# End Source File
# Begin Source File

SOURCE=.\CategoryTree.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\cmercury.cpp
# End Source File
# Begin Source File

SOURCE=.\ComPortDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DBDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogView.cpp
# End Source File
# Begin Source File

SOURCE=.\DictGoodsFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnterCash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFindAll.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInsert.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgManageKKM.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMultQty.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelDate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectGood.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetPeriod.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetQuantity.cpp
# End Source File
# Begin Source File

SOURCE=.\drvfr.cpp
# End Source File
# Begin Source File

SOURCE=.\dtpicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ExplorerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDialog2K.cpp
# End Source File
# Begin Source File

SOURCE=.\FindEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\FindView.cpp
# End Source File
# Begin Source File

SOURCE=.\FirstStepPage.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\FontCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\FontToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Ftab.cpp
# End Source File
# Begin Source File

SOURCE=.\GoodsGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\MainChildFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MDIChild.cpp
# End Source File
# Begin Source File

SOURCE=.\MDIClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MultButton.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiSplitterView.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\NaklForm.cpp
# End Source File
# Begin Source File

SOURCE=.\NodeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\NTree.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\PPLAPrinter.cpp
# End Source File
# Begin Source File

SOURCE=.\PSDlgInsertGood.cpp
# End Source File
# Begin Source File

SOURCE=.\PupText.cpp
# End Source File
# Begin Source File

SOURCE=.\ReciclingView.cpp
# End Source File
# Begin Source File

SOURCE=.\Register.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportView.cpp
# End Source File
# Begin Source File

SOURCE=.\ReturnDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ReturnView.cpp
# End Source File
# Begin Source File

SOURCE=.\SalaryDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SecondStepPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StatLink.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SuperTree.cpp
# End Source File
# Begin Source File

SOURCE=.\TableValue1.cpp
# End Source File
# Begin Source File

SOURCE=.\ThirdStepPage.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeNode.cpp
# End Source File
# Begin Source File

SOURCE=.\UpFolderTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UserThreads.cpp
# End Source File
# Begin Source File

SOURCE=.\UserThreads.rc
# End Source File
# Begin Source File

SOURCE=.\UserThreadsView.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewManager.cpp
# End Source File
# Begin Source File

SOURCE=.\vsflexdatasource.cpp
# End Source File
# Begin Source File

SOURCE=.\vsflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\WntRetEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ZReportDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ZReportView.cpp
# End Source File
# Begin Source File

SOURCE=.\ZReportWizard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\1CHelper.h
# End Source File
# Begin Source File

SOURCE=.\Barcode.h
# End Source File
# Begin Source File

SOURCE=.\BarcodeEdit.h
# End Source File
# Begin Source File

SOURCE=.\BarCodeReader.h
# End Source File
# Begin Source File

SOURCE=.\CashDoc.h
# End Source File
# Begin Source File

SOURCE=.\CashPrinter.h
# End Source File
# Begin Source File

SOURCE=.\CategoryTree.h
# End Source File
# Begin Source File

SOURCE=.\CheckButton.h
# End Source File
# Begin Source File

SOURCE=.\CheckDoc.h
# End Source File
# Begin Source File

SOURCE=.\cmercury.h
# End Source File
# Begin Source File

SOURCE=.\ComPortDlg.h
# End Source File
# Begin Source File

SOURCE=.\DBDoc.h
# End Source File
# Begin Source File

SOURCE=.\DialogView.h
# End Source File
# Begin Source File

SOURCE=.\DictGoodsFrame.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnterCash.h
# End Source File
# Begin Source File

SOURCE=.\DlgFindAll.h
# End Source File
# Begin Source File

SOURCE=.\DlgInsert.h
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.h
# End Source File
# Begin Source File

SOURCE=.\DlgManageKKM.h
# End Source File
# Begin Source File

SOURCE=.\DlgMultQty.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelDate.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectGood.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetPeriod.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetQuantity.h
# End Source File
# Begin Source File

SOURCE=.\DocSetter.h
# End Source File
# Begin Source File

SOURCE=.\drvfr.h
# End Source File
# Begin Source File

SOURCE=.\dtpicker.h
# End Source File
# Begin Source File

SOURCE=.\ExplorerDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileDialog2K.h
# End Source File
# Begin Source File

SOURCE=.\FindEdit.h
# End Source File
# Begin Source File

SOURCE=.\FindView.h
# End Source File
# Begin Source File

SOURCE=.\FirstStepPage.h
# End Source File
# Begin Source File

SOURCE=.\FolderFrame.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\FontCombo.h
# End Source File
# Begin Source File

SOURCE=.\FontToolBar.h
# End Source File
# Begin Source File

SOURCE=.\Ftab.h
# End Source File
# Begin Source File

SOURCE=.\GoodsGrid.h
# End Source File
# Begin Source File

SOURCE=.\InfoConsole.h
# End Source File
# Begin Source File

SOURCE=.\InfoFrame.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\LimitSingleInstance.h
# End Source File
# Begin Source File

SOURCE=.\MainChildFrame.h
# End Source File
# Begin Source File

SOURCE=.\MainDocument.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MDIChild.h
# End Source File
# Begin Source File

SOURCE=.\MDIClient.h
# End Source File
# Begin Source File

SOURCE=.\MultButton.h
# End Source File
# Begin Source File

SOURCE=.\MultiSplitterView.h
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\NaklForm.h
# End Source File
# Begin Source File

SOURCE=.\NodeItem.h
# End Source File
# Begin Source File

SOURCE=.\NTree.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\PPLAPrinter.h
# End Source File
# Begin Source File

SOURCE=.\PSDlgInsertGood.h
# End Source File
# Begin Source File

SOURCE=.\PupText.h
# End Source File
# Begin Source File

SOURCE=.\ReciclingView.h
# End Source File
# Begin Source File

SOURCE=.\Register.h
# End Source File
# Begin Source File

SOURCE=.\ReportFrame.h
# End Source File
# Begin Source File

SOURCE=.\ReportView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ReturnDoc.h
# End Source File
# Begin Source File

SOURCE=.\ReturnView.h
# End Source File
# Begin Source File

SOURCE=.\SalaryDoc.h
# End Source File
# Begin Source File

SOURCE=.\SecondStepPage.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StatLink.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SuperTree.h
# End Source File
# Begin Source File

SOURCE=.\TableValue1.h
# End Source File
# Begin Source File

SOURCE=.\ThirdStepPage.h
# End Source File
# Begin Source File

SOURCE=.\TreeNode.h
# End Source File
# Begin Source File

SOURCE=.\UpFolderTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UserThreads.h
# End Source File
# Begin Source File

SOURCE=.\UserThreadsView.h
# End Source File
# Begin Source File

SOURCE=.\ViewManager.h
# End Source File
# Begin Source File

SOURCE=.\vsflexdatasource.h
# End Source File
# Begin Source File

SOURCE=.\vsflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\WindowTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\WntRetEdit.h
# End Source File
# Begin Source File

SOURCE=.\ZReportDoc.h
# End Source File
# Begin Source File

SOURCE=.\ZReportView.h
# End Source File
# Begin Source File

SOURCE=.\ZReportWizard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ABORT.BMP
# End Source File
# Begin Source File

SOURCE=.\res\AccountUsers.ico
# End Source File
# Begin Source File

SOURCE=.\res\allbistrue.bmp
# End Source File
# Begin Source File

SOURCE=.\BarCodeReader.rgs
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BOOKS05.ICO
# End Source File
# Begin Source File

SOURCE=.\res\bmp\bundle_016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp\bundle_048.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp\bundle_256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Calendar_scheduleHS.ico
# End Source File
# Begin Source File

SOURCE=.\res\CheckNottrans.ico
# End Source File
# Begin Source File

SOURCE=.\res\Checktransacted.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Delete.ico
# End Source File
# Begin Source File

SOURCE=.\res\DoubleLeftArrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\DoubleRightArrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\EXPLORER.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FLDRSHUT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FOLDER01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FOLDER02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FOLDRS01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FOLDRS02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FORM.ICO
# End Source File
# Begin Source File

SOURCE=.\res\good.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_find.ico
# End Source File
# Begin Source File

SOURCE=.\mdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\MSGBOX02.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MSGBOX04.ICO
# End Source File
# Begin Source File

SOURCE=.\res\OK.ico
# End Source File
# Begin Source File

SOURCE=.\res\REFBAR.ICO
# End Source File
# Begin Source File

SOURCE=.\res\RightArrow.ico
# End Source File
# Begin Source File

SOURCE=.\res\ROCKET.ICO
# End Source File
# Begin Source File

SOURCE=.\res\selectdoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\selectdoc1.ico
# End Source File
# Begin Source File

SOURCE=.\res\selgood.ico
# End Source File
# Begin Source File

SOURCE=.\res\SHIPPING.BMP
# End Source File
# Begin Source File

SOURCE=.\res\SPLASH.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Symbol-Delete.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\UserThreads.ico
# End Source File
# Begin Source File

SOURCE=.\res\UserThreads.rc2
# End Source File
# Begin Source File

SOURCE=.\UserThreads.rgs
# End Source File
# Begin Source File

SOURCE=.\res\UserThreadsDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\FILEDEL_16.AVI
# End Source File
# Begin Source File

SOURCE=.\Plans
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section UserThreads : {20DD1B9B-87C4-11D1-8BE3-0000F8754DA1}
# 	2:5:Class:CDTPicker
# 	2:10:HeaderFile:dtpicker.h
# 	2:8:ImplFile:dtpicker.cpp
# End Section
# Section UserThreads : {01D21C18-1D08-01D2-801E-D201701FD201}
# 	1:15:IDR_USERTHREADS:120
# End Section
# Section UserThreads : {20DD1B9E-87C4-11D1-8BE3-0000F8754DA1}
# 	2:21:DefaultSinkHeaderFile:dtpicker.h
# 	2:16:DefaultSinkClass:CDTPicker
# End Section
