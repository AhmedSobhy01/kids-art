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
	CTriangle();
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	void Draw(Output* pOut) ;
	bool CheckSelected(int x, int y);
	Point GetCenter() const;
	void SetCenter(Point);
	bool Validate(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
};

