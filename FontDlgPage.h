#pragma once
#include "afxwin.h"

#ifdef _WIN32_WCE
#error "COlePropertyPage is not supported for Windows CE."
#endif 

// CFontDlgPage : Property page dialog

class CFontDlgPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFontDlgPage)
	//DECLARE_OLECREATE_EX(CFontDlgPage)

// Constructors
public:
	CFontDlgPage();

// Dialog Data
	enum { IDD = IDD_FONTDLG };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support
	void GetFontDescription(CFont* font,CString& szDescr)
	{
		CString strFDescr;
		LOGFONT logFont;
		font->GetLogFont(&logFont);
		int szFont=-(logFont.lfHeight*72/GetDeviceCaps(GetDC()->GetSafeHdc(),LOGPIXELSY));


		szDescr.Format(_T("Font name:%s FontSize=%d"),logFont.lfFaceName,szFont);
		//szDescr=strFDescr;
		return ;
	}

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedBtnSelFnt();
private:
	CFont m_fntEdit;
	CEdit m_wndSampleFont;
	CString m_strFontDescr;
	CString m_strSampleText;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeLstFonts();
	void SendFontChangeNotify();
	afx_msg void OnBnClickedSetFnt();
};
