#pragma once

#include <iostream>
#include "lesson.hpp"

class LessonFactory
{
public:
	Lesson* create(std::string, std::string, std::string, std::string, int, Professor*, int);
};
