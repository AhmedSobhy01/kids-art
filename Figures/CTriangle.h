#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CFigure.h"

class CTriangle : public CFigure
{
	Point P1; // First point of the triangle
	Point P2; // Second point of the triangle
	Point P3; // Third point of the triangle

	double CalcTriangleArea(Point, Point, Point); // Calculate the area of the triangle

public:
	CTriangle();
	CTriangle(Point, Point, Point, GfxInfo);

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