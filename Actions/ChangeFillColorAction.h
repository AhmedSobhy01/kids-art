#ifndef CHANGE_FILL_COLOR_ACTION_H
#define CHANGE_FILL_COLOR_ACTION_H

#include "UndoableAction.h"

class ChangeFillColorAction : public UndoableAction
{
	color OldColor;
	color NewColor;
	CFigure *Figure;

public:
	ChangeFillColorAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();

	virtual void PlayRecord();

	virtual void Undo();
	virtual void Redo();
};

#endif
