#include "stdafx.h"
#include "start.hpp"

Start::Start()
{

}

Start::Start(std::vector<std::string> nameProfs)
{
	int all = nameProfs.size();
	for (int i = 0; i < all; i++)
	{
		listProfs.push_back(nameProfs[i]);
	}
}

void Start::start(ExcelReader* excel, Data* data)
{
	Reader* reader = new Reader();
	reader->startReading(excel, data);
	delete reader;
}

void Start::uniteSt(Data* data, std::vector<std::string> mergeProfs, CString newName)
{
	CT2CA tmp(newName);
	std::string name(tmp);
	name = (name.c_str());

	Calculate* calc = new Calculate;
	calc->uniteProfessors(data, mergeProfs, name );
	delete calc;
}

void Start::end(ExcelWriter * write, Data * data)
{
	int all = listProfs.size();
	std::vector<Cell*> schedule;
	int prof_koord_y = 6;
	write->shablon(all);
	for (int i = 0; i < all; i++)
	{
		Calculate* calc = new Calculate;
		schedule = calc->generateSchedule(listProfs[i], data, prof_koord_y);
		prof_koord_y += 5;
		for (int i = 0; i < schedule.size(); i++)
			write->writeCell(schedule[i]->getKoord_x(), schedule[i]->getKoord_y(), schedule[i]->getText(), schedule[i]->getColor());
		delete calc;
	}
}

Start::~Start()
{
	int all = listProfs.size();
	for (int i = 0; i < all; i++)
		listProfs[i].pop_back(); 
}
