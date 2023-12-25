#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output; // forward declaration

class Input // The application manager should have a pointer to this class
{
private:
	window *pWind; // Pointer to the Graphics Window
public:
	Input(window *pW); // Constructor

	void GetPointClicked(int &, int &) const; // Get coordinate where user clicks
	void GetMouseCoord(int &, int &) const;	  // Get coordinate where user clicks
	color GetSelectedColor(Output *) const;
	string GetString(Output *) const; // Returns a string entered by the user
	bool GetLeftClickState(int &, int &) const;
	ActionType GetUserAction(int * = NULL) const; // Read the user click and map to an action
	ActionType GetAction(Point &);				  // Gets the user action according to a given point

	~Input();
};

#endif