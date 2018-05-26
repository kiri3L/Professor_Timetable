#include "stdafx.h"
#include "calculate.hpp"

void Calculate::uniteProfessors(Data* data, std::string first, std::string second)
{
	for(int i = 0;i < data->lessons.size();++i)
		if(data->lessons[i]->getProfessor()->getName() == second)
			data->lessons[i]->getProfessor()->setName(first);
	for(int i = 0;i < data->professors.size();++i)
		if(data->professors[i]->getName() == second)
		{
			const int prost = i;
			data->professors.erase(data->professors.begin() + i);
			break;
		}
}

std::vector<Cell*> Calculate::generateSchedule(std::string prof, Data* data, int prof_koord_y)
{
	std::vector<Cell*> schedule;
	int prof_x = 1, prof_y = prof_koord_y;
	Cell* temp = new Cell;
	temp->fillCell(prof_x, prof_y, prof);
	schedule.push_back(temp);
	for (int les = 0; les < data->lessons.size(); ++les)
	{
		if (prof == data->lessons[les]->getProfessor()->getName())
		{
			int lesson_x = data->lessons[les]->getKoord(), lesson_y = prof_y;
			int flag = 0;
			for (int iter = 0; iter < schedule.size(); iter++)
			{
				if (schedule[iter]->getKoord_x() == lesson_x && schedule[iter]->getKoord_y() == lesson_y)
				{
					MessageBox(NULL, L" ", L" ", MB_OK);
					std::stringstream name, type, group, aud, stud;
					name << schedule[iter]->getText() << "\n" << data->lessons[les]->getName();
					type << schedule[iter + 1]->getText() << "\n" << data->lessons[les]->getType();
					group << schedule[iter + 2]->getText() << "\n" << data->lessons[les]->getGroup();
					aud << schedule[iter + 3]->getText() << "\n" << data->lessons[les]->getAuditory();
					stud << schedule[iter + 4]->getText() << "\n" << std::to_string(data->lessons[les]->getStudents());
					schedule[iter]->paintCell();
					schedule[iter]->setText(name.str());
					schedule[iter + 1]->setText(type.str());
					schedule[iter + 2]->setText(group.str());
					schedule[iter + 3]->setText(aud.str());
					schedule[iter + 4]->setText(stud.str());
					flag = 1;
				}
			}

			if(flag == 0)
			{
				temp = new Cell;
				temp->fillCell(lesson_x, lesson_y, data->lessons[les]->getName());
				schedule.push_back(temp);

				temp = new Cell;
				temp->fillCell(lesson_x, lesson_y + 1, data->lessons[les]->getType());
				schedule.push_back(temp);

				temp = new Cell;
				temp->fillCell(lesson_x, lesson_y + 2, data->lessons[les]->getGroup());
				schedule.push_back(temp);

				temp = new Cell;
				temp->fillCell(lesson_x, lesson_y + 3, data->lessons[les]->getAuditory());
				schedule.push_back(temp);

				temp = new Cell;
				temp->fillCell(lesson_x, lesson_y + 4, std::to_string(data->lessons[les]->getStudents()));
				schedule.push_back(temp);
			}
		}
	}

	return schedule;
}
