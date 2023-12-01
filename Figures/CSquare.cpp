#include "CSquare.h"

CSquare::CSquare(Point Center, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo) {
	this->center = Center;
}

void CSquare::Draw(Output* pOut) const{
	pOut->DrawSquare(center, FigGfxInfo,Selected);
}
