#include "CHexagon.h"

CHexagon::CHexagon(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
}

void CHexagon::Draw(Output* pOut) const {
	pOut->DrawHexagon(center, FigGfxInfo, Selected);
}

