#pragma once


// Диалоговое окно Progress_dlg

class Progress_dlg : public CDialog
{
	DECLARE_DYNAMIC(Progress_dlg)

public:
	Progress_dlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~Progress_dlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl progress;
};
