#pragma once
#include "CFigure.h"
class CTriangle : public CFigure
{
private:
	Point P1;
	Point P2;
	Point P3;
	double calcArea(Point, Point, Point);
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	void Draw(Output* pOut) const;
	bool CheckSelected(int x, int y);
};

