#include "CSquare.h"

const int CSquare::squareSize = 150;


CSquare::CSquare(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	type = SQUARE;
}

void CSquare::Draw(Output* pOut) const {
	pOut->DrawSquare(center, squareSize, FigGfxInfo, Selected);
}

int CSquare::getSquareSize() {
	return squareSize;
}

bool CSquare::CheckSelected(int x, int y) {
	if (Hidden) return false;

	Point p1, p2;
	p1.x = center.x - squareSize / 2;
	p1.y = center.y - squareSize / 2;
	p2.x = center.x + squareSize / 2;
	p2.y = center.y + squareSize / 2;
	bool cond1 = (p1.x < x) && (x < p2.x);
	bool cond2 = (p1.y < y) && (y < p2.y);
	return cond1 && cond2;
}
Point CSquare::GetCenter() const
{
	return center;
}
void CSquare::SetCenter(Point center) {
	if (!Validate(center))return;
	this->center = center;
}
bool CSquare::Validate(Point c) {
	return (c.y - squareSize / 2) > UI.ToolBarHeight && (c.y + squareSize / 2) <= (UI.height - UI.StatusBarHeight);
}