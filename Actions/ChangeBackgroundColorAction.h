#ifndef CHANGE_BACKGROUND_COLOR_ACTION_H
#define CHANGE_BACKGROUND_COLOR_ACTION_H

#include "UndoableAction.h"
#include "..\ApplicationManager.h"

class ChangeBackgroundColorAction : public UndoableAction
{
	color OldColor;
	color NewColor;

public:
	ChangeBackgroundColorAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();

	virtual void PlayRecord();

	virtual void Undo();
	virtual void Redo();
};

#endif