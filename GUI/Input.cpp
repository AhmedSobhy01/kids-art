#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::SetColorMenuWind(window* ptr) {
	colorMenuWind = ptr;
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_EXIT: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
/////////////////////////////////


//This function reads the position where the user clicks to determine the selected color
color Input::GetSelectedColor() const
{
	if (colorMenuWind) {
		int x, y;
		colorMenuWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

		if (y >= 0 && y < UI.ColorMenuHeight)
		{
			int ClickedColorOrder = (x / UI.ColorMenuItemWidth);

			switch (ClickedColorOrder)
			{
				case COLOR_MENU_ITM_BLACK: return BLACK;
				case COLOR_MENU_ITM_RED: return RED;
				case COLOR_MENU_ITM_BLUE: return BLUE;
				case COLOR_MENU_ITM_GREEN: return GREEN;
				case COLOR_MENU_ITM_MAGENTA: return MAGENTA;
				case COLOR_MENU_ITM_ORANGE: return ORANGE;
				case COLOR_MENU_ITM_BROWN: return BROWN;
				case COLOR_MENU_ITM_CYAN: return CYAN;
				case COLOR_MENU_ITM_YELLOW: return YELLOW;

				default: return TRANSPARENT_COLOR;
			}
		}
	}

	return TRANSPARENT_COLOR;
}
/////////////////////////////////
	
Input::~Input()
{
}
