
// MFC_Cursach.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
#include "ExLab.h"
#include "data.hpp"


// CMFC_CursachApp:
// О реализации данного класса см. MFC_Cursach.cpp
//

class CMFC_CursachApp : public CWinApp
{
public:
	CMFC_CursachApp();
	Excel::_ApplicationPtr pApp;//АХТУНГ глобальная переменная без нёё совсем туго
	Data* data;
	CString MergeName;

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFC_CursachApp theApp;
