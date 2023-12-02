#pragma once
#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point center;
	static const int hexagonSize;
	double calcTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3);
public:
	CHexagon(Point, GfxInfo);
	void Draw(Output* pOut)const;
	static int getHexagonSize();
	bool CheckSelected(int x, int y);
};


