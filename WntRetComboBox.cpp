
// WntRetComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "WntRetComboBox.h"


// WntRetComboBox

IMPLEMENT_DYNAMIC(WntRetComboBox, CComboBox)

WntRetComboBox::WntRetComboBox()
{

}

WntRetComboBox::~WntRetComboBox()
{
}


BEGIN_MESSAGE_MAP(WntRetComboBox, CComboBox)
END_MESSAGE_MAP()



// WntRetComboBox message handlers




BOOL WntRetComboBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			CB_NMRETURN nm;
			nm.hwndFrom = m_hWnd;
			nm.idFrom = GetDlgCtrlID();
			nm.code = NM_RETURN;
			CString strText;
			GetWindowText(strText);
			nm.strText=strText;

			CWnd* pParent=GetParent();
			pParent->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
			return TRUE;
		}
	}
	return CComboBox::PreTranslateMessage(pMsg);
}
