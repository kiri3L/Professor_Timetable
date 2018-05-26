#include "stdafx.h"
#include "calculate.hpp"

void Calculate::uniteProfessors(Data* data, std::vector<std::string> profs, std::string newProf)
{
	data->addProfessor(newProf);
	for(int les = 0;les < data->lessons.size();++les)
		for(int prof = 0;prof < profs.size();++prof)
			if(data->lessons[les]->getProfessor()->getName() == profs[prof])
				data->lessons[les]->setProfessor(data->professors[data->professors.size()-1]);
	for(int prof = 0;prof < profs.size();++prof)
		for(int i = 0;i < data->professors.size();++i)
			if(data->professors[i]->getName() == profs[prof])
			{
				delete data->professors[i];
				data->professors.erase(data->professors.begin()+i);
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
			bool flag = 0;
			for (int iter = 0; iter < schedule.size(); iter++)
			{
				if(schedule[iter]->getKoord_x() == lesson_x && schedule[iter]->getKoord_y() == lesson_y && schedule[iter]->getText() == data->lessons[les]->getName() && schedule[iter+1]->getText() == data->lessons[les]->getType() && schedule[iter+3]->getText() == data->lessons[les]->getAuditory())
				{
					std::string::size_type sz;
					std::stringstream add_group, add_stud;
					add_group << schedule[iter+2]->getText() << "\n" << data->lessons[les]->getGroup();
					add_stud << std::to_string(stoi(schedule[iter+4]->getText(), &sz) + data->lessons[les]->getStudents());
					schedule[iter+2]->setText(add_group.str());
					schedule[iter+4]->setText(add_stud.str());
					flag = 1;
				}
				else if (schedule[iter]->getKoord_x() == lesson_x && schedule[iter]->getKoord_y() == lesson_y)
				{
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
