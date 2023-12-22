#ifndef PLAY_RECORDING_ACTION_H
#define PLAY_RECORDING_ACTION_H

#include "Action.h"
#include "../ApplicationManager.h"

class PlayRecordingAction: public Action
{
public:
	PlayRecordingAction(ApplicationManager*);
	void ReadActionParameters();
	bool Execute();
};

#endif