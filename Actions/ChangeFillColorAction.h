#ifndef CHANGE_FILL_COLOR_ACTION_H
#define CHANGE_FILL_COLOR_ACTION_H

#include "Action.h"
#include "ChangeOutlineColorAction.h"

class ChangeFillColorAction : public Action
{
public:
	ChangeFillColorAction(ApplicationManager*);
	void ReadActionParameters();
	void Execute();
};

#endif

