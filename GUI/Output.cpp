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
	UI.ColorMenuWidth = COLOR_MENU_ITM_COUNT * UI.ColorMenuItemWidth + 40;
	UI.ColorMenuHeight = UI.ColorMenuItemWidth + 16;

	UI.DrawColor = BLUE;			  // Drawing color
	UI.FillColor = TRANSPARENT_COLOR; // Filling color
	UI.MsgColor = TEXT;				  // Messages color
	UI.BkGrndColor = BASE;			  // Background color
	UI.HighlightColor = MAUVE;		  // This color should NOT be used to draw figures, use if for highlight only
	UI.StatusBarColor = SURFACE0;	  // Status bar background color
	UI.PenWidth = 3;				  // Width of the figures frames

	// Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	// Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	// Initialize Color Menu Window Pointer
	colorMenuWind = NULL;

	IsPlayingRecording = false;
	PlayActionSoundEnabled = true;

	CreateDrawToolBar();
	CreateStatusBar();
	pWind->UpdateBuffer();
	lastMessage = "";
}

Input *Output::CreateInput() const
{
	Input *pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//


void Output::UpdateBuffer() {
	pWind->UpdateBuffer();
}

window *Output::CreateWind(int w, int h, int x, int y) const
{
	window *pW = new window(w, h, x, y);
	pW->SetBuffering(true);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);

	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	pW->UpdateBuffer();
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
	const int arraySize = COLOR_MENU_ITM_COUNT - 1;
	color colors[arraySize] = {PINK, RED, PEACH, YELLOW, GREEN, SKY, BLUE, LAVENDER, BASE, BLACK};

	colorMenuWind->DrawRectangle(0, 0, UI.ColorMenuWidth, UI.ColorMenuHeight);
	for (int i = 0; i < arraySize; i++)
	{
		colorMenuWind->SetBrush(colors[i]);
		colorMenuWind->SetPen(BLACK, 1);
		colorMenuWind->DrawCircle(i * UI.ColorMenuItemWidth + (UI.ColorMenuItemWidth / 2), UI.ColorMenuItemWidth / 2, UI.ColorMenuItemWidth / 2 - 4, FILLED);
	}
	if (withTransparent)
	{
		int xArray[12] = {-8, 0, 8, 16, 8, 16, 8, 0, -8, -16, -8, -16};
		int yArray[12] = {-16, -8, -16, -8, 0, 8, 16, 8, 16, 8, 0, -8};
		for (int i = 0; i < 12; i++)
		{
			xArray[i] *= 0.9;
			yArray[i] *= 0.9;
			xArray[i] += (arraySize)*UI.ColorMenuItemWidth + (UI.ColorMenuItemWidth / 2) - 2;
			yArray[i] += (UI.ColorMenuItemWidth / 2);
		}
		colorMenuWind->SetBrush(BLACK);
		colorMenuWind->SetPen(BLACK, 1);
		colorMenuWind->DrawPolygon(xArray, yArray, 12, FILLED);
	}
	pWind->UpdateBuffer();
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

void Output::ClearStatusBar()
{
	// Clear Status bar by drawing a filled white rectangle
	lastMessage = "";
	CreateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	pWind->SetPen(SURFACE0, 1);
	pWind->SetBrush(SURFACE0);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	// Draw mode toolbar images
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_PLAY_MODE] = "images\\DrawMode\\PlayMode.jpg";
	MenuItemImages[ITM_RECT] = "images\\DrawMode\\Rectangle.jpg";
	MenuItemImages[ITM_CIRCLE] = "images\\DrawMode\\Circle.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\DrawMode\\Square.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\DrawMode\\Triangle.jpg";
	MenuItemImages[ITM_HEXAGON] = "images\\DrawMode\\Hexagon.jpg";
	MenuItemImages[ITM_BORDER_WIDTH] = "images\\DrawMode\\BorderWidthMed.jpg";
	MenuItemImages[ITM_OUTLINE_COLOR] = "images\\DrawMode\\ForegroundColor.jpg";
	MenuItemImages[ITM_FILL_COLOR] = "images\\DrawMode\\BackgroundColor.jpg";
	MenuItemImages[ITM_SELECT] = "images\\DrawMode\\Select.jpg";
	MenuItemImages[ITM_REMOVE] = "images\\DrawMode\\Remove.jpg";
	MenuItemImages[ITM_MOVE] = "images\\DrawMode\\Move.jpg";
	MenuItemImages[ITM_DRAG_MOVE] = "images\\DrawMode\\DragMove.jpg";
	MenuItemImages[ITM_DRAG_RESIZE] = "images\\DrawMode\\DragResize.jpg";
	MenuItemImages[ITM_PLAY_RECORDING] = "images\\DrawMode\\PlayRecording.jpg";
	MenuItemImages[ITM_UNDO] = "images\\DrawMode\\Undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\DrawMode\\Redo.jpg";
	MenuItemImages[ITM_CLEAR_ALL] = "images\\DrawMode\\ClearAll.jpg";
	MenuItemImages[ITM_BACKGROUND_COLOR] = "images\\DrawMode\\ArtboardBackground.jpg";
	MenuItemImages[ITM_OPEN] = "images\\DrawMode\\Open.jpg";
	MenuItemImages[ITM_SAVE] = "images\\DrawMode\\Save.jpg";
	MenuItemImages[ITM_TOGGLE_SOUND] = PlayActionSoundEnabled ? "images\\DrawMode\\ToggleSoundOn.jpg" : "images\\DrawMode\\ToggleSoundOff.jpg";
	MenuItemImages[ITM_EXIT] = "images\\DrawMode\\Exit.jpg";

	if (IsPlayingRecording) {
		MenuItemImages[ITM_START_RECORDING] = "images\\DrawMode\\StartRecordingFaded.jpg";
		MenuItemImages[ITM_STOP_RECORDING] = "images\\DrawMode\\StopRecording.jpg";
	}
	else {
		MenuItemImages[ITM_START_RECORDING] = "images\\DrawMode\\StartRecording.jpg";
		MenuItemImages[ITM_STOP_RECORDING] = "images\\DrawMode\\StopRecordingFaded.jpg";
	}

	// Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::SetPlayActionState(bool state)
{
	PlayActionSoundEnabled = state;
	UpdateToolBar();
}

void Output::SetRecordingState(bool state)
{
	IsPlayingRecording = state;
	UpdateToolBar();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	// Clear toolbar
	pWind->SetPen(SURFACE0, 1);
	pWind->SetBrush(SURFACE0);
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

void Output::PrintMessage(string msg,bool update) // Prints a message on status bar
{
	
	lastMessage = msg;
	CreateStatusBar(); // First clear the status bar
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - int(UI.StatusBarHeight / 1.2), msg);
	if(update)
		pWind->UpdateBuffer();
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::GetCurrentDrawColor() const // Get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::GetCurrentFillColor() const // Get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCurrentPenWidth() const // Get current pen width
{
	return UI.PenWidth;
}

void Output::UpdateStatusBar() {
	PrintMessage(lastMessage,false);
}

void Output::UpdateToolBar() {
	if (UI.InterfaceMode == MODE_DRAW)CreateDrawToolBar();
	else CreatePlayToolBar();
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) // Drawing Rectangle
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; // Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	int MinY = min(P1.y, P2.y);
	int MaxY = max(P1.y, P2.y);
	if (MinY <= UI.ToolBarHeight)
		UpdateToolBar();
	
	if (MaxY >= UI.height - UI.StatusBarHeight)
		UpdateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawSquare(Point P1, int DefaultSquareSize, GfxInfo SquareGfxInfo, bool selected) // Drawing square
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = SquareGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, SquareGfxInfo.BorderWidth);
	drawstyle style;

	if (SquareGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillClr);
	}
	else
		style = FRAME;

	Point p1, p2;
	p1.x = P1.x + DefaultSquareSize / 2;
	p1.y = P1.y + DefaultSquareSize / 2;
	p2.x = P1.x - DefaultSquareSize / 2;
	p2.y = P1.y - DefaultSquareSize / 2;

	pWind->DrawRectangle(p1.x, p1.y, p2.x, p2.y, style);
	if (p2.y <= UI.ToolBarHeight)
		UpdateToolBar();
	if (p1.y >= UI.height - UI.StatusBarHeight)
		UpdateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) // Drawing Triangle
{
	color DrawingClr;
	drawstyle style;
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = TriangleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriangleGfxInfo.BorderWidth);
	if (TriangleGfxInfo.isFilled)
	{
		pWind->SetBrush(TriangleGfxInfo.FillClr);
		style = FILLED;
	}
	else
		style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
	int MinY = min(P1.y, P2.y);
	MinY = min(MinY, P3.y);
	int MaxY = max(P1.y, P2.y);
	MaxY = max(MaxY, P3.y);
	if (MinY <= UI.ToolBarHeight)
		UpdateToolBar();
	if (MaxY >= (UI.height - UI.StatusBarHeight))
		UpdateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected)
{
	color drawcolor;
	drawstyle style;
	if (selected)
		drawcolor = UI.HighlightColor; 
	else
		drawcolor = CircleGfxInfo.DrawClr;

	pWind->SetPen(drawcolor, CircleGfxInfo.BorderWidth);
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
	pWind->DrawCircle(P1.x, P1.y, radius, style);
	if ((P1.y - radius) <= UI.ToolBarHeight)
		UpdateToolBar();
	
	if ((P1.y + radius) >= (UI.height - UI.StatusBarHeight)) 
		UpdateStatusBar();
	

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawHexagon(Point P1, int hexagonSize, GfxInfo HexagonGfxInfo, bool selected)
{

	color drawcolor;
	drawstyle style;
	if (selected)
		drawcolor = UI.HighlightColor;
	else
		drawcolor = HexagonGfxInfo.DrawClr;

	pWind->SetPen(drawcolor, HexagonGfxInfo.BorderWidth);
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
	if ((P1.y - hexagonSize / 2 * sqrt(3) - 2) <= UI.ToolBarHeight) 
		UpdateToolBar();
	
	if ((P1.y + hexagonSize / 2 * sqrt(3) + 2) >= (UI.height - UI.StatusBarHeight)) 
		UpdateStatusBar();
	
}
//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	delete pWind;

	if (colorMenuWind)
		delete colorMenuWind;
}
