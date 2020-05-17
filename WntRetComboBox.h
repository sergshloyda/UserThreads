#pragma once


// WntRetComboBox
struct CB_NMRETURN : public NMHDR {		 // notification struct
	// item index
	CString strText; 					 // ptr to data, if any
};
class WntRetComboBox : public CComboBox
{
	DECLARE_DYNAMIC(WntRetComboBox)

public:
	WntRetComboBox();
	virtual ~WntRetComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


