#pragma once
#include "CFigure.h"
class CTriangle : public CFigure
{
private:
	Point P1;
	Point P2;
	Point P3;
	double CalcTriangleArea(Point, Point, Point);

public:
	CTriangle();
	CTriangle(Point, Point, Point, GfxInfo);
	void Draw(Output *);
	bool IsPointInside(Point);
	Point GetCenter() const;
	void SetCenter(Point);
	void Save(ofstream &);
	void Load(ifstream &);
	void PrintInfo(Output *);
	bool GetCorner(Point &, int &);
	void SetCorner(Point, int);
};
