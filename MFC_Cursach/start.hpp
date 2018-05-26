#pragma once

#include "stdafx.h"
#include "ExcelReader.h"
#include "ExcelWriter.h"
#include "data.hpp"
#include "reader.hpp"
#include "calculate.hpp"
#include "professor.hpp"

class Start
{
	
public:
	std::vector <std::string> listProfs;

	Start();
	Start( std::vector<std::string> );
	void start(ExcelReader*, Data*);
	void uniteSt(Data*, std::vector<std::string> , CString );
	void end(ExcelWriter*, Data*);
	~Start();
};

