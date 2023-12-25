#include "CFigure.h"
#include <string>

int CFigure::LastID = 0;

CFigure::CFigure()
{
	Selected = false;
	Hidden = false;
	LastID++;
	ID = LastID;
	ReferenceCount = 0;
}

CFigure::CFigure(GfxInfo FigureGfxInfo) : CFigure()
{
	FigGfxInfo = FigureGfxInfo; // Default status is non-filled.
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}

color CFigure::GetDrawColor() const
{
	return FigGfxInfo.DrawColor;
}

color CFigure::GetFillColor() const
{
	return FigGfxInfo.FillColor;
}

int CFigure::GetBorderWidth() const
{
	return FigGfxInfo.BorderWidth;
}

void CFigure::ChangeDrawColor(color Dclr)
{
	FigGfxInfo.DrawColor = Dclr;
}

void CFigure::ChangeFillColor(color Fclr)
{
	FigGfxInfo.IsFilled = Fclr != TRANSPARENT_COLOR;
	FigGfxInfo.FillColor = Fclr;
}

void CFigure::ChangeBorderWidth(int BWidth)
{
	FigGfxInfo.BorderWidth = BWidth;
}

bool CFigure::IsHidden()
{
	return Hidden;
}

void CFigure::Hide()
{
	Hidden = true;
}

void CFigure::Unhide()
{
	Hidden = false;
}

bool CFigure::IsFilled()
{
	return FigGfxInfo.IsFilled;
}

bool CFigure::operator==(CFigure& Fig2)				// Compares the type and the color of the figures
{
	return (Type() == Fig2.Type()) && (GetFillColor() == Fig2.GetFillColor());
}

void CFigure::ResetID()
{
	LastID = 0;
}

std::string CFigure::Type()
{
	return TypeName;
}
