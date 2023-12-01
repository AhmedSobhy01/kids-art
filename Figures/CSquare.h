#pragma once
#include "CFigure.h"
class CSquare : public CFigure
{
private:
	Point center;
public:
	CSquare(Point, GfxInfo);
	void Draw(Output* pOut)const;
};

