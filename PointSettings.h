#pragma once
class CPointSettings:public CPropertySheet
{
	DECLARE_DYNAMIC(CPointSettings)
public:
	CPointSettings(UINT nIDCaption,CWnd* pParentWnd=NULL,UINT iSelectedPage=0);
	CPointSettings(LPCTSTR pszCaption,CWnd* pParentWnd=NULL,UINT iSelectedPage=0);
	virtual ~CPointSettings();

	virtual BOOL OnInitDialog();

private:
	CButton m_OKButton;
	CButton m_CancelBtn;
DECLARE_MESSAGE_MAP()
};