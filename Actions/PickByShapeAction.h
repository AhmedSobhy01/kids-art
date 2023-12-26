#ifndef PICK_BY_SHAPE_ACTION_H
#define PICK_BY_SHAPE_ACTION_H

#include "PlayMode.h"

class PickByShapeAction : public PlayMode
{
public:
	PickByShapeAction(ApplicationManager *);

	virtual bool Execute();

	void StartingMessage();
};

#endif