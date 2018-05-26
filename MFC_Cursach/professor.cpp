#include "stdafx.h"
#include "professor.hpp"

Professor::Professor(std::string name)
{
	this->name = name;
}

std::string Professor::getName()
{
	return this->name;
}

void Professor::setName(std::string name)
{
	this->name = name;
}
