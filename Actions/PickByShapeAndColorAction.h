#ifndef PICK_BY_SHAPE_AND_COLOR_ACTION_H
#define PICK_BY_SHAPE_AND_COLOR_ACTION_H
#include "Action.h"
#include "..\ApplicationManager.h"

class PickByShapeAndColorAction : public Action
{
private:
	Point P;
	CFigure *RandomFigure;
	int CorrectPicks;
	int Counter;			  // Counter for total picks made
	int RandomColorFigNumber; // Integer that stores how many instances for the random properties to be picked
public:
	PickByShapeAndColorAction(ApplicationManager *);
	virtual void ReadActionParameters();
	virtual bool Execute();
	void StartingMessage();				   // To print the starting message
	void GetClickedAction(bool &, bool &); // Gets the user action
	void FinalMsg(bool &);
	virtual bool ShouldRecord() const;
};
#endif