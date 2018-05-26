#pragma once

#include <iostream>

class Cell
{
private:
	int koord_x;
	int koord_y;
	bool color;
	std::string text;
public:

	Cell();
	int getKoord_x();
	int getKoord_y();
	bool getColor();
	std::string getText();
	
	void fillCell(int, int, std::string);
	void paintCell();
	void setText(std::string);
};
