#ifndef PICK_BY_SHAPE_ACTION_H
#define PICK_BY_SHAPE_ACTION_H
#include "Action.h"
#include "..\ApplicationManager.h"
#include <string>
using namespace std;

class PickByShapeAction : public Action {
	Point P;
	CFigure* RandomFigure;
	string RandomFigureType;
	int CorrectPicks;
	int Counter;						// Counter for how many picks made
	int FiguresNumber;					// Integer to store total number of figures in FigList
	int RandomFigureNumber;				// Integer to store how many instances for the random figure to be picked

public:
	PickByShapeAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	void PrintMessage();		// Prints the starting message according to the shape type
};
#endif