#pragma once

#include <iostream>
#include "professor.hpp"

class ProfessorFactory
{
public:
	Professor* create(std::string);
};
