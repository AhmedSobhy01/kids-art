#pragma once
#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point center;
	static const int DefaultHexagonSize;
	int hexagonSize;

	double calcTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3);
public:
	CHexagon();
	CHexagon(Point, GfxInfo);
	void Draw(Output* pOut);
	static int GetDefaultHexagonSize();
	bool IsPointInside(Point);
	Point GetCenter() const;
	void SetCenter(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
	bool GetCorner(Point, int&);
	void SetCorner(Point, int);
};


