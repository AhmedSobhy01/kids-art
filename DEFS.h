#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	TO_PLAY,		//Switch interface to Play mode
	TO_DRAW,		//Switch interface to Draw mode
	DRAW_RECT,		//Draw Rectangle
	DRAW_CIRCLE,
	DRAW_SQUARE,
	DRAW_TRIANGLE,
	DRAW_HEXAGON,
	OUTLINE,
	SELECT,
	BORDER_WIDTH,
	OUTLINE_COLOR,
	FILL_COLOR,
	FILL,
	REMOVE,
	MOVE,
	RESIZE,
	DRAG_MOVE,
	DRAG_RESIZE,
	UNDO,
	REDO,
	CLEAR_ALL,
	START_RECORDING,
	STOP_RECORDING,
	PLAY_RECORDING,
	BACKGROUND_COLOR,
	OPEN_GRAPH,
	SAVE_GRAPH,
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar
	EXIT		    //Exit

	///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif