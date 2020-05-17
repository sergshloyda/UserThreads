#if !defined(AFX_MAINDOCUMENT_H__A8C8486F_D30F_4AFB_9C90_08E3D7BE850E__INCLUDED_)
#define AFX_MAINDOCUMENT_H__A8C8486F_D30F_4AFB_9C90_08E3D7BE850E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDocument.h : header file
//
#include "NTree.h" 
#include "1CHelper.h"
#include "Repository.h"
#define MSGLABELSIZE 256
/////////////////////////////////////////////////////////////////////////////
// CMainDocument document
class CDocInfo
{
public: 
  
	CDocInfo()
	{
		
		szDocId=new TCHAR[14];
		memset(szDocId,0,14);
		nId=0;
		szDocType=new TCHAR[4];
		memset(szDocType,0,4);
		tmDocDate=COleDateTime::GetCurrentTime ();
		tmDocTime=COleDateTime::GetCurrentTime();
		flSumma=0.0;
		blIsLoaded=0;
		szBaseDoc=new TCHAR[14];
		memset(szBaseDoc,0,14);
	}
	~CDocInfo()
	{
		delete szDocId;
		delete szDocType;
		delete szBaseDoc;
	}
	TCHAR* szDocId;
	int nId;
	TCHAR* szDocType;
	COleDateTime tmDocDate;
	COleDateTime tmDocTime;
	float flSumma;
	int blIsLoaded;
	TCHAR *szBaseDoc;  
};

class CMainDocument : public CDocument
{
protected:
	CMainDocument();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMainDocument)

// Attributes
public:

	CString GetComPort() const { return m_strComPort; }

	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDocument)
	public:
	virtual void Serialize(CArchive& ar);// overridden for document i/o
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainDocument)
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:

	HRESULT SendDataInQueue(BSTR bstrData,LPCTSTR strLabel=NULL);
	void ReestablishObject(BSTR bstrDN);
	void UpdateJournal(LPCTSTR strDocid);
	void AddDocInBufferTable(LPCTSTR strDocId,IUnknown *pDocUnk);

	BOOL SendDocIn1CQueue(IUnknown *pDoc,LPCTSTR strLabel=NULL);
	BOOL Load1C();
	void ReadSettings();

	BOOL m_blKKMOnLine;
	C1CHelper App1C;
	CString m_strEKLZ;
	CString m_strKKM;
	CString m_strINN;
	CString m_strFirma;
	CString m_strMainPointId;
	CString m_strMainCashId;
	CString m_strCashId;
	CString m_strMachineName;
	CString m_strStockId;
	CString m_strTypePriceId;
	HIMAGELIST m_hSysImgLst;
	BOOL m_blIsDirty;
	COleDateTime m_tmPointActual;
	HANDLE m_hDocTransacted;
	BOOL GetCheckInfo(CString strDocId,CString& strPointId,CString& strSalerId,CString& strContragId,COleDateTime& tmCheckDate);
	
	CString m_strCurDocId;
	int m_nCurMaxDocNum;
	CString m_strPointId;
	CString m_strPointName;
	CString m_strUserId;
	CString m_strUserName;
	CString m_strUserNick;
	CString m_strContragId;
	CString  m_strPrefix;
	BOOL blCatalogOpen;
	_RecordsetPtr pRstCatalog;
	CString m_strQueuePath;
	BOOL m_bQueueCreated;

	BOOL CloseAllRecordsets();
	BOOL SetEnvironmentPoint();
	void DisconnectBase();
	void ReadComPort();  
	void SaveFont(LPCTSTR fntName,CFont* pFont);
	BOOL ReadFont(LPCTSTR fntName);
	void ReadFonts();
	




	void LoadCategoryTree();
	BOOL CreateQueue();
	HRESULT OpenMyQueue(WCHAR *wszPathName,DWORD dwAccessMode,DWORD dwShareMode,IMSMQQueuePtr& pQueue);
	HRESULT CreateObjRefDispName(IUnknown *pUnk, BSTR *bsDN);
protected:

	


	private:
	CString m_strComPort;

	public:

		typedef std::map<CString,std::shared_ptr<CFont>> FontMap;
		FontMap m_FontMap;


	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDOCUMENT_H__A8C8486F_D30F_4AFB_9C90_08E3D7BE850E__INCLUDED_)
