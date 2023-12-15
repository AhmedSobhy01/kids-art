#ifndef TOGGLE_SOUND_ACTION_H
#define TOGGLE_SOUND_ACTION_H

#include "Action.h"
#include "../ApplicationManager.h"

class ToggleSoundAction: public Action
{
public:
	ToggleSoundAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual bool Execute();

	virtual bool ShouldRecord() const;
};

#endif