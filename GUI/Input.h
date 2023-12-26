#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output; // forward declaration

class Input // The application manager should have a pointer to this class
{
	window *pWind; // Pointer to the Graphics Window

public:
	Input(window *pW);

	// Color menu functions
	color GetSelectedColor(Output *) const; // Returns the selected color from the color menu

	// Mouse & Keyboard functions
	void GetPointClicked(int &, int &) const;	// Get coordinate where user clicks
	void GetMouseCoord(int &, int &) const;		// Get current mouse coordinates
	bool GetLeftClickState(int &, int &) const; // Get if left click is pressed or not
	std::string GetString(Output *) const;		// Returns a string entered by the user

	// Action type functions
	ActionType GetUserAction(int * = NULL) const; // Read the user click and map to an action
	ActionType GetAction(Point &);				  // Gets the user action according to a given point

	~Input();
};

#endif