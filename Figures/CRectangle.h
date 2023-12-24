#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
public:
	CRectangle();
	CRectangle(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) ;
	bool IsPointInside(Point);
	Point GetCenter() const;
	void SetCenter(Point);
	void Save(ofstream&);
	void Load(ifstream&);
	void PrintInfo(Output* pOut);
	bool GetCorner(Point, int&);
	void SetCorner(Point, int);
};

#endif