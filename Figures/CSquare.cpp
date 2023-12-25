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

	Point P1, P2;
	P1.x = Center.x - SquareSize / 2;
	P1.y = Center.y - SquareSize / 2;
	P2.x = Center.x + SquareSize / 2;
	P2.y = Center.y + SquareSize / 2;
	bool cond1 = (P1.x <= P.x) && (P.x <= P2.x);
	bool cond2 = (P1.y <= P.y) && (P.y <= P2.y);
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
						 << " " << ID << " " << Center.x << " " << Center.y << " " << SquareSize << " " << FigGfxInfo.DrawColor << " " << FigGfxInfo.FillColor << endl; // added figure size to handle resized figures
		return;
	}
}

void CSquare::Load(ifstream &FileInputStream)
{
	if (FileInputStream.is_open())
	{
		FileInputStream >> ID >> Center.x >> Center.y >> SquareSize >> FigGfxInfo.DrawColor >> FigGfxInfo.FillColor;
		if (FigGfxInfo.FillColor == TRANSPARENT_COLOR)
			FigGfxInfo.IsFilled = false;
		FigGfxInfo.BorderWidth = 3;
		return;
	}
}

void CSquare::PrintInfo(Output *pOut)
{
	std::string Info = "Square: ID = " + to_string(ID);
	Info += ", Center = (" + to_string(Center.x) + ", " + to_string(Center.y) + ")";
	Info += ", SideLength = " + to_string(SquareSize);
	Info += ", Outline Color: " + FigGfxInfo.DrawColor.ReturnColor();
	Info += ", Fill Color: " + FigGfxInfo.FillColor.ReturnColor();

	pOut->PrintMessage(Info);
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