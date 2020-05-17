// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _IReaderEvents wrapper class

class _IReaderEvents : public COleDispatchDriver
{
public:
	_IReaderEvents() {}		// Calls COleDispatchDriver default constructor
	_IReaderEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IReaderEvents(const _IReaderEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'ReceiveBarCode' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IReader wrapper class

class IReader : public COleDispatchDriver
{
public:
	IReader() {}		// Calls COleDispatchDriver default constructor
	IReader(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IReader(const IReader& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void OpenCommPort(LPCTSTR CommPort);
	void CloseCommPort();
	void Execute();
};
/////////////////////////////////////////////////////////////////////////////
// _IReaderEvents wrapper class

class _IReaderEvents : public COleDispatchDriver
{
public:
	_IReaderEvents() {}		// Calls COleDispatchDriver default constructor
	_IReaderEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_IReaderEvents(const _IReaderEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'ReceiveBarCode' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IReader wrapper class

class IReader : public COleDispatchDriver
{
public:
	IReader() {}		// Calls COleDispatchDriver default constructor
	IReader(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IReader(const IReader& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void OpenCommPort(LPCTSTR CommPort);
	void CloseCommPort();
	void Execute();
};
