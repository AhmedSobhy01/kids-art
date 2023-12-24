#ifndef PICK_BY_SHAPE_AND_COLOR_ACTION_H
#define PICK_BY_SHAPE_AND_COLOR_ACTION_H
#include "Action.h"
#include "..\ApplicationManager.h"

#include "PlayMode.h"
class PickByShapeAndColorAction: public PlayMode
{
public:
	PickByShapeAndColorAction(ApplicationManager*);
	virtual void StartingMessage();
	virtual bool Execute();
};
#endif
