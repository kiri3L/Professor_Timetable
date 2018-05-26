#include "stdafx.h"
#include "reader.hpp"

int Reader::checker(std::string temp)
{
	int flag = 0;
	for (int i = 0; i < temp.size(); ++i)
		if (temp[i] == '\n' && i != temp.size() - 1)
			flag = i;
	return flag;
}

void Reader::insLesson(Data* data, std::string lesson, std::string auditory, std::string group, std::string type, int koord_x, std::string professor, int students)
{
	int flag = -1;
	for (int prof = 0; prof < data->professors.size(); ++prof)
		if (data->professors[prof]->getName() == professor)
		{
			flag = prof;
			break;
		}

	if (flag == -1)
	{
		data->addProfessor(professor);
		data->addLesson(lesson, auditory, group, type, koord_x, data->professors[data->professors.size() - 1], students);
	}
	else
		data->addLesson(lesson, auditory, group, type, koord_x, data->professors[flag], students);
}

void Reader::startReading(ExcelReader* reader, Data* data)
{
	int group_x = 3, group_y = 7;
	bool stoper = 1;
	for(int find_y = 1;stoper && find_y < 10;++find_y)
	for(int find_x = 1;stoper && find_x < 10;++find_x)
	{
		std::string tempo = reader->readCell(find_x, find_y);
		if(tempo == "1")
		{
			group_x = find_x - 2;
			group_y = find_y + 4;
			stoper = 0;
		}
	}
	std::string::size_type sz;
	std::string group, professor, auditory, type, lesson;
	int students;
	int stop_flag = 1;
	int boost_flag = 1;
	for (int y = group_y; stop_flag; y += 4 + 5 * (boost_flag > 3))
	{
		if (boost_flag > 3)
			boost_flag = 1;
		++boost_flag;

		group = reader->readCell(group_x, y);
		if (group.empty())
		{
			stop_flag = 0;
			continue;
		}

		students = std::stoi(reader->readCell(group_x, y + 3), &sz);

		for (int x = group_x + 2; x <= group_x + 73; ++x)
		{
			professor = reader->readCell(x, y + 2);

			if (professor.empty())
				continue;
			int koord_x = x - group_x + 1;

			lesson = reader->readCell(x, y);
			type = reader->readCell(x, y + 1);
			auditory = reader->readCell(x, y + 3);

			int ch_prof = checker(professor), ch_les = checker(lesson), ch_type = checker(type), ch_aud = checker(auditory);

			if (ch_prof || ch_les || ch_type || ch_aud)
			{
				std::string les1, aud1, type1, prof1;
				std::string les2, aud2, type2, prof2;
				if (ch_prof)
				{
					prof1 = professor;
					prof1.erase(prof1.begin() + ch_prof, prof1.end());
					prof2 = professor;
					prof2.erase(prof2.begin(), prof2.begin() + ch_prof + 1);
				}
				else
				{
					prof1 = professor;
					prof2 = professor;
				}

				if (ch_aud)
				{
					aud1 = auditory;
					aud1.erase(aud1.begin() + ch_aud, aud1.end());
					aud2 = auditory;
					aud2.erase(aud2.begin(), aud2.begin() + ch_aud + 1);
				}
				else
				{
					aud1 = auditory;
					aud2 = auditory;
				}

				if (ch_type)
				{
					type1 = type;
					type1.erase(type1.begin() + ch_type, type1.end());
					type2 = type;
					type2.erase(type2.begin(), type2.begin() + ch_type + 1);
				}
				else
				{
					type1 = type;
					type2 = type;
				}

				if (ch_les)
				{
					les1 = lesson;
					les1.erase(les1.begin() + ch_les, les1.end());
					les2 = lesson;
					les2.erase(les2.begin(), les2.begin() + ch_les + 1);
				}
				else
				{
					les1 = lesson;
					les2 = lesson;
				}


				insLesson(data, les1, aud1, group, type1, koord_x, prof1, students);
				insLesson(data, les2, aud2, group, type2, koord_x, prof2, students);

			}
			else
				insLesson(data, lesson, auditory, group, type, koord_x, professor, students);

		}

	}
}
