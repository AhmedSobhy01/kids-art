#include "CHexagon.h"

const int CHexagon::hexagonSize = 80;

CHexagon::CHexagon(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
}

void CHexagon::Draw(Output* pOut) const {
	pOut->DrawHexagon(center, hexagonSize, FigGfxInfo, Selected);
}

int CHexagon::getHexagonSize() {
	return hexagonSize;
}
