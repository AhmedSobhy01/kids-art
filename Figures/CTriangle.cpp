#include "CTriangle.h"



CTriangle::CTriangle() :CFigure()
{
	type = "Triangle";
}

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->P3 = P3;
	type = "Triangle";
}


void CTriangle::Draw(Output* pOut)
{
	pOut->DrawTriangle(P1, P2, P3, FigGfxInfo, Selected);
}


double CTriangle::calcArea(Point P1, Point P2, Point P3) {
	return  abs(P1.x * (P2.y - P3.y) + P2.x * (P3.y - P1.y) + P3.x * (P1.y - P2.y)) / 2;
}

bool CTriangle::IsPointInside(Point P) {
	if (Hidden) return false;

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
		FigGfxInfo.BorderWidth = 3;
		return;
	}
}

void CTriangle::PrintInfo(Output* pOut) {
	string info = "Triangle: ID = " + to_string(ID);
	info += ", Vertex1 = (" + to_string(P1.x) + ", " + to_string(P1.y) + ")";
	info += ", Vertex2 = (" + to_string(P2.x) + ", " + to_string(P2.y) + ")";
	info += ", Vertex3 = (" + to_string(P3.x) + ", " + to_string(P3.y) + ")";
	info += ", Outline Color: " + FigGfxInfo.DrawClr.ReturnColor();
	info += ", Fill Color: " + FigGfxInfo.FillClr.ReturnColor();
	pOut->PrintMessage(info);
}

bool CTriangle::GetCorner(Point p, int& index) {
	Point Corners[3] = { P1,P2,P3 };
	int errx, erry;
	for (int i = 0; i < 3; i++) {
		erry = abs(p.y - Corners[i].y);
		errx = abs(p.x - Corners[i].x);
		if (errx < 6 && erry < 6) {
			index = i;
			return true;

		}
	}
	return false;
}
void CTriangle::SetCorner(Point p, int index) {
	Point* Corners[3] = { &P1,&P2,&P3 };
	*Corners[index] = p;
}
