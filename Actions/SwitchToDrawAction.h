#ifndef SWITCH_TO_DRAW_H
#define SWITCH_TO_DRAW_H

#include "Action.h"

class SwitchToDrawAction: public Action {
public:
	SwitchToDrawAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual bool Execute();

	virtual bool ShouldRecord() const;
};

#endif