#include "CHexagon.h"

const int CHexagon::DefaultHexagonSize = 80;

CHexagon::CHexagon() :CFigure()
{
	hexagonSize = DefaultHexagonSize;
	type = "Hexagon";
}

CHexagon::CHexagon(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	hexagonSize = DefaultHexagonSize;
	type = "Hexagon";
}

void CHexagon::Draw(Output* pOut) {
	pOut->DrawHexagon(center, hexagonSize, FigGfxInfo, Selected);
}

int CHexagon::GetDefaultHexagonSize() {
	return DefaultHexagonSize;
}

double CHexagon::CalcTriangleArea(PointDouble P1, PointDouble P2, PointDouble P3) {
	return  abs(P1.x * (P2.y - P3.y) + P2.x * (P3.y - P1.y) + P3.x * (P1.y - P2.y)) / 2.0;
}

bool CHexagon::IsPointInside(Point P) {
	if (Hidden) return false;

	// check if the area made by the triangle of P and 2 adjecent verticies of the hexagon
	// are equal to the total area of the hexagon

	double totalArea = 3 * sqrt(3) * hexagonSize * hexagonSize / 2;
	PointDouble P1, P2;
	double PArea = 0;
	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians
	P1.x = center.x + hexagonSize;
	P1.y = center.y;
	for (int i = 1; i <= 6; i++)
	{
		P2.x = center.x + hexagonSize * cos(i * angle);
		P2.y = center.y + hexagonSize * sin(i * angle);
		PArea += CalcTriangleArea(P, P1, P2);
		P1.x = P2.x;
		P1.y = P2.y;
	}
	double err = totalArea - PArea;
	return -0.001 < err && err < 0.001;
}

Point CHexagon::GetCenter() const
{
	return center;
}

void CHexagon::SetCenter(Point c) {
	this->center = c;
}



void CHexagon::Save(ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "HEXAGON" << " " << ID << " " << center.x << " " << center.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CHexagon::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> center.x >> center.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.isFilled = false;
		return;
	}
}

void CHexagon::PrintInfo(Output* pOut) {
	string info = "Hexagon: ID = ";
	info += to_string(ID);
	info += ", Center = (";
	info += to_string(center.x);
	info += ", ";
	info += to_string(center.y);
	info += "), SideLength = ";
	info += to_string(hexagonSize);
	pOut->PrintMessage(info);
}
bool CHexagon::GetCorner(Point& p, int& index) {
	double angle = 2.0 * cdPi / 6.0;
	double errx = 100, erry = 100;
	int i = 0;
	while (i < 6 && (errx >= 6 || erry >= 6)) {

		//calculate the distance between the mouse and every vertex
		errx = abs(p.x - (center.x + hexagonSize * cos(i * angle)));
		erry = abs(p.y - (center.y + hexagonSize * sin(i * angle)));
		++i;
	}
	
	//if the distance is less than 6 pixels: 
	if (errx < 6 && erry < 6) {
		index = 0;
		p = { center.x + hexagonSize,center.y };
		return true;
	}

	return false;
}
void CHexagon::SetCorner(Point p, int index) {
	hexagonSize = sqrt(pow(p.x - center.x, 2) + pow(p.y - center.y, 2));
}
