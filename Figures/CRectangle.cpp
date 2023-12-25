#include "CRectangle.h"

CRectangle::CRectangle() : CFigure()
{
	TypeName = "Rectangle";
}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	TypeName = "Rectangle";
}

void CRectangle::Draw(Output *pOut)
{
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::IsPointInside(Point P)
{
	if (Hidden)
		return false;
	int length = abs(Corner1.y - Corner2.y);
	int width = abs(Corner1.x - Corner2.x);

	bool cond1 = Corner1.x + Corner2.x - width <= 2 * P.x && 2 * P.x <= Corner1.x + Corner2.x + width;
	bool cond2 = Corner1.y + Corner2.y - length <= 2 * P.y && 2 * P.y <= Corner1.y + Corner2.y + length;
	return cond1 && cond2;
}
Point CRectangle::GetCenter() const
{
	return {(Corner1.x + Corner2.x) / 2, (Corner1.y + Corner2.y) / 2};
}
void CRectangle::SetCenter(Point c)
{
	Point Center = {(Corner1.x + Corner2.x) / 2, (Corner1.y + Corner2.y) / 2};
	int dy = c.y - Center.y;
	int dx = c.x - Center.x;
	Corner1.x += dx;
	Corner2.x += dx;
	Corner1.y += dy;
	Corner2.y += dy;
}

void CRectangle::Save(ofstream &FileOutputStream)
{
	if (FileOutputStream.is_open())
	{
		FileOutputStream << "RECTANGLE"
						 << " " << ID << " " << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " " << FigGfxInfo.DrawColor << " " << FigGfxInfo.FillColor << " " << FigGfxInfo.BorderWidth << endl; // added figure size to handle resized figures
		return;
	}
}

void CRectangle::Load(ifstream &FileInputStream)
{
	if (FileInputStream.is_open())
	{
		FileInputStream >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> FigGfxInfo.DrawColor >> FigGfxInfo.FillColor >> FigGfxInfo.BorderWidth;
		if (FigGfxInfo.FillColor == TRANSPARENT_COLOR)
			FigGfxInfo.IsFilled = false;
		return;
	}
}

void CRectangle::PrintInfo(Output *pOut)
{
	std::string Info = "Rectangle: ID = " + to_string(ID);
	Info += ", Start Point = (" + to_string(Corner1.x) + ", " + to_string(Corner1.y) + ")";
	Info += ", End Point = (" + to_string(Corner2.x) + ", " + to_string(Corner2.y) + ")";
	Info += ", Vertical Length = " + to_string(abs(Corner1.y - Corner2.y));
	Info += ", Horizontal Width = " + to_string(abs(Corner1.x - Corner2.x));
	Info += ", Outline Color: " + FigGfxInfo.DrawColor.ReturnColor();
	Info += ", Fill Color: " + FigGfxInfo.FillColor.ReturnColor();
	pOut->PrintMessage(Info);
}

bool CRectangle::GetCorner(Point &p, int &index)
{
	// the index is encoded by the function as a binary value
	//  00 means Corner1.x Corner1.y
	//  01 means Corner2.x Corner1.y
	//  10 means Corner1.x Corner2.y
	//  11 means Corner2.x Corner2.y
	//  which can be easily get decoded by the SetCorner function to set the apppropriate corner

	int Xarr[2] = {Corner1.x, Corner2.x};
	int Yarr[2] = {Corner1.y, Corner2.y};
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
		index = i;
		p = {Xarr[i % 2], Yarr[i / 2]};
		return true;
	}
	return false;
}
void CRectangle::SetCorner(Point p, int index)
{
	int *Xarr[2] = {&Corner1.x, &Corner2.x};
	int *Yarr[2] = {&Corner1.y, &Corner2.y};
	*Xarr[index % 2] = p.x;
	*Yarr[index / 2] = p.y;
}
