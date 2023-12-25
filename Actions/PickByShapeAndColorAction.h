#ifndef PICK_BY_SHAPE_AND_COLOR_ACTION_H
#define PICK_BY_SHAPE_AND_COLOR_ACTION_H
#include "PlayMode.h"

class PickByShapeAndColorAction: public PlayMode
{
public:
	PickByShapeAndColorAction(ApplicationManager*);
	void StartingMessage();
	bool Execute();
};
#endif
