// DlgSetQuantity.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgSetQuantity.h"
#include "UserThreadsView.h"
#include "Repository.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetQuantity dialog


CDlgSetQuantity::CDlgSetQuantity(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetQuantity::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetQuantity)
	m_nQty = 0;

	//}}AFX_DATA_INIT
	m_blPass=FALSE;
	pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
}

CDlgSetQuantity::CDlgSetQuantity(LPCTSTR strCaption,CWnd* pParent /*=NULL*/)
: CDialog(CDlgSetQuantity::IDD, pParent)
{
	m_blPass=FALSE;
	m_nQty = 0;
	m_strCaption=strCaption;
	pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
}
CDlgSetQuantity::CDlgSetQuantity(BOOL blPass,CWnd* pParent /*=NULL*/)
: CDialog(CDlgSetQuantity::IDD, pParent)
{
	
	m_nQty = 0;
	m_blPass=blPass;
	m_strHolder=_T("");
	pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
}
void CDlgSetQuantity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetQuantity)
	DDX_Control(pDX, IDC_EDIT1, m_wndEdit);
	DDX_Text(pDX, IDC_EDIT1, m_nQty);
	//}}AFX_DATA_MAP
	if(pDX->m_bSaveAndValidate )
	{
		for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
		{
			m_strHolder+=*myVectorIterator;
			
		}
	}
}


BEGIN_MESSAGE_MAP(CDlgSetQuantity, CDialog)
	//{{AFX_MSG_MAP(CDlgSetQuantity)
	ON_BN_CLICKED(IDC_1NUM, On1num)
	ON_BN_CLICKED(IDC_2NUM, On2num)
	ON_BN_CLICKED(IDC_3NUM, On3num)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_0NUM, On0num)
	ON_BN_CLICKED(IDC_BACKSPC, OnBackspc)
	ON_BN_CLICKED(IDC_4NUM, On4num)
	ON_BN_CLICKED(IDC_5NUM, On5num)
	ON_BN_CLICKED(IDC_6NUM, On6num)
	ON_BN_CLICKED(IDC_7NUM, On7num)
	ON_BN_CLICKED(IDC_8NUM, On8num)
	ON_BN_CLICKED(IDC_9NUM, On9num)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetQuantity message handlers

BOOL CDlgSetQuantity::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CClientDC dc(this);
	CMainDocument* pMainDoc=CUserThreadsApp::GetDocument<CMainDocument> ();

	CFont* pOldFont=dc.SelectObject (pMainDoc->m_FontMap[_T("Dialogs")].get());
	m_wndEdit.SetFont(pMainDoc->m_FontMap[_T("Dialogs")].get());
	TEXTMETRIC tm;
	dc.GetTextMetrics (&tm);
	int  nHeight=tm.tmHeight+tm.tmHeight/4  ; 
	CRect rc;
	m_wndEdit.GetWindowRect (&rc);
	ScreenToClient(&rc);
	int nOldHeight=rc.Height();
	rc.bottom=rc.top + nHeight;
	int nDelta=rc.Height()-nOldHeight;
	m_wndEdit.MoveWindow (&rc);
	nDelta+=15;
	GetDlgItem(IDOK)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top+=nDelta;
	rc.bottom +=nDelta;
	GetDlgItem(IDOK)->MoveWindow(&rc);

	GetDlgItem(IDCANCEL)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	rc.top+=nDelta;
	rc.bottom +=nDelta;
	GetDlgItem(IDCANCEL)->MoveWindow(&rc);

	GetWindowRect(&rc);
	rc.bottom +=nDelta;
	MoveWindow(&rc);
	m_nQty=1;
	UpdateData(FALSE);
	if(!m_strCaption.IsEmpty())
	{
	Repository* pRep=CUserThreadsApp::GetDocument<Repository>();
	boost::shared_ptr<Repository::ProductsReference> refProducts=pRep->getProducts();
	m_strCaption.Trim();
	USES_CONVERSION;
		if(refProducts->FindByCode(A2W(m_strCaption))>0)
		{
			RefItemPtr curProduct=refProducts->getCurrent();
			SetWindowText(W2A(curProduct->_descr.c_str()));
		}
	}
	// TODO: Add extra initialization here
	dc.SelectObject (pOldFont);
	if(m_blPass)
	m_wndEdit.SetPasswordChar ('*');
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSetQuantity::On0num() 
{
	char val='0';
	charStack.push_back(val);
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
	
	
}
void CDlgSetQuantity::On1num() 
{
		charStack.push_back('1');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
}

void CDlgSetQuantity::On2num() 
{

		charStack.push_back('2');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
	
}

void CDlgSetQuantity::On3num() 
{

		charStack.push_back('3');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
	
}

void CDlgSetQuantity::On4num() 
{
	
		charStack.push_back('4');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
}

void CDlgSetQuantity::On5num() 
{
	
		charStack.push_back('5');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
}

void CDlgSetQuantity::On6num() 
{

		charStack.push_back('6');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
}

void CDlgSetQuantity::On7num() 
{

		charStack.push_back('7');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
	
}

void CDlgSetQuantity::On8num() 
{
	
		charStack.push_back('8');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
	
}

void CDlgSetQuantity::On9num() 
{

		charStack.push_back('9');
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
        myVectorIterator != charStack.end();
        myVectorIterator++)
	{
		str+=*myVectorIterator;
	
	}
	m_wndEdit.SetWindowText (str);
	
}
void CDlgSetQuantity::OnClear() 
{

	charStack.erase(charStack.begin(),charStack.end());
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
	myVectorIterator != charStack.end();
	myVectorIterator++)
	{
		str+=*myVectorIterator;
		
	}
	m_wndEdit.SetWindowText (str);
	
}



void CDlgSetQuantity::OnBackspc() 
{
	if(charStack.size()>0)
	{
	charStack.pop_back();
	CString str=_T("");
	for(myVectorIterator = charStack.begin(); 
	myVectorIterator != charStack.end();
	myVectorIterator++)
	{
		str+=*myVectorIterator;
		
	}
	m_wndEdit.SetWindowText (str);
	}
	
	
}

void CDlgSetQuantity::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	::Sleep(500);
	CDialog::OnCancel();
}


BOOL CDlgSetQuantity::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_ESCAPE)
		{
				/*this->ShowWindow(SW_HIDE);
				return TRUE;*/
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
