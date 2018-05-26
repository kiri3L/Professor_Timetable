#include "stdafx.h"
#include "ExcelReader.h"

ExcelReader::ExcelReader(CString way1, Excel::_ApplicationPtr pApp1)
{
	CT2CA tmp(way1);
	std::string s(tmp);
	way = (s.c_str()); 
	pApp = pApp1;
	flag = false;
	File = pApp->Workbooks->Open(way);
	if (File == NULL) flag = true;
	Sheet = File->Worksheets->Item[1];//sheet теперь указывает на первый лист

	pApp->PutVisible(0, FALSE);
	pApp->PutDisplayAlerts(0, FALSE);//отключить уведомления
//	pApp->PutScreenUpdating(0, false);
//	pApp->PutCalculation(0, Excel::xlCalculationManual);
//	pApp->PutEnableEvents(false); //Отключаем отслеживание событий	
//	pApp->PutStatusBar(0, false);

}

std::string ExcelReader::readCell(int strok, int stolb)
{
	Excel::RangePtr Cell = Sheet->Cells->Item[strok][stolb];
	std::string text = (char *)_bstr_t(Cell->Text);
	
	return text;
}

bool ExcelReader::getFlag()
{
	return flag;
}

ExcelReader::~ExcelReader()
{
	
//	pApp->PutScreenUpdating(0, true);
//	pApp->PutCalculation(0, Excel::xlCalculationAutomatic);
//	pApp->PutEnableEvents(true); //Отключаем отслеживание событий	
//	pApp->PutStatusBar(0, true);
}
