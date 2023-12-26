#ifndef START_RECORDING_ACTION_H
#define START_RECORDING_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

class StartRecordingAction : public Action
{
public:
	StartRecordingAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();
};

#endif