#ifndef PLAY_MODE_H
#define PLAY_MODE_H

#include "..\ApplicationManager.h"
#include "Action.h"

class PlayMode: public Action {
protected:
	CFigure* RandomFigure;
	ActionType Mode;
	int Target;			// Target number of choices
private:
	CFigure* ClickedFigure;
	Point P;
	bool CorrectCondition;
	int Counter;		// Counts how many picks are made
	int CorrectPicks;	// Counts how many correct picks are made
public:
	PlayMode(ApplicationManager*);
	bool Execute();
	void ReadActionParameters();
	virtual void StartingMessage() =0;
	void FinalMessage(bool&);
	void GetClickedAction(bool&, bool&);
	void SetCorrectCondition();
};
#endif