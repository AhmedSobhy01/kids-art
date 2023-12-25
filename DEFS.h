#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported
{
	TO_PLAY,			 // Switch interface to play mode
	TO_DRAW,			 // Switch interface to draw mode
	DRAW_RECT,			 // Draw Rectangle
	DRAW_CIRCLE,		 // Draw Circle
	DRAW_SQUARE,		 // Draw Square
	DRAW_TRIANGLE,		 // Draw Triangle
	DRAW_HEXAGON,		 // Draw Hexagon
	BORDER_WIDTH,		 // Change Border Width
	SELECT,				 // Select Shape
	OUTLINE_COLOR,		 // Outline Color Menu
	FILL_COLOR,			 // Fill Color Menu
	REMOVE,				 // Remove Selected Shape
	MOVE,				 // Move Selected Shape
	DRAG_MOVE,			 // Move Selected Shape By Dragging
	DRAG_RESIZE,		 // Resize Selected Shape By Dragging
	UNDO,				 // Undo Last Action
	REDO,				 // Redo Last Action
	CLEAR_ALL,			 // Clear Canvas
	START_RECORDING,	 // Start Recording
	STOP_RECORDING,		 // Stop Recording
	PLAY_RECORDING,		 // Play Recording
	BACKGROUND_COLOR,	 // Canvas Background Color Menu
	TOGGLE_SOUND,		 // Toggle Action Sound Playing
	OPEN_GRAPH,			 // Open Saved Graph
	SAVE_GRAPH,			 // Save Current Graph
	PICK_BY_COLOR,		 // Pick By Color Game Mode (Play Mode)
	PICK_BY_SHAPE,		 // Pick By Shape Game Mode (Play Mode)
	PICK_BY_SHAPE_COLOR, // Pick By Shape and Color Game Mode (Play Mode)
	DRAWING_AREA,		 // A click on the drawing area
	STATUS,				 // A click on the status bar
	EMPTY,				 // A click on empty place in the toolbar
	EXIT				 // Exit
};

struct Point // To be used for figures points
{
	int x, y;
};

struct GfxInfo // Graphical info of each figure
{
	color DrawClr;	 // Draw color of the figure
	color FillClr;	 // Fill color of the figure
	bool IsFilled;	 // Figure Filled or not
	int BorderWidth; // Width of figure borders
};

#endif