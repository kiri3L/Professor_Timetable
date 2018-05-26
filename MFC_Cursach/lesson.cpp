#include "stdafx.h"
#include "lesson.hpp"

Lesson::Lesson(std::string name, std::string auditory, std::string group, std::string type, int koord, Professor* professor, int students)
{
	this->name = name;
	this->auditory = auditory;
	this->type = type;
	this->professor = professor;
	this->group = group;
	this->koord = koord;
	this->students = students;
}
std::string Lesson::getName()
{
	return this->name;
}

std::string Lesson::getAuditory()
{
	return this->auditory;
}

std::string Lesson::getGroup()
{
	return this->group;
}

std::string Lesson::getType()
{
	return this->type;
}

int Lesson::getKoord()
{
	return this->koord;
}

Professor* Lesson::getProfessor()
{
	return this->professor;
}

int Lesson::getStudents()
{
	return this->students;
}

void Lesson::setProfessor(Professor* prof)
{
	professor = prof;
}

Lesson::~Lesson()
{

}
