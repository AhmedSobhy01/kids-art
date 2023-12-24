#ifndef PICK_BY_COLOR_ACTION_H
#define PICK_BY_COLOR_ACTION_H
#include "PlayMode.h"
class PickByColorAction : public PlayMode
{
public:
	PickByColorAction(ApplicationManager*);
	virtual void StartingMessage();
	virtual bool Execute();
};
#endif