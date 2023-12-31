#ifndef CHANGE_BORDER_WIDTH_ACTION_H
#define CHANGE_BORDER_WIDTH_ACTION_H

#include "UndoableAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"

class ChangeBorderWidthAction : public UndoableAction
{
	int OldWidth;
	int NewWidth;
	CFigure *Figure;
	Output *pOut;

public:
	ChangeBorderWidthAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();

	virtual void PlayRecord();

	virtual void Undo();
	virtual void Redo();
};

#endif