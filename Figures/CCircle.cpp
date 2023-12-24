#include "CCircle.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"

CCircle::CCircle() :CFigure()
{
	type = "Circle";
}

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
	return (c.y - radius) > UI.ToolBarHeight && (c.y + radius) < (UI.height - UI.StatusBarHeight);
}

void CCircle::Save(ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "CIRCLE" << " " << ID << " " << center.x << " " << center.y << " " << radius.x << " " << radius.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CCircle::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> center.x >> center.y >> radius.x >> radius.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.isFilled = false;
		return;
	}
}

void CCircle::PrintInfo(Output* pOut) {
	string info = "Circle: ID = ";
	info += to_string(ID);
	info += ", Center = (";
	info += to_string(center.x);
	info += ", ";
	info += to_string(center.y);
	info += "), Radius = ";
	int radius = sqrt(pow(center.x - this->radius.x, 2) + pow(center.y - this->radius.y, 2));
	info += to_string(radius);
	pOut->PrintMessage(info);
}
bool CCircle::GetCorner(Point p, int& index) {
	int CurrentRadius = sqrt(pow(center.x - this->radius.x, 2) + pow(center.y - this->radius.y, 2));
	int PointRadius = sqrt(pow(center.x - p.x, 2) + pow(center.y - p.y, 2));
	if (abs(CurrentRadius - PointRadius) < 4) {
		index = 0;
		return true;
	}
	return false;
}
bool CCircle::SetCorner(Point p, int) {
	Point radius = this->radius;
	this->radius = p;
	if (!Validate(center)) {
		this->radius = radius;
		return false;
	}
	return true;
}
