// Progress_dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MFC_Cursach.h"
#include "Progress_dlg.h"
#include "afxdialogex.h"


// Диалоговое окно Progress_dlg

IMPLEMENT_DYNAMIC(Progress_dlg, CDialog)

Progress_dlg::Progress_dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PROGRESS_DLG, pParent)
{

}

Progress_dlg::~Progress_dlg()
{
}

void Progress_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, progress);
}


BEGIN_MESSAGE_MAP(Progress_dlg, CDialog)
END_MESSAGE_MAP()


// Обработчики сообщений Progress_dlg
