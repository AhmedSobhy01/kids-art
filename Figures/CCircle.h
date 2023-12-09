#ifndef CCIRCLE_H
#define CCIRCLE_H
#include "CFigure.h"
class CCircle : public CFigure
{
private:
	Point center;
	Point radius;
public:
	CCircle(Point, Point, GfxInfo);
	void Draw(Output* pOut)const;
	bool CheckSelected(int x, int y);
	Point GetCenter() const;
	void SetCenter(Point);
	bool Validate(Point);
};
#endif

