
// MainDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "MFC_Cursach.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Professor_Dlg.h"
#include "Progress_dlg.h"
#include <string>
#include <vector>

#include "ExcelReader.h"
#include "ExLab.h"

#include "data.hpp"
#include "start.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно MainDlg



MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_CURSACH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PATH, path_list);
}

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_HELP, &MainDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_GET_FILE_NAME, &MainDlg::OnBnClickedBtnGetFileName)
	ON_BN_CLICKED(IDC_BTN_ADD_ALL_FILES, &MainDlg::OnBnClickedBtnAddAllFiles)
	ON_BN_CLICKED(IDC_BTN_DELETE, &MainDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// обработчики сообщений MainDlg

BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	HRESULT hRes = E_FAIL;
	CoInitialize(NULL);
	hRes = theApp.pApp.CreateInstance("Excel.Application");
	if (FAILED(hRes))
	{
		MessageBox( L"Excel не найден!", L"Ошибка", MB_OK);
		OnOK();
	}
	
	path_list.InsertColumn(0, L"Полное имя файла", LVCFMT_LEFT, 1000);
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void MainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//не настроил порядок табуляции, не привязал переменные к листконтролам, у диалога выбора преподавателя на большом экране не идет смещение для ОК и отмена
//

void MainDlg::OnBnClickedBtnHelp()
{
	CString help_messege;

	help_messege = L" Нажмите на \"Обзор\", чтобы выбрать файл.\n";
	help_messege += L" Выбранные вами файлы будут добалены в список.\n";
	help_messege += L" Убедитесь, что вы добавили все файлы.\n\n";
	help_messege += L" Если вы ошиблись с выбором файла, нажмите на его имя в\n";
	help_messege += L" списке, затем нажмите кнопку \"Удалить\".\n\n";
	help_messege += L" Все файлы должны иметь расширение \".xlsx\".\n\n";
	help_messege += L" После того, как вы добавили все необходимые файлы,\n";
	help_messege += L" нажмите на кнопку \"Загрузить файлы\" и подождите некоторое время. После обработки каждого файла будет выводится сообщение о прогрессе обработки\n\n";
	help_messege += L" Вы сможете вернуться в это меню\n";
	help_messege += L" если вам потребуется обработать еще файлы.\n\n";
	MessageBox(help_messege, L"Помощь", MB_OK | MB_ICONINFORMATION);
}


void MainDlg::OnBnClickedBtnGetFileName()
{
	CFileDialog f_dlg(TRUE);
	if (f_dlg.DoModal() == IDOK)
	{
		CString file_name;
		file_name = f_dlg.m_ofn.lpstrFile;
		if (CFileFind().FindFile(file_name) == TRUE)
		{
			if (file_name.Find(L".xlsx", 0) != -1)
			{
				LVFINDINFO info;
				info.flags = LVFI_PARTIAL | LVFI_STRING;
				info.psz = file_name;
				if (path_list.FindItem(&info, -1) == -1)
				{
					//MessageBox(L"фаил добавлен 1 раз", L"OK", MB_OK | MB_ICONINFORMATION);
					path_list.InsertItem(path_list.GetItemCount(), file_name, -1);
					//path_list.SetItemData()
				}
				else
				{
					MessageBox(L"фаил уже есть в списке", L"ERROR", MB_OK | MB_ICONERROR);
				}

			}
			else
			{
				MessageBox(L"фаил не .xlsx", L"ERROR", MB_OK | MB_ICONERROR);
			}
		}
		else
		{
			MessageBox(L"фаил не существует", L"ERROR", MB_OK | MB_ICONERROR);
		}
	}
}


void MainDlg::OnBnClickedBtnAddAllFiles()
{
	if (path_list.GetItemCount() == 0)
	{
		MessageBox(L"Список файлов пуст", L"Ошибка", MB_OK | MB_ICONERROR);
		return;
	}
	theApp.data = new Data;
	int fileNumb = 0;
	int all = path_list.GetItemCount();
	POSITION pos = path_list.GetFirstSelectedItemPosition();
	int index = path_list.GetNextSelectedItem(pos);
	//MessageBox(L"Начинаю считывать файлы", L"Загрузка", MB_OK | MB_ICONINFORMATION);
	Progress_dlg dlg;
	dlg.CreateIndirect();
	
	for (int i = 0; i < all; i++)
		{
		Start* starter = new Start;
		ExcelReader* fil = new ExcelReader(path_list.GetItemText(index + 1 + i, 0), theApp.pApp);
		if ( fil->getFlag() == 0 ) starter->start(fil, theApp.data);
		else
		{
			CString namefile;
			namefile = "Не удалось открыть файл";
			namefile += path_list.GetItemText(index + 1 + i, 0);		
			MessageBox(namefile, L"Ошибка", MB_OK | MB_ICONERROR);
		}
		delete fil;
		delete starter;
		//CString exit; 
		fileNumb++;
		//exit.Format(_T(" Я прочел  %d файлов из %d"), fileNumb, all); 
		//MessageBox(exit, L"Загрузка", MB_OK | MB_ICONINFORMATION);
		}
		Professor_Dlg Prof_dlg;
		Prof_dlg.DoModal();
		delete theApp.data;
	

}


void MainDlg::OnBnClickedBtnDelete()
{
	POSITION pos = path_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"Выберите файл, который хотите убрать из списка", L"", MB_OK);
	}
	else
	{
		int item_ind = path_list.GetNextSelectedItem(pos);
		CString temp_name = L"Вы уверены, что хотите удалить файл с именем\n "
			+ path_list.GetItemText(item_ind, -1);
		if (MessageBox(temp_name, L"Удалить из списка?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			path_list.DeleteItem(item_ind);
		}
	}
}
