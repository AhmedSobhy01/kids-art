#ifndef PICK_BY_SHAPE_AND_COLOR_ACTION_H
#define PICK_BY_SHAPE_AND_COLOR_ACTION_H_
#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\UI_Info.h"
#include "..\Figures\CFigure.h"

class PickByShapeAndColorAction :public Action {
private:
	Point P;
	color RandomColor;
	CFigure* RandomFigure;
	string RandomFigureName;	// To store the random figure name as a string
	string RandomColorName;		// To store the random figure color as a string
	int CorrectPicks;
	int Counter;				// Counter for total picks made
	int FiguresNumber;			// Integer that stores number of all figures
	int RandomColorFigNumber;	// Integer that stores how many instances for the random properties to be picked
public:
	PickByShapeAndColorAction::PickByShapeAndColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual void Execute();
	void PrintMessage();		// To print the starting message
	void GetFigureStats(CFigure*); // Converts the enum values of the figures properties and assigns them into the string members
};
#endif