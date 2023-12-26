#ifndef CHEXAGON_H
#define CHEXAGON_H

#include "CFigure.h"

class CHexagon : public CFigure
{
	static const int DefaultHexagonSize; // Default size of the hexagon

	Point Center;	 // Center of the hexagon
	int HexagonSize; // Size of the hexagon

	double CalcTriangleArea(PointDouble, PointDouble, PointDouble); // Calculate the area of the triangle

public:
	static int GetDefaultHexagonSize(); // Get the default size of the hexagon

	CHexagon();
	CHexagon(Point, GfxInfo);

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