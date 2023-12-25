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
	CRectangle(Point, Point, GfxInfo);
	virtual void Draw(Output *);
	bool IsPointInside(Point);
	Point GetCenter() const;
	void SetCenter(Point);
	void Save(ofstream &);
	void Load(ifstream &);
	void PrintInfo(Output *);
	bool GetCorner(Point &, int &);
	void SetCorner(Point, int);
};

#endif