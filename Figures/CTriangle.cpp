#include "CTriangle.h"



CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->P3 = P3;
	type = TRIANGLE;
}


void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTriangle(P1, P2, P3, FigGfxInfo, Selected);
}


double CTriangle::calcArea(Point P1, Point P2, Point P3) {
	return  abs(P1.x * (P2.y - P3.y) + P2.x * (P3.y - P1.y) + P3.x * (P1.y - P2.y)) / 2;
}

bool CTriangle::CheckSelected(int x, int y) {
	Point P = { x,y };
	double totalArea = calcArea(P1, P2, P3);
	double A1 = calcArea(P, P2, P3);
	double A2 = calcArea(P, P1, P3);
	double A3 = calcArea(P, P2, P1);
	double err = totalArea - A1 - A2 - A3;
	return -2 < err && err < 2;

	///another way to find a point inside a triangle using barycantric corrdinates

	//int ACx = P3.x - P1.x;
	//int ACy = P3.y - P1.y;
	//int ABx = P2.x - P1.x;
	//int ABy = P2.y - P1.y;
	//double w1 = (P1.x * ACy + (P.y - P1.y) * ACx - P.x * ACy)/(ABy*ACx-ABx*ACy);
	//double w2 = ((P.y - P1.y) - w1 * ABy) / ACy;
	//return w1 >= 0 && w2 >= 0 && (w1 + w2)<=1;
}

void CTriangle::SetCenter(Point c) {
	Point center = { (P1.x + P2.x + P3.x) / 3,(P1.y + P2.y + P3.y) / 3 };
	int dx = c.x - center.x;
	int dy = c.y - center.y;
	P1.x += dx;
	P2.x += dx;
	P3.x += dx;
	P1.y += dy;
	P2.y += dy;
	P3.y += dy;

}
bool CTriangle::Validate(Point c) {
	Point center = { (P1.x + P2.x + P3.x) / 3,(P1.y + P2.y + P3.y) / 3 };
	int dx = c.x - center.x;
	int dy = c.y - center.y;
	bool cond1 = P1.y + dy >= UI.ToolBarHeight && P1.y + dy <= (UI.height - UI.StatusBarHeight);
	bool cond2 = P2.y + dy >= UI.ToolBarHeight && P2.y + dy <= (UI.height - UI.StatusBarHeight);
	bool cond3 = P3.y + dy >= UI.ToolBarHeight && P3.y + dy <= (UI.height - UI.StatusBarHeight);
	return cond1 && cond2 && cond3;
}