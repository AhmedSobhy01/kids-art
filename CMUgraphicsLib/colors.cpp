/*
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "colors.h"

ostream &operator<<(ostream &OutputStream, const color &Color)
{
	// Compare the color to each color and output the corresponding string
	if (Color == PINK)
		OutputStream << "PINK";
	else if (Color == RED)
		OutputStream << "RED";
	else if (Color == ORANGE)
		OutputStream << "ORANGE";
	else if (Color == YELLOW)
		OutputStream << "YELLOW";
	else if (Color == GREEN)
		OutputStream << "GREEN";
	else if (Color == SKY)
		OutputStream << "SKY";
	else if (Color == BLUE)
		OutputStream << "BLUE";
	else if (Color == LAVENDER)
		OutputStream << "LAVENDER";
	else if (Color == BASE)
		OutputStream << "WHITE";
	else if (Color == BLACK)
		OutputStream << "BLACK";
	else
		OutputStream << "NO_FILL";

	return OutputStream;
}

istream &operator>>(istream &InputStream, color &Color)
{
	std::string X;
	InputStream >> X; // Read the color as a string

	// Compare the string to each color and set the color to the corresponding color
	if (X == "BLACK")
		Color = BLACK;
	else if (X == "RED")
		Color = RED;
	else if (X == "BLUE")
		Color = BLUE;
	else if (X == "GREEN")
		Color = GREEN;
	else if (X == "PINK")
		Color = PINK;
	else if (X == "ORANGE")
		Color = ORANGE;
	else if (X == "SKY")
		Color = SKY;
	else if (X == "LAVENDER")
		Color = LAVENDER;
	else if (X == "YELLOW")
		Color = YELLOW;
	else if (X == "WHITE")
		Color = BASE;
	else
		Color = TRANSPARENT_COLOR;

	return InputStream;
}

bool operator==(color a, color b)
{
	return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue)); // Compare the RGB values of the two colors
}

bool operator!=(color a, color b)
{
	return !(a == b); // Use the == operator to determine if the colors are not equal
}

color color::operator-(unsigned char c) const
{
	unsigned char r = ucRed <= c ? 0 : ucRed - c;
	unsigned char g = ucGreen <= c ? 0 : ucGreen - c;
	unsigned char b = ucBlue <= c ? 0 : ucBlue - c;

	return color(r, g, b);
}

std::string color::ReturnColor() const
{
	// Compare the color to each color and return the corresponding string
	if (*this == BLACK)
		return "Black";
	else if (*this == RED)
		return "Red";
	else if (*this == BLUE)
		return "Blue";
	else if (*this == GREEN)
		return "Green";
	else if (*this == PINK)
		return "Pink";
	else if (*this == ORANGE)
		return "Orange";
	else if (*this == SKY)
		return "Sky";
	else if (*this == LAVENDER)
		return "Lavender";
	else if (*this == YELLOW)
		return "Yellow";
	else if (*this == BASE)
		return "White";
	else
		return "Transparent";
}
