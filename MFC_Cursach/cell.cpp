#include "stdafx.h"
#include "cell.hpp"

Cell::Cell()
{
	color = 0;
}

void Cell::fillCell(int x, int y, std::string text)
{
	this->koord_x = x;
	this->koord_y = y;
	this->text = text;
}

void Cell::paintCell()
{
	color = 1;
}

void Cell::setText(std::string text)
{
	this->text = text;
}

int Cell::getKoord_x()
{
	return koord_x;
}

int Cell::getKoord_y()
{
	return koord_y;
}

bool Cell::getColor()
{
	return color;
}

std::string Cell::getText()
{
	return text;
}
