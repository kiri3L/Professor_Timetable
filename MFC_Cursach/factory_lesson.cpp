#include "stdafx.h"
#include "factory_lesson.hpp"

Lesson* LessonFactory::create(std::string name, std::string auditory, std::string group, std::string type, int koord, Professor* professor, int students)
{
	return new Lesson(name, auditory, group, type, koord, professor, students);
}
