
// MFC_Cursach.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include "ExLab.h"
#include "data.hpp"


// CMFC_CursachApp:
// � ���������� ������� ������ ��. MFC_Cursach.cpp
//

class CMFC_CursachApp : public CWinApp
{
public:
	CMFC_CursachApp();
	Excel::_ApplicationPtr pApp;//������ ���������� ���������� ��� � ������ ����
	Data* data;
	CString MergeName;

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CMFC_CursachApp theApp;
