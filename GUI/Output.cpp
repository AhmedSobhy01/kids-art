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
	UI.BackgroundColor = BASE-5;		  // Background color
	UI.HighlightColor = MAUVE;		  // This color should NOT be used to draw figures, use if for highlight only
	UI.StatusBarColor = SURFACE0;	  // Status bar background color
	UI.PenWidth = 3;				  // Width of the figures frames

	// Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	// Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	// Initialize Color Menu Window Pointer
	pColorMenuWind = NULL;

	IsPlayingRecording = false;
	PlayActionSoundEnabled = true;

	CreateDrawToolBar();
	CreateStatusBar();
	pWind->UpdateBuffer();
	LastMessage = "";
	UpdateToolBar = false;
	UpdateStatusBar = false;
}

Input *Output::CreateInput() const
{
	Input *pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::UpdateInterface()
{
	if (UpdateToolBar)
	{
		if (UI.InterfaceMode == MODE_DRAW)
			CreateDrawToolBar();
		else
			CreatePlayToolBar();
	}
	if (UpdateStatusBar)
		PrintMessage(LastMessage, false);
	UpdateToolBar = false;
	UpdateStatusBar = false;
	pWind->UpdateBuffer();
}

window *Output::CreateWind(int w, int h, int x, int y) const
{
	window *pW = new window(w, h, x, y);
	pW->SetBuffering(true);
	pW->SetBrush(UI.BackgroundColor);
	pW->SetPen(UI.BackgroundColor, 1);
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

	pColorMenuWind = new window(UI.ColorMenuWidth, UI.ColorMenuHeight, xPos, UI.wy + UI.ToolBarHeight + 35);
	pColorMenuWind->ChangeTitle("Colors");
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawColorMenuItems(bool withTransparent) const
{
	const int ArraySize = COLOR_MENU_ITM_COUNT - 1;
	color colors[ArraySize] = {PINK, RED, ORANGE, YELLOW, GREEN, SKY, BLUE, LAVENDER, BASE, BLACK};

	pColorMenuWind->DrawRectangle(0, 0, UI.ColorMenuWidth, UI.ColorMenuHeight);
	for (int i = 0; i < ArraySize; i++)
	{
		pColorMenuWind->SetBrush(colors[i]);
		pColorMenuWind->SetPen(BLACK, 1);
		pColorMenuWind->DrawCircle(i * UI.ColorMenuItemWidth + (UI.ColorMenuItemWidth / 2), UI.ColorMenuItemWidth / 2, UI.ColorMenuItemWidth / 2 - 4, FILLED);
	}
	if (withTransparent)
	{
		int xArray[12] = {-8, 0, 8, 16, 8, 16, 8, 0, -8, -16, -8, -16};
		int yArray[12] = {-16, -8, -16, -8, 0, 8, 16, 8, 16, 8, 0, -8};
		for (int i = 0; i < 12; i++)
		{
			xArray[i] *= 0.9;
			yArray[i] *= 0.9;
			xArray[i] += (ArraySize)*UI.ColorMenuItemWidth + (UI.ColorMenuItemWidth / 2) - 2;
			yArray[i] += (UI.ColorMenuItemWidth / 2);
		}
		pColorMenuWind->SetBrush(BLACK);
		pColorMenuWind->SetPen(BLACK, 1);
		pColorMenuWind->DrawPolygon(xArray, yArray, 12, FILLED);
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
	if (pColorMenuWind)
	{
		delete pColorMenuWind;
		pColorMenuWind = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

window *Output::GetColorMenuWind() const
{
	return pColorMenuWind;
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
	LastMessage = "";
	CreateStatusBar();
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;
	pWind->SetPen(SURFACE0, 1);
	pWind->SetBrush(SURFACE0);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	std::string MenuItemImages[DRAW_ITM_COUNT];
	// Draw mode toolbar images
	MenuItemImages[ITM_PLAY_MODE] = "images\\DrawMode\\PlayMode.jpg";
	MenuItemImages[ITM_RECT] = "images\\DrawMode\\Rectangle.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\DrawMode\\Square.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\DrawMode\\Triangle.jpg";
	MenuItemImages[ITM_CIRCLE] = "images\\DrawMode\\Circle.jpg";
	MenuItemImages[ITM_HEXAGON] = "images\\DrawMode\\Hexagon.jpg";
	MenuItemImages[ITM_BORDER_WIDTH] = "images\\DrawMode\\BorderWidth" + to_string(UI.PenWidth - 1) + ".jpg";
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
	MenuItemImages[ITM_BACKGROUND_COLOR] = "images\\DrawMode\\ArtboardBackground.jpg";
	MenuItemImages[ITM_CLEAR_ALL] = "images\\DrawMode\\ClearAll.jpg";
	MenuItemImages[ITM_OPEN] = "images\\DrawMode\\Open.jpg";
	MenuItemImages[ITM_SAVE] = "images\\DrawMode\\Save.jpg";
	MenuItemImages[ITM_TOGGLE_SOUND] = PlayActionSoundEnabled ? "images\\DrawMode\\ToggleSoundOn.jpg" : "images\\DrawMode\\ToggleSoundOff.jpg";
	MenuItemImages[ITM_EXIT] = "images\\DrawMode\\Exit.jpg";
	if (IsPlayingRecording)
	{
		MenuItemImages[ITM_START_RECORDING] = "images\\DrawMode\\StartRecordingFaded.jpg";
		MenuItemImages[ITM_STOP_RECORDING] = "images\\DrawMode\\StopRecording.jpg";
	}
	else
	{
		MenuItemImages[ITM_START_RECORDING] = "images\\DrawMode\\StartRecording.jpg";
		MenuItemImages[ITM_STOP_RECORDING] = "images\\DrawMode\\StopRecordingFaded.jpg";
	}

	// Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::SetPlayActionState(bool State)
{
	PlayActionSoundEnabled = State;
	UpdateToolBar = true;
}

void Output::SetRecordingState(bool State)
{
	IsPlayingRecording = State;
	UpdateToolBar = true;
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
	std::string PlayMenuItems[PLAY_ITM_COUNT];
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
	pWind->SetPen(UI.BackgroundColor, 1);
	pWind->SetBrush(UI.BackgroundColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(std::string Message, bool Update) // Prints a message on status bar
{
	LastMessage = Message;
	CreateStatusBar(); // First clear the status bar
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - int(UI.StatusBarHeight / 1.2), Message);
	if (Update)
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

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool Selected) // Drawing Rectangle
{
	color DrawingColor;
	if (Selected)
		DrawingColor = UI.HighlightColor; // Figure should be drawn highlighted
	else
		DrawingColor = RectGfxInfo.DrawColor;

	pWind->SetPen(DrawingColor, RectGfxInfo.BorderWidth);
	drawstyle Style;
	if (RectGfxInfo.IsFilled)
	{
		Style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillColor);
	}
	else
		Style = FRAME;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, Style);
	int MinY = min(P1.y, P2.y);
	int MaxY = max(P1.y, P2.y);
	if (MinY <= UI.ToolBarHeight)
		UpdateToolBar = true;

	if (MaxY >= UI.height - UI.StatusBarHeight)
		UpdateStatusBar = true;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawSquare(Point _P1, int DefaultSquareSize, GfxInfo SquareGfxInfo, bool Selected) // Drawing square
{
	color DrawingColor;
	if (Selected)
		DrawingColor = UI.HighlightColor;
	else
		DrawingColor = SquareGfxInfo.DrawColor;

	pWind->SetPen(DrawingColor, SquareGfxInfo.BorderWidth);
	drawstyle Style;

	if (SquareGfxInfo.IsFilled)
	{
		Style = FILLED;
		pWind->SetBrush(SquareGfxInfo.FillColor);
	}
	else
		Style = FRAME;

	Point P1, P2;
	P1.x = _P1.x + DefaultSquareSize / 2;
	P1.y = _P1.y + DefaultSquareSize / 2;
	P2.x = _P1.x - DefaultSquareSize / 2;
	P2.y = _P1.y - DefaultSquareSize / 2;

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, Style);
	if (P2.y <= UI.ToolBarHeight)
		UpdateToolBar = true;
	if (P1.y >= UI.height - UI.StatusBarHeight)
		UpdateStatusBar = true;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool Selected) // Drawing Triangle
{
	color DrawingColor;
	drawstyle Style;
	if (Selected)
		DrawingColor = UI.HighlightColor;
	else
		DrawingColor = TriangleGfxInfo.DrawColor;

	pWind->SetPen(DrawingColor, TriangleGfxInfo.BorderWidth);
	if (TriangleGfxInfo.IsFilled)
	{
		pWind->SetBrush(TriangleGfxInfo.FillColor);
		Style = FILLED;
	}
	else
		Style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, Style);
	int MinY = min(P1.y, P2.y);
	MinY = min(MinY, P3.y);
	int MaxY = max(P1.y, P2.y);
	MaxY = max(MaxY, P3.y);
	if (MinY - ((UI.PenWidth + 1) / 2) <= UI.ToolBarHeight)
		UpdateToolBar = true;
	if (MaxY + ((UI.PenWidth + 1) / 2) >= (UI.height - UI.StatusBarHeight))
		UpdateStatusBar = true;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool Selected)
{
	color DrawColor;
	drawstyle Style;
	if (Selected)
		DrawColor = UI.HighlightColor;
	else
		DrawColor = CircleGfxInfo.DrawColor;

	pWind->SetPen(DrawColor, CircleGfxInfo.BorderWidth);
	if (CircleGfxInfo.IsFilled)
	{
		Style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillColor);
	}
	else
		Style = FRAME;
	int Radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
	pWind->DrawCircle(P1.x, P1.y, Radius, Style);
	if ((P1.y - Radius) <= UI.ToolBarHeight)
		UpdateToolBar = true;

	if ((P1.y + Radius) >= (UI.height - UI.StatusBarHeight))
		UpdateStatusBar = true;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawHexagon(Point P1, int HexagonSize, GfxInfo HexagonGfxInfo, bool Selected)
{

	color DrawColor;
	drawstyle Style;
	if (Selected)
		DrawColor = UI.HighlightColor;
	else
		DrawColor = HexagonGfxInfo.DrawColor;

	pWind->SetPen(DrawColor, HexagonGfxInfo.BorderWidth);
	if (HexagonGfxInfo.IsFilled)
	{
		Style = FILLED;
		pWind->SetBrush(HexagonGfxInfo.FillColor);
	}
	else
		Style = FRAME;

	int xPointsArray[6];
	int yPointsArray[6];

	double angle = 2.0 * cdPi / 6.0; // Angle between each side of the hexagon in radians

	for (int i = 0; i < 6; i++)
	{
		xPointsArray[i] = P1.x + HexagonSize * cos(i * angle);
		yPointsArray[i] = P1.y + HexagonSize * sin(i * angle);
	}
	pWind->DrawPolygon(xPointsArray, yPointsArray, 6, Style);
	if ((P1.y - HexagonSize / 2 * sqrt(3) - ((UI.PenWidth + 1) / 2)) <= UI.ToolBarHeight)
		UpdateToolBar = true;

	if ((P1.y + HexagonSize / 2 * sqrt(3) + ((UI.PenWidth + 1) / 2)) >= (UI.height - UI.StatusBarHeight))
		UpdateStatusBar = true;
}
//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	delete pWind;

	if (pColorMenuWind)
		delete pColorMenuWind;
}
