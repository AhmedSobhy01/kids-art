#include "GUI\Input.h"
#include "GUI\Output.h"

// This is a test code to test the Input and Output classes

void printSelectedColor(Output *, const color &); // Prints status message in status bar for selected color

int main()
{
	int x, y;

	// Create Input and Output objects to test
	Output *pOut = new Output();
	Input *pIn = pOut->CreateInput();

	// Starting the test
	pOut->PrintMessage("This demo is to test input and output classes, click anywhere to start the test");
	pIn->GetPointClicked(x, y); // Wait for any click

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 0:
	//			Creates color menu in the center of main window and closes after selection of color
	//			Selected color is stored in a variable of name "selectedColor"
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST0: Color menu window, click anywhere to open color menu window");
	pIn->GetPointClicked(x, y); // Wait for any click

	pOut->OpenColorMenuWind();						 // Creates color window instance

	pOut->PrintMessage("Select a color from color menu");
	color selectedColor = pIn->GetSelectedColor(pOut); // Gets user selection of the color

	printSelectedColor(pOut, selectedColor); // Prints selected color to the status bar
	pIn->GetPointClicked(x, y);				 // Wait for any click 

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 1:
	//			Creates the toolbar, drawing area, and status bar
	//			This has already been done through the constructor of class Output
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST1: Drawing toolbar, status bar and drawing area, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:
	//			Drawing all the figures with all possible states:
	//			unfilled, filled, and highlighted in both cases
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST2: Drawing all the figures with all possible states, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	GfxInfo gfxInfo; // To be used with draw function of the class Ouput
	Point P1, P2, P3;

	/// 2.1 - Rectangle Test ///
	/// ====================
	pOut->PrintMessage("Drawing a rectangle with all possible states, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	// 2.1.1 - Drawing unhighlighted, unfilled rectangle
	// =================================================
	do
	{
		pOut->PrintMessage("Drawing a rectangle => unhighlighted and unfilled, click two points");
		pIn->GetPointClicked(P1.x, P1.y);
		pIn->GetPointClicked(P2.x, P2.y);

		if (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The rectangle can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight);

	gfxInfo.BorderWidth = 5;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.isFilled = false;
	pOut->DrawRect(P1, P2, gfxInfo, false);

	// 2.1.2 - Drawing highlighted, unfilled rectangle
	// ===============================================
	pOut->PrintMessage("Drawing a rectangle => highlighted and unfilled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);

	// 2.1.3 - Drawing unhighlighted, filled rectangle
	// ===============================================
	do
	{
		pOut->PrintMessage("Drawing a rectangle => unhighlighted and filled, click two points");
		pIn->GetPointClicked(P1.x, P1.y);
		pIn->GetPointClicked(P2.x, P2.y);
		if (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The rectangle can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight);

	gfxInfo.BorderWidth = 6;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.FillClr = YELLOW;
	gfxInfo.isFilled = true;
	pOut->DrawRect(P1, P2, gfxInfo, false);

	// 2.1.4 - Drawing highlighted, filled rectangle
	// =============================================
	pOut->PrintMessage("Drawing a rectangle => highlighted and filled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);

	pOut->PrintMessage("Drawing a rectangle test is done, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.2 - Square Test ///
	/// =================
	const int squareSize = 150;

	pOut->PrintMessage("Drawing a square with all possible states, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	// 2.2.1 - Drawing unhighlighted, unfilled square
	// ==============================================
	do
	{
		pOut->PrintMessage("Drawing a square => unhighlighted and unfilled, click one point");
		pIn->GetPointClicked(P1.x, P1.y);

		if (P1.y - squareSize / 2 < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The square can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y - squareSize / 2 < UI.ToolBarHeight);

	gfxInfo.BorderWidth = 5;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.isFilled = false;
	pOut->DrawSquare(P1, gfxInfo, false);

	// 2.2.2 - Drawing highlighted, unfilled square
	// ============================================
	pOut->PrintMessage("Drawing a square => highlighted and unfilled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->DrawSquare(P1, gfxInfo, true);

	// 2.2.3 - Drawing unhighlighted, filled square
	// ============================================
	do
	{
		pOut->PrintMessage("Drawing a square => unhighlighted and filled, click one point");
		pIn->GetPointClicked(P1.x, P1.y);
		if (P1.y - squareSize / 2 < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The square can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y - squareSize / 2 < UI.ToolBarHeight);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWidth = 5;
	gfxInfo.FillClr = YELLOW;
	gfxInfo.isFilled = true;
	pOut->DrawSquare(P1, gfxInfo, false);

	// 2.2.4 - Drawing highlighted, filled square
	// ==========================================
	pOut->PrintMessage("Drawing a square => highlighted and filled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click

	pOut->DrawSquare(P1, gfxInfo, true);

	pOut->PrintMessage("Drawing a square test is done, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.3- Triangle Test ///
	/// ==================
	pOut->PrintMessage("Drawing a triangle with all possible states, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	// 2.3.1 - Drawing unhighlighted, unfilled triangle
	// ================================================
	do
	{
		pOut->PrintMessage("Drawing a triangle => unhighlighted and unfilled, click three point");
		pIn->GetPointClicked(P1.x, P1.y);
		pIn->GetPointClicked(P2.x, P2.y);
		pIn->GetPointClicked(P3.x, P3.y);
		if (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight || P3.y < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The triangle can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight || P3.y < UI.ToolBarHeight);

	gfxInfo.BorderWidth = 5;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.isFilled = false;
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, false);

	// 2.3.2 - Drawing highlighted, unfilled triangle
	// ==============================================
	pOut->PrintMessage("Drawing a triangle => highlighted and unfilled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, true);

	// 2.3.3 - Drawing unhighlighted, filled triangle
	// ==============================================
	do
	{
		pOut->PrintMessage("Drawing a triangle => unhighlighted and filled, click three point");
		pIn->GetPointClicked(P1.x, P1.y);
		pIn->GetPointClicked(P2.x, P2.y);
		pIn->GetPointClicked(P3.x, P3.y);
		if (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight || P3.y < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The triangle can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight || P3.y < UI.ToolBarHeight);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWidth = 5;
	gfxInfo.FillClr = YELLOW;
	gfxInfo.isFilled = true;
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, false);

	// 2.3.4 - Drawing highlighted, filled triangle
	// ============================================
	pOut->PrintMessage("Drawing a triangle => highlighted and filled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click

	pOut->DrawTriangle(P1, P2, P3, gfxInfo, true);

	pOut->PrintMessage("Drawing a triangle test is done, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.4 - Hexagon Test ///
	/// ==================
	const int hexagonSize = 80;

	pOut->PrintMessage("Drawing a hexagon with all possible states, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	// 2.4.1 - Drawing unhighlighted, unfilled hexagon
	// ===============================================
	do
	{
		pOut->PrintMessage("Drawing a hexagon => unhighlighted and unfilled, click one point");
		pIn->GetPointClicked(P1.x, P1.y);
		if (P1.y - hexagonSize / 2.0 * sqrt(3) < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The hexagon can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y - hexagonSize / 2.0 * sqrt(3) < UI.ToolBarHeight);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWidth = 5;
	gfxInfo.isFilled = false;
	pOut->DrawHexagon(P1, gfxInfo, false);

	// 2.4.2 - Drawing highlighted, unfilled hexagon
	// =============================================
	pOut->PrintMessage("Drawing a hexagon => highlighted and unfilled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->DrawHexagon(P1, gfxInfo, true);

	// 2.4.3 - Drawing unhighlighted, filled hexagon
	// =============================================
	do
	{
		pOut->PrintMessage("Drawing a hexagon => unhighlighted and filled, click one point");
		pIn->GetPointClicked(P1.x, P1.y);
		if (P1.y - hexagonSize / 2.0 * sqrt(3) < UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The hexagon can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y - hexagonSize / 2.0 * sqrt(3) < UI.ToolBarHeight);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWidth = 5;
	gfxInfo.isFilled = true;
	gfxInfo.FillClr = YELLOW;
	pOut->DrawHexagon(P1, gfxInfo, false);

	// 2.4.4 - Drawing highlighted, filled hexagon
	// ===========================================
	pOut->PrintMessage("Drawing a hexagon => highlighted and filled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click

	pOut->DrawHexagon(P1, gfxInfo, true);

	pOut->PrintMessage("Drawing a hexagon test is done, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->ClearDrawArea();

	/// 2.5 - Circle Test ///
	/// ==================
	pOut->PrintMessage("Drawing a circle with all possible states, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	// 2.5.1 - Drawing unhighlighted, unfilled circle
	// ==============================================
	int radius = 0;

	do
	{
		pOut->PrintMessage("Drawing a circle => unhighlighted and unfilled, click two point");
		pIn->GetPointClicked(P1.x, P1.y);
		pIn->GetPointClicked(P2.x, P2.y);
		radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

		if (P1.y - radius <= UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The circle can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y - radius <= UI.ToolBarHeight);

	gfxInfo.BorderWidth = 5;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.isFilled = false;
	pOut->DrawCircle(P1, P2, gfxInfo, false);

	// 2.5.2 - Drawing highlighted, unfilled circle
	// ============================================
	pOut->PrintMessage("Drawing a circle => highlighted and unfilled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->DrawCircle(P1, P2, gfxInfo, true);

	// 2.5.3 - Drawing unhighlighted, filled circle
	// ============================================
	do
	{
		pOut->PrintMessage("Drawing a circle => unhighlighted and filled, click two point");
		pIn->GetPointClicked(P1.x, P1.y);
		pIn->GetPointClicked(P2.x, P2.y);
		radius = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));

		if (P1.y - radius <= UI.ToolBarHeight)
		{
			pOut->PrintMessage("[OUT OF RANGE] The circle can't be drawn over the toolbar, click anywhere to continue");
			pIn->GetPointClicked(x, y); // Wait for any click
		}
	} while (P1.y - radius <= UI.ToolBarHeight);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWidth = 5;
	gfxInfo.FillClr = YELLOW;
	gfxInfo.isFilled = true;
	pOut->DrawCircle(P1, P2, gfxInfo, false);

	// 2.5.4 - Drawing highlighted, filled circle
	// ==========================================
	pOut->PrintMessage("Drawing a circle => highlighted and filled, click anywhere to highlight");
	pIn->GetPointClicked(x, y); // Wait for any click

	pOut->DrawCircle(P1, P2, gfxInfo, true);
	pOut->PrintMessage("Drawing a circle test is done, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->ClearDrawArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3:
	//			Input Class: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST3: Input class for reading strings, click anywhere to continue");
	pIn->GetPointClicked(x, y); // Wait for any click

	pOut->PrintMessage("Testing Input ability to read strings, type using your keyboard and click enter at the end");

	string userInput = pIn->GetString(pOut);
	pOut->PrintMessage("You Entered: " + userInput);
	pIn->GetPointClicked(x, y); // Wait for any click
	pOut->ClearDrawArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4:
	//			Input Class : Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST4: Input class for detecting user action, click anywhere");

	int ClickedItemOrder = 0;
	ActionType actionType;

	do
	{
		actionType = pIn->GetUserAction(&ClickedItemOrder);

		switch (actionType)
		{
		case TO_DRAW:
			pOut->PrintMessage("Action: Switched to draw mode, click anywhere");
			pOut->CreateDrawToolBar();
			break;
		case TO_PLAY:
			pOut->PrintMessage("Action: Switched to play mode, click anywhere");
			pOut->CreatePlayToolBar();
			break;
		case DRAW_RECT:
			pOut->PrintMessage("Action: Draw a rectangle, click anywhere");
			break;
		case DRAW_CIRCLE:
			pOut->PrintMessage("Action: Draw a circle, click anywhere");
			break;
		case DRAW_SQUARE:
			pOut->PrintMessage("Action: Draw a square, click anywhere");
			break;
		case DRAW_TRIANGLE:
			pOut->PrintMessage("Action: Draw a triangle, click anywhere");
			break;
		case DRAW_HEXAGON:
			pOut->PrintMessage("Action: Draw a hexagon, click anywhere");
			break;
		case OUTLINE:
			pOut->PrintMessage("Action: Outline selected shape, click anywhere");
			break;
		case SELECT:
			pOut->PrintMessage("Action: Select a shape, click anywhere");
			break;
		case BORDER_WIDTH:
			pOut->PrintMessage("Action: Border width, click anywhere");
			break;
		case OUTLINE_COLOR:
			pOut->PrintMessage("Action: Outline color, select a color");

			pOut->OpenColorMenuWind(ClickedItemOrder * UI.MenuItemWidth, false);
			selectedColor = pIn->GetSelectedColor(pOut);

			printSelectedColor(pOut, selectedColor);
			break;
		case FILL_COLOR:
			pOut->PrintMessage("Action: Fill color, select a color");

			pOut->OpenColorMenuWind(ClickedItemOrder * UI.MenuItemWidth);
			selectedColor = pIn->GetSelectedColor(pOut);

			printSelectedColor(pOut, selectedColor);
			break;
		case FILL:
			pOut->PrintMessage("Action: Fill selected shape, click anywhere");
			break;
		case REMOVE:
			pOut->PrintMessage("Action: Remove selected shape, click anywhere");
			break;
		case MOVE:
			pOut->PrintMessage("Action: Move selected shape, click anywhere");
			break;
		case RESIZE:
			pOut->PrintMessage("Action: Resize selected shape, click anywhere");
			break;
		case DRAG_MOVE:
			pOut->PrintMessage("Action: Move selected shape by dragging, click anywhere");
			break;
		case DRAG_RESIZE:
			pOut->PrintMessage("Action: Resize selected shape by dragging, click anywhere");
			break;
		case UNDO:
			pOut->PrintMessage("Action: Undo, click anywhere");
			break;
		case REDO:
			pOut->PrintMessage("Action: Redo, click anywhere");
			break;
		case CLEAR_ALL:
			pOut->PrintMessage("Action: Clear the canvas, click anywhere");
			break;
		case START_RECORDING:
			pOut->PrintMessage("Action: Start recording, click anywhere");
			break;
		case STOP_RECORDING:
			pOut->PrintMessage("Action: Stop recording, click anywhere");
			break;
		case PLAY_RECORDING:
			pOut->PrintMessage("Action: Play recording, click anywhere");
			break;
		case BACKGROUND_COLOR:
			pOut->PrintMessage("Action: Background color, select a color");

			pOut->OpenColorMenuWind(ClickedItemOrder * UI.MenuItemWidth, false);
			UI.BkGrndColor = pIn->GetSelectedColor(pOut);

			pOut->ClearDrawArea();
			break;
		case OPEN_GRAPH:
			pOut->PrintMessage("Action: Open graph, click anywhere");
			break;
		case SAVE_GRAPH:
			pOut->PrintMessage("Action: Save graph, click anywhere");
			break;
		case PICK_BY_SHAPE:
			pOut->PrintMessage("Action: Pick by shape game mode, click anywhere");
			break;
		case PICK_BY_COLOR:
			pOut->PrintMessage("Action: Pick by color game mode, click anywhere");
			break;
		case PICK_BY_SHAPE_COLOR:
			pOut->PrintMessage("Action: Pick by shape and color game mode, click anywhere");
			break;
		case DRAWING_AREA:
			pOut->PrintMessage("Action: Drawing Area, click anywhere");
			break;
		case STATUS:
			pOut->PrintMessage("Action: Status Bar, click anywhere");
			break;
		case EMPTY:
			pOut->PrintMessage("Action: Empty area in the toolbar, click anywhere");
			break;
		case EXIT:
			break;
		}
	} while (actionType != EXIT);

	/// Exiting
	pOut->PrintMessage("Action: Exit, click anywhere to exit");
	pIn->GetPointClicked(x, y); // Wait for any click

	delete pIn;
	delete pOut;
	return 0;
}

void printSelectedColor(Output *outputPtr, const color &color)
{
	if (color == BLACK)
		outputPtr->PrintMessage("You selected Black, click anywhere to continue");
	else if (color == RED)
		outputPtr->PrintMessage("You selected Red, click anywhere to continue");
	else if (color == BLUE)
		outputPtr->PrintMessage("You selected Blue, click anywhere to continue");
	else if (color == GREEN)
		outputPtr->PrintMessage("You selected Green, click anywhere to continue");
	else if (color == MAGENTA)
		outputPtr->PrintMessage("You selected Magenta, click anywhere to continue");
	else if (color == ORANGE)
		outputPtr->PrintMessage("You selected Orange, click anywhere to continue");
	else if (color == BROWN)
		outputPtr->PrintMessage("You selected Brown, click anywhere to continue");
	else if (color == CYAN)
		outputPtr->PrintMessage("You selected Cyan, click anywhere to continue");
	else if (color == YELLOW)
		outputPtr->PrintMessage("You selected Yellow, click anywhere to continue");
	else if (color == LIGHTGOLDENRODYELLOW)
		outputPtr->PrintMessage("You selected Gold, click anywhere to continue");
	else if (color == TRANSPARENT_COLOR)
		outputPtr->PrintMessage("You selected Transparent, click anywhere to continue");
}
