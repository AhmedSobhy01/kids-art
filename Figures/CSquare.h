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
	void Draw(Output* pOut)const;
	static int GetDefaultSquareSize();
	bool CheckSelected(int x, int y);
	Point GetCenter() const;
	void SetCenter(Point);
	bool Validate(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
	bool GetCorner(Point, int&);
	bool SetCorner(Point, int);
};

