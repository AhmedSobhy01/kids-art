#ifndef _SWITCH_TO_PLAY_ACTION_H_
#define _SWITCH_TO_PLAY_ACTION_H_


#include "Actions/Action.h"
#include "GUI/UI_Info.h"

class SwitchToPlayAction: public Action {
private:
	ActionType actType;
public:
	SwitchToPlayAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
};
#endif