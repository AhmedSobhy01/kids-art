#include "CSquare.h"

CSquare::CSquare(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
}

void CSquare::Draw(Output* pOut) const {
	pOut->DrawSquare(center, FigGfxInfo, Selected);
}
