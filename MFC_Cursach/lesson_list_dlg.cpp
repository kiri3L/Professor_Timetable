// lesson_list_dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MFC_Cursach.h"
#include "lesson_list_dlg.h"
#include "afxdialogex.h"


// диалоговое окно lesson_list_dlg

IMPLEMENT_DYNAMIC(lesson_list_dlg, CDialogEx)

lesson_list_dlg::lesson_list_dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LESSONS_LIST_DIALOG, pParent)
{

}

lesson_list_dlg::~lesson_list_dlg()
{
}

void lesson_list_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LESSON, lesson_list);

}


BEGIN_MESSAGE_MAP(lesson_list_dlg, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений lesson_list_dlg
