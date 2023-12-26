#ifndef PLAY_RECORDING_ACTION_H
#define PLAY_RECORDING_ACTION_H

#include "Action.h"
#include "../ApplicationManager.h"

class PlayRecordingAction : public Action
{
public:
	PlayRecordingAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();
};

#endif