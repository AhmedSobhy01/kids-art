/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "colors.h"

ostream& operator<<(ostream& c, const color& col)
{
	if (col == BLACK)
		c << "BLACK";
	else if (col == RED)
		c << "RED";
	else if (col == BLUE)
		c << "BLUE";
	else if (col == GREEN)
		c << "GREEN";
	else if (col == MAGENTA)
		c << "MAGENTA";
	else if (col == ORANGE)
		c << "ORANGE";
	else if (col == BROWN)
		c << "BROWN";
	else if (col == CYAN)
		c << "CYAN";
	else if (col == YELLOW)
		c << "YELLOW";
	else if (col == LIGHTGOLDENRODYELLOW)
		c << "LIGHTGOLDENRODYELLOW";
	else
		c << "TRANSPARENT_COLOR";
	return c;
}

istream& operator>>(istream& c, color& col)
{
	string x;
	c >> x;
	if (x == "BLACK")
		col = BLACK;
	else if (x == "RED")
		col = RED;
	else if (x == "BLUE")
		col = BLUE;
	else if (x == "GREEN")
		col = GREEN;
	else if (x == "MAGENTA")
		col = MAGENTA;
	else if (x == "ORANGE")
		col = ORANGE;
	else if (x == "BROWN")
		col = BROWN;
	else if (x == "CYAN")
		col = CYAN;
	else if (x == "YELLOW")
		col = YELLOW;
	else if (x == "LIGHTGOLDENRODYELLOW")
		col = LIGHTGOLDENRODYELLOW;
	else
		col = TRANSPARENT_COLOR;
	return c;
}

bool operator==(color a, color b) {

  return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue));

}

bool operator!=(color a, color b) {

  return !(a == b);
  
}

string color::ReturnColor(color col)
{
	string c;
	if (col == BLACK)
		c = "Black";
	else if (col == RED)
		c = "Red";
	else if (col == BLUE)
		c = "Blue";
	else if (col == GREEN)
		c = "Green";
	else if (col == MAGENTA)
		c = "Magenta";
	else if (col == ORANGE)
		c = "Orange";
	else if (col == BROWN)
		c = "Brown";
	else if (col == CYAN)
		c = "Cyan";
	else if (col == YELLOW)
		c = "Yellow";
	else if (col == LIGHTGOLDENRODYELLOW)
		c = "Light Golden Or Yellow";
	else
		c = "Transparent color";
	return c;
}
