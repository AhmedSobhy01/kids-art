#ifndef PLAY_MODE_H
#define PLAY_MODE_H

#include "..\ApplicationManager.h"
#include "Action.h"
class PlayMode: public Action {
protected:
	Point P;
	CFigure* RandomFigure;	/// used in derived
	CFigure* ClickedFigure;
	ActionType Mode;		/// used in derived
	int CorrectPicks;
	int Counter;
	int Target;				/// used in derived
	bool CorrectCondition;
public:
	PlayMode(ApplicationManager*);
	bool Execute();
	void ReadActionParameters();
	virtual void StartingMessage() = 0;
	void FinalMessage(bool&);
	void GetClickedAction(bool&, bool&);
	void SetCorrectCondition();

};
#endif