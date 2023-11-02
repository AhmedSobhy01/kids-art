#include "Output.h"
#include <cmath>

Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr,1);
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}

void Output::DrawSquare(Point P1, GfxInfo SquareGfxInfo, bool selected)const	//Drawing square
{
	color DrawingColor;
	if (selected)
		DrawingColor = UI.HighlightColor;
	else
		DrawingColor = SquareGfxInfo.DrawClr;
	pWind->SetPen(DrawingColor, 1);
	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;
	Point p1, p2;
	SquareGfxInfo.size = 150;
	p1.x = P1.x + SquareGfxInfo.size / 2;
	p1.y = P1.y + SquareGfxInfo.size / 2;
	p2.x = P1.x - SquareGfxInfo.size / 2;
	p2.y = P1.y - SquareGfxInfo.size / 2;
	pWind->DrawRectangle(p1.x, p1.y, p2.x, p2.y, style);

}

void Output::DrawingTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) const	//Drawing Triangle
{
	color drawcolor;
	drawstyle style;
	if (selected) 
		drawcolor = UI.HighlightColor;
	else
		drawcolor = TriangleGfxInfo.DrawClr;
	pWind->SetPen(drawcolor, 1);
	if (TriangleGfxInfo.isFilled) {
		pWind->SetBrush(TriangleGfxInfo.FillClr);
		style = FILLED;
	}
	else
		style = FRAME;
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output::DrawingCircle(Point P1, Point P2,GfxInfo CircleGfxInfo, bool selected)const
{
	color drawcolor;
	drawstyle style;
	if (selected)
		drawcolor = UI.HighlightColor;
	else
		drawcolor = CircleGfxInfo.DrawClr;
	pWind->SetPen(drawcolor, 1);
	if (CircleGfxInfo.isFilled) {
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
		pWind->DrawCircle(P1.x, P1.y, radius, style);
	
}

void Output::DrawingHexagon(Point P1, GfxInfo HexagonGfxInfo, bool selected) const
{
	color drawcolor;
	drawstyle style;
	if (selected)
		drawcolor = UI.HighlightColor;
	else
		drawcolor = HexagonGfxInfo.DrawClr;
	pWind->SetPen(drawcolor, 1);
	if (HexagonGfxInfo.isFilled) {
		style = FILLED;
		pWind->SetBrush(HexagonGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int l = 100;
	Point p1, p2, p3, p4, p5, p6;
	p1.x = P1.x + l / sqrt(3);
	p1.y = P1.y;
	p4.x = P1.x - l / sqrt(3);
	p4.y = P1.y;
	p2.x = P1.x + sqrt(3) * l / 6;
	p2.y = P1.y + 0.5 *l;
	p3.x = P1.x - sqrt(3) * l / 6;
	p3.y = P1.y + 0.5 *l;
	p5.x = P1.x - sqrt(3) * l / 6;
	p5.y = P1.y - 0.5*l;
	p6.x = P1.x + sqrt(3) * l / 6;
	p6.y = P1.y - 0.5 *l;
	int arrayxpoints[6] = { p1.x, p2.x, p3.x, p4.x, p5.x, p6.x };
	int arrayYpoints[6] = { p1.y, p2.y, p3.y, p4.y, p5.y, p6.y };
	pWind->DrawPolygon(arrayxpoints, arrayYpoints, 6, style);
}
//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

