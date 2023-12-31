#ifndef PICK_BY_COLOR_ACTION_H
#define PICK_BY_COLOR_ACTION_H

#include "PlayMode.h"
#include "../ApplicationManager.h"

class PickByColorAction : public PlayMode
{
public:
	PickByColorAction(ApplicationManager *);

	virtual bool Execute();

	void StartingMessage();
};

#endif