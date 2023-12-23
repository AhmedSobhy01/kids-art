#ifndef PICK_BY_SHAPE_AND_COLOR_ACTION_H
#define PICK_BY_SHAPE_AND_COLOR_ACTION_H
#include "Action.h"
#include "..\ApplicationManager.h"

class PickByShapeAndColorAction :public Action {
private:
	Point P;
	color RandomFigureColor;
	CFigure* RandomFigure;
	string RandomFigureType;
	string RandomColorName;		// To store the random figure color as a string
	int CorrectPicks;
	int Counter;				// Counter for total picks made
	int FiguresNumber;			// Integer that stores number of all figures
	int RandomColorFigNumber;	// Integer that stores how many instances for the random properties to be picked
	bool ChangedAction;
	bool EmptyClick;
public:
	PickByShapeAndColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	void StartingMessage();		// To print the starting message
	void GetAction();			// Gets the user action
	void FinalMsg();

	virtual bool ShouldRecord() const;
};
#endif