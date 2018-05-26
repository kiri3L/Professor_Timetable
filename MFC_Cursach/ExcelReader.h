#pragma once
#include "ExLab.h"
#include <string>

class ExcelReader
{
private: bstr_t way; Excel::_ApplicationPtr pApp; Excel::_WorkbookPtr File; Excel::_WorksheetPtr Sheet; bool flag;
public: 
	ExcelReader(CString way1, Excel::_ApplicationPtr pApp1); //или string как кириллу удобнее
	std::string readCell(int strok, int stolb);
	bool getFlag();
	~ExcelReader();
};
//		CString a(fil->readCell(2, 8).c_str());