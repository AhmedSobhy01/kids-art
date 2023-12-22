#include "Output.h"
#include <cmath>

Output::Output()
{
	// Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 45;
	UI.MenuItemWidth = 45;

	UI.ColorMenuItemWidth = 40;
	UI.ColorMenuWidth = COLOR_MENU_ITM_COUNT * UI.ColorMenuItemWidth + 13;
	UI.ColorMenuHeight = 60;

	UI.DrawColor = BLUE;				   // Drawing color
	UI.FillColor = TRANSPARENT_COLOR;		// Filling color
	UI.MsgColor = RED;					   // Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW; // Background color
	UI.HighlightColor = MAGENTA;		   // This color should NOT be used to draw figures, use if for highlight only
	UI.StatusBarColor = TURQUOISE;		   // Status bar background color
	UI.PenWidth = 3;					   // Width of the figures frames

	// Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	// Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	// Initialize Color Menu Window Pointer
	colorMenuWind = NULL;

	CreateDrawToolBar();
	CreateStatusBar();
}

Input *Output::CreateInput() const
{
	Input *pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window *Output::CreateWind(int w, int h, int x, int y) const
{
	window *pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateColorMenuWind(int x, bool withTransparent)
{
	int xPos = UI.wx + x;
	if ((xPos + UI.ColorMenuWidth) > UI.width || x < UI.wx)
		xPos = (UI.width - UI.ColorMenuWidth) / 2;

	colorMenuWind = new window(UI.ColorMenuWidth, UI.ColorMenuHeight, xPos, UI.wy + UI.ToolBarHeight + 35);
	colorMenuWind->ChangeTitle("Colors");
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawColorMenuItems(bool withTransparent) const
{
	int arraySize = (withTransparent ? COLOR_MENU_ITM_COUNT : COLOR_MENU_ITM_COUNT - 1);
	string *ColorMenuItemImages = new string[arraySize];

	ColorMenuItemImages[COLOR_MENU_ITM_BLACK] = "images\\Colors\\Black.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_RED] = "images\\Colors\\Red.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_BLUE] = "images\\Colors\\Blue.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_GREEN] = "images\\Colors\\Green.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_MAGENTA] = "images\\Colors\\Magenta.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_ORANGE] = "images\\Colors\\Orange.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_BROWN] = "images\\Colors\\Brown.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_CYAN] = "images\\Colors\\Cyan.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_YELLOW] = "images\\Colors\\Yellow.jpg";
	ColorMenuItemImages[COLOR_MENU_ITM_GOLD] = "images\\Colors\\Gold.jpg";

	if (withTransparent)
		ColorMenuItemImages[COLOR_MENU_ITM_TRANSPARENT] = "images\\Colors\\Transparent.jpg";

	for (int i = 0; i < arraySize; i++)
		colorMenuWind->DrawImage(ColorMenuItemImages[i], i * UI.ColorMenuItemWidth, 0, UI.ColorMenuItemWidth, UI.ColorMenuItemWidth);

	delete[] ColorMenuItemImages;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::OpenColorMenuWind(int x, bool withTransparent)
{
	UI.ColorMenuWidth = (withTransparent ? COLOR_MENU_ITM_COUNT : COLOR_MENU_ITM_COUNT - 1) * UI.ColorMenuItemWidth + 13;

	CreateColorMenuWind(x, withTransparent); // Initializes a new window and sets data member to that pointer

	DrawColorMenuItems(withTransparent); // Draws color images to color menu window
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CloseColorMenuWind()
{
	if (colorMenuWind)
	{
		delete colorMenuWind;
		colorMenuWind = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

window *Output::GetColorMenuWind() const
{
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
	// Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	// Draw mode toolbar images
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_PLAY_MODE] = "images\\DrawMode\\PlayMode.jpg";
	MenuItemImages[ITM_RECT] = "images\\DrawMode\\Rectangle.jpg";
	MenuItemImages[ITM_CIRCLE] = "images\\DrawMode\\Circle.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\DrawMode\\Square.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\DrawMode\\Triangle.jpg";
	MenuItemImages[ITM_HEXAGON] = "images\\DrawMode\\Hexagon.jpg";
	MenuItemImages[ITM_OUTLINE_COLOR] = "images\\DrawMode\\ForegroundColor.jpg";
	MenuItemImages[ITM_FILL_COLOR] = "images\\DrawMode\\BackgroundColor.jpg";
	MenuItemImages[ITM_SELECT] = "images\\DrawMode\\Select.jpg";
	MenuItemImages[ITM_REMOVE] = "images\\DrawMode\\Remove.jpg";
	MenuItemImages[ITM_MOVE] = "images\\DrawMode\\Move.jpg";
	MenuItemImages[ITM_DRAG_MOVE] = "images\\DrawMode\\DragMove.jpg";
	MenuItemImages[ITM_DRAG_RESIZE] = "images\\DrawMode\\DragResize.jpg";
	MenuItemImages[ITM_UNDO] = "images\\DrawMode\\Undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\DrawMode\\Redo.jpg";
	MenuItemImages[ITM_CLEAR_ALL] = "images\\DrawMode\\ClearAll.jpg";
	MenuItemImages[ITM_START_RECORDING] = "images\\DrawMode\\StartRecording.jpg";
	MenuItemImages[ITM_STOP_RECORDING] = "images\\DrawMode\\StopRecording.jpg";
	MenuItemImages[ITM_PLAY_RECORDING] = "images\\DrawMode\\PlayRecording.jpg";
	MenuItemImages[ITM_BACKGROUND_COLOR] = "images\\DrawMode\\ArtboardBackground.jpg";
	MenuItemImages[ITM_TOGGLE_SOUND] = "images\\DrawMode\\ToggleSound.jpg";
	MenuItemImages[ITM_OPEN] = "images\\DrawMode\\Open.jpg";
	MenuItemImages[ITM_SAVE] = "images\\DrawMode\\Save.jpg";
	MenuItemImages[ITM_EXIT] = "images\\DrawMode\\Exit.jpg";

	// Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	// Clear toolbar
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	UI.InterfaceMode = MODE_PLAY;

	// Draw mode toolbar images
	string PlayMenuItems[PLAY_ITM_COUNT];
	PlayMenuItems[ITM_DRAW_MODE] = "images\\PlayMode\\DrawMode.jpg";
	PlayMenuItems[ITM_PICKBYSHAPE] = "images\\PlayMode\\PickByShape.jpg";
	PlayMenuItems[ITM_PICKBYCOLOR] = "images\\PlayMode\\PickByColor.jpg";
	PlayMenuItems[ITM_PICKBYSHAPEANDCOLOR] = "images\\PlayMode\\PickByShapeAndColor.jpg";
	PlayMenuItems[ITM_EXIT_PLAY] = "images\\DrawMode\\Exit.jpg";

	// Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(PlayMenuItems[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const // Prints a message on status bar
{
	ClearStatusBar(); // First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - int(UI.StatusBarHeight / 1.2), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const // Get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const // Get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCurrentPenWidth() const // Get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const // Drawing Rectangle
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; // Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
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
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawSquare(Point P1, int squareSize, GfxInfo SquareGfxInfo, bool selected) const // Drawing square
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
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
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) const // Drawing Triangle
{
	color DrawingClr;
	drawstyle style;
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = TriangleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	if (TriangleGfxInfo.isFilled)
	{
		pWind->SetBrush(TriangleGfxInfo.FillClr);
		style = FILLED;
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected) const
{
	color drawcolor;
	drawstyle style;
	if (selected)
		drawcolor = UI.HighlightColor;
	else
		drawcolor = CircleGfxInfo.DrawClr;

	pWind->SetPen(drawcolor, UI.PenWidth);
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
	pWind->DrawCircle(P1.x, P1.y, radius, style);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawHexagon(Point P1, int hexagonSize, GfxInfo HexagonGfxInfo, bool selected) const
{

	color drawcolor;
	drawstyle style;
	if (selected)
		drawcolor = UI.HighlightColor;
	else
		drawcolor = HexagonGfxInfo.DrawClr;

	pWind->SetPen(drawcolor, UI.PenWidth);
	if (HexagonGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexagonGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int xPointsArray[6];
	int yPointsArray[6];

	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians

	for (int i = 0; i < 6; i++)
	{
		xPointsArray[i] = P1.x + hexagonSize * cos(i * angle);
		yPointsArray[i] = P1.y + hexagonSize * sin(i * angle);
	}

	pWind->DrawPolygon(xPointsArray, yPointsArray, 6, style);
}
//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	delete pWind;

	if (colorMenuWind)
		delete colorMenuWind;
}
