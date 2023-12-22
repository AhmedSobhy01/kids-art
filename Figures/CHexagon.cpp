#include "CHexagon.h"

const int CHexagon::hexagonSize = 80;

CHexagon::CHexagon() :CFigure()
{
	currentHexagonSize = hexagonSize;
	type = "Hexagon";
}

CHexagon::CHexagon(Point center, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo) {
	this->center = center;
	currentHexagonSize = hexagonSize;
	type = "Hexagon";
}

void CHexagon::Draw(Output* pOut) const {
	pOut->DrawHexagon(center, currentHexagonSize, FigGfxInfo, Selected);
}

int CHexagon::getHexagonSize() {
	return hexagonSize;
}

double CHexagon::calcTriangleArea(double x1, double y1, double x2, double y2, double x3, double y3) {
	return  abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
}

bool CHexagon::CheckSelected(int x, int y) {
	if (Hidden) return false;

	//double r = sqrt(pow(center.x - x, 2) + pow(center.y - y, 2));
	//double theta = atan2((y - center.y), (x - center.x));
	//const int n = 6;
	//return r/currentHexagonSize - cos(cdPi / n) / cos(acos(cos(n * theta + cdPi)) / n)<=0;
	double totalArea = 3 * sqrt(3) * currentHexagonSize * currentHexagonSize / 2;
	double xPointsArray[6];
	double yPointsArray[6];
	double PArea = 0;
	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians
	for (int i = 0; i < 6; i++)
	{
		xPointsArray[i] = center.x + currentHexagonSize * cos(i * angle);
		yPointsArray[i] = center.y + currentHexagonSize * sin(i * angle);
	}
	for (int i = 0; i < 6; i++) {
		PArea += calcTriangleArea(x, y, xPointsArray[i], yPointsArray[i], xPointsArray[(i + 1) % 6], yPointsArray[(i + 1) % 6]);
	}
	double err = totalArea - PArea;
	return -0.001 < err && err < 0.001;
}

Point CHexagon::GetCenter() const
{
	return center;
}

void CHexagon::SetCenter(Point c) {
	if (!Validate(c))return;
	this->center = c;
}

bool CHexagon::Validate(Point c) {
	return (c.y - currentHexagonSize / 2 * sqrt(3)-1) > UI.ToolBarHeight && (c.y + currentHexagonSize / 2 * sqrt(3) +1) < (UI.height - UI.StatusBarHeight);
}

void CHexagon::Save(ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "HEXAGON" << " " << ID << " " << center.x << " " << center.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CHexagon::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> center.x >> center.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.isFilled = false;
		return;
	}
}

void CHexagon::PrintInfo(Output* pOut) {
	string info = "Hexagon: ID = ";
	info += to_string(ID);
	info += ", Center = (";
	info += to_string(center.x);
	info += ", ";
	info += to_string(center.y);
	info += "), SideLength = ";
	info += to_string(currentHexagonSize);
	pOut->PrintMessage(info);
}
bool CHexagon::GetCorner(Point p, int& index) {
	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians
	double errx, erry;
	for (int i = 0; i < 6; i++)
	{

		errx = abs(p.x - (center.x + currentHexagonSize * cos(i * angle)));
		erry = abs(p.y - (center.y + currentHexagonSize * sin(i * angle)));
		if (errx < 2 && erry < 2) {
			index == 0;
			return true;
		}
	}

	return false;
}
bool CHexagon::SetCorner(Point p, int index) {
	int size = currentHexagonSize;
	currentHexagonSize = sqrt(pow(p.x - center.x, 2) + pow(p.y - center.y, 2));
	if (!Validate(center)) { 
		currentHexagonSize = size;
		return false;
	}
	return true;
}
