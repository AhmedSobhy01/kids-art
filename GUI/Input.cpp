#include "Input.h"
#include "Output.h"

Input::Input(window *pW)
{
	pWind = pW; // point to the passed window
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Input::GetPointClicked(int &x, int &y) const
{
	
	pWind->WaitMouseClick(x, y); // Wait for mouse click
}
void Input::GetMouseCoord(int& x, int& y) const
{

	pWind->GetMouseCoord(x, y); // get mouse current position
}

bool Input::GetLeftClickState(int& x, int& y)const {
	button b = LEFT_BUTTON;
	return pWind->GetButtonState(b,x, y) == BUTTON_DOWN;
}

//////////////////////////////////////////////////////////////////////////////////////////

string Input::GetString(Output *pO) const
{
	pWind->FlushKeyQueue();
	pWind->FlushMouseQueue();

	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27) { // ESCAPE key is pressed
			pWind->FlushKeyQueue();
			pWind->FlushMouseQueue();

			return ""; // returns nothing as user has cancelled label
		}

		if (Key == 13) { // ENTER key is pressed
			pWind->FlushKeyQueue();
			pWind->FlushMouseQueue();

			return Label;
		}

		if ((Key == 8) && (Label.size() >= 1)) // BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;

		if (pO)
			pO->PrintMessage(Label);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

ActionType Input::GetUserAction(int *_ClickedItemOrder) const // This function reads the position where the user clicks to determine the desired action
{
	int x, y;
	pWind->WaitMouseClick(x, y); // Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW) // GUI in the DRAW mode
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
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
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}
	else // GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
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
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}
}
ActionType Input::GetAction(Point& P)
{
		int clickeditem = P.x / UI.MenuItemWidth;
		switch (clickeditem) {
		case ITM_DRAW_MODE:
			return TO_DRAW;
		case ITM_PICKBYSHAPE:
			return PICK_BY_SHAPE;
		case ITM_PICKBYCOLOR:
			return PICK_BY_COLOR;
		case ITM_PICKBYSHAPEANDCOLOR:
			return PICK_BY_SHAPE_COLOR;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////

color Input::GetSelectedColor(Output* pO) const // This function reads the position where the user clicks to determine the selected color
{
	if (pO->GetColorMenuWind())
	{
		int x, y;
		pO->GetColorMenuWind()->WaitMouseClick(x, y); // Get the coordinates of the user click

		if (y >= 0 && y < UI.ColorMenuHeight)
		{
			int ClickedColorOrder = (x / UI.ColorMenuItemWidth);
			color selectedColor;

			switch (ClickedColorOrder)
			{
			case COLOR_MENU_ITM_BLACK:
				selectedColor = BLACK;
				break;
			case COLOR_MENU_ITM_RED:
				selectedColor = RED;
				break;
			case COLOR_MENU_ITM_BLUE:
				selectedColor = BLUE;
				break;
			case COLOR_MENU_ITM_GREEN:
				selectedColor = GREEN;
				break;
			case COLOR_MENU_ITM_LAVENDER:
				selectedColor = LAVENDER;
				break;
			case COLOR_MENU_ITM_ORANGE:
				selectedColor = PEACH;
				break;
			case COLOR_MENU_ITM_PINK:
				selectedColor = PINK;
				break;
			case COLOR_MENU_ITM_SKY:
				selectedColor = SKY;
				break;
			case COLOR_MENU_ITM_YELLOW:
				selectedColor = YELLOW;
				break;
			case COLOR_MENU_ITM_BASE:
				selectedColor = BASE;
				break;

			default:
				selectedColor = TRANSPARENT_COLOR;
				break;
			}

			pO->CloseColorMenuWind();
			return selectedColor;
		}
	}

	return TRANSPARENT_COLOR;
}
//////////////////////////////////////////////////////////////////////////////////////////

Input::~Input()
{
}
