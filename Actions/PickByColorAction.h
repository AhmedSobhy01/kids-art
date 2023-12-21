#ifndef PICK_BY_COLOR_ACTION_H
#define PICK_BY_COLOR_ACTION_H
#include "Action.h"
#include "..\ApplicationManager.h"

class PickByColorAction: public Action {
private:
	Point P;
	color RandomColor;
	CFigure* RandomFigure;
	int CorrectPicks;
	int Counter;							// Counter for total picks made
	int RandomColorNumber;					// Integer to store how many instances for the random color to be picked
public:
	PickByColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	void StartingMessage();					// Prints the starting message
	void GetClickedAction(bool&, bool&);	// Gets the user action
	void FinalMsg(bool&);
};
#endif