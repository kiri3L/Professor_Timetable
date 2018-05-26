#pragma once

#include "data.hpp"
#include "ExcelReader.h"

class Reader
{
private:
	int Reader::checker(std::string);
	void Reader::insLesson(Data*, std::string, std::string, std::string, std::string, int, std::string, int);

public:
	void startReading(ExcelReader*, Data*);
};
