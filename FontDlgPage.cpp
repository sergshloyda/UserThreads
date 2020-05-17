// FontDlgPage.cpp : implementation file
//

#include "stdafx.h"
#include "UserThreads.h"
#include "FontDlgPage.h"
#include "MainFrm.h"
#include "MainChildFrame.h"


// CFontDlgPage dialog

IMPLEMENT_DYNCREATE(CFontDlgPage, CPropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CFontDlgPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_SEL_FNT, &CFontDlgPage::OnBnClickedBtnSelFnt)
	ON_LBN_SELCHANGE(IDC_LST_FONTS, &CFontDlgPage::OnLbnSelchangeLstFonts)
	ON_BN_CLICKED(IDC_SET_FNT, &CFontDlgPage::OnBnClickedSetFnt)
END_MESSAGE_MAP()






// CFontDlgPage::CFontDlgPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CFontDlgPage





// CFontDlgPage::CFontDlgPage - Constructor

// TODO: Define string resource for page caption; replace '0' below with ID.

CFontDlgPage::CFontDlgPage() :
	CPropertyPage(CFontDlgPage::IDD)
		, m_strFontDescr(_T(""))
	{
		LOGFONT lf;
		afxGlobalData.fontRegular.GetLogFont(&lf);
		m_fntEdit.CreateFontIndirect(&lf);
		
}



// CFontDlgPage::DoDataExchange - Moves data between page and properties

void CFontDlgPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAMPLE_FONT, m_wndSampleFont);
	DDX_Text(pDX,IDC_FONT_DESCR,m_strFontDescr);
	DDX_Text(pDX,IDC_SAMPLE_FONT,m_strSampleText);
}



// CFontDlgPage message handlers


void CFontDlgPage::OnBnClickedBtnSelFnt()
{
	LOGFONT logFont;
	/*m_spCurrFont->GetLogFont(&logFont);*/

	CListBox* pListBox=(CListBox*)GetDlgItem(IDC_LST_FONTS);
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	CString strCurSel;
	pListBox->GetText(pListBox->GetCurSel(),strCurSel);
	CMainDocument::FontMap::iterator it=pDoc->m_FontMap.begin();

	it=pDoc->m_FontMap.find(strCurSel);
	if(it!=pDoc->m_FontMap.end())
	{

		it->second->GetLogFont(&logFont);
		CWnd* pWndSampleText=GetDlgItem(IDC_SAMPLE_FONT);
		pWndSampleText->SetFont(it->second.get());
		GetFontDescription(it->second.get(),m_strFontDescr);
	}

	CFontDialog dlg(&logFont);
	if(dlg.DoModal()==IDOK){
		dlg.GetCurrentFont(&logFont);

		CWnd* pWndSampleText=GetDlgItem(IDC_SAMPLE_FONT);

		CListBox* pListBox=(CListBox*)GetDlgItem(IDC_LST_FONTS);
		CString strCurSel;
		pListBox->GetText(pListBox->GetCurSel(),strCurSel);
		CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument>();
		CMainDocument::FontMap::iterator it=pDoc->m_FontMap.find(strCurSel);
		if(it!=pDoc->m_FontMap.end())
		{
			it->second->DeleteObject();

			it->second->CreateFontIndirect(&logFont);
			pWndSampleText->SetFont(it->second.get());
			GetFontDescription(it->second.get(),m_strFontDescr);

		}



		UpdateData(FALSE);


	}
}


BOOL CFontDlgPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	
	m_strSampleText.LoadString(IDC_SAMPLE_FONT);


	CListBox* pListBox=(CListBox*)GetDlgItem(IDC_LST_FONTS);
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	std::for_each(pDoc->m_FontMap.begin(),pDoc->m_FontMap.end(),[pListBox](std::pair<CString,std::shared_ptr<CFont> > curItem){
		pListBox->AddString(curItem.first);
	});

	pListBox->SetCurSel(0);
	CString strKey=_T("Button");
	int nSel=pListBox->GetCurSel();
	if(nSel!=LB_ERR)
		pListBox->GetText(nSel,strKey);
	CMainDocument::FontMap::iterator it=pDoc->m_FontMap.find(strKey);
	if(it!=pDoc->m_FontMap.end()){
		CWnd* pWndSampleText=GetDlgItem(IDC_SAMPLE_FONT);
		pWndSampleText->SetFont(it->second.get());
		GetFontDescription(it->second.get(),m_strFontDescr);
	}




	// TODO:  Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CFontDlgPage::OnLbnSelchangeLstFonts()
{
	CListBox* pListBox=(CListBox*)GetDlgItem(IDC_LST_FONTS);
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument>();
	CString strCurSel;
	pListBox->GetText(pListBox->GetCurSel(),strCurSel);
	CMainDocument::FontMap::iterator it=pDoc->m_FontMap.begin();
	//OutputDebugString(_T("OnLbnSelchangeLstFonts\n"));
	//for(it;it!=pDoc->m_FontMap.end();++it)
	//{
	//	CString str;
	//	GetFontDescription(it->second.get(),str);
	//	str+=it->first;
	//	
	//	OutputDebugString(str);

	//}
	it=pDoc->m_FontMap.find(strCurSel);
	if(it!=pDoc->m_FontMap.end())
	{
		LOGFONT lf;
		it->second->GetLogFont(&lf);
		//m_spCurrFont->DeleteObject();
		//m_spCurrFont->CreateFontIndirect(&lf);
		CWnd* pWndSampleText=GetDlgItem(IDC_SAMPLE_FONT);
		pWndSampleText->SetFont(it->second.get());
		GetFontDescription(it->second.get(),m_strFontDescr);
	}
	//m_spCurrFont.reset(it->second.get());
	//if(m_spCurrFont!=NULL){
	//	CWnd* pWndSampleText=GetDlgItem(IDC_SAMPLEFONT);
	//	pWndSampleText->SetFont(m_spCurrFont.get());
	//	GetFontDescription(m_spCurrFont.get(),m_strFontDescription);
	//}

	// TODO:  Add extra initialization here
	UpdateData(FALSE);
}

void CFontDlgPage::SendFontChangeNotify()
{
	CMainFrame *pMainFrame=static_cast<CMainFrame*>(AfxGetMainWnd());
	CFrameWnd* pChild = static_cast<CFrameWnd*>(pMainFrame->GetActiveFrame());
	CView* pView = pChild->GetActiveView();
	NMHDR nm;
	memset((void*)&nm,0,sizeof(NMHDR));
	CWnd* pBtn=GetDlgItem(IDC_SET_FNT);
	nm.hwndFrom=pBtn->m_hWnd;
	nm.code=NM_FONTCHANGED;
	nm.idFrom=IDC_SET_FNT;
	OutputDebugString(_T("Before  notify\n"));
	pView->SendMessage(WM_NOTIFY,NULL,(LPARAM)&nm);
	//::SendMessage(pView->m_hWnd,WM_NOTIFY,0L,(LPARAM)&nm);

	//pView->SendMessage(WM_FONTCHANGE,NULL,NULL);
	OutputDebugString(_T("After notify\n"));
}


void CFontDlgPage::OnBnClickedSetFnt()
{
	SendFontChangeNotify();// TODO: Add your control notification handler code here
}
