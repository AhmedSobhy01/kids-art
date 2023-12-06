#include "CHexagon.h"

const int CHexagon::hexagonSize = 80;

CHexagon::CHexagon(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	type = HEXAGON;
}

void CHexagon::Draw(Output* pOut) const {
	pOut->DrawHexagon(center, hexagonSize, FigGfxInfo, Selected);
}

int CHexagon::getHexagonSize() {
	return hexagonSize;
}

double CHexagon::calcTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3) {
	return  abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
}

bool CHexagon::CheckSelected(int x, int y) {
	//double r = sqrt(pow(center.x - x, 2) + pow(center.y - y, 2));
	//double theta = atan2((y - center.y), (x - center.x));
	//const int n = 6;
	//return r/hexagonSize - cos(cdPi / n) / cos(acos(cos(n * theta + cdPi)) / n)<=0;
	double totalArea = 3 * sqrt(3) * hexagonSize * hexagonSize / 2;
	double xPointsArray[6];
	double yPointsArray[6];
	double PArea = 0;
	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians
	for (int i = 0; i < 6; i++)
	{
		xPointsArray[i] = center.x + hexagonSize * cos(i * angle);
		yPointsArray[i] = center.y + hexagonSize * sin(i * angle);
	}
	for (int i = 0; i < 6; i++) {
		PArea += calcTriangleArea(x, y, xPointsArray[i], yPointsArray[i], xPointsArray[(i + 1) % 6], yPointsArray[(i + 1) % 6]);
	}
	double err = totalArea - PArea;
	return -0.001 < err && err < 0.001;
}

void CHexagon::SetCenter(Point c) {
	this->center = c;
}

bool CHexagon::Validate(Point c) {
	return (c.y - hexagonSize / 2 * sqrt(3)) > UI.ToolBarHeight && (c.y + hexagonSize / 2 * sqrt(3)) <= (UI.height - UI.StatusBarHeight);
}