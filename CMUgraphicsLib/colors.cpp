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

bool operator==(color a, color b) {

  return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue));

}

bool operator!=(color a, color b) {

  return !(a == b);
  
}
