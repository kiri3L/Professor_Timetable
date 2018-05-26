#pragma once

#include <iostream>
#include <vector>
#include "professor.hpp"

class Lesson
{

private:
	std::string name;
	std::string auditory;
	std::string group;
	std::string type;
	Professor* professor;
	int koord;
	int students;

public:
	Lesson(std::string, std::string, std::string, std::string, int, Professor*, int);


	std::string getName();
	std::string getAuditory();
	std::string getGroup();
	std::string getType();
	Professor* getProfessor();
	int getKoord();
	int getStudents();

	void setProfessor(Professor*);

	~Lesson();
	
};
