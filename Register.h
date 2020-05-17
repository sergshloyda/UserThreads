// Register.h: interface for the Register class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTER_H__9189C714_784A_43F3_8921_4D95E8BF9D8E__INCLUDED_)
#define AFX_REGISTER_H__9189C714_784A_43F3_8921_4D95E8BF9D8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Register  
{
	
public:
	static LPCTSTR GetValue(LPCTSTR strKey);
	static void SetValue(LPCTSTR strKey,LPCTSTR strValue);
	static void ShowErrorMessage(_com_error &e);

	virtual ~Register();
		Register();
private:
static	CMapStringToString repository;

};

#endif // !defined(AFX_REGISTER_H__9189C714_784A_43F3_8921_4D95E8BF9D8E__INCLUDED_)
