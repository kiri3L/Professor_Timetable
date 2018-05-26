// Professor_Dlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MFC_Cursach.h"
#include "Professor_Dlg.h"
#include "NewNameTeacher.h"
#include "afxdialogex.h"

#include <vector>
#include "ExcelWriter.h"
#include "start.hpp"


// диалоговое окно Professor_Dlg

IMPLEMENT_DYNAMIC(Professor_Dlg, CDialog)

Professor_Dlg::Professor_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PROFESSOR_LIST_DIALOG, pParent)
{
}

Professor_Dlg::~Professor_Dlg()
{
}

void Professor_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROFESSOR, professor_list);
}


BEGIN_MESSAGE_MAP(Professor_Dlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_PROFESSOR_SELECT, &Professor_Dlg::OnBnClickedBtnProfessorSelect)
	ON_BN_CLICKED(IDC_BTN_EDIT_PROFESSOR_LIST, &Professor_Dlg::OnBnClickedBtnEditProfessorList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROFESSOR, &Professor_Dlg::OnNMClickListProfessor)
	ON_BN_CLICKED(IDC_BTN_HELP, &Professor_Dlg::OnBnClickedBtnHelp)
END_MESSAGE_MAP()

BOOL Professor_Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	professor_list.InsertColumn(0, L" ФИО преподавателей ", LVCFMT_LEFT, 200);
	professor_list.InsertColumn(1, L" ", LVCFMT_LEFT, 200);
	// получаем славины объекты переводим их в CString и вставляем их
	int all = theApp.data->professors.size();
	for (int i = 0; i < all; i++)
	{
		std::string slavinObjectName = theApp.data->professors[i]->getName();
		CString name;
		name = slavinObjectName.c_str();	
		professor_list.InsertItem(0, name);
	}
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// обработчики сообщений Professor_Dlg


void Professor_Dlg::OnBnClickedBtnProfessorSelect()
{
	std::vector <std::string> listProfs;
	int item_c = professor_list.GetItemCount();
	for (int i = 0; i < item_c; i++)
	{
		if (professor_list.GetItemText(i, 1) == L"ВЫБРАН")
		{
			CString profName = professor_list.GetItemText(i, 0);
			CT2CA tmp(profName);
			std::string s(tmp);
			listProfs.push_back(s);
		}
	}
	if (listProfs.empty())
		MessageBox(L"Не выбран ни один преподаватель", L" ", MB_OK | MB_ICONERROR);
	else
	{
		ExcelWriter* write = new ExcelWriter("C:\\Users\\Public\\Созданный excel.xlsx", theApp.pApp); //это путь по умолчанию
		Start* st = new Start(listProfs);
		st->end(write, theApp.data);
		delete st;
		delete write;
	}
	int all = listProfs.size();
	for (int i = 0; i < all; i++) listProfs.pop_back();
}


void Professor_Dlg::OnBnClickedBtnEditProfessorList()
{
	std::vector <std::string> mergeProfs;
	int item_c = professor_list.GetItemCount();
	bool flag = false;
	for (int i = 0; i < item_c; i++)
	{
		if (professor_list.GetItemText(i, 1) == L"ВЫБРАН")
		{
			if (flag)
			{
				CString profName = professor_list.GetItemText(i, 0);
				CT2CA tmp(profName);
				std::string s(tmp);
				mergeProfs.push_back(s);
			}
			else
			{
				CString profName = professor_list.GetItemText(i, 0);
				CT2CA tmp(profName);
				std::string s(tmp);
				theApp.MergeName = professor_list.GetItemText(i, 0);
				mergeProfs.push_back(s);
				flag = true;
			}
		}
	}
	if (mergeProfs.size() <= 1)
		MessageBox(L"Не выбраны преподаватели или выбран только один",L"", MB_OK | MB_ICONERROR);	
	else
	{
		NewNameTeacher Name_dlg;
		Name_dlg.DoModal();
		if (theApp.MergeName != "")
		{
			Start* st = new Start(mergeProfs);
			st->uniteSt(theApp.data, mergeProfs, theApp.MergeName);
			//надо перерисовать профессоров
			professor_list.DeleteAllItems();
			// получаем славины объекты переводим их в CString и вставляем их
			int all = theApp.data->professors.size();
			for (int i = 0; i < all; i++)
			{
				std::string slavinObjectName = theApp.data->professors[i]->getName();
				CString name;
				name = slavinObjectName.c_str();
				professor_list.InsertItem(0, name);
			}
			delete st;
		}
		
	} 
	int all = mergeProfs.size();
	for (int i = 0; i < all; i++) mergeProfs.pop_back();
}


void Professor_Dlg::OnNMClickListProfessor(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	POSITION pos = professor_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	else
	{
		
		int item_ind = professor_list.GetNextSelectedItem(pos);
		
		if (professor_list.GetItemText(item_ind, 1) == L"ВЫБРАН")
		{
			professor_list.SetItemText(item_ind, 1, L"");
		}
		else
		{
			professor_list.SetItemText(item_ind, 1, L"ВЫБРАН");
		}
	}
	*pResult = 0;
}


void Professor_Dlg::OnBnClickedBtnHelp()
{
	CString help_messege;

	help_messege = L" Выберите преподавателей\n";
	help_messege += L" Кнопка соединить выбранных преподавателей позволит объединить их в одного и переназвать его.\n";
	help_messege += L" Нажав кнопку 'Вывести выбранных преподавателей' выберете место сохранения файла и подождите. После закрытия программы, вы можете открыть новый файл\n";
	MessageBox(help_messege, L"Помощь", MB_OK | MB_ICONINFORMATION);
}
