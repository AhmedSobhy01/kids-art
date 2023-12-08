#ifndef PICK_BY_COLOR_ACTION_H
#define PICK_BY_COLOR_ACTION_H
#include "Action.h"
#include "..\GUI\UI_Info.h"

class PickByColorAction: public Action {
private:
	Point P;
	color RandomColor;
	int CorrectPicks;
	int Counter;							// Counter for total picks made
	int FiguresNumber;						// Integer to store total number of figures in FigList
	int RandomColorNumber;					// Integer to store how many instances for the random color to be picked

public:
	PickByColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	void PrintMessage();					// Prints the starting message
	string GetFigureColor(color);			// Returns the color of a figure as a string
};
#endif