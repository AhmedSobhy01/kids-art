#ifndef PLAY_MODE_H
#define PLAY_MODE_H

#include "..\ApplicationManager.h"
#include "Action.h"
class PlayMode: public Action {
protected:
	Point P;
	CFigure* RandomFigure;
	CFigure* ClickedFigure;
	ActionType Mode;
	int CorrectPicks;
	int Counter;
	int Target;
	bool CorrectCondition;
public:
	PlayMode(ApplicationManager*);
	bool Execute();
	void ReadActionParameters();
	virtual void StartingMessage() = 0;
	void FinalMessage(bool&);
	void GetClickedAction(bool&, bool&);
	bool ShouldRecord() const;
	void SetCorrectCondition();
};
#endif
