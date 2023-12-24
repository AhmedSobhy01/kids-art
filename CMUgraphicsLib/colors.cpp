/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "colors.h"

ostream& operator<<(ostream& c, const color& col)
{
	if (col == PINK)
		c << "PINK";
	else if (col == RED)
		c << "RED";
	else if (col == PEACH)
		c << "PEACH";
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
		c << "BASE";
	else if (col == BLACK)
		c << "BLACK";
	else
		c << "NO_FILL";
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
	else if (x == "PINK")
		col = PINK;
	else if (x == "PEACH")
		col = PEACH;
	else if (x == "SKY")
		col = SKY;
	else if (x == "LAVENDER")
		col = LAVENDER;
	else if (x == "YELLOW")
		col = YELLOW;
	else if (x == "BASE")
		col = BASE;
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

string color::ReturnColor()
{
	string c;
	if (*this == BLACK)
		c = "BLACK";
	else if (*this == RED)
		c = "RED";
	else if (*this == BLUE)
		c = "BLUE";
	else if (*this == GREEN)
		c = "GREEN";
	else if (*this == PINK)
		c = "PINK";
	else if (*this == PEACH)
		c = "PEACH";
	else if (*this == SKY)
		c = "SKY";
	else if (*this == LAVENDER)
		c = "LAVENDER";
	else if (*this == YELLOW)
		c = "YELLOW";
	else if (*this == BASE)
		c = "BASE";
	else
		c = "NO_FILL";
	return c;
}
