#include "Output.h"
#include <cmath>
Output::Output()
{
	Darken = 1.08;
	UI.InterfaceMode = MODE_DRAW; // Sets the interface mode to draw mode

	UI.width = 1250; // Sets the width of the window
	UI.height = 650; // Sets the height of the window
	UI.wx = 5;		 // Sets the x position of the window
	UI.wy = 5;		 // Sets the y position of the window

	UI.StatusBarHeight = 50; // Sets the height of the status bar
	UI.ToolBarHeight = 49;	 // Sets the height of the toolbar
	UI.MenuItemWidth = 49;	 // Sets the width of the toolbar icons

	UI.ColorMenuItemWidth = 40;											   // Sets the width of the color menu items
	UI.ColorMenuWidth = COLOR_MENU_ITM_COUNT * UI.ColorMenuItemWidth + 40; // Sets the width of the color menu window
	UI.ColorMenuHeight = UI.ColorMenuItemWidth + 16;					   // Sets the height of the color menu window

	UI.DrawColor = BLUE;				// Drawing color
	UI.FillColor = TRANSPARENT_COLOR;	// Filling color
	UI.MsgColor = TEXT;					// Messages color
	UI.BackgroundColor = BASE;			// Background color
	UI.HighlightColor = HIGHLIGHTCOLOR; // This color should NOT be used to draw figures, use if for highlight only
	UI.StatusBarColor = SURFACE0;		// Status bar background color
	UI.PenWidth = 3;					// Width of the figures frames

	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);				   // Creates the window
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project"); // Changes the title of the window

	pColorMenuWind = NULL; // Initializes the color menu window pointer

	IsPlayingRecording = false;	   // Initializes the recording state to false
	PlayActionSoundEnabled = true; // Initializes the play action sound state to true

	CreateDrawToolBar();   // Creates the draw toolbar
	CreateStatusBar();	   // Creates the status bar
	pWind->UpdateBuffer(); // Updates the buffer

	LastMessage = "";		 // Initializes the last message to an empty string
	UpdateToolBar = false;	 // Initializes the update toolbar flag to false
	UpdateStatusBar = false; // Initializes the update status bar flag to false
}

Input *Output::CreateInput() const
{
	Input *pIn = new Input(pWind); // Creates a new input object
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//
void Output::UpdateInterface()
{
	if (UpdateToolBar) // If the toolbar should be updated
	{
		if (UI.InterfaceMode == MODE_DRAW) // If the interface mode is draw mode
			CreateDrawToolBar();		   // Creates the draw toolbar
		else
			CreatePlayToolBar(); // Creates the play toolbar
	}

	if (UpdateStatusBar)				  // If the status bar should be updated
		PrintMessage(LastMessage, false); // Prints the last message on the status bar

	UpdateToolBar = false;	 // Resets the update toolbar flag
	UpdateStatusBar = false; // Resets the update status bar flag

	pWind->UpdateBuffer(); // Updates the buffer
}

window *Output::CreateWind(int w, int h, int x, int y) const
{
	window *pW = new window(w, h, x, y); // Creates a new window object

	pW->SetBuffering(true); // Enables double buffering

	// Note: we darken the background a little bit to distinguish it from the figures color
	pW->SetBrush(UI.BackgroundColor / Darken);	// Sets the brush color
	pW->SetPen(UI.BackgroundColor / Darken, 1); // Sets the pen color

	pW->DrawRectangle(0, UI.ToolBarHeight, w, h); // Draws the drawing area rectangle

	pW->UpdateBuffer(); // Updates the buffer

	return pW;
}

//======================================================================================//
//								Color Menu Functions									//
//======================================================================================//
void Output::CreateColorMenuWind(int x, bool withTransparent)
{
	int xPos = UI.wx + x; // x position of the color menu window

	if ((xPos + UI.ColorMenuWidth) > UI.width || x < UI.wx) // If the color menu window will exceed the right border of the screen
		xPos = (UI.width - UI.ColorMenuWidth) / 2;			// Center the color menu window

	pColorMenuWind = new window(UI.ColorMenuWidth, UI.ColorMenuHeight, xPos, UI.wy + UI.ToolBarHeight + 35); // Creates a new window
	pColorMenuWind->ChangeTitle("Colors");																	 // Changes the title of the color menu window
}

void Output::DrawColorMenuItems(bool withTransparent) const
{
	const int ArraySize = COLOR_MENU_ITM_COUNT - 1;													// Number of colors in the color menu
	color colors[ArraySize] = {PINK, RED, ORANGE, YELLOW, GREEN, SKY, BLUE, LAVENDER, BASE, BLACK}; // Array of colors in the color menu

	pColorMenuWind->DrawRectangle(0, 0, UI.ColorMenuWidth, UI.ColorMenuHeight); // Draws the color menu window
	for (int i = 0; i < ArraySize; i++)											// Draws the color images
	{
		pColorMenuWind->SetBrush(colors[i]);																												   // Sets the brush color
		pColorMenuWind->SetPen(BLACK, 1);																													   // Sets the pen color
		pColorMenuWind->DrawCircle(i * UI.ColorMenuItemWidth + (UI.ColorMenuItemWidth / 2), UI.ColorMenuItemWidth / 2, UI.ColorMenuItemWidth / 2 - 4, FILLED); // Draws the color image
	}

	if (withTransparent) // If the color menu window should have a transparent color option
	{
		int xArray[12] = {-8, 0, 8, 16, 8, 16, 8, 0, -8, -16, -8, -16}; // Array of x coordinates of the transparent color image
		int yArray[12] = {-16, -8, -16, -8, 0, 8, 16, 8, 16, 8, 0, -8}; // Array of y coordinates of the transparent color image

		for (int i = 0; i < 12; i++) // Scales the transparent color image
		{
			xArray[i] *= 0.9;
			yArray[i] *= 0.9;
			xArray[i] += ArraySize * UI.ColorMenuItemWidth + (UI.ColorMenuItemWidth / 2) - 2;
			yArray[i] += (UI.ColorMenuItemWidth / 2);
		}

		pColorMenuWind->SetBrush(BLACK);						 // Sets the brush color
		pColorMenuWind->SetPen(BLACK, 1);						 // Sets the pen color
		pColorMenuWind->DrawPolygon(xArray, yArray, 12, FILLED); // Draws the transparent color image
	}

	pWind->UpdateBuffer(); // Updates the buffer
}

void Output::OpenColorMenuWind(int x, bool withTransparent)
{
	UI.ColorMenuWidth = (withTransparent ? COLOR_MENU_ITM_COUNT : COLOR_MENU_ITM_COUNT - 1) * UI.ColorMenuItemWidth + 13; // Sets the width of the color menu window

	CreateColorMenuWind(x, withTransparent); // Initializes a new window and sets data member to that pointer

	DrawColorMenuItems(withTransparent); // Draws color images to color menu window
}

void Output::CloseColorMenuWind()
{
	if (pColorMenuWind) // If the color menu window is open
	{
		delete pColorMenuWind;
		pColorMenuWind = NULL;
	}
}

window *Output::GetColorMenuWind() const
{
	return pColorMenuWind; // Returns the pointer to the color menu window
}

//======================================================================================//
//								Toolbar Functions										//
//======================================================================================//
void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY; // Sets the interface mode to play mode

	pWind->SetPen(SURFACE0, 1);								// Sets the pen color
	pWind->SetBrush(SURFACE0);								// Sets the brush color
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight); // Draws the toolbar rectangle

	std::string PlayMenuItems[PLAY_ITM_COUNT]; // Array of image paths for the toolbar icons

	PlayMenuItems[ITM_DRAW_MODE] = "images\\PlayMode\\DrawMode.jpg";
	PlayMenuItems[ITM_PICKBYSHAPE] = "images\\PlayMode\\PickByShape.jpg";
	PlayMenuItems[ITM_PICKBYCOLOR] = "images\\PlayMode\\PickByColor.jpg";
	PlayMenuItems[ITM_PICKBYSHAPEANDCOLOR] = "images\\PlayMode\\PickByShapeAndColor.jpg";
	PlayMenuItems[ITM_EXIT_PLAY] = "images\\DrawMode\\Exit.jpg";

	for (int i = 0; i < PLAY_ITM_COUNT; i++) // Draws the toolbar icons
		pWind->DrawImage(PlayMenuItems[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW; // Sets the interface mode to draw mode

	pWind->SetPen(SURFACE0, 1);								// Sets the pen color
	pWind->SetBrush(SURFACE0);								// Sets the brush color
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight); // Draws the toolbar rectangle

	std::string MenuItemImages[DRAW_ITM_COUNT]; // Array of image paths for the toolbar icons

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

	if (IsPlayingRecording) // If the user is recording and sets the icons of the play and stop recording buttons accordingly
	{
		MenuItemImages[ITM_START_RECORDING] = "images\\DrawMode\\StartRecordingFaded.jpg";
		MenuItemImages[ITM_STOP_RECORDING] = "images\\DrawMode\\StopRecording.jpg";
	}
	else
	{
		MenuItemImages[ITM_START_RECORDING] = "images\\DrawMode\\StartRecording.jpg";
		MenuItemImages[ITM_STOP_RECORDING] = "images\\DrawMode\\StopRecordingFaded.jpg";
	}

	for (int i = 0; i < DRAW_ITM_COUNT; i++) // Draws the toolbar icons
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
}

//======================================================================================//
//								Status Bar Functions									//
//======================================================================================//
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);										  // Sets the pen color
	pWind->SetBrush(UI.StatusBarColor);											  // Sets the brush color
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height); // Draws the status bar rectangle
}

void Output::PrintMessage(std::string Message, bool Update) // Prints a message on status bar
{
	LastMessage = Message; // Sets the last message to the message passed to the function
	CreateStatusBar();	   // Clears the status bar

	pWind->SetPen(UI.MsgColor, 50);											   // Sets the pen color
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");								   // Sets the font
	pWind->DrawString(10, UI.height - int(UI.StatusBarHeight / 1.2), Message); // Draws the message on the status bar

	if (Update) // If the message should be updated
		pWind->UpdateBuffer();
}

void Output::ClearStatusBar()
{
	LastMessage = "";  // Clears the last message
	CreateStatusBar(); // Clears the status bar
}

//======================================================================================//
//								Play Action Sound Functions								//
//======================================================================================//
void Output::SetPlayActionSoundState(bool State)
{
	PlayActionSoundEnabled = State; // Sets the state of the play action sound
	UpdateToolBar = true;			// Updates the toolbar
}

void Output::SetRecordingState(bool State)
{
	IsPlayingRecording = State; // Sets the state of the recording
	UpdateToolBar = true;		// Updates the toolbar
}

//======================================================================================//
//								UI Manipulation Functions								//
//======================================================================================//
void Output::ClearDrawArea() const
{
	// Note: we darken the background a little bit to distinguish it from the figures color
	pWind->SetPen(UI.BackgroundColor / Darken, 1);										 // Sets the pen color
	pWind->SetBrush(UI.BackgroundColor / Darken);										 // Sets the brush color
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight); // Draws the drawing area rectangle
}

//======================================================================================//
//								UI Getter Functions										//
//======================================================================================//
color Output::GetCurrentDrawColor() const // Get current drawing color
{
	return UI.DrawColor;
}

color Output::GetCurrentFillColor() const // Get current filling color
{
	return UI.FillColor;
}

int Output::GetCurrentPenWidth() const // Get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//
void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool Selected)
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

void Output::DrawSquare(Point _P1, int DefaultSquareSize, GfxInfo SquareGfxInfo, bool Selected)
{
	color DrawingColor; // Color of the outline of the square
	drawstyle Style;	// Style of the square

	if (Selected)						  // If the square should be drawn highlighted
		DrawingColor = UI.HighlightColor; // Figure should be drawn highlighted
	else
		DrawingColor = SquareGfxInfo.DrawColor; // Color of the outline of the square

	pWind->SetPen(DrawingColor, SquareGfxInfo.BorderWidth); // Sets the pen color

	if (SquareGfxInfo.IsFilled) // If the square should be filled
	{
		Style = FILLED;							  // Sets the style to filled
		pWind->SetBrush(SquareGfxInfo.FillColor); // Sets the brush color
	}
	else // If the square should not be filled
		Style = FRAME;

	Point P1, P2;						  // Points of the square
	P1.x = _P1.x + DefaultSquareSize / 2; // Sets the x coordinate of the first point
	P1.y = _P1.y + DefaultSquareSize / 2; // Sets the y coordinate of the first point
	P2.x = _P1.x - DefaultSquareSize / 2; // Sets the x coordinate of the second point
	P2.y = _P1.y - DefaultSquareSize / 2; // Sets the y coordinate of the second point

	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, Style); // Draws the square

	if (P2.y <= UI.ToolBarHeight) // If the square is under the toolbar
		UpdateToolBar = true;
	if (P1.y >= UI.height - UI.StatusBarHeight) // If the square is under the status bar
		UpdateStatusBar = true;
}

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool Selected)
{
	color DrawingColor; // Color of the outline of the triangle
	drawstyle Style;	// Style of the triangle

	if (Selected)						  // If the triangle should be drawn highlighted
		DrawingColor = UI.HighlightColor; // Figure should be drawn highlighted
	else
		DrawingColor = TriangleGfxInfo.DrawColor; // Color of the outline of the triangle

	pWind->SetPen(DrawingColor, TriangleGfxInfo.BorderWidth); // Sets the pen color

	if (TriangleGfxInfo.IsFilled) // If the triangle should be filled
	{
		Style = FILLED;								// Sets the style to filled
		pWind->SetBrush(TriangleGfxInfo.FillColor); // Sets the brush color
	}
	else // If the triangle should not be filled
		Style = FRAME;

	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, Style); // Draws the triangle

	int MinY = min(P1.y, P2.y); // Minimum y coordinate of the triangle
	MinY = min(MinY, P3.y);

	int MaxY = max(P1.y, P2.y); // Maximum y coordinate of the triangle
	MaxY = max(MaxY, P3.y);

	if (MinY - ((UI.PenWidth + 1) / 2) <= UI.ToolBarHeight) // If the triangle is under the toolbar
		UpdateToolBar = true;
	if (MaxY + ((UI.PenWidth + 1) / 2) >= (UI.height - UI.StatusBarHeight)) // If the triangle is under the status bar
		UpdateStatusBar = true;
}

void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfxInfo, bool Selected)
{
	color DrawColor; // Color of the outline of the circle
	drawstyle Style; // Style of the circle

	if (Selected)					   // If the circle should be drawn highlighted
		DrawColor = UI.HighlightColor; // Figure should be drawn highlighted
	else
		DrawColor = CircleGfxInfo.DrawColor; // Color of the outline of the circle

	pWind->SetPen(DrawColor, CircleGfxInfo.BorderWidth); // Sets the pen color

	if (CircleGfxInfo.IsFilled) // If the circle should be filled
	{
		Style = FILLED;							  // Sets the style to filled
		pWind->SetBrush(CircleGfxInfo.FillColor); // Sets the brush color
	}
	else
		Style = FRAME;

	int Radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2)); // Radius of the circle

	pWind->DrawCircle(P1.x, P1.y, Radius, Style); // Draws the circle

	if ((P1.y - Radius) <= UI.ToolBarHeight) // If the circle is under the toolbar
		UpdateToolBar = true;
	if ((P1.y + Radius) >= (UI.height - UI.StatusBarHeight)) // If the circle is under the status bar
		UpdateStatusBar = true;
}

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
	delete pWind; // Deletes the window

	if (pColorMenuWind)		   // If the color menu window is open
		delete pColorMenuWind; // Deletes the color menu window
}
