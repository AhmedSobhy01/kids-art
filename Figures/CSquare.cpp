#include "CSquare.h"

const int CSquare::squareSize = 150;


CSquare::CSquare(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
}

void CSquare::Draw(Output* pOut) const {
	pOut->DrawSquare(center, squareSize,FigGfxInfo, Selected);
}

int CSquare::getSquareSize() {
	return squareSize;
}
