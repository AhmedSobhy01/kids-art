#ifndef UNDOABLE_ACTION_H
#define UNDOABLE_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

class UndoableAction : public Action
{
public:
	UndoableAction(ApplicationManager *pApp) : Action(pApp) {}

	virtual void Undo() = 0; // Undo the action (code depends on action type)
	virtual void Redo() = 0; // Redo the action (code depends on action type)

	virtual ~UndoableAction(){};
};

#endif