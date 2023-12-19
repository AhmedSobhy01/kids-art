#ifndef PICK_BY_COLOR_ACTION_H
#define PICK_BY_COLOR_ACTION_H
#include "Action.h"
#include "..\ApplicationManager.h"

class PickByColorAction: public Action {
private:
	Point P;
	color RandomColor;
	CFigure* RandomFigure;
	string RandomColorName;
	int CorrectPicks;
	int Counter;							// Counter for total picks made
	int FiguresNumber;						// Integer to store total number of figures in FigList
	int RandomColorNumber;					// Integer to store how many instances for the random color to be picked
	bool ChangedAction;
	bool EmptyClick;
public:
	PickByColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	void StartingMessage();					// Prints the starting message
	void GetAction();						// Gets the user action
	void FinalMsg();
};
#endif