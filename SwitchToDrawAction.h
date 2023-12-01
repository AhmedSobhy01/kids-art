#ifndef _SWITCH_TO_DRAW_H_
#define _SWITCH_TO_DRAW_H_

#include "Actions/Action.h"
#include "GUI/UI_Info.h"

class SwitchToDrawAction: public Action {
private:
	ActionType actType;
public:
	SwitchToDrawAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
};
#endif