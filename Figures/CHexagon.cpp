#include "CHexagon.h"

const int CHexagon::DefaultHexagonSize = 80;

CHexagon::CHexagon() : CFigure()
{
	HexagonSize = DefaultHexagonSize;
	TypeName = "Hexagon";
}

CHexagon::CHexagon(Point Center, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	this->Center = Center;
	HexagonSize = DefaultHexagonSize;
	TypeName = "Hexagon";
}

void CHexagon::Draw(Output *pOut)
{
	pOut->DrawHexagon(Center, HexagonSize, FigGfxInfo, Selected);
}

int CHexagon::GetDefaultHexagonSize()
{
	return DefaultHexagonSize;
}

double CHexagon::CalcTriangleArea(PointDouble P1, PointDouble P2, PointDouble P3)
{
	return abs(P1.x * (P2.y - P3.y) + P2.x * (P3.y - P1.y) + P3.x * (P1.y - P2.y)) / 2.0;
}

bool CHexagon::IsPointInside(Point P)
{
	if (Hidden)
		return false;

	// check if the area made by the triangle of P and 2 adjecent verticies of the hexagon
	// are equal to the total area of the hexagon

	double totalArea = 3 * sqrt(3) * HexagonSize * HexagonSize / 2;
	PointDouble P1, P2;
	double PArea = 0;
	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians
	P1.x = Center.x + HexagonSize;
	P1.y = Center.y;
	for (int i = 1; i <= 6; i++)
	{
		P2.x = Center.x + HexagonSize * cos(i * angle);
		P2.y = Center.y + HexagonSize * sin(i * angle);
		PArea += CalcTriangleArea(P, P1, P2);
		P1.x = P2.x;
		P1.y = P2.y;
	}
	double Err = totalArea - PArea;
	return -0.001 < Err && Err < 0.001;
}

Point CHexagon::GetCenter() const
{
	return Center;
}

void CHexagon::SetCenter(Point c)
{
	this->Center = c;
}

void CHexagon::Save(ofstream &FileOutputStream)
{
	if (FileOutputStream.is_open())
	{
		FileOutputStream << "HEXAGON"
						 << " " << ID << " " << Center.x << " " << Center.y << " " << HexagonSize << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl; // added figure size to handle resized figures
		return;
	}
}

void CHexagon::Load(ifstream &fin)
{
	if (fin.is_open())
	{
		fin >> ID >> Center.x >> Center.y >> HexagonSize >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.IsFilled = false;
		FigGfxInfo.BorderWidth = 3;

		return;
	}
}

void CHexagon::PrintInfo(Output *pOut)
{
	string info = "Hexagon: ID = " + to_string(ID);
	info += ", Center = (" + to_string(Center.x) + ", " + to_string(Center.y) + ")";
	info += ", SideLength = " + to_string(HexagonSize);
	info += ", Outline Color: " + FigGfxInfo.DrawClr.ReturnColor();
	info += ", Fill Color: " + FigGfxInfo.FillClr.ReturnColor();
	pOut->PrintMessage(info);
}

bool CHexagon::GetCorner(Point &p, int &index)
{
	double angle = 2.0 * cdPi / 6.0;
	double ErrX = 100, ErrY = 100;
	int i = 0;
	while (i < 6 && (ErrX >= 6 || ErrY >= 6))
	{
		// calculate the distance between the mouse and every vertex
		ErrX = abs(p.x - (Center.x + HexagonSize * cos(i * angle)));
		ErrY = abs(p.y - (Center.y + HexagonSize * sin(i * angle)));
		++i;
	}
	// if the distance is less than 6 pixels:
	if (ErrX < 6 && ErrY < 6)
	{
		index = 0;
		p = {Center.x + HexagonSize, Center.y};
		return true;
	}

	return false;
}
void CHexagon::SetCorner(Point p, int index)
{
	HexagonSize = sqrt(pow(p.x - Center.x, 2) + pow(p.y - Center.y, 2));
}
