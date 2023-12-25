#include "CFigure.h"
#include <string>
using namespace std;

int CFigure::LastID = 0;

CFigure::CFigure()
{
	Selected = false;
	Hidden = false;
	LastID++;
	ID = LastID;
	ReferenceCount = 0;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	ReferenceCount = 0;
	FigGfxInfo = FigureGfxInfo; // Default status is non-filled.
	Selected = false;
	Hidden = false;
	LastID++;
	ID = LastID;
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}

color CFigure::GetDrawClr() const
{
	return FigGfxInfo.DrawClr;
}

color CFigure::GetFillClr() const
{
	return FigGfxInfo.FillClr;
}

int CFigure::GetBorderWidth() const
{
	return FigGfxInfo.BorderWidth;
}

void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.IsFilled = Fclr != TRANSPARENT_COLOR;
	FigGfxInfo.FillClr = Fclr;
}

void CFigure::ChngBorderWidth(int BWidth)
{
	FigGfxInfo.BorderWidth = BWidth;
}

bool CFigure::isHidden()
{
	return Hidden;
}

void CFigure::Hide()
{
	Hidden = true;
}

void CFigure::UnHide()
{
	Hidden = false;
}

bool CFigure::IsFilled()
{
	return FigGfxInfo.IsFilled;
}

bool CFigure::operator==(CFigure &Fig2)
{
	return (Type() == Fig2.Type()) && (GetFillClr() == Fig2.GetFillClr());
}

void CFigure::ResetID()
{
	LastID = 0;
}

string CFigure::Type()
{
	return TypeName;
}
