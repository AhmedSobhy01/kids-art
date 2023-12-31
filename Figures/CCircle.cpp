#include "CCircle.h"
#include "..\GUI\Output.h"

CCircle::CCircle() : CFigure()
{
	TypeName = "Circle";
}

CCircle::CCircle(Point Center, Point Radius, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	this->Center = Center;
	this->Radius = Radius;
	TypeName = "Circle";
}

void CCircle::Draw(Output *pOut)
{
	pOut->DrawCircle(Center, Radius, FigGfxInfo, Selected);
}

bool CCircle::IsPointInside(Point P)
{
	return !Hidden && (sqrt(pow(Center.x - P.x, 2) + pow(Center.y - P.y, 2)) <= sqrt(pow(Center.x - Radius.x, 2) + pow(Center.y - Radius.y, 2)));
}

Point CCircle::GetCenter() const
{
	return Center;
}

void CCircle::SetCenter(Point c)
{
	this->Radius.x += (c.x - this->Center.x);
	this->Radius.y += (c.y - this->Center.y);
	this->Center = c;
}

void CCircle::Save(ofstream &FileOutputStream)
{
	if (FileOutputStream.is_open())
	{
		FileOutputStream << "CIRCLE"
						 << " " << ID << " " << Center.x << " " << Center.y << " " << Radius.x << " " << Radius.y << " " << FigGfxInfo.DrawColor << " " << FigGfxInfo.FillColor << " " << FigGfxInfo.BorderWidth << endl; // added figure size to handle resized figures
		return;
	}
}

void CCircle::Load(ifstream &FileInputStream)
{
	FigGfxInfo.BorderWidth = 3;
	if (FileInputStream.is_open())
	{
		FileInputStream >> ID >> Center.x >> Center.y >> Radius.x >> Radius.y >> FigGfxInfo.DrawColor >> FigGfxInfo.FillColor;
		if (FileInputStream.peek() != '\n')FileInputStream >> FigGfxInfo.BorderWidth;
		if (FigGfxInfo.FillColor == TRANSPARENT_COLOR)
			FigGfxInfo.IsFilled = false;
		return;
	}
}

void CCircle::PrintInfo(Output *pOut)
{
	int Radius = sqrt(pow(Center.x - this->Radius.x, 2) + pow(Center.y - this->Radius.y, 2));

	std::string Info = "Circle: ID = " + to_string(ID);
	Info += ", Center = (" + to_string(Center.x) + ", " + to_string(Center.y) + ")";
	Info += ", Radius = " + to_string(Radius);
	Info += ", Outline Color: " + FigGfxInfo.DrawColor.ReturnColor();
	Info += ", Fill Color: " + FigGfxInfo.FillColor.ReturnColor();

	pOut->PrintMessage(Info);
}

bool CCircle::GetCorner(Point &p, int &index)
{
	// check if the point is on the circle circumeference
	int CurrentRadius = sqrt(pow(Center.x - this->Radius.x, 2) + pow(Center.y - this->Radius.y, 2));
	int PointRadius = sqrt(pow(Center.x - p.x, 2) + pow(Center.y - p.y, 2));
	if (abs(CurrentRadius - PointRadius) < 6)
	{
		index = 0;
		p = Radius;
		return true;
	}
	return false;
}

void CCircle::SetCorner(Point P, int)
{
	this->Radius = P;
}
