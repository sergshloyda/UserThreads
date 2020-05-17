// UpFolderTabCtrl.h: interface for the CUpFolderTabCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPFOLDERTABCTRL_H__DED4CD38_4FD2_4309_912D_FCBF40FE8965__INCLUDED_)
#define AFX_UPFOLDERTABCTRL_H__DED4CD38_4FD2_4309_912D_FCBF40FE8965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ftab.h"

class CUpFolderTabCtrl : public CFolderTabCtrl  
{
public:
	virtual void DrawTabs(CDC& dc,const CRect &rc);
	CUpFolderTabCtrl();
	virtual ~CUpFolderTabCtrl();

};

#endif // !defined(AFX_UPFOLDERTABCTRL_H__DED4CD38_4FD2_4309_912D_FCBF40FE8965__INCLUDED_)
