#include "CSquare.h"

const int CSquare::DefaultSquareSize = 150;


CSquare::CSquare() :CFigure()
{
	squareSize = DefaultSquareSize;
	type = "Square";
}

CSquare::CSquare(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	squareSize = DefaultSquareSize;
	this->center = center;
	type = "Square";
}

void CSquare::Draw(Output* pOut) {
	pOut->DrawSquare(center, squareSize, FigGfxInfo, Selected);
}

int CSquare::GetDefaultSquareSize() {
	return DefaultSquareSize;
}

bool CSquare::IsPointInside(Point P) {
	if (Hidden) return false;

	Point p1, p2;
	p1.x = center.x - squareSize / 2;
	p1.y = center.y - squareSize / 2;
	p2.x = center.x + squareSize / 2;
	p2.y = center.y + squareSize / 2;
	bool cond1 = (p1.x <= P.x) && (P.x <= p2.x);
	bool cond2 = (p1.y <= P.y) && (P.y <= p2.y);
	return cond1 && cond2;
}
Point CSquare::GetCenter() const
{
	return center;
}
void CSquare::SetCenter(Point center) {
	this->center = center;
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

bool CSquare::GetCorner(Point& p, int& index) {
	int Xarr[2] = { center.x - squareSize / 2 , center.x + squareSize / 2 };
	int Yarr[2] = { center.y - squareSize / 2 , center.y + squareSize / 2 };
	int errx = 100, erry = 100;
	int i = 0;
	while (i < 4 && (errx >= 6 || erry >= 6)) {
		errx = abs(p.x - Xarr[i % 2]);
		erry = abs(p.y - Yarr[i / 2]);
		++i;
	}
	--i;
	if (errx < 6 && erry < 6) {
		index = 0;
		p = { center.x + squareSize / 2, center.y + squareSize / 2 };
		return true;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
		}
	}
	return false;
}
void CSquare::SetCorner(Point p, int index) {
	squareSize = sqrt((pow(p.x - center.x, 2) + pow(p.y - center.y, 2)) * 2);
}