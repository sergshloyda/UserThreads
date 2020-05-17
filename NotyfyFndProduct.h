#pragma once
#include <wtypes.h>
#include <atldbcli.h>
#include <afxcom_.h>
class CNotyfyFndProduct;
typedef struct tagNMFNDPRODUCT
{
	NMHDR nmHdr;
	CNotyfyFndProduct* pObject;
} NMFNDPRODUCT;
typedef NMFNDPRODUCT* LPNMFNDPRODUCT;
enum{FND_BY_CODE=0,FND_BY_BARCODE};
class CNotyfyFndProduct
{
public:
	NMFNDPRODUCT m_hdrObject;

	CNotyfyFndProduct(void)
	{
	}
	CNotyfyFndProduct(NMHDR& Hdr,const int qty,LPCTSTR code,LPCTSTR barcode):qty_(qty),code_(code),barcode_(barcode)
	{
		memcpy(&(m_hdrObject.nmHdr),&(Hdr),sizeof(m_hdrObject.nmHdr));
		m_hdrObject.pObject=this;
	 
	}
	

	~CNotyfyFndProduct(void)
	{
	}
	CString GetCode() const { return code_; }
	
	int GetQty() const { return qty_; }
	CString GetBarCode()const{return barcode_;}
protected:
	int qty_;
	CString code_;
	CString barcode_;

};

