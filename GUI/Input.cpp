#include "Input.h"
#include "Output.h"

Input::Input(window *pW)
{
	pWind = pW; // Point to the passed window
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//
void Input::GetPointClicked(int &x, int &y) const
{

	pWind->WaitMouseClick(x, y); // Wait for mouse click
}

void Input::GetMouseCoord(int &x, int &y) const
{

	pWind->GetMouseCoord(x, y); // Gets the current mouse coordinates
}

bool Input::GetLeftClickState(int &x, int &y) const
{
	button b = LEFT_BUTTON;
	return pWind->GetButtonState(b, x, y) == BUTTON_DOWN; // Gets the state of the left mouse button
}

std::string Input::GetString(Output *pO) const // Returns a string entered by the user
{
	pWind->FlushKeyQueue();	  // Clear all previous events
	pWind->FlushMouseQueue(); // Clear all previous events

	std::string Label; // Label to be returned
	char Key;		   // Last character pressed

	while (1) // Loop until Enter is pressed or ESCAPE is pressed
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)
		{ // ESCAPE key is pressed
			pWind->FlushKeyQueue();
			pWind->FlushMouseQueue();

			return ""; // Returns nothing as user has cancelled label
		}

		if (Key == 13)
		{ // ENTER key is pressed
			pWind->FlushKeyQueue();
			pWind->FlushMouseQueue();

			return Label;
		}

		if ((Key == 8) && (Label.size() >= 1)) // BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key; // Append the key character to the string

		if (pO)
			pO->PrintMessage(Label); // Print the label on the status bar
	}
}

//======================================================================================//
//								User Action Functions									//
//======================================================================================//
ActionType Input::GetUserAction(int *_ClickedItemOrder) const // This function reads the position where the user clicks to determine the desired action
{
	pWind->FlushMouseQueue(); // Clear all previous mouse events

	Point P;
	pWind->WaitMouseClick(P.x, P.y); // Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW) // GUI in the DRAW mode
	{
		// [1] If user clicks on the Toolbar
		if (P.y >= 0 && P.y < UI.ToolBarHeight)
		{
			// Check which menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (P.x / UI.MenuItemWidth);
			// Divide x coord of the point clicked by the menu item width (int division)
			// if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			if (_ClickedItemOrder)
				*_ClickedItemOrder = ClickedItemOrder; // Return ClickedItemOrder if it was wanted in the parameters list

			switch (ClickedItemOrder)
			{
			case ITM_PLAY_MODE:
				return TO_PLAY;
			case ITM_RECT:
				return DRAW_RECT;
			case ITM_CIRCLE:
				return DRAW_CIRCLE;
			case ITM_SQUARE:
				return DRAW_SQUARE;
			case ITM_TRIANGLE:
				return DRAW_TRIANGLE;
			case ITM_HEXAGON:
				return DRAW_HEXAGON;
			case ITM_BORDER_WIDTH:
				return BORDER_WIDTH;
			case ITM_SELECT:
				return SELECT;
			case ITM_OUTLINE_COLOR:
				return OUTLINE_COLOR;
			case ITM_FILL_COLOR:
				return FILL_COLOR;
			case ITM_REMOVE:
				return REMOVE;
			case ITM_MOVE:
				return MOVE;
			case ITM_DRAG_MOVE:
				return DRAG_MOVE;
			case ITM_DRAG_RESIZE:
				return DRAG_RESIZE;
			case ITM_UNDO:
				return UNDO;
			case ITM_REDO:
				return REDO;
			case ITM_CLEAR_ALL:
				return CLEAR_ALL;
			case ITM_START_RECORDING:
				return START_RECORDING;
			case ITM_STOP_RECORDING:
				return STOP_RECORDING;
			case ITM_PLAY_RECORDING:
				return PLAY_RECORDING;
			case ITM_BACKGROUND_COLOR:
				return BACKGROUND_COLOR;
			case ITM_OPEN:
				return OPEN_GRAPH;
			case ITM_SAVE:
				return SAVE_GRAPH;
			case ITM_TOGGLE_SOUND:
				return TOGGLE_SOUND;
			case ITM_EXIT:
				return EXIT;

			default:
				return EMPTY; // A click on empty place in design toolbar
			}
		}

		// [2] User clicks on the drawing area
		if (P.y >= UI.ToolBarHeight && P.y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}
	else // GUI is in PLAY mode
	{
		if (P.y >= 0 && P.y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (P.x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_DRAW_MODE:
				return TO_DRAW;
			case ITM_PICKBYSHAPE:
				return PICK_BY_SHAPE;
			case ITM_PICKBYCOLOR:
				return PICK_BY_COLOR;
			case ITM_PICKBYSHAPEANDCOLOR:
				return PICK_BY_SHAPE_COLOR;
			case ITM_EXIT_PLAY:
				return EXIT;
			default:
				return EMPTY; // A click on empty place in design toolbar
			}
		}

		// [2] User clicks on the drawing area
		if (P.y >= UI.ToolBarHeight && P.y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}
}

ActionType Input::GetAction(Point &P)
{
	if (P.y >= 0 && P.y <= UI.StatusBarHeight) // User clicks on the toolbar
	{
		int ClickedItem = P.x / UI.MenuItemWidth;
		switch (ClickedItem)
		{
		case ITM_DRAW_MODE:
			return TO_DRAW;
		case ITM_PICKBYSHAPE:
			return PICK_BY_SHAPE;
		case ITM_PICKBYCOLOR:
			return PICK_BY_COLOR;
		case ITM_PICKBYSHAPEANDCOLOR:
			return PICK_BY_SHAPE_COLOR;
		case ITM_EXIT_PLAY:
			return EXIT;
		default:
			return EMPTY;
		}
	}
	else
		return DRAWING_AREA; // User clicks on the drawing area
}

//======================================================================================//
//								Color Menu Functions									//
//======================================================================================//
color Input::GetSelectedColor(Output *pO) const // This function reads the position where the user clicks to determine the selected color
{
	if (pO->GetColorMenuWind()) // If the color menu window is already open
	{
		Point P;
		pO->GetColorMenuWind()->WaitMouseClick(P.x, P.y); // Get the coordinates of the user click

		if (P.y >= 0 && P.y < UI.ColorMenuHeight) // If the user clicks on the color menu window
		{
			int ClickedColorOrder = (P.x / UI.ColorMenuItemWidth);
			color SelectedColor;

			switch (ClickedColorOrder)
			{
			case COLOR_MENU_ITM_PINK:
				SelectedColor = PINK;
				break;
			case COLOR_MENU_ITM_RED:
				SelectedColor = RED;
				break;
			case COLOR_MENU_ITM_ORANGE:
				SelectedColor = ORANGE;
				break;
			case COLOR_MENU_ITM_YELLOW:
				SelectedColor = YELLOW;
				break;
			case COLOR_MENU_ITM_GREEN:
				SelectedColor = GREEN;
				break;
			case COLOR_MENU_ITM_SKY:
				SelectedColor = SKY;
				break;
			case COLOR_MENU_ITM_BLUE:
				SelectedColor = BLUE;
				break;
			case COLOR_MENU_ITM_LAVENDER:
				SelectedColor = LAVENDER;
				break;
			case COLOR_MENU_ITM_BASE:
				SelectedColor = BASE;
				break;
			case COLOR_MENU_ITM_BLACK:
				SelectedColor = BLACK;
				break;

			default:
				SelectedColor = TRANSPARENT_COLOR;
				break;
			}

			pO->CloseColorMenuWind();
			return SelectedColor;
		}
	}

	return TRANSPARENT_COLOR; // If the user clicks anywhere else
}
//////////////////////////////////////////////////////////////////////////////////////////

Input::~Input()
{
}
