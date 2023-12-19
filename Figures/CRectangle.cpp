#include "CRectangle.h"

CRectangle::CRectangle() :CFigure()
{
}

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
	if (Hidden) return false;
	int length = abs(Corner1.y - Corner2.y);
	int width = abs(Corner1.x - Corner2.x);

	bool cond1 = Corner1.x + Corner2.x - width < 2 * x && 2 * x < Corner1.x + Corner2.x + width; 
	bool cond2 = Corner1.y + Corner2.y - length < 2 * y && 2 * y < Corner1.y + Corner2.y + length;
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
	bool cond1 = Corner1.y + dy >= UI.ToolBarHeight && Corner1.y + dy <= (UI.height - UI.StatusBarHeight);
	bool cond2 = Corner2.y + dy >= UI.ToolBarHeight && Corner2.y + dy <= (UI.height - UI.StatusBarHeight);
	return cond1 && cond2;

}

void CRectangle::Save(ofstream& fout)
{
	if (fout.is_open())
	{
		fout << "RECTANGLE" << " " << ID << " " << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " " << FigGfxInfo.DrawClr << " " << FigGfxInfo.FillClr << " " << FigGfxInfo.isFilled << " " << Selected << endl;
		return;
	}
}

void CRectangle::Load(ifstream& fin)
{
	if (fin.is_open())
	{
		fin >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> FigGfxInfo.DrawClr >> FigGfxInfo.FillClr >> FigGfxInfo.isFilled >> Selected;
		return;
	}
}

void CRectangle::PrintInfo(Output* pOut) {
	string info = "Rectangle: Corner1 = (";
	info += to_string(Corner1.x);
	info += ", ";
	info += to_string(Corner1.y);
	info += "), Corner2 = (";
	info += to_string(Corner2.x);
	info += ", ";
	info += to_string(Corner2.y);
	info += "), Vertical Length = ";
	info += to_string(abs(Corner1.y-Corner2.y));
	info += ", Horizontal Width = ";
	info += to_string(abs(Corner1.x - Corner2.x));
	pOut->PrintMessage(info);
}
