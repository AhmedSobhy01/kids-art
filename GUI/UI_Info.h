#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

// User Interface information file.
// This file contains info that is needed by Input and Output classes to
// Handle the user interface

enum GUI_MODE // Graphical user interface mode
{
	MODE_DRAW, // Drawing mode (startup mode)
	MODE_PLAY  // Playing mode
};

enum DrawMenuItem // The items of the draw menu (ordered)
{
	ITM_PLAY_MODE,		  // Switch To Play Mode
	ITM_RECT,			  // Draw Rectangle
	ITM_SQUARE,			  // Draw Square
	ITM_TRIANGLE,		  // Draw Triangle
	ITM_CIRCLE,			  // Draw Circle
	ITM_HEXAGON,		  // Draw Hexagon
	ITM_OUTLINE_COLOR,	  // Outline Color Menu
	ITM_FILL_COLOR,		  // Fill Color Menu
	ITM_SELECT,			  // Select Shape
	ITM_REMOVE,			  // Remove Selected Shape
	ITM_MOVE,			  // Move Selected Shape
	ITM_DRAG_MOVE,		  // Move Selected Shape By Dragging
	ITM_DRAG_RESIZE,	  // Resize Selected Shape By Dragging
	ITM_START_RECORDING,  // Start Recording
	ITM_STOP_RECORDING,	  // Stop Recording
	ITM_PLAY_RECORDING,	  // Play Recording
	ITM_UNDO,			  // Undo Last Action
	ITM_REDO,			  // Redo Last Action
	ITM_BACKGROUND_COLOR, // Canvas Background Color Menu
	ITM_CLEAR_ALL,		  // Clear Canvas
	ITM_OPEN,			  // Open Graph
	ITM_SAVE,			  // Save Graph
	ITM_TOGGLE_SOUND,	  // Toggle Action Sound Playing
	ITM_EXIT,			  // Exit

	DRAW_ITM_COUNT, // No of menu items
};

enum ColorMenuItem // The items of the color menu (ordered)
{
	COLOR_MENU_ITM_PINK,		// Brown
	COLOR_MENU_ITM_RED,			// Red
	COLOR_MENU_ITM_ORANGE,		// Orange
	COLOR_MENU_ITM_YELLOW,		// Yellow
	COLOR_MENU_ITM_GREEN,		// Green
	COLOR_MENU_ITM_SKY,		// Cyan
	COLOR_MENU_ITM_BLUE,		// Blue
	COLOR_MENU_ITM_LAVENDER,		// Magenta
	COLOR_MENU_ITM_BASE,		// Base
	COLOR_MENU_ITM_BLACK,		// Black
	COLOR_MENU_ITM_TRANSPARENT, // Transparent
	COLOR_MENU_ITM_COUNT,		// No of color menu items
};

enum PlayMenuItem // The items of the play menu (ordered)
{
	ITM_DRAW_MODE,			 // Switch To Draw Mode
	ITM_PICKBYSHAPE,		 // Pick By Shape Game Mode
	ITM_PICKBYCOLOR,		 // Pick By Color Game Mode
	ITM_PICKBYSHAPEANDCOLOR, // Pick By Shape and Color Game Mode
	ITM_EXIT_PLAY,			 // Exit Play Mode
	PLAY_ITM_COUNT,			 // No of play menu items
};

__declspec(selectany) // This line to prevent "redefinition error"

	struct UI_Info // User Interface Info.
{
	GUI_MODE InterfaceMode;

	int width, height,	 // Window width and height
		wx, wy,			 // Window starting coordinates
		StatusBarHeight, // Status Bar Height
		ToolBarHeight,	 // Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;	 // Width of each item in toolbar menu

	int ColorMenuWidth, ColorMenuHeight, ColorMenuItemWidth;

	color DrawColor;	  // Drawing color
	color FillColor;	  // Filling color
	color HighlightColor; // Highlighting color
	color MsgColor;		  // Messages color
	color BkGrndColor;	  // Background color
	color StatusBarColor; // Status bar color
	int PenWidth;		  // Width of the pen that draws shapes
} UI;					  // Create a global object UI

#endif