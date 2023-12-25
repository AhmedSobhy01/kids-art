/*
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "colors.h"

ostream &operator<<(ostream &c, const color &col)
{
	if (col == PINK)
		c << "PINK";
	else if (col == RED)
		c << "RED";
	else if (col == ORANGE)
		c << "ORANGE";
	else if (col == YELLOW)
		c << "YELLOW";
	else if (col == GREEN)
		c << "GREEN";
	else if (col == SKY)
		c << "SKY";
	else if (col == BLUE)
		c << "BLUE";
	else if (col == LAVENDER)
		c << "LAVENDER";
	else if (col == BASE)
		c << "WHITE";
	else if (col == BLACK)
		c << "BLACK";
	else
		c << "NO_FILL";
	return c;
}

istream &operator>>(istream &c, color &col)
{
	std::string x;
	c >> x;
	if (x == "BLACK")
		col = BLACK;
	else if (x == "RED")
		col = RED;
	else if (x == "BLUE")
		col = BLUE;
	else if (x == "GREEN")
		col = GREEN;
	else if (x == "PINK")
		col = PINK;
	else if (x == "ORANGE")
		col = ORANGE;
	else if (x == "SKY")
		col = SKY;
	else if (x == "LAVENDER")
		col = LAVENDER;
	else if (x == "YELLOW")
		col = YELLOW;
	else if (x == "WHITE")
		col = BASE;
	else
		col = TRANSPARENT_COLOR;
	return c;
}

bool operator==(color a, color b)
{

	return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue));
}

bool operator!=(color a, color b)
{

	return !(a == b);
}

color color::operator-(unsigned char c) const {
	unsigned char r = ucRed <= c ? 0 : ucRed - c;
	unsigned char g = ucGreen <= c ? 0 : ucGreen - c;
	unsigned char b = ucBlue <= c ? 0 : ucBlue - c;
	return color(r,g,b);
}

std::string color::ReturnColor()
{
	std::string c;
	if (*this == BLACK)
		c = "Black";
	else if (*this == RED)
		c = "Red";
	else if (*this == BLUE)
		c = "Blue";
	else if (*this == GREEN)
		c = "Green";
	else if (*this == PINK)
		c = "Pink";
	else if (*this == ORANGE)
		c = "Orange";
	else if (*this == SKY)
		c = "Sky";
	else if (*this == LAVENDER)
		c = "Lavender";
	else if (*this == YELLOW)
		c = "Yellow";
	else if (*this == BASE)
		c = "White";
	else
		c = "Transparent";
	return c;
}
