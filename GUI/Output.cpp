#include "Output.h"
#include <cmath>

Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;

	UI.StatusBarHeight = 45;
	UI.ToolBarHeight = 45;
	UI.MenuItemWidth = 45;

	UI.ColorMenuItemWidth = 40;
	UI.ColorMenuWidth = COLOR_MENU_ITM_COUNT * UI.ColorMenuItemWidth + 20;
	UI.ColorMenuHeight = 60;
  
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

	// Initialize Color Menu Window Pointer
	colorMenuWind = nullptr;
  
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
void Output::CreateColorMenuWind(int x)
{
	colorMenuWind = new window(UI.ColorMenuWidth, UI.ColorMenuHeight, (UI.wx + x) < UI.width ? (UI.wx + x) : (UI.width - 10), UI.wy + UI.ToolBarHeight + 35);
	colorMenuWind->ChangeTitle("Colors");
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawColorMenuItems() const
{
	string ColorMenuItemImages[COLOR_MENU_ITM_COUNT];
	ColorMenuItemImages[COLOR_MENU_ITM_BLACK] = "images\\Colors\\Black.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_RED] = "images\\Colors\\Red.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_BLUE] = "images\\Colors\\Blue.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_GREEN] = "images\\Colors\\Green.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_MAGENTA] = "images\\Colors\\Magenta.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_ORANGE] = "images\\Colors\\Orange.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_BROWN] = "images\\Colors\\Brown.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_CYAN] = "images\\Colors\\Cyan.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_YELLOW] = "images\\Colors\\Yellow.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_TRANSPARENT] = "images\\Colors\\Transparent.jpg";

	for (int i = 0; i < COLOR_MENU_ITM_COUNT; i++)
		colorMenuWind->DrawImage(ColorMenuItemImages[i], i * UI.ColorMenuItemWidth, 0, UI.ColorMenuItemWidth, UI.ColorMenuItemWidth);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::OpenColorMenuWind(int x)
{
	CreateColorMenuWind(x); // Intializes a new window and sets data memeber to that pointer 

	DrawColorMenuItems(); // Draws color images to color menu window
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CloseColorMenuWind()
{
	delete colorMenuWind;
	colorMenuWind = nullptr;
}
//////////////////////////////////////////////////////////////////////////////////////////
window* Output::GetColorMenuWind() const {
	return colorMenuWind;
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
	MenuItemImages[PlayMode] = "images\\DrawMode\\PlayMode.jpg";
	MenuItemImages[Rect] = "images\\DrawMode\\Rectangle.jpg";
	MenuItemImages[Circle] = "images\\DrawMode\\Circle.jpg";
	MenuItemImages[Square] = "images\\DrawMode\\Square.jpg";
	MenuItemImages[Triangle] = "images\\DrawMode\\Triangle.jpg";
	MenuItemImages[Hexagon] = "images\\DrawMode\\Hexagon.jpg";
	MenuItemImages[Outline] = "images\\DrawMode\\Outline.jpg";
	MenuItemImages[BorderWidth] = "images\\DrawMode\\BorderWidth.jpg";
	MenuItemImages[ForegroundColor] = "images\\DrawMode\\ForegroundColor.jpg";
	MenuItemImages[BackgroundColor] = "images\\DrawMode\\BackgroundColor.jpg";
	MenuItemImages[Fill] = "images\\DrawMode\\Fill.jpg";
	MenuItemImages[Select] = "images\\DrawMode\\Select.jpg";
	MenuItemImages[Remove] = "images\\DrawMode\\Remove.jpg";
	MenuItemImages[Move] = "images\\DrawMode\\Move.jpg";
	MenuItemImages[Resize] = "images\\DrawMode\\Resize.jpg";
	MenuItemImages[DragMove] = "images\\DrawMode\\DragMove.jpg";
	MenuItemImages[DragResize] = "images\\DrawMode\\DragResize.jpg";
	MenuItemImages[Undo] = "images\\DrawMode\\Undo.jpg";
	MenuItemImages[Redo] = "images\\DrawMode\\Redo.jpg";
	MenuItemImages[ClearAll] = "images\\DrawMode\\ClearAll.jpg";
	MenuItemImages[StartRecording] = "images\\DrawMode\\StartRecording.jpg";
	MenuItemImages[StopRecording] = "images\\DrawMode\\StopRecording.jpg";
	MenuItemImages[PlayRecording] = "images\\DrawMode\\PlayRecording.jpg";
	MenuItemImages[ArtBoardBackground] = "images\\DrawMode\\ArtboardBackground.jpg";
	MenuItemImages[Open] = "images\\DrawMode\\Open.jpg";
	MenuItemImages[Save] = "images\\DrawMode\\Save.jpg";
	MenuItemImages[Exit] = "images\\DrawMode\\Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	string PlayMenuItems[PLAY_ITM_COUNT];
	PlayMenuItem[DrawMode] = "images\\PlayMode\\draw-mode.jpg";
	PlayMenuItem[ExitPlay] = "images\\DrawMode\\Exit.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(PlayMenuItem[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

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
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const		//Drawing Rectangle
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
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
	int squareSize = 150;
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;


	Point p1, p2;
	p1.x = P1.x + squareSize / 2;
	p1.y = P1.y + squareSize / 2;
	p2.x = P1.x - squareSize / 2;
	p2.y = P1.y - squareSize / 2;


	pWind->DrawRectangle(p1.x, p1.y, p2.x, p2.y, style);
}

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) const	//Drawing Triangle
{
	color DrawingClr;
	drawstyle style;
	if (selected) 
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = TriangleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	if (TriangleGfxInfo.isFilled) {
		pWind->SetBrush(TriangleGfxInfo.FillClr);
		style = FILLED;
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output::DrawCircle(Point P1, Point P2,GfxInfo CircleGfxInfo, bool selected)const
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

void Output::DrawHexagon(Point P1, GfxInfo HexagonGfxInfo, bool selected) const
{
	int hexagonSize = 80;
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

	
	int xPointsArray[6];
	int yPointsArray[6];

	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians

	for (int i = 0; i < 6; i++) {
		xPointsArray[i] = P1.x + hexagonSize * cos(i * angle);
		yPointsArray[i] = P1.y + hexagonSize * sin(i * angle);
	}


	pWind->DrawPolygon(xPointsArray, yPointsArray, 6, style);
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;

	if (colorMenuWind) delete colorMenuWind;
}

