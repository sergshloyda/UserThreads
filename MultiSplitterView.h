// MultiSplitterView.h: interface for the CMultiSplitterView class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MULTISPLITTERVIEW_H_
#define _MULTISPLITTERVIEW_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Disable warning messages 4786.
#pragma warning( disable : 4786 )

#include <map>
using namespace std;

/*****************************************************************************
*
* Class   : CMultiSplitterView


* Notes   :Switch views in Splitter Window
******************************************************************************/
class CMultiSplitterView  : public  CSplitterWnd
{
public:
	CWnd * GetViewPtr(UINT id, int paneRow, int paneCol);
	bool SwitchView(UINT id, int paneRow, int paneCol);
	bool AddSwitchableView(UINT id , CRuntimeClass*, CCreateContext* pContext,
					const CRect & size, bool isFirstView = false, UINT altId= 0);
	CMultiSplitterView();
	~CMultiSplitterView();

	map<CWnd *, UINT> views;

};

#endif // _MULTISPLITTERVIEW_H_
