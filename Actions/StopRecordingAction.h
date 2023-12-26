#ifndef STOP_RECORDING_ACTION_H
#define STOP_RECORDING_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

class StopRecordingAction : public Action
{
public:
	StopRecordingAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();
};

#endif