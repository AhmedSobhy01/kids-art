#ifndef PICK_BY_SHAPE_ACTION_H
#define PICK_BY_SHAPE_ACTION_H
#include "Action.h"
#include "..\ApplicationManager.h"

class PickByShapeAction: public Action {
private:
	Point P;
	CFigure* RandomFigure;
	string RandomFigureType;
	int CorrectPicks;
	int Counter;							// Counter for total picks made
	int RandomFigureNumber;					// Integer to store how many instances for the random figure to be picked
public:
	PickByShapeAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	void StartingMessage();					// Prints the starting message
	void GetClickedAction(bool&, bool&);	// Gets the user action
	void FinalMsg(bool&);
};
#endif