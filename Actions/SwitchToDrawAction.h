#ifndef SWITCH_TO_DRAW_H
#define SWITCH_TO_DRAW_H

#include "Action.h"

class SwitchToDrawAction : public Action
{
public:
	SwitchToDrawAction(ApplicationManager *);

	virtual void ReadActionParameters();

	virtual bool Execute();
};

#endif