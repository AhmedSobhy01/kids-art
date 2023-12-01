#include "CTriangle.h"


CTriangle::CTriangle(Point P1, Point P2,Point P3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	this->P1 = P1;
	this->P2 = P2;
	this->P3 = P3;
}


void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTriangle(P1, P2, P3,FigGfxInfo, Selected);
}