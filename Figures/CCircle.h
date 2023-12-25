#ifndef CCIRCLE_H
#define CCIRCLE_H
#include "CFigure.h"
class CCircle : public CFigure
{
private:
	Point Center;
	Point Radius;

public:
	CCircle();
	CCircle(Point, Point, GfxInfo);
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
#endif
