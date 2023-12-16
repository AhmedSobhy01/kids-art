#include "CCircle.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"

CCircle::CCircle(Point center, Point radius, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	this->radius = radius;
	type = "Circle";
}

void CCircle::Draw(Output* pOut) const {
	pOut->DrawCircle(center, radius, FigGfxInfo, Selected);
}
bool CCircle::CheckSelected(int x, int y) {
	return !Hidden && (sqrt(pow(center.x - x, 2) + pow(center.y - y, 2)) <= sqrt(pow(center.x - radius.x, 2) + pow(center.y - radius.y, 2)));
}

Point CCircle::GetCenter() const
{
	return center;
}

void CCircle::SetCenter(Point c) {
	if (!Validate(c))return;
	this->radius.x += (c.x - this->center.x);
	this->radius.y += (c.y - this->center.y);
	this->center = c;
}

bool CCircle::Validate(Point c) {
	int radius = sqrt(pow(center.x - this->radius.x, 2) + pow(center.y - this->radius.y, 2));
	return (c.y - radius) >= UI.ToolBarHeight && (c.y + radius) <= (UI.height - UI.StatusBarHeight);
}

void CCircle::PrintInfo(Output* pOut) {
	string info = "Circle: Center = (";
	info += to_string(center.x);
	info += ", ";
	info += to_string(center.y);
	info += "), Radius = ";
	int radius = sqrt(pow(center.x - this->radius.x, 2) + pow(center.y - this->radius.y, 2));
	info += to_string(radius);
	pOut->PrintMessage(info);
}