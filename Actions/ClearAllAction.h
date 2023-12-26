#ifndef CLEAR_ALL_ACTION_H
#define CLEAR_ALL_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

class ClearAllAction : public Action
{
public:
	ClearAllAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();
};

#endif
