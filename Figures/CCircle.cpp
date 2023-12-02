#include "CCircle.h"

CCircle::CCircle(Point center, Point radius, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	this->radius = radius;
}

void CCircle::Draw(Output* pOut) const {
	pOut->DrawCircle(center, radius, FigGfxInfo, Selected);
}
bool CCircle::CheckSelected(int x, int y) {
	return sqrt(pow(center.x - x, 2) + pow(center.y - y, 2)) <= sqrt(pow(center.x - radius.x, 2) + pow(center.y - radius.y, 2));
}