#ifndef CHANGE_BACKGROUND_COLOR_ACTION_H
#define CHANGE_BACKGROUND_COLOR_ACTION_H

#include "Action.h"
#include "../ApplicationManager.h"

class ChangeBackgroundColorAction : public Action
{
private:
	color BkgndCol;
public:
	ChangeBackgroundColorAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual bool Execute();
	virtual void PlayRecord();
};

#endif 