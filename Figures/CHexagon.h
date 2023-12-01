#pragma once
#include "CFigure.h"
class CHexagon : public CFigure
{
private:
	Point center;
	static const int hexagonSize;
public:
	CHexagon(Point, GfxInfo);
	void Draw(Output* pOut)const;
	static int getHexagonSize();
};

