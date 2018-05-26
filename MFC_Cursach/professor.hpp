#pragma once

#include <iostream>

class Professor
{
private:
	std::string name;
public:
	Professor(std::string);
	std::string getName();
	void setName(std::string);
};
