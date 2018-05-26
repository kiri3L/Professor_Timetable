#include "stdafx.h"
#include "factory_prof.hpp"

Professor* ProfessorFactory::create(std::string name)
{
	return new Professor(name);
}
