#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CFigure.h"

class CRectangle : public CFigure
{
	Point Corner1; // One corner of the rectangle
	Point Corner2; // Another corner of the rectangle

public:
	CRectangle();
	CRectangle(Point, Point, GfxInfo);

	virtual void Draw(Output *); // Draw the figure

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