#include "CCircle.h"

CCircle::CCircle(Point center, Point radius, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	this->radius = radius;
}

void CCircle::Draw(Output* pOut) const {
	pOut->DrawCircle(center, radius, FigGfxInfo, Selected);
}