#ifndef REDO_ACTION_H
#define REDO_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

class RedoAction : public Action
{
public:
	RedoAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();

	virtual void PlayRecord();
};

#endif