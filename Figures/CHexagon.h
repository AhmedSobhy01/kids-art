#pragma once
#include "CFigure.h"
class CHexagon : public CFigure
{
private:
	Point center;
public:
	CHexagon(Point, GfxInfo);
	void Draw(Output* pOut)const;
};

