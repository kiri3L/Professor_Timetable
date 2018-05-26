// NewNameTeacher.cpp: файл реализации
//

#include "stdafx.h"
#include "MFC_Cursach.h"
#include "NewNameTeacher.h"
#include "afxdialogex.h"
#include "NewNameTeacher.h"

// диалоговое окно NewNameTeacher

IMPLEMENT_DYNAMIC(NewNameTeacher, CDialog)

NewNameTeacher::NewNameTeacher(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_MergeName, pParent)
	, CurrentName(_T(""))
{

}

NewNameTeacher::~NewNameTeacher()
{
}

void NewNameTeacher::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NewTeachName, CurrentName);
}


BEGIN_MESSAGE_MAP(NewNameTeacher, CDialog)
	ON_BN_CLICKED(IDC_BTN_ChangeName, &NewNameTeacher::OnBnClickedBtnChangename)
	ON_BN_CLICKED(IDC_BTN_CANSEL, &NewNameTeacher::OnBnClickedBtnCansel)
END_MESSAGE_MAP()

BOOL NewNameTeacher::OnInitDialog()
{
	CDialog::OnInitDialog();

	CurrentName = theApp.MergeName;
	UpdateData(false);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}
// обработчики сообщений NewNameTeacher


void NewNameTeacher::OnBnClickedBtnChangename()
{
	UpdateData(true);
	theApp.MergeName = CurrentName;
	OnOK();
}


void NewNameTeacher::OnBnClickedBtnCansel()
{
	theApp.MergeName = "";
	OnCancel();
}
