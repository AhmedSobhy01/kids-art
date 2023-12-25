#include "CTriangle.h"

CTriangle::CTriangle() : CFigure()
{
	TypeName = "Triangle";
}

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->P3 = P3;
	TypeName = "Triangle";
}

void CTriangle::Draw(Output *pOut)
{
	pOut->DrawTriangle(P1, P2, P3, FigGfxInfo, Selected);
}

double CTriangle::CalcTriangleArea(Point P1, Point P2, Point P3)
{
	return abs(P1.x * (P2.y - P3.y) + P2.x * (P3.y - P1.y) + P3.x * (P1.y - P2.y)) / 2.0;
}

bool CTriangle::IsPointInside(Point P)
{
	if (Hidden)
		return false;

	double totalArea = CalcTriangleArea(P1, P2, P3);
	double A1 = CalcTriangleArea(P, P2, P3);
	double A2 = CalcTriangleArea(P, P1, P3);
	double A3 = CalcTriangleArea(P, P2, P1);
	double Err = totalArea - A1 - A2 - A3;
	return -2 < Err && Err < 2;

	/// another way to find a point inside a triangle using barycentric corrdinates

	// int ACx = P3.x - P1.x;
	// int ACy = P3.y - P1.y;
	// int ABx = P2.x - P1.x;
	// int ABy = P2.y - P1.y;
	// double w1 = (P1.x * ACy + (P.y - P1.y) * ACx - P.x * ACy)/(ABy*ACx-ABx*ACy);
	// double w2 = ((P.y - P1.y) - w1 * ABy) / ACy;
	// return w1 >= 0 && w2 >= 0 && (w1 + w2)<=1;
}

Point CTriangle::GetCenter() const
{
	return {(P1.x + P2.x + P3.x) / 3, (P1.y + P2.y + P3.y) / 3};
}

void CTriangle::SetCenter(Point c)
{
	Point Center = {(P1.x + P2.x + P3.x) / 3, (P1.y + P2.y + P3.y) / 3};
	int dx = c.x - Center.x;
	int dy = c.y - Center.y;
	P1.x += dx;
	P2.x += dx;
	P3.x += dx;
	P1.y += dy;
	P2.y += dy;
	P3.y += dy;
}

void CTriangle::Save(ofstream &FileOutputStream)
{
	if (FileOutputStream.is_open())
	{
		FileOutputStream << "TRIANGLE"
						 << " " << ID << " " << P1.x << " " << P1.y << " " << P2.x << " " << P2.y << " " << P3.x << " " << P3.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CTriangle::Load(ifstream &fin)
{
	if (fin.is_open())
	{
		fin >> ID >> P1.x >> P1.y >> P2.x >> P2.y >> P3.x >> P3.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.IsFilled = false;
		return;
	}
}

void CTriangle::PrintInfo(Output *pOut)
{
	string Info = "Triangle: ID = ";
	Info += to_string(ID);
	Info += ", Vertex1 = (";
	Info += to_string(P1.x);
	Info += ", ";
	Info += to_string(P1.y);
	Info += "), Vertex2 = (";
	Info += to_string(P2.x);
	Info += ", ";
	Info += to_string(P2.y);
	Info += "), Vertex3 = (";
	Info += to_string(P3.x);
	Info += ", ";
	Info += to_string(P3.y);
	Info += ")";
	pOut->PrintMessage(Info);
}

bool CTriangle::GetCorner(Point &p, int &Index)
{
	Point Corners[3] = {P1, P2, P3};
	int ErrX = 100, ErrY = 100;
	int i = 0;
	while (i < 3 && (ErrX >= 6 || ErrY >= 6))
	{
		ErrY = abs(p.y - Corners[i].y);
		ErrX = abs(p.x - Corners[i].x);
		++i;
	}
	--i;
	if (ErrX < 6 && ErrY < 6)
	{
		Index = i;
		p = Corners[i];
		return true;
	}
	return false;
}
void CTriangle::SetCorner(Point p, int Index)
{
	Point *Corners[3] = {&P1, &P2, &P3};
	*Corners[Index] = p;
}
