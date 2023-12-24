#pragma once
#include "CFigure.h"
class CSquare : public CFigure
{
private:
	Point center;
	static const int DefaultSquareSize;
	int squareSize;
public:
	CSquare();
	CSquare(Point, GfxInfo);
	void Draw(Output* pOut);
	static int GetDefaultSquareSize();
	bool IsPointInside(Point);
	Point GetCenter() const;
	void SetCenter(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
	bool GetCorner(Point, int&);
	void SetCorner(Point, int);
};

