#include "CFigure.h"
#include <string>
using namespace std;

int CFigure::last_ID = 0;

CFigure::CFigure()
{
	Selected = false;
	Hidden = false;
	last_ID++;
	ID = last_ID;
	ReferenceCount = 0;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	ReferenceCount = 0;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	Hidden = false;
	last_ID++;
	ID = last_ID;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

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
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = Fclr != TRANSPARENT_COLOR;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngBorderWidth(int BWidth)
{
	FigGfxInfo.BorderWidth = BWidth;
}

bool CFigure::isHidden() {
	return Hidden;
}

void CFigure::Hide() {
	Hidden = true;
}

void CFigure::UnHide() {
	Hidden = false;
}

bool CFigure::isFilled()
{
	return FigGfxInfo.isFilled;
}

bool CFigure::operator==(CFigure& Fig2)				// Compares the type and the color of the figures
{
	return (Type() == Fig2.Type())&& (GetFillClr() == Fig2.GetFillClr());
}

void CFigure::ResetID()
{
	last_ID = 0;
}


string CFigure::Type(){
	return type;
}
