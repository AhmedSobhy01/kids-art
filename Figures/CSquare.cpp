#include "CSquare.h"

const int CSquare::DefaultSquareSize = 150;

CSquare::CSquare() : CFigure()
{
	SquareSize = DefaultSquareSize;
	TypeName = "Square";
}

CSquare::CSquare(Point Center, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	SquareSize = DefaultSquareSize;
	this->Center = Center;
	TypeName = "Square";
}

void CSquare::Draw(Output *pOut)
{
	pOut->DrawSquare(Center, SquareSize, FigGfxInfo, Selected);
}

int CSquare::GetDefaultSquareSize()
{
	return DefaultSquareSize;
}

bool CSquare::IsPointInside(Point P)
{
	if (Hidden)
		return false;

	Point p1, p2;
	p1.x = Center.x - SquareSize / 2;
	p1.y = Center.y - SquareSize / 2;
	p2.x = Center.x + SquareSize / 2;
	p2.y = Center.y + SquareSize / 2;
	bool cond1 = (p1.x <= P.x) && (P.x <= p2.x);
	bool cond2 = (p1.y <= P.y) && (P.y <= p2.y);
	return cond1 && cond2;
}
Point CSquare::GetCenter() const
{
	return Center;
}
void CSquare::SetCenter(Point Center)
{
	this->Center = Center;
}

void CSquare::Save(ofstream &FileOutputStream)
{
	if (FileOutputStream.is_open())
	{
		FileOutputStream << "SQUARE"
						 << " " << ID << " " << Center.x << " " << Center.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CSquare::Load(ifstream &fin)
{
	if (fin.is_open())
	{
		fin >> ID >> Center.x >> Center.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.IsFilled = false;
		return;
	}
}

void CSquare::PrintInfo(Output *pOut)
{
	string info = "Square: ID = ";
	info += to_string(ID);
	info += ", Center = (";
	info += to_string(Center.x);
	info += ", ";
	info += to_string(Center.y);
	info += "), Length = ";
	info += to_string(SquareSize);
	pOut->PrintMessage(info);
}

bool CSquare::GetCorner(Point &p, int &index)
{
	int Xarr[2] = {Center.x - SquareSize / 2, Center.x + SquareSize / 2};
	int Yarr[2] = {Center.y - SquareSize / 2, Center.y + SquareSize / 2};
	int ErrX = 100, ErrY = 100;
	int i = 0;
	while (i < 4 && (ErrX >= 6 || ErrY >= 6))
	{
		ErrX = abs(p.x - Xarr[i % 2]);
		ErrY = abs(p.y - Yarr[i / 2]);
		++i;
	}
	--i;
	if (ErrX < 6 && ErrY < 6)
	{
		index = 0;
		p = {Center.x + SquareSize / 2, Center.y + SquareSize / 2};
		return true;
	}
	return false;
}
void CSquare::SetCorner(Point p, int index)
{
	SquareSize = sqrt((pow(p.x - Center.x, 2) + pow(p.y - Center.y, 2)) * 2);
}