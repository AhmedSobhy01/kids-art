#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	type = RECTANGLE;
}


void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::CheckSelected(int x, int y) {
	bool cond1 = Corner1.x < x && x < Corner2.x;
	bool cond2 = Corner1.y < y && y < Corner2.y;
	return cond1 && cond2;
}
Point CRectangle::GetCenter() const
{
	return { (Corner1.x + Corner2.x) / 2, (Corner1.y + Corner2.y) / 2 };
}
void CRectangle::SetCenter(Point c) {
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
	bool cond1 = Corner1.y + dy >= UI.ToolBarHeight && Corner1.y + dy <= (UI.height - UI.StatusBarHeight);
	bool cond2 = Corner2.y + dy >= UI.ToolBarHeight && Corner2.y + dy <= (UI.height - UI.StatusBarHeight);
	return cond1 && cond2;

}