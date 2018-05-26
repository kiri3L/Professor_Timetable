#include "stdafx.h"
#include "data.hpp"

void Data::addProfessor(std::string name)
{
	ProfessorFactory* factory = new ProfessorFactory;
	professors.push_back(factory->create(name));
	delete factory;
}


void Data::addLesson(std::string name, std::string auditory, std::string group, std::string type, int koord, Professor* professor, int students)
{
	LessonFactory* factory = new LessonFactory;
	lessons.push_back(factory->create(name, auditory, group, type, koord, professor, students));
	delete factory;
}
Data::~Data()
{
	for(int i = 0;i < professors.size();++i)
		delete professors[i];
	for(int i = 0;i < lessons.size();++i)
		delete lessons[i];

}
