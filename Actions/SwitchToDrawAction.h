#ifndef _SWITCH_TO_DRAW_H_
#define _SWITCH_TO_DRAW_H_
#include "Action.h"

class SwitchToDrawAction: public Action {
public:
	SwitchToDrawAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
};
#endif