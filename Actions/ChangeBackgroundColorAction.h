#ifndef CHANGE_BACKGROUND_COLOR_ACTION_H
#define CHANGE_BACKGROUND_COLOR_ACTION_H

#include "Action.h"
#include "../ApplicationManager.h"

class ChangeBackgroundColorAction : public Action
{
public:
	ChangeBackgroundColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
};

#endif 