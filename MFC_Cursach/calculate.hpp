#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "data.hpp"
#include "lesson.hpp"
#include "factory_lesson.hpp"
#include "cell.hpp"

class Calculate
{
private:

public:

	void uniteProfessors(Data*, std::vector<std::string>, std::string);

//	bool checkLesson(Lesson*);
	std::vector<Cell*> generateSchedule(std::string , Data*, int);

};
