#ifndef PLAY_MODE_H
#define PLAY_MODE_H

#include "..\ApplicationManager.h"
#include "Action.h"
class PlayMode: public Action {
protected:
	CFigure* RandomFigure;	/// used in derived
	ActionType Mode;		/// used in derived
	int Target;				/// used in derived
private:
	bool CorrectCondition;
	int Counter;
	int CorrectPicks;
	CFigure* ClickedFigure;
	Point P;
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