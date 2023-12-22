#include "CSquare.h"

const int CSquare::squareSize = 150;


CSquare::CSquare() :CFigure()
{
	type = "Square";
}

CSquare::CSquare(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	type = "Square";
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
	bool cond1 = (p1.x <= x) && (x <= p2.x);
	bool cond2 = (p1.y <= y) && (y <= p2.y);
	return cond1 && cond2;
}
Point CSquare::GetCenter() const
{
	return center;
}
bool CSquare::SetCenter(Point center) {
	if (!Validate(center))return false;
	this->center = center;
	return true;
}
bool CSquare::Validate(Point c) {
	return (c.y - squareSize / 2 +1) > UI.ToolBarHeight && (c.y + squareSize / 2 -1) < (UI.height - UI.StatusBarHeight);
}

void CSquare::Save(ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "SQUARE" << " " << ID << " " << center.x << " " << center.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CSquare::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> center.x >> center.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.isFilled = false;
		return;
	}
}

void CSquare::PrintInfo(Output* pOut) {
	string info = "Square: ID = ";
	info += to_string(ID);
	info += ", Center = (";
	info += to_string(center.x);
	info += ", ";
	info += to_string(center.y);
	info += "), Length = ";
	info += to_string(squareSize);
	pOut->PrintMessage(info);
}
