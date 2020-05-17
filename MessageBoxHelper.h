#pragma once

class MessageBoxHelper
{
public:
	MessageBoxHelper(void);
	~MessageBoxHelper(void);
	static void ShowError(const char* errMsg)
	{
		AfxMessageBox(errMsg,MB_ICONERROR|MB_OK);
	}
	static void ShowError(const CStringW errMsg)
	{
		USES_CONVERSION;
		AfxMessageBox(W2A(errMsg),MB_ICONERROR|MB_OK);
	}
	static void PrintComError(_com_error &e)
	{
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());

		// Print Com errors.
		CString msg1("Error\n");
		CString msg2;
		msg2.Format (_T("\tCode = %08lx\n"), e.Error());
		CString msg3;
		msg3.Format(_T("\tCode meaning = %s\n"), e.ErrorMessage());
		CString msg4;
		msg4.Format(_T("\tSource = %s\n"), (LPCSTR) bstrSource);
		CString msg5;
		msg5.Format(_T("\tDescription = %s\n"), (LPCSTR) bstrDescription);
		AfxMessageBox(msg1+msg2+msg3+msg4+msg5);
		CString msg6;
		msg6.Format(_T("HRESULT=%x"),e.Error ());
		AfxMessageBox(msg1+msg2+msg3+msg4+msg5+msg6,MB_ICONSTOP|MB_SETFOREGROUND);
	}
};

