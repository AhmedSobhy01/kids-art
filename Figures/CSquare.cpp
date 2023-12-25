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
		fout << "SQUARE" << " " << ID << " " << center.x << " " << center.y << " " << squareSize << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl; // added figure size to handle resized figures
		return;
	}
}

void CSquare::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> center.x >> center.y >> squareSize >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.isFilled = false;
		FigGfxInfo.BorderWidth = 3;
		return;
	}
}

void CSquare::PrintInfo(Output* pOut) {
	string info = "Square: ID = " + to_string(ID);
	info += ", Center = (" + to_string(center.x) + ", " + to_string(center.y) + ")";
	info += ", SideLength = " + to_string(squareSize);
	info += ", Outline Color: " + FigGfxInfo.DrawClr.ReturnColor();
	info += ", Fill Color: " + FigGfxInfo.FillClr.ReturnColor();
	pOut->PrintMessage(info);
}

bool CSquare::GetCorner(Point p, int& index) {
	int Xarr[2] = { center.x - squareSize / 2 , center.x + squareSize / 2 };
	int Yarr[2] = { center.y - squareSize / 2 , center.y + squareSize / 2 };
	int errx, erry;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			errx = abs(p.x - Xarr[i]);
			erry = abs(p.y - Yarr[j]);
			if (errx < 6 && erry < 6) {
				index = 0;
				return true;
			}
		}
	}
	return false;
}
void CSquare::SetCorner(Point p, int index) {
	int size = squareSize;
	squareSize = sqrt((pow(p.x - center.x, 2) + pow(p.y - center.y, 2)) * 2);
}