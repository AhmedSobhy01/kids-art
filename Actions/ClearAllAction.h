#ifndef CLEAR_ALL_ACTION_H
#define CLEAR_ALL_ACTION_H
#include "Action.h"
class ClearAllAction: public Action
{
public:
	ClearAllAction(ApplicationManager* );
	void ReadActionParameters();
	virtual bool Execute();
};
#endif

