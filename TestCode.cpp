#include "GUI\Input.h"
#include "GUI\Output.h"

//This is a test code to test the Input and Output classes

int main()
{
	int x, y;

	//Create Input and Output objects to test
	Output* pOut = new Output();
	Input* pIn = pOut->CreateInput();

	//Starting the test
	pOut->PrintMessage("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x, y);	//Wait for any click

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 0:	
	//			Creates color menu in the center of main window and closes after selection of color	
	//			Selected color is sorted in the variable of name "selectedColor"
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST0: Color Menu Window, Click anywhere to open color menu window");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->OpenColorMenuWind((UI.width - UI.ColorMenuWidth) / 2);
	pIn->SetColorMenuWind(pOut->GetColorMenuWind());

	color selectedColor = pIn->GetSelectedColor();

	pOut->CloseColorMenuWind();
	pIn->SetColorMenuWind(pOut->GetColorMenuWind());

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 1:	
	//			Create The FULL Tool bar, the drawing area and the status bar	
	//			This has already been done through the constrcutor of class Output
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:	
	//			Drawing all the Figures with all possible states: 
	//			Non-filled, Filled, and highlighted in both cases			
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST2: Now we will show that Output class can draw any figure in any state, Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	GfxInfo gfxInfo;//to be used with draw function of the class Ouput
	Point P1, P2, P3;

	/// 2.1- Rectangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Rectangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	// 2.1.1 - Drawing non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.isFilled = false;	//Figure is NOT filled
	pOut->DrawRect(P1, P2, gfxInfo, false);

	// 2.1.2 - Drawing highlighted non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);


	// 2.1.3 - Drawing a filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo.BorderWdth = 6;
	gfxInfo.DrawClr = BLUE;	//any color for border
	gfxInfo.FillClr = GREENYELLOW;//any color for filling
	gfxInfo.isFilled = true;//Figure is filled
	pOut->DrawRect(P1, P2, gfxInfo, false);


	// 2.1.4 - Drawing a highlighted filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawRect(P1, P2, gfxInfo, true);



	pOut->PrintMessage("Drawing a Rectangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.2- Square Test ///
	/// ============== 
	pOut->PrintMessage("Drawing a Square, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	// 2.2.1 - Drawing a Square non-filled
	pOut->PrintMessage("Drawing a Square ==> non-filled,  Click one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.isFilled = false;
	pOut->DrawSquare(P1, gfxInfo, false);

	// 2.2.2 - Drawing highlighted non-filled Square
	pOut->PrintMessage("Drawing a highlighted non-filled Square, Click to highlight");
	pIn->GetPointClicked(x, y);
	pOut->DrawSquare(P1, gfxInfo, true);


	// 2.2.3 - Drawing a filled Square
	pOut->PrintMessage("Drawing a Square ==> Filled, Click one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWdth = 5;
	gfxInfo.FillClr = GOLD;
	gfxInfo.isFilled = true;
	pOut->DrawSquare(P1, gfxInfo, false);

	// 2.2.4 - Drawing highlighted filled Square
	pOut->PrintMessage("Drawing a highlighted filled Square, Click to highlight");
	pIn->GetPointClicked(x, y);

	pOut->DrawSquare(P1, gfxInfo, true);


	pOut->PrintMessage("Drawing a Square Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.3- Triangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Triangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click


	// 2.3.1 - Drawing a Triangle non-filled
	pOut->PrintMessage("Drawing a Triangle ==> non-filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.isFilled = false;
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, false);

	// 2.3.2 - Drawing highlighted non-filled Triangle
	pOut->PrintMessage("Drawing a highlighted non-filled Triangle, Click to highlight");
	pIn->GetPointClicked(x, y);
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, true);


	// 2.3.3 - Drawing a filled Triangle
	pOut->PrintMessage("Drawing a Triangle ==> Filled, Click three point");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);


	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWdth = 5;
	gfxInfo.FillClr = YELLOW;
	gfxInfo.isFilled = true;
	pOut->DrawTriangle(P1, P2, P3, gfxInfo, false);

	// 2.3.4 - Drawing highlighted filled Triangle
	pOut->PrintMessage("Drawing a highlighted filled Triangle, Click to highlight");
	pIn->GetPointClicked(x, y);

	pOut->DrawTriangle(P1, P2, P3, gfxInfo, true);

	pOut->PrintMessage("Drawing a Triangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.4- Hexagon Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Hexagon, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->PrintMessage("Drawing a Hexagon ==> Non-filled, click one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWdth = 5;
	gfxInfo.isFilled = false;
	pOut->DrawHexagon(P1, gfxInfo, false);

	pOut->PrintMessage("Drawing a highlighted non-filled Hexagon, click to highlight");
	pIn->GetPointClicked(x, y);

	pOut->DrawHexagon(P1, gfxInfo, true);

	pOut->PrintMessage("Drawing a Hexagon ==> Filled, click one point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWdth = 5;
	gfxInfo.isFilled = true;
	gfxInfo.FillClr = WHITE;
	pOut->DrawHexagon(P1, gfxInfo, false);

	pOut->PrintMessage("Drawing a highlighted filled Hexagon, click to highlight");
	pIn->GetPointClicked(x, y);

	pOut->DrawHexagon(P1, gfxInfo, true);

	pOut->PrintMessage("Drawing a Hexagon Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.5- Circle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Circle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	// 2.4.1 - Drawing a Circle non-filled
	pOut->PrintMessage("Drawing a Circle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo.BorderWdth = 5;
	gfxInfo.DrawClr = BLUE;
	gfxInfo.isFilled = false;
	pOut->DrawCircle(P1, P2, gfxInfo, false);

	// 2.4.2 - Drawing highlighted non-filled Circle
	pOut->PrintMessage("Drawing a highlighted non-filled Circle, Click to highlight");
	pIn->GetPointClicked(x, y);
	pOut->DrawCircle(P1, P2, gfxInfo, true);


	// 2.4.3 - Drawing a filled Circle
	pOut->PrintMessage("Drawing a Circle ==> Filled, Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);


	gfxInfo.DrawClr = BLUE;
	gfxInfo.BorderWdth = 5;
	gfxInfo.FillClr = GRAY;
	gfxInfo.isFilled = true;
	pOut->DrawCircle(P1, P2, gfxInfo, false);

	// 2.4.4 - Drawing highlighted filled Circle
	pOut->PrintMessage("Drawing a highlighted filled Circle, Click to highlight");
	pIn->GetPointClicked(x, y);

	pOut->DrawCircle(P1, P2, gfxInfo, true);
	pOut->PrintMessage("Drawing a Circle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: 
	//			Input Class: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x, y);	//Wait for any click

	pOut->PrintMessage("Testing Input ability to read strings");

	// 1- Read a string from the user on the status bar
	// 2- After reading the string clear the status bar
	// 3- print on the status bar "You Entered" then print the string
	string userInput = pIn->GetString(pOut);
	pOut->PrintMessage("You Entered " + userInput);
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: 
	//			Input Class : Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;

	///TODO:  
	//You must add a case for each action (both Draw mode and Play mode actions)
	//Add cases for the missing actions below
	do
	{
		ActType = pIn->GetUserAction();
		switch (ActType)
		{
		case TO_DRAW:
			pOut->PrintMessage("Action: Switch to Draw Mode, creating simualtion tool bar");
			pOut->CreateDrawToolBar();
			break;
		case TO_PLAY:
			pOut->PrintMessage("Action: Switch to Play Mode, creating Design tool bar");
			pOut->CreatePlayToolBar();
			break;
		case DRAW_RECT:
			pOut->PrintMessage("Action: Draw a Rectangle , Click anywhere");
			break;
		case DRAW_CIRCLE:
			pOut->PrintMessage("Action: Draw a Circle , Click anywhere");
			break;
		case DRAW_SQUARE:
			pOut->PrintMessage("Action: Draw a Square , Click anywhere");
			break;
		case DRAW_TRIANGLE:
			pOut->PrintMessage("Action: Draw a Triangle , Click anywhere");
			break;
		case DRAW_HEXAGON:
			pOut->PrintMessage("Action: Draw a Hexagon , Click anywhere");
			break;
		case OUTLINE:
			pOut->PrintMessage("Action: Outline a Shape , Select a shape to outline");
			break;
		case SELECT:
			pOut->PrintMessage("Action: Select a Shape , Click on a shape");
			break;
		case BORDER_WIDTH:
			pOut->PrintMessage("Action: Border Width , Click on a size");
			break;
		case OUTLINE_COLOR:
			pOut->PrintMessage("Action: Ouline Color , Click to choose a color");
			break;
		case FILL_COLOR:
			pOut->PrintMessage("Action: Fill Color , Click to choose a color");
			break;
		case FILL:
			pOut->PrintMessage("Action: Fill a Shape , Select a shape to fill");
			break;
		case REMOVE:
			pOut->PrintMessage("Action: Remove a Shape , Select a shape to remove");
			break;
		case MOVE:
			pOut->PrintMessage("Action: Move a Shape , Select a shape to move");
			break;
		case RESIZE:
			pOut->PrintMessage("Action: Resize a Shape , Select a shape to resize");
			break;
		case DRAG_MOVE:
			pOut->PrintMessage("Action: Move a Shape , Drag the shape to move");
			break;
		case DRAG_RESIZE:
			pOut->PrintMessage("Action: Resize a Shape , Drag the corners of a shape to resize");
			break;
		case UNDO:
			pOut->PrintMessage("Action: Undo");
			break;
		case REDO:
			pOut->PrintMessage("Action: Redo");
			break;
		case CLEAR_ALL:
			pOut->PrintMessage("Action: Clear the canvas");
			break;
		case START_RECORDING:
			pOut->PrintMessage("Action: Start Recording");
			break;
		case STOP_RECORDING:
			pOut->PrintMessage("Action: Stop Recording");
			break;
		case PLAY_RECORDING:
			pOut->PrintMessage("Action: Play Recording");
			break;
		case BACKGROUND_COLOR:
			pOut->PrintMessage("Action: Background color , Click to choose a color");
			break;
		case OPEN_GRAPH:
			pOut->PrintMessage("Action: Open graph , Type the graph name to open");
			break;
		case SAVE_GRAPH:
			pOut->PrintMessage("Action: Save graph , Type the graph name to save");
			break;
		case DRAWING_AREA:
			pOut->PrintMessage("Action: a click on the Drawing Area, Click anywhere");
			break;
		case STATUS:
			pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
			break;
		case EMPTY:
			pOut->PrintMessage("Action: a click on empty area in the Design Tool Bar, Click anywhere");
			break;
		case EXIT:
			break;
		}


	} while (ActType != EXIT);


	/// Exiting
	pOut->PrintMessage("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x, y);


	delete pIn;
	delete pOut;
	return 0;
}


