#ifndef UNDO_ACTION_H
#define UNDO_ACTION_H

#include "Action.h"
#include "../ApplicationManager.h"

class UndoAction: public Action
{
public:
	UndoAction(ApplicationManager*);

	virtual void ReadActionParameters();

	virtual bool Execute();

	virtual bool ShouldRecord() const;
};

#endif