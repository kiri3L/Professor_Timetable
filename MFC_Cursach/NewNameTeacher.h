#pragma once


// диалоговое окно NewNameTeacher

class NewNameTeacher : public CDialog
{
	DECLARE_DYNAMIC(NewNameTeacher)

public:
	NewNameTeacher(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~NewNameTeacher();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MergeName };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	BOOL NewNameTeacher::OnInitDialog();
	CString CurrentName;
	afx_msg void OnBnClickedBtnChangename();
	afx_msg void OnBnClickedBtnCansel();
};
