#ifndef _SWITCH_TO_PLAY_ACTION_H_
#define _SWITCH_TO_PLAY_ACTION_H_
#include "Action.h"

class SwitchToPlayAction: public Action {
public:
	SwitchToPlayAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
};
#endif