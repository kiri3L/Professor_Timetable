#pragma once
#include "ExLab.h"
#include <string>


class ExcelWriter
{
private: bstr_t way; Excel::_ApplicationPtr pApp; Excel::_WorkbookPtr newFile; Excel::_WorksheetPtr Sheet;
public:
	ExcelWriter(std::string way1, Excel::_ApplicationPtr pApp1);
	void writeCell(int strok, int stolb, std::string text, bool color = 0);
	void shablon(int teachNumb);
	~ExcelWriter();
};