#pragma once
#include "afxcmn.h"


// диалоговое окно lesson_list_dlg

class lesson_list_dlg : public CDialogEx
{
	DECLARE_DYNAMIC(lesson_list_dlg)

public:
	lesson_list_dlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~lesson_list_dlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LESSONS_LIST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl lesson_list;
};
