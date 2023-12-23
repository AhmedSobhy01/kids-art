#include "CRectangle.h"

CRectangle::CRectangle() :CFigure()
{
	type = "Rectangle";
}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	type = "Rectangle";
}


void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::CheckSelected(int x, int y) {
	if (Hidden) return false;
	int length = abs(Corner1.y - Corner2.y);
	int width = abs(Corner1.x - Corner2.x);

	bool cond1 = Corner1.x + Corner2.x - width <= 2 * x && 2 * x <= Corner1.x + Corner2.x + width;
	bool cond2 = Corner1.y + Corner2.y - length <= 2 * y && 2 * y <= Corner1.y + Corner2.y + length;
	return cond1 && cond2;
}
Point CRectangle::GetCenter() const
{
	return { (Corner1.x + Corner2.x) / 2, (Corner1.y + Corner2.y) / 2 };
}
void CRectangle::SetCenter(Point c) {
	if (!Validate(c))return;
	Point center = { (Corner1.x + Corner2.x) / 2,(Corner1.y + Corner2.y) / 2 };
	int dy = c.y - center.y;
	int dx = c.x - center.x;
	Corner1.x += dx;
	Corner2.x += dx;
	Corner1.y += dy;
	Corner2.y += dy;
}

bool CRectangle::Validate(Point c) {
	Point center = { (Corner1.x + Corner2.x) / 2,(Corner1.y + Corner2.y) / 2 };
	int dy = c.y - center.y;
	int dx = c.x - center.x;
	bool cond1 = (Corner1.y + dy - 1) > UI.ToolBarHeight && (Corner1.y + dy + 1) < (UI.height - UI.StatusBarHeight);
	bool cond2 = (Corner2.y + dy - 1) > UI.ToolBarHeight && (Corner2.y + dy + 1) < (UI.height - UI.StatusBarHeight);
	return cond1 && cond2;

}

void CRectangle::Save(ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "RECTANGLE" << " " << ID << " " << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << endl;
		return;
	}
}

void CRectangle::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr;
		if (FigGfxInfo.FillClr == TRANSPARENT_COLOR)
			FigGfxInfo.isFilled = false;
		return;
	}
}

void CRectangle::PrintInfo(Output* pOut) {
	string info = "Rectangle: ID = ";
	info += to_string(ID);
	info += ", Corner1 = (";
	info += to_string(Corner1.x);
	info += ", ";
	info += to_string(Corner1.y);
	info += "), Corner2 = (";
	info += to_string(Corner2.x);
	info += ", ";
	info += to_string(Corner2.y);
	info += "), Vertical Length = ";
	info += to_string(abs(Corner1.y - Corner2.y));
	info += ", Horizontal Width = ";
	info += to_string(abs(Corner1.x - Corner2.x));
	pOut->PrintMessage(info);
}

bool CRectangle::GetCorner(Point p, int& index) {
	int Xarr[2] = { Corner1.x ,Corner2.x };
	int Yarr[2] = { Corner1.y ,Corner2.y };
	int errx, erry;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			erry = abs(p.y - Yarr[i]);
			errx = abs(p.x - Xarr[j]);
			if (errx < 5 && erry < 5) {
				index = 2 * i + j;
				return true;
			}
		}
	}
	return false;
}
bool CRectangle::SetCorner(Point p, int index) {
	Point OldC1, OldC2;
	OldC1 = Corner1;
	OldC2 = Corner2;
	Point Center = { (Corner1.x + Corner2.x) / 2, (Corner1.y + Corner2.y) / 2 };
	int* Xarr[2] = { &Corner1.x ,&Corner2.x };
	int* Yarr[2] = { &Corner1.y ,&Corner2.y };
	*Xarr[index % 2] = p.x;
	*Yarr[index / 2] = p.y;
	if (!Validate(Center)) {
		Corner1 = OldC1;
		Corner2 = OldC2;
		return false;
	}
	return true;

}
