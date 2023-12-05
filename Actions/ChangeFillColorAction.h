#ifndef CHANGE_FILL_COLOR_ACTION_H
#define CHANGE_FILL_COLOR_ACTION_H

#include "Action.h"

class ChangeFillColorAction: public Action
{
public:
	ChangeFillColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
};

#endif
