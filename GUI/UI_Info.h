#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
<<<<<<< HEAD
	PlayMode,
	Rect,
	Circle,
	Square,
	Triangle,
	Hexagon,
	Outline,
	Select,
	BorderWidth,
	ForegroundColor,
	BackgroundColor,
	Fill,
	Remove,
	Move,
	Resize,
	DragMove,
	DragResize,
	Undo,
	Redo,
	ClearAll,
	StartRecording,
	StopRecording,
	PlayRecording,
	ArtBoardBackground,
	Open,
	Save,
	Exit,

	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

=======
	ITM_PLAY_MODE,
	ITM_RECT,
	ITM_CIRCLE,
	ITM_SQUARE,
	ITM_TRIANGLE,
	ITM_HEXAGON,
	ITM_OUTLINE,
	ITM_SELECT,
	ITM_BORDER_WIDTH,
	ITM_OUTLINE_COLOR,
	ITM_FILL_COLOR,
	ITM_FILL,
	ITM_REMOVE,
	ITM_MOVE,
	ITM_RESIZE,
	ITM_DRAG_MOVE,
	ITM_DRAG_RESIZE,
	ITM_UNDO,
	ITM_REDO,
	ITM_CLEAR_ALL,
	ITM_START_RECORDING,
	ITM_STOP_RECORDING,
	ITM_PLAY_RECORDING,
	ITM_PICKBYSHAPE,
	ITM_PICKBYCOLOR,
	ITM_PICKBYSHAPEANDCOLOR,
	ITM_BACKGROUND_COLOR,
	ITM_OPEN,
	ITM_SAVE,
	ITM_EXIT,

	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum ColorMenuItem
{
	COLOR_MENU_ITM_BLACK,
	COLOR_MENU_ITM_RED,
	COLOR_MENU_ITM_BLUE,
	COLOR_MENU_ITM_GREEN,
	COLOR_MENU_ITM_MAGENTA,
	COLOR_MENU_ITM_ORANGE,
	COLOR_MENU_ITM_BROWN,
	COLOR_MENU_ITM_CYAN,
	COLOR_MENU_ITM_YELLOW,
	COLOR_MENU_ITM_TRANSPARENT,
	COLOR_MENU_ITM_COUNT,
>>>>>>> 3e460de9b056249ea846da5ec49dd64881ff4cca
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here

	//TODO: Add more items names here
<<<<<<< HEAD
	DrawMode,
	ExitPlay,
=======
	ITM_DRAW_MODE,
	ITM_EXIT_PLAY,
>>>>>>> 3e460de9b056249ea846da5ec49dd64881ff4cca
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,	    //Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu

	int ColorMenuWidth, ColorMenuHeight, ColorMenuItemWidth;

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed

}UI;	//create a global object UI

#endif