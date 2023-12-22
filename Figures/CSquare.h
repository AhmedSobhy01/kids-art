#pragma once
#include "CFigure.h"
class CSquare : public CFigure
{
private:
	Point center;
	static const int squareSize;
public:
	CSquare();
	CSquare(Point, GfxInfo);
	void Draw(Output* pOut)const;
	static int getSquareSize();
	bool CheckSelected(int x, int y);
	Point GetCenter() const;
	bool SetCenter(Point);
	bool Validate(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
};

