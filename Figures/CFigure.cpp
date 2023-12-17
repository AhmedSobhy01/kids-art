#include "CFigure.h"

int CFigure::last_ID = 0;

CFigure::CFigure()
{
	Selected = false;
	Hidden = false;
	last_ID++;
	ID = last_ID;
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

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = Fclr != TRANSPARENT_COLOR;
	FigGfxInfo.FillClr = Fclr; 
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


ShapeType CFigure::Type(){
	return type;
}
