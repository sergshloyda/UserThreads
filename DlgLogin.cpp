// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "DlgLogin.h"
#include "MainFrm.h"
#include "DlgSetQuantity.h"
#include "Entity.h"
#include "Repository.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog


CDlgLogin::CDlgLogin(CDocument* pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
	m_strPassword = _T("");
	m_pMainDoc=(CMainDocument*)pDoc;
	//}}AFX_DATA_INIT

}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Control(pDX, IDC_CBUSERS, m_cbUsers);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	ON_CBN_SELCHANGE(IDC_CBUSERS, OnSelchangeCbusers)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_GETDIGIT, OnGetdigit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

BOOL CDlgLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	/*
	В реестре хранится название кассы к которой прикручена программа 
	в дальнейшем этот параметр будет влиять на проведение чеков в 1С
	с ним связаны все атрибуты вносимые в документ

	*/
	try{
	CUserThreadsApp* pApp=static_cast<CUserThreadsApp*>(AfxGetApp());
			Repository* pRepDoc=CUserThreadsApp::GetDocument<Repository>();
			boost::shared_ptr<Repository::EmployeesReference> refEmpls=pRepDoc->getEmployees();
			boost::shared_ptr<Repository::PointsReference> refPoints=pRepDoc->getPoints();
			Repository::ReferenceItem point;
			if(refPoints->FindByAttribute(L"code",_bstr_t(m_pMainDoc->m_strPointId))>0)
			{
			point=refPoints->getCurrent();
			refEmpls->UseOwner(point);
			refEmpls->SelectItems();
			int i=0;
			do
			{
				boost::shared_ptr<RefItemV> empl=refEmpls->getCurrent();
				
				CString strItem=(LPCTSTR)(_bstr_t)(empl->getAttribute(L"nickname"));
				strItem.TrimRight ();
				m_cbUsers.InsertString (i,strItem);
				CString strId=(LPCTSTR)(_bstr_t)(empl->getAttribute(L"code"));
				strId.TrimRight ();
				CString strPassword=(LPCTSTR)(_bstr_t)(empl->getAttribute(L"password"));
				strPassword.TrimRight ();
				CString strName=(LPCTSTR)(_bstr_t)(empl->getAttribute(L"descr"));
				strName.TrimRight ();
				
				//		//strCashName.
				//		
				m_lsItems.AddTail (new ItemData(strId,strName,strPassword,strItem));
				//		
				i++;
			}while(refEmpls->getNext());
		}


		




		m_cbUsers.SetCurSel (0);

		SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE ); 

		GetDlgItem(IDC_PASSWORD)->SetFocus();
		//
		return TRUE; 
	}
	catch(DbContext::DbContextError &err)
	{
		CString strMsg;
		strMsg.Format (_T("Error #%08x \nDescription %s \nFrom %s"),err.what(),"","DlgLogin InitInstance");
		MessageBoxHelper::ShowError(strMsg);
		EndDialog(IDCANCEL);
		return FALSE;
	}

	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLogin::OnSelchangeCbusers() 
{
	
	
	POSITION pos=m_lsItems.FindIndex (m_cbUsers.GetCurSel());
	ItemData* pItem=static_cast<ItemData*>(m_lsItems.GetAt(pos));
	m_strCompare=pItem->password ;
	m_strCompare.TrimRight ();
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	pDoc->m_strUserName=pItem->name ;
	pDoc->m_strUserName.TrimRight();
	pDoc->m_strUserId=pItem->id ;
	pDoc->m_strUserId.TrimRight();



	
	
}

void CDlgLogin::PostNcDestroy() 
{

	while (!m_lsItems.IsEmpty())
		delete (ItemData*)m_lsItems.RemoveHead();
	CDialog::PostNcDestroy();
}





void CDlgLogin::OnOk() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	POSITION pos=m_lsItems.FindIndex (m_cbUsers.GetCurSel());
	ItemData* pItem=static_cast<ItemData*>(m_lsItems.GetAt(pos));
	m_strCompare=pItem->password ;
	m_strCompare.TrimRight ();
	CMainDocument* pDoc=CUserThreadsApp::GetDocument<CMainDocument> ();
	//pDoc->m_strCashId =m_strCashID;
	pDoc->m_strUserName=pItem->name ;
	pDoc->m_strUserName.TrimRight();
	pDoc->m_strUserId=pItem->id ;
	pDoc->m_strUserId.TrimRight();
	pDoc->m_strUserNick=pItem->Nick;
	m_strPassword.TrimLeft ();
	m_strPassword.TrimRight ();
	if(m_strCompare.Compare(m_strPassword)==0)
	{
	CString msg=_T("Успешно зарегистрирован пользователь:\n");
	msg+=pDoc->m_strUserName ;
	msg+=_T("\nТочка:");
	msg+=pDoc->m_strPointName ;
	msg+=_T("\nТабельный номер:");
	msg+=pDoc->m_strUserId ;
	
	AfxMessageBox(msg,MB_ICONINFORMATION|MB_TOPMOST | MB_SETFOREGROUND | MB_OK );

		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox(_T("Неверный пароль"),MB_ICONSTOP);
		CEdit* pWnd=(CEdit*)GetDlgItem(IDC_PASSWORD);
		pWnd->SetSel (0,-1);
		pWnd->Clear ();
		//pWnd->SendMessage(WM_CLEAR);
		pWnd->SetFocus ();
		//CDialog::OnCancel();
	}

	
}







void CDlgLogin::OnGetdigit() 
{
	CDlgSetQuantity dlg(TRUE);
	dlg.DoModal ();
	m_strPassword=dlg.m_strHolder ;
	UpdateData (FALSE);
}
