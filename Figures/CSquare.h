#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
	static const int DefaultSquareSize; // Default size of the square

	Point Center;	// Center of the square
	int SquareSize; // Size of the square

public:
	static int GetDefaultSquareSize(); // Get the default size of the square

	CSquare();
	CSquare(Point, GfxInfo);

	void Draw(Output *); // Draw the figure

	bool IsPointInside(Point); // Check whether the point is inside the figure or not

	Point GetCenter() const; // Get the center of the figure
	void SetCenter(Point);	 // Set the center of the figure

	void Save(ofstream &); // Save the figure parameters to the file
	void Load(ifstream &); // Load the figure parameters to the file

	void PrintInfo(Output *); // Print all figure info on the status bar

	bool GetCorner(Point &, int &); // Get the corner of the figure
	void SetCorner(Point, int);		// Set the corner of the figure
};
#endif
