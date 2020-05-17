// 1CHelper.cpp: implementation of the C1CHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "userthreads.h"
#include "1CHelper.h"
#include <objbase.h>
#include <comdef.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C1CHelper::C1CHelper()
{
/*	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		AfxMessageBox("Невозможно инициализировать COM!");
	
	}*/
}

C1CHelper::~C1CHelper()
{
/*	if (pv77)
			pv77->Release();
		CoUninitialize();
		*/
}

BOOL C1CHelper::Open1C(BSTR bstrParam)
{
	
	//для начала инициализируем COM
	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("Невозможно инициализировать COM!"));
		return FALSE;
	}
	
	/*
	Прежде всего, нам необходимо получить
	 ID сервера OLE Automation 1С Предприятия.
	*/
	CLSID   cls77;
	
	/*
	Используем универсальный ключ 1С Предприятия 
	
	  Подробнее см. КЖК – если у Вас установлена единственная 
		версия 1С – то этого достаточно, если несколько разных, 
		то нужно загрузить нужный. Вот краткий список возможных значений:
		
		  V1CEnterprise.Application - версия независимый ключ;
		  V77.Application - версия зависимый ключ;
		  V77S.Application - версия зависимый ключ, SQL-версия;
		  V77L.Application - версия зависимый ключ, локальная-версия;
		  V77M.Application - версия зависимый ключ, сетевая-версия.
	*/
	
	hr = CLSIDFromProgID(L"V77.Application", &cls77); 
	if(FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("Переустановите 1С Предприятие!"));
		CoUninitialize();
		return FALSE;
	}
	
	//основной интерфейс, за который мы будем "дёргать"
	IDispatch *pv77;
	
	/*
	Создаём инстанцию 1С Предприятия. 
	
	  CLSCTX_LOCAL_SERVER – это значит, что 1С Предприятие 
	  будет запущено в виде отдельного процесса – по другому оно не умеет.
	*/
	
	hr = CoCreateInstance(cls77, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&pv77);
	
	if(FAILED(hr)  ||  !pv77)
	{
		MessageBoxHelper::ShowError(_T("Невозможно инициализировать интерфейс 1С Предприятия")); 
		CoUninitialize();
		return FALSE;
	}
	
	/*
	пока всё было понятно и очевидно, дальше начинаются сложности… 
	  1С предоставляет для запуска приложения функцию Initialize. 
	  Вызов этой функции выглядит в VB элементарно
	  
		V7.Initialize(V7.RMTrade,"D:\1C\ТипаБаза /N"+Пользователь ,"NO_SPLASH_SHOW");
		
		  - мы практически забываем, что же происходит внутри.
		  Но занимающиеся С++ люди хладнокровные, трудностей не боятся. 
			 Во-первых: мы должны помнить, что аргументы необходимо заталкивать задом наперёд…
			 Во-вторых: мы должны помнить, что RMTrade - это доже IDispatch интерфейс.. и его сперва нужно получить.
	*/
	
	VARIANT       vRet;
	DISPID dispIDRmTrade, dispIDInitialize;
	DISPPARAMS args = {0, 0, 0, 0};
	VARIANT vars[3];  // Параметры для вызова Initialize
	
	//Мы получим IDispatch интерфейс от RMTrade сразу в vars[2]
	
	BSTR rmTrade = L"RMTrade";
	
	hr = pv77->GetIDsOfNames(IID_NULL, &rmTrade, 1, 0, &dispIDRmTrade);
	
	if (FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("Невозможно получить ID от RMTrade"));
		if (pv77)
			pv77->Release();
		CoUninitialize();
		return FALSE;
	}
	
	hr = pv77->Invoke(dispIDRmTrade, IID_NULL, 0, DISPATCH_PROPERTYGET, &args,
		&vars[2], NULL, NULL);
	
	if (FAILED(hr))
	{
		MessageBoxHelper::ShowError(_T("Невозможно получить интерфейс от RMTrade"));
		if (pv77)
			pv77->Release();
		CoUninitialize();
		return FALSE;
	}
	
	//нужно получить ID для Initialize(..);
	BSTR init = L"Initialize";
	hr = pv77->GetIDsOfNames(IID_NULL, &init, 1, 0, &dispIDInitialize);
	if (FAILED(hr))
	{
		MessageBoxHelper::ShowError (_T("Не удалось получить ID от Initialize"));
		if (pv77)
			pv77->Release();
		CoUninitialize();
		return FALSE;
	}
	
	/*
	а теперь – вызвать этот самый Initialize(..), 
	но сперва необходимо заполнить массив аргументов функции
	*/
	
	args.cArgs = 3;
	args.rgvarg = vars;
	vars[0] = _variant_t("NO_SPLASH_SHOW");
	vars[1] = _variant_t("/D C:\\TS\\DistrDB /N Test ");
	
	/*
	vars[2] – у нас уже есть, мы его получили при запросе 
	интерфейса RMTrade в момент предыдущего Invoke
	*/
	
	hr = pv77->Invoke(dispIDInitialize, IID_NULL, 0, DISPATCH_PROPERTYGET, &args, 
		&vRet, NULL, NULL);
	
	if(FAILED(hr) ||  (vRet.vt ==  VT_BOOL && vRet.bstrVal == 0x00))
	{
		MessageBoxHelper::ShowError(_T("Невозможно запустить 1С Предприятие"));
		return FALSE;
		
	}
	return TRUE;
}



BOOL C1CHelper::Open1CEx(const CString &strPath, const CString& strUser, const CString& strPassword)
{
	
	BYTE *parms;
		CString strSection       = "";
	CString strStringItem    = "1CProgID";
	
	 CString strProgID=	AfxGetApp()->GetProfileString (strSection,strStringItem,_T("V77S.Application"));
 
		if (drvApp.CreateDispatch(strProgID))
		{
			CString strRMTrade("RMTrade");     
			BSTR rmTrade = strRMTrade.AllocSysString() ;
			
			DISPID id_rmtrade=0;
			HRESULT hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&rmTrade,1,LOCALE_SYSTEM_DEFAULT,&id_rmtrade);
			::SysFreeString (rmTrade);
			if(hr!=S_OK || id_rmtrade==0 || id_rmtrade==-1)
			{
				AfxMessageBox(_T("ОБЪЕКТ 1C НЕ НАЙДЕН\n"),MB_ICONSTOP);
				return FALSE ;
			}
			// и получаем его значение
			long RMTrade=0;
			drvApp.GetProperty(id_rmtrade,VT_I4,&RMTrade);
			
			// дальше надо проинициализировать 1С
			
			BOOL init;
			
			// находим ID метода Initialize
			CComBSTR name=_T("Initialize");
			DISPID id_init=0;
			hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_init);
			// путь к базе данных 1С
			CString strCommand;
			strCommand.Format (_T("/D %s /N %s /P %s"),strPath,strUser,strPassword);
			// необязательный параметр, значение NO_SPLASH_SHOW - не показывать заставку при загрузке 1С
			CString strEmpty="NO_SPLASH_SHOW";
			// параметры вызова метода Initialize
			parms=(BYTE*)(VTS_I4 VTS_BSTR VTS_BSTR);
			drvApp.InvokeHelper(id_init,DISPATCH_METHOD,VT_BOOL,&init,parms,RMTrade,(void*)(LPCTSTR)strCommand,(void*)(LPCTSTR)strEmpty);
			if(init==FALSE)
			{
				AfxMessageBox(_T("База не загружена"),MB_ICONSTOP|MB_TOPMOST | MB_SETFOREGROUND | MB_OK);

				return FALSE;
			}
 

			return TRUE;
		}
		return FALSE;
	
}
/*Функция ФормироватьДокументОтчетККМ(НомДок,ДатаДок,ВремяДок,КодТочки,КодПродавца,КодПокупателя)
	перем дбф,докОтчетККМ,спрТочки,спрПродавцы,спрПокупатели,спрВалюты,флаг,сЗначВремя;
	
	дбф=СоздатьОбъект("XBase");
	докОтчетККМ=СоздатьОбъект("Документ.ОтчетККМ");
	
	Если докОтчетККМ.НайтиПоНомеру(НомДок,ДатаДок)=0 Тогда
		
		спрТочки=СоздатьОбъект("Справочник.Точки");
		спрПродавцы=СоздатьОбъект("Справочник.Работники");
		спрПокупатели=СоздатьОбъект("Справочник.Контрагенты");
		спрВалюты=СоздатьОбъект("Справочник.Валюты");
		спрНоменклатура=СоздатьОбъект("Справочник.Номенклатура");
		сЗначВремя=СоздатьОбъект("СписокЗначений");
		флаг=0;
		
		Если спрТочки.НайтиПоКоду(КодТочки,0)=0 Тогда
			Сообщить("Точка с Кодом: "+ КодТочки+ "  не найдена","!!!");
			Возврат 0;
		КонецЕсли;
		Если 	спрПродавцы.НайтиПоКоду(КодПродавца,0)=0 Тогда
			Сообщить("Продавец с Кодом: "+ КодПродавца+ "  не найден","!!!");
			Возврат 0;
		КонецЕсли;
		Если спрПокупатели.НайтиПоКоду(КодПокупателя,0)=0 Тогда
			Сообщить("Покупатель с Кодом: "+ КодПокупателя+ "  не найден","!!!");
			Возврат 0;
		КонецЕсли; 
		Если спрВалюты.НайтиПоКоду("810",0)=0 Тогда
			Сообщить("Валюта с Кодом: 810  не найдена","!!!");
			Возврат 0;
		КонецЕсли;
		
		сЗначВремя.ДобавитьЗначение("Часы",0);
		сЗначВремя.ДобавитьЗначение("Минуты",0);
		сЗначВремя.ДобавитьЗначение("Секунды",0);
		РазобратьСтрВремя(ВремяДок,":",сЗначВремя);
		Час=0;
		Минута=0;
		Секунда=0;
		Час=сЗначВремя.Получить("Часы");
		Минута=сЗначВремя.Получить("Минуты");
		Секунда=сЗначВремя.Получить("Секунды");
		
		дбф.ОткрытьФайл(КатРазАрх+"\TZREPIMP.DBF");
		Если дбф.Открыта()=0 Тогда
			Предупреждение("Не удалось открыть файл таблицы Отчетов по кассе");
			Возврат 0;
		КонецЕсли;
		дбф.КодоваяСтраница(0);
		дбф.Первая();
		дбф.ПоказыватьУдаленные(0);
		
		докОтчетККМ.Новый();
		докОтчетККМ.НомерДок=НомДок;
		докОтчетККМ.ДатаДок=ДатаДок;
		докОтчетККМ.АвтоВремяОтключить();
		докОтчетККМ.УстановитьВремя(Час,Минута,Секунда);
		докОтчетККМ.Точка=спрТочки.ТекущийЭлемент();
		докОтчетККМ.Продавец=спрПродавцы.ТекущийЭлемент();
		докОтчетККМ.Покупатель=спрПокупатели.ТекущийЭлемент();
		докОтчетККМ.Валюта=спрВалюты.ТекущийЭлемент(); 
		спрВалюты.ИспользоватьДату(ДатаДок);
		докОтчетККМ.Курс=спрВалюты.Курс;
		докОтчетККМ.ТипЦен=спрТочки.ТипЦен;
		докОтчетККМ.УчитыватьНДС=1;
		докОтчетККМ.СуммаВклНДС=1;
		докОтчетККМ.УчитыватьНП=0;
		докОтчетККМ.СуммаВклНП=0;
		Пока дбф.ВКонце()=0 Цикл
			Если дбф.docid=НомДок Тогда
				флаг=1;
				докОтчетККМ.НоваяСтрока();
				Если спрНоменклатура.НайтиПоКоду(дбф.nomenid,0)=1 Тогда
					докОтчетККМ.Номенклатура=спрНоменклатура.ТекущийЭлемент();
					докОтчетККМ.Количество=дбф.qty;
					докОтчетККМ.ЕдИзмерения=спрНоменклатура.ЕдиницаИзмерения;
					докОтчетККМ.Цена=дбф.price;
					докОтчетККМ.Сумма=дбф.qty*дбф.price;
					докОтчетККМ.НомерЧека=дбф.checkid;
					докОтчетККМ.ВремяЧека=дбф.checktime;
					докОтчетККМ.ВидМатериальногоРесурса = спрНоменклатура.ВидМатериальногоРесурса;
				    докОтчетККМ.ВидДеятельности=спрНоменклатура.ВидДеятельности;
					докОтчетККМ.ДокументПоступления=ПолучитьПустоеЗначение();
				КонецЕсли;
				//Сообщить(ДатаДок);
				//Сообщить(дбф.docid+ "  |  " + дбф.checkid + "  |  " + дбф.nomenid + "  |  "+ Строка(дбф.qty) + "  |  "+ Строка(дбф.price) + "  |  "+ Строка(дбф.checkdate) + "  |  " + Строка(дбф.checktime) );
				//Сообщить(дбф.checktime);
			КонецЕсли; 
			дбф.Следующая();
		КонецЦикла;
		если флаг=1 тогда
			докОтчетККМ.Записать();
		конецесли;
		дбф.ЗакрытьФайл();
	Иначе
		Сообщить("Документ с Номером: "+ НомДок+ "  существует","!!!");
		
	КонецЕсли;
КонецФункции*/
BOOL C1CHelper::SaveZReportIn1C(const CString& strNumDoc,  const COleDateTime& tmTimeDoc,
								const CString& strNumPoint,const CString& strEmpl,
								const CString& strCust,    VARIANT* vtArray)
{
	//Уф помолясь!!!!
	
	
    // находим ID метода CreateObject
	BYTE *parms;
	
	
		CComBSTR name=_T("CreateObject");
		DISPID id_create=0;
		HRESULT    hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_create);
		
		// указатель на объект, который надо получить
		IDispatch *pZRT=NULL;
		// параметры вызова метода CreateObject
		parms=(BYTE*)(VTS_BSTR);
		// имя объекта
		CString strZRT="Документ.ОтчетККМ";
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pZRT,parms,(void*)(LPCTSTR)strZRT);
		if(pZRT==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}
		
		COleDispatchDriver drvZRT;
		drvZRT.AttachDispatch(pZRT);
		// drvZRT - и есть наш Документ ОтчетККМ
		//докОтчетККМ=СоздатьОбъект("Документ.ОтчетККМ");
		//Если докОтчетККМ.НайтиПоНомеру(НомДок,ДатаДок)=0 Тогда
		//Дата для поиска 0 для поиска во всем диапазоне
		COleDateTime tmNow=COleDateTime::GetCurrentTime();
		
		CString strExpr=_T("");
		strExpr.Format (_T("Date('01/01/%d')"),tmNow.GetYear ());
		name=_T("EvalExpr");
		DISPID id_Eval=0;
		hr=drvApp.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Eval);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR );
		CString pDate;
		drvApp.InvokeHelper(id_Eval,DISPATCH_METHOD,VT_BSTR,&pDate,parms,(void*)(LPCTSTR)strExpr);

		name="НайтиПоНомеру";
		DISPID id_Find=0;
		hr=drvZRT.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Find);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR VTS_BSTR VTS_BSTR);
		BOOL  ret;

		drvZRT.InvokeHelper (id_Find,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strNumDoc,(void*)(LPCTSTR)pDate,_bstr_t(L"ОтчетККМ"));
		if(ret)
		{
			AfxMessageBox(_T("Документ с таким номером уже существует"),MB_ICONSTOP);
			return FALSE;
		}
		return TRUE;
	
}
/*******************************************    
Функция ПодготовитьЧек(Точка,Касса,ДокЧек,НомерЧека) 
	перем Склад,Валюта,Курс,Кратность,Получено;

	Кузя=СоздатьОбъект("Справочник.Пользователи");
	Если Кузя.НайтиПоНаименованию(ИмяПользователя(),0)=1   Тогда 
	докчек.Фирма=Кузя.ОсновнаяФирма;
	докЧек.Автор=Кузя.Текущийэлемент();
КонецЕсли;

	спрТочка=СоздатьОбъект("Справочник.ТорговыеТочки");
	Если спрТочка.НайтиПоКоду(Точка,0)=1 Тогда 
		докЧек.Склад=спрТочка.ТекущийЭлемент().Склад;
		докЧек.Касса=спрТочка.ТекущийЭлемент().ОсновнаяКасса;  
	КонецЕсли;
	Валюта=СоздатьОбъект("Справочник.Валюты");
	Если Валюта.НайтиПОНаименованию("руб",0)=1  Тогда
		докЧек.Валюта=Валюта.ТекущийЭлемент();
		докЧек.Курс=1;
		докЧек.Кратность=1;
		докЧек.Получено=0;
	КонецЕсли;
    докЧек.ВидОперации=Перечисление.ВидыОперацийЧекККМ.Чек;
	докЧек.НомерЧекаККМ=НомерЧека;
	докЧек.ЧекПробитККМ=0;
	докЧек.Скидка=ПолучитьПустоеЗначение();
	докЧек.ДокОснование=ПолучитьПустоеЗначение();
	Возврат 1;
КонецФункции 

Функция ПолучитьТовар(ШтрихКод,ВремТовар,ВремЕдиница)
	Рез = 0;
	
	СпрЕдиницы = СоздатьОбъект("Справочник.Единицы");
	СпрТовар   = СоздатьОбъект("Справочник.Номенклатура");
	Если СпрЕдиницы.НайтиПоРеквизиту("Штрихкод", ШтрихКод, 1) = 1 Тогда
		ВремТовар	= СпрЕдиницы.Владелец;
		ВремЕдиница	= СпрЕдиницы.ТекущийЭлемент();
		Рез         = 1;

	КонецЕсли;	
    
	Возврат Рез;
КонецФункции // ПолучитьТовар()



Процедура Сформировать()
	перем ДокЧек,ВремТовар,ВремЕдиница;
     ШтрихКод= "9785845901224";
	докЧек=СоздатьОбъект("Документ.ЧекККМ");
	ПрефДок = ТекущаяИБКод();
	докЧек.ПрефиксНомера(ПрефДок);
	докЧек.Новый();

	ПодготовитьЧек(1,"C0004",докЧек,123456);
	
	ДокЧек.НоваяСтрока();
	Если ПолучитьТовар(СокрЛП(ШтрихКод), ВремТовар, ВремЕдиница) = 1 Тогда
			ДокЧек.Номенклатура = ВремТовар;
			ДокЧек.ШтрихКод=ШтрихКод;
			ДокЧек.Единица      = ВремЕдиница;
			ДокЧек.Коэффициент  = ВремЕдиница.Коэффициент;
			ДокЧек.Цена=140;
			ДокЧек.Сумма=140;
			ДокЧек.Количество=1;
			ДокЧек.Записать();
            ДокЧек.Провести();
		Иначе
			Предупреждение("Товар со штрих-кодом "+СокрЛП(ШтрихКод)+" не найден!", 60);
		
		КонецЕсли


	
КонецПроцедуры
 *************************************************************************************/
BOOL C1CHelper::SaveCheckIn1C(const CString &strPointName, const CString &strUser, int nCheckNum,VARIANT* vtArray)
{
	//Подготовить чек
	AfxGetApp()->BeginWaitCursor ();
		BYTE *parms;
	//*докЧек=СоздатьОбъект("Документ.ЧекККМ");
		COleException e ;
  
  try {

		CComBSTR name=_T("CreateObject");
		DISPID id_create=0;
		HRESULT    hr=drvApp.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_create);
		TESTHR(hr);
		// указатель на объект, который надо получить
		IDispatch *pDocCheck=NULL;
		// параметры вызова метода CreateObject
		parms=(BYTE*)(VTS_BSTR);
		// имя объектаCString strZRT="Документ.ОтчетККМ";
		CString strDocCheck=_T("Документ.ЧекККМ");
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pDocCheck,parms,(void*)(LPCTSTR)strDocCheck);
		
		if(pDocCheck==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			
			
			return FALSE;
		}
		COleDispatchDriver drvDocCheck;
		drvDocCheck.AttachDispatch(pDocCheck);
	
	//*ПрефДок = ТекущаяИБКод()**********************************************************************
		name=_T("EvalExpr");
		DISPID id_Eval=0;
		hr=drvApp.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Eval);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR );
		CString strPrefixDoc;
		CString strExpr=_T("ТекущаяИБКод()");
		drvApp.InvokeHelper(id_Eval,DISPATCH_METHOD,VT_BSTR,&strPrefixDoc,parms,(void*)(LPCTSTR)strExpr);

	//** докЧек.ПрефиксНомера(ПрефДок)***************************************************************
		name=_T("ПрефиксНомера");
		DISPID id_Prefix=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Prefix);
		TESTHR(hr);
		parms=(BYTE*)(VTS_BSTR );
		CString strPrefixBefore;
		strPrefixDoc.TrimRight ();
		drvDocCheck.InvokeHelper(id_Prefix,DISPATCH_METHOD,VT_BSTR,&strPrefixBefore,parms,(void*)(LPCTSTR)strPrefixDoc);
//*  докЧек.АвтоВремяТекущее();****************************************************************************
		name=_T("АвтоВремяТекущее");
		DISPID id_AutoTime=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_AutoTime);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_AutoTime,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
    //*  докЧек.Новый();****************************************************************************
		name=_T("Новый");
		DISPID id_New=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_New);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_New,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);

	//***Кузя=СоздатьОбъект("Справочник.Пользователи");

		CString strUSR=_T("Справочник.Пользователи");
		IDispatch *pUSR=NULL;
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pUSR,parms,(void*)(LPCTSTR)strUSR);
		
		if(pUSR==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}
	
		COleDispatchDriver drvUSR;
		drvUSR.AttachDispatch(pUSR);
	//**Если Кузя.НайтиПоНаименованию(ИмяПользователя(),0)=0   Тогда Возврат;
		name=_T("НайтиПоКоду");
		DISPID id_FindByName=0;
		hr=drvUSR.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_FindByName);
		BOOL ret=FALSE;
		parms=(BYTE*)(VTS_BSTR VTS_I4);
		int nFlag=0;
		
		drvUSR.InvokeHelper(id_FindByName,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strUser,nFlag);
		if(!ret)
			return FALSE;

	//**докчек.Фирма=Кузя.ОсновнаяФирма;
		//Сначала получим свойство ОсновнаяФирма у Кузи
		name=_T("ОсновнаяФирма");
		DISPID id_BaseFirma=0;
		hr=drvUSR.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_BaseFirma);
	 	TESTHR(hr);
		IDispatch *pBaseFirma=NULL;//свойство ОсновнаяФирма у Кузи
		drvUSR.GetProperty(id_BaseFirma,VT_DISPATCH,(void*)&pBaseFirma);
		COleDispatchDriver drvFirma;
		drvFirma.AttachDispatch(pBaseFirma);
		//Теперь установим свойство фирма для документа
		name=_T("Фирма");
		_variant_t vt;
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pBaseFirma;
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
		
		/*DISPID id_Firma=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Firma);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_Firma,VT_DISPATCH,(LPDISPATCH)drvFirma);//докчек.Фирма=Кузя.ОсновнаяФирма;
	*/
	//*докЧек.Автор=Кузя.Текущийэлемент();
			name=_T("Текущийэлемент");

		DISPID id_current=0;
		hr=drvUSR.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_current);
		TESTHR(hr);
		// указатель на объект, который надо получить
		IDispatch *pCurUser=NULL;
	
		
		drvUSR.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurUser,NULL,NULL);
		
		if(pCurUser==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}
		name=_T("Автор");
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pCurUser;

	/*	DISPID id_Avtor=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Avtor);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_Avtor,VT_DISPATCH,drvUSR.m_lpDispatch );//докЧек.Автор=Кузя.Текущийэлемент();
*/
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
			
	//*спрТочка=СоздатьОбъект("Справочник.ТорговыеТочки");
		CString strPoints=_T("Справочник.ТорговыеТочки");
		IDispatch *pPoints=NULL;
		parms=(BYTE*)(VTS_BSTR );
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pPoints,parms,(void*)(LPCTSTR)strPoints);
		
		if(pPoints==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}
	
		COleDispatchDriver drvPoints;
		drvPoints.AttachDispatch(pPoints);

	
	//*Если спрТочка.НайтиПоКоду(Точка,0)=1 Тогда
		name=_T("НайтиПоНаименованию");
		DISPID id_FindByCode=0;
		hr=drvPoints.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_FindByCode);
		ret=FALSE;
		parms=(BYTE*)(VTS_BSTR VTS_I4);
		nFlag=0;
		CString		strPName=strPointName;
		strPName.TrimRight ();
		drvPoints.InvokeHelper(id_FindByCode,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strPName,nFlag);
		if(!ret)
			return FALSE;

	//*докЧек.Склад=спрТочка.Склад;
		//Сначала получим свойство Склад у точки
		name=_T("Склад");
		DISPID id_StockGet=0;
		hr=drvPoints.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_StockGet);
	 	TESTHR(hr);
		IDispatch *pStockProp=NULL;//свойство свойство Склад у точки
		drvPoints.GetProperty(id_StockGet,VT_DISPATCH,(void*)&pStockProp);
		//Теперь установим свойство Склад для документа
		name=_T("Склад");
		/*
		DISPID id_StockSet=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_StockSet);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_StockSet,VT_DISPATCH,pStockProp);//докЧек.Склад=спрТочка.Склад;
		*/
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pStockProp;
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
	//*докЧек.Касса=спрТочка.ОсновнаяКасса;  
		//Сначала получим свойство Касса у точки
	
		name=_T("ОсновнаяКасса");
		DISPID id_CashGet=0;
		hr=drvPoints.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CashGet);
	 	TESTHR(hr);
		IDispatch *pCashProp=NULL;//свойство Касса у точки
		drvPoints.GetProperty(id_CashGet,VT_DISPATCH,(void*)&pCashProp);
		//Теперь установим свойство Касса для документа
		name=_T("Касса");
		/*
		DISPID id_CashSet=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CashSet);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_CashSet,VT_DISPATCH,pCashProp);//докЧек.Касса=спрТочка.ОсновнаяКасса; 
*/
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pCashProp;
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
	
	//*Валюта=СоздатьОбъект("Справочник.Валюты");
		CString strCurr=_T("Справочник.Валюты");
		IDispatch *pCurr=NULL;
		parms=(BYTE*)(VTS_BSTR );
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pCurr,parms,(void*)(LPCTSTR)strCurr);
		
		if(pCurr==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}
	
		COleDispatchDriver drvCurrs;
		drvCurrs.AttachDispatch(pCurr);

	
	//*Если Валюта.НайтиПОНаименованию("руб",0)=1
		name=_T("НайтиПоНаименованию");
		DISPID id_CurrFindByName=0;
		hr=drvCurrs.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CurrFindByName);
		ret=FALSE;
		parms=(BYTE*)(VTS_BSTR VTS_I4);
		nFlag=0;
		CString strCurrName=_T("руб");
		drvCurrs.InvokeHelper(id_FindByCode,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strCurrName,nFlag);
		if(!ret)
			return FALSE;

	//*докЧек.Валюта=Валюта.ТекущийЭлемент();

		name=_T("Текущийэлемент");

		id_current=0;
		hr=drvCurrs.m_lpDispatch->GetIDsOfNames(IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_current);
		TESTHR(hr);
		// указатель на объект, который надо получить
		IDispatch *pCurValuta=NULL;
	
		
		drvCurrs.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurValuta,NULL,NULL);
		
		if(pCurValuta==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}

		name=_T("Валюта");
		/*
		DISPID id_CurrSet=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CurrSet);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_CurrSet,VT_DISPATCH,drvCurrs.m_lpDispatch );//докЧек.Валюта=Валюта.ТекущийЭлемент();
*/
		vt.vt =VT_DISPATCH;
		vt.pdispVal= pCurValuta;
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vt))
			return FALSE;
	
	//*докЧек.Курс=1;
		name=_T("Курс");
		DISPID id_Curs=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Curs);
	 	TESTHR(hr);
		int nKurs=1;
		drvDocCheck.SetProperty(id_Curs,VT_I4,nKurs );

	//*докЧек.Кратность=1;
		name=_T("Кратность");
		DISPID id_Kratnost=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Kratnost);
	 	TESTHR(hr);
		int nKratnost=1;
		drvDocCheck.SetProperty(id_Kratnost,VT_I4,nKratnost );

	//*докЧек.Получено=0;
		name=_T("Получено");
		DISPID id_Nal=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Nal);
	 	TESTHR(hr);
		double dblNal=0.0;
		drvDocCheck.SetProperty(id_Nal,VT_R8,dblNal );

	//*докЧек.ВидОперации=Перечисление.ВидыОперацийЧекККМ.Чек;
		_variant_t vtCheck;
		strExpr=_T("Перечисление.ВидыОперацийЧекККМ.Чек");
		parms=(BYTE*)(VTS_BSTR);
		drvApp.InvokeHelper(id_Eval,DISPATCH_METHOD,VT_VARIANT,&vtCheck,parms,(void*)(LPCTSTR)strExpr);

		name=_T("ВидОперации");
		DISPID id_VidOper=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_VidOper);
	 	TESTHR(hr);
		if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,name,vtCheck))
			return FALSE;

	//*докЧек.НомерЧекаККМ=НомерЧека;
		name=_T("НомерЧекаККМ");
		DISPID id_NomCheck=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_NomCheck);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_NomCheck,VT_I4,nCheckNum);

	//*докЧек.ЧекПробитККМ=0;
		name=_T("ЧекПробитККМ");
		DISPID id_CheckKKM=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_CheckKKM);
	 	TESTHR(hr);
		drvDocCheck.SetProperty(id_CheckKKM,VT_I4,0);

	
		//*СпрЕдиницы = СоздатьОбъект("Справочник.Единицы");
		CString strUnits=_T("Справочник.Единицы");
		parms=(BYTE*)(VTS_BSTR);
		IDispatch *pUnits=NULL;
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pUnits,parms,(void*)(LPCTSTR)strUnits);
		if(pUnits==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}
		COleDispatchDriver drvUnits;
		drvUnits.AttachDispatch(pUnits);

	//*	СпрТовар   = СоздатьОбъект("Справочник.Номенклатура");
		CString strTovary=_T("Справочник.Номенклатура");
		parms=(BYTE*)(VTS_BSTR);
		IDispatch *pGoods=NULL;
		drvApp.InvokeHelper(id_create,DISPATCH_METHOD,VT_DISPATCH,&pGoods,parms,(void*)(LPCTSTR)strTovary);
		if(pGoods==NULL)
		{
			TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
			return FALSE;
		}
		COleDispatchDriver drvGoods;
		drvGoods.AttachDispatch(pGoods);

		//*чешем по таблице ищем по коду

		COleSafeArray sa;
		sa.Attach (*vtArray);
		//sa.Attach (vtArray);
		long lNumRows;
		long lNumCols;
		sa.GetUBound(1, &lNumRows);
		sa.GetUBound(2, &lNumCols);
		
		//Display the elements in the SAFEARRAY.
		long index[2];
	
		
		//Determine upper bounds for both dimensions
		long r, c;
		sa.GetLBound(1, &r);
		sa.GetLBound(2, &c);
		
		for(;r <= lNumRows; r++ )
		{
			_variant_t val;
			CComBSTR bstrMethod;
			//*ДокЧек.НоваяСтрока();
			name=_T("НоваяСтрока");
			DISPID id_NewLine=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_NewLine);
			TESTHR(hr);
			drvDocCheck.InvokeHelper(id_NewLine,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
			
			
			index[0]=r;
			index[1]=lNumCols;
			sa.GetElement(index, &val);//код товара
			//*Если СпрТовар.НайтиПоКоду(Код, 0) = 1 Тогда
			bstrMethod=_T("НайтиПоКоду");
			DISPID id_FindByCode=0;
			HRESULT hr=drvGoods.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_FindByCode);
			BOOL ret=FALSE;
			BYTE* parms=(BYTE*)(VTS_BSTR VTS_I4);
			nFlag=0;
			CString		strCode=(LPCTSTR)(_bstr_t)val;
			strCode.TrimRight ();
			drvGoods.InvokeHelper(id_FindByCode,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strCode,nFlag);
			if(!ret)
			{
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				AfxThrowOleDispatchException(1001, 
					_T("Не нашли товар по коду"));
				
			}
			//::VariantClear(&val);//не надо больше

			//*ДокЧек.Номенклатура = СпрТовар.ТекущийЭлемент()
			bstrMethod=_T("Текущийэлемент");

			DISPID id_current=0;
			hr=drvGoods.m_lpDispatch->GetIDsOfNames(IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_current);
			TESTHR(hr);
			// указатель на объект, который надо получить
			IDispatch *pCurGood=NULL;
			drvGoods.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurGood,NULL,NULL);
			if(pCurGood==NULL)
			{
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				TRACE0("ОБЪЕКТ НЕ НАЙДЕН\n");
				return FALSE;
			}
		
			bstrMethod=_T("Номенклатура");
			_variant_t vt;
			vt.vt =VT_DISPATCH;
			vt.pdispVal= pCurGood ;
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,bstrMethod,vt))
				return FALSE;

		//*ДокЧек.ШтрихКод=ШтрихКод;
			CString strBarCode=_T("");
			index[1]=0L;
			sa.GetElement (index,&val);
			CComBSTR bstrBarcode;
			hr=::VarBstrFromR8(val.dblVal,LOCALE_SYSTEM_DEFAULT,LOCALE_NOUSEROVERRIDE,&bstrBarcode);
			if (hr)
				AfxThrowOleDispatchException(1001, 
				_T("Ytghfdbkmyj ds,hfy byltrc vfccbdb BarCode не строка"));
			strBarCode=(LPCTSTR)(_bstr_t)bstrBarcode;
			int nPos=strBarCode.FindOneOf (_T(",."));
			if(nPos!=-1)
			{
			strBarCode.Remove ('.');
			strBarCode.Remove (',');
			}
			if(strBarCode.GetLength ()<13)
			{
				int append=13-strBarCode.GetLength ();
				for(int i=0;i<append;i++)
					strBarCode.Insert (i,_T("0"));
			}
			bstrMethod=_T("ШтрихКод");
			DISPID id_BarCode=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_BarCode);
	 		TESTHR(hr);
			drvDocCheck.SetProperty(id_BarCode,VT_BSTR,(void*)(LPCTSTR)strBarCode );
		
		//*Если СпрЕдиницы.НайтиПоРеквизиту("Штрихкод", ШтрихКод, 1) = 1 Тогда
			bstrMethod=_T("НайтиПоРеквизиту");
			DISPID id_FindByAttribute=0;
			hr=drvUnits.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_FindByAttribute);
	 		if(hr!=S_OK)
			{		//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
					AfxThrowOleDispatchException(1001, 
					_T("НайтиПоРеквизиту"));
			}
			ret=FALSE;
			parms=(BYTE*)(VTS_BSTR VTS_BSTR VTS_I4);
			nFlag=1;
			CString strParamether=_T("Штрихкод");
			strBarCode.TrimRight ();
			
			drvUnits.InvokeHelper(id_FindByAttribute,DISPATCH_METHOD,VT_BOOL,&ret,parms,(void*)(LPCTSTR)strParamether,(void*)(LPCTSTR)strBarCode,nFlag);
			if(!ret)
			{
					//pCurGood->Release  ();
				CString msg;
				msg.Format (_T(" Товар на позиции %d с штрихкодом %s не имеет атрибут штрихкод.\nУдалите его и перепроведите чек."),r+1,strBarCode);
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				AfxThrowOleDispatchException(10010, 
				msg);
			}

			bstrMethod=_T("Текущийэлемент");

			id_current=0;
			hr=drvUnits.m_lpDispatch->GetIDsOfNames(IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_current);
			TESTHR(hr);
			// указатель на объект, который надо получить
			IDispatch *pCurUnit=NULL;
			drvUnits.InvokeHelper(id_current,DISPATCH_METHOD,VT_DISPATCH,&pCurUnit,NULL,NULL);
			if(pCurUnit==NULL)
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
			AfxThrowOleDispatchException(1001, 
					_T("ОБЪЕКТ НЕ НАЙДЕН"));
			}
				
		
			/*COleDispatchDriver drvBaseUnit;
			drvBaseUnit.AttachDispatch(pBaseUnit);*/
			bstrMethod=_T("Единица");
			vt.vt =VT_DISPATCH;
			vt.pdispVal= pCurUnit;
			if(!SetPropertyValue(drvDocCheck.m_lpDispatch ,bstrMethod,vt))
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
				AfxThrowOleDispatchException(1001, 
					_T("Товар.БазоваяЕдиница не установился"));
			}

		//*ДокЧек.Коэффициент  = Товар.БазоваяЕдиница.Коэффициент;
			bstrMethod=_T("Коэффициент");
			DISPID id_Coeff=0;
			hr=pCurUnit ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Coeff);
	 		if(hr!=S_OK)
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
					AfxThrowOleDispatchException(1001, 
					_T("БазоваяЕдиница.Коэффициент;"));
			}
			int nCoeff=1;
			//drvBaseUnit.GetProperty(id_Coeff,VT_I4,(void*)&nCoeff);

			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Coeff);
	 		if(hr!=S_OK)
			{
					//pCurGood->Release  ();
					pCashProp->Release ();
					pStockProp->Release ();
					pCurUser->Release ();
					*vtArray=sa.Detach ();
					AfxThrowOleDispatchException(1001, 
					_T("ДокЧек.Коэффициент;"));
			}
			drvDocCheck.SetProperty(id_Coeff,VT_I4,nCoeff);

		//*	ДокЧек.Количество=Kol;
			bstrMethod=_T("Количество");
			DISPID id_Qty=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Qty);
	 		TESTHR(hr);
			double dblQty=0L;
			index[1]=4L;
			sa.GetElement(index, &val);
			dblQty=val.dblVal ;
			//::VariantClear(&val);
			drvDocCheck.SetProperty(id_Qty,VT_R8,dblQty);


		//*	ДокЧек.Цена=140;
			double dblPrice=0.0;
			index[1]=2L;
			sa.GetElement(index, &val);
			dblPrice=val.dblVal;
			//::VariantClear(&val);
			bstrMethod=_T("Цена");
			DISPID id_Price=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Price);
	 		TESTHR(hr);
			drvDocCheck.SetProperty(id_Price,VT_R8,dblPrice);

		//*ДокЧек.Сумма=140;
			double dblSumma=dblPrice*dblQty;
			
			bstrMethod=_T("Сумма");
			DISPID id_Summa=0;
			hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&bstrMethod,1,LOCALE_SYSTEM_DEFAULT,&id_Summa);
	 		TESTHR(hr);
			drvDocCheck.SetProperty(id_Summa,VT_R8,dblSumma);
		
			pCurGood->Release  ();
		}	

	//*ДокЧек.Записать();
		

		name=_T("Записать");
		DISPID id_Save=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Save);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_Save,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
		
		/**/name=_T("Провести");
		DISPID id_Transact=0;
		hr=drvDocCheck.m_lpDispatch ->GetIDsOfNames (IID_NULL,&name,1,LOCALE_SYSTEM_DEFAULT,&id_Transact);
		TESTHR(hr);
		drvDocCheck.InvokeHelper(id_Transact,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	//	pCurUnit->Release ();
		//pCurValuta->Release ();
		pCashProp->Release ();
		pStockProp->Release ();
		pCurUser->Release ();
		*vtArray=sa.Detach ();
		AfxGetApp()->EndWaitCursor ();
		return TRUE;
	}
   
  //Catch control-specific exceptions.
   catch (COleDispatchException * e) 
  {
    CString cStr;

    if (!e->m_strSource.IsEmpty())
      cStr = e->m_strSource + " - ";
    if (!e->m_strDescription.IsEmpty())
      cStr += e->m_strDescription;
    else
      cStr += "unknown error";

    AfxMessageBox(cStr, MB_OK, 
      (e->m_strHelpFile.IsEmpty())? 0:e->m_dwHelpContext);

    e->Delete();
	return FALSE;
  }
  //Catch all MFC exceptions, including COleExceptions.
  // OS exceptions will not be caught.
   catch (CException *e) 
  {
    TRACE(_T("%s(%d): OLE Execption caught: SCODE = %x"), 
      __FILE__, __LINE__, COleException::Process(e));
    e->Delete();
	return FALSE;
  }



}
BOOL C1CHelper::SetPropertyValue(IDispatch* pDisp,BSTR strPropertyName, VARIANT vtValue)
{
  
  if ( !pDisp )
    return FALSE;

  DISPID dispid = 0;
  HRESULT hr = NULL;
  OLECHAR* name = strPropertyName;
  _variant_t vtRetval;

  vtRetval.vt = VT_EMPTY;

  hr = pDisp->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
  if ( FAILED(hr) )
  {
    MessageBoxHelper::ShowError(_T("FAILED to get DISPID"));
    return FALSE;
  }


  CComVariant varResult;

  VariantClear(&varResult);
  DISPPARAMS disp = { NULL, NULL, 0, 0 };
  DISPID dispidNamed = DISPID_PROPERTYPUT;
  
  disp.cArgs = 1;
  disp.rgvarg = &vtValue;
  disp.cNamedArgs = 1;
  disp.rgdispidNamedArgs = &dispidNamed;


  hr = pDisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT | DISPATCH_METHOD, &disp, NULL, NULL, NULL);
  if ( FAILED(hr) )
  {
    MessageBoxHelper::ShowError(_T("FAILED to Invoke Method"));
    return FALSE;
  }  


  return TRUE;
}