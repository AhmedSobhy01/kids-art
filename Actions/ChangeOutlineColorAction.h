#ifndef CHANGE_OUTLINE_COLOR_ACTION_H
#define CHANGE_OUTLINE_COLOR_ACTION_H

#include "UndoableAction.h"

class ChangeOutlineColorAction: public UndoableAction
{
	color OldColor;
	color NewColor;
	CFigure* Figure;
public:
	ChangeOutlineColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	virtual void PlayRecord();

	virtual void Undo();
	virtual void Redo();
};

#endif