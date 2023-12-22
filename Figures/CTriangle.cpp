#include "CTriangle.h"



CTriangle::CTriangle() :CFigure()
{
}

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->P3 = P3;
	type = "Triangle";
}


void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTriangle(P1, P2, P3, FigGfxInfo, Selected);
}


double CTriangle::calcArea(Point P1, Point P2, Point P3) {
	return  abs(P1.x * (P2.y - P3.y) + P2.x * (P3.y - P1.y) + P3.x * (P1.y - P2.y)) / 2;
}

bool CTriangle::CheckSelected(int x, int y) {
	if (Hidden) return false;

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

Point CTriangle::GetCenter() const
{
	return { (P1.x + P2.x + P3.x) / 3,(P1.y + P2.y + P3.y) / 3 };
}

void CTriangle::SetCenter(Point c) {
	if (!Validate(c))return;
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
	bool cond1 = P1.y + dy - FigGfxInfo.BorderWidth / 2 >= UI.ToolBarHeight && P1.y + dy + FigGfxInfo.BorderWidth / 2 < (UI.height - UI.StatusBarHeight);
	bool cond2 = P2.y + dy - FigGfxInfo.BorderWidth / 2 >= UI.ToolBarHeight && P2.y + dy + FigGfxInfo.BorderWidth / 2 < (UI.height - UI.StatusBarHeight);
	bool cond3 = P3.y + dy - FigGfxInfo.BorderWidth / 2 >= UI.ToolBarHeight && P3.y + dy + FigGfxInfo.BorderWidth / 2 < (UI.height - UI.StatusBarHeight);
	return cond1 && cond2 && cond3;
}

void CTriangle::Save(ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "TRIANGLE" << " " << ID << " " << P1.x << " " << P1.y << " " << P2.x << " " << P2.y << " " << P3.x << " " << P3.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CTriangle::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> P1.x >> P1.y >> P2.x >> P2.y >> P3.x >> P3.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.isFilled = false;
		return;
	}
}

void CTriangle::PrintInfo(Output* pOut) {
	string info = "Triangle: ID = ";
	info += to_string(ID);
	info += ", Vertex1 = (";
	info += to_string(P1.x);
	info += ", ";
	info += to_string(P1.y);
	info += "), Vertex2 = (";
	info += to_string(P2.x);
	info += ", ";
	info += to_string(P2.y);
	info += "), Vertex3 = (";
	info += to_string(P3.x);
	info += ", ";
	info += to_string(P3.y);
	info += ")";
	pOut->PrintMessage(info);
}

bool CTriangle::GetCorner(Point, int&) { return false; }
void CTriangle::SetCorner(Point, int) {}