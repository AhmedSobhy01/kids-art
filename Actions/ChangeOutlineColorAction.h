#ifndef CHANGE_OUTLINE_COLOR_ACTION_H
#define CHANGE_OUTLINE_COLOR_ACTION_H

#include "Action.h"

class ChangeOutlineColorAction : public Action
{
public:
	ChangeOutlineColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif