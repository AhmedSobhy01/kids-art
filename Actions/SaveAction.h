#ifndef SAVE_ACTION_H
#define SAVE_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

class SaveAction : public Action
{
	std::string FileName;

public:
	SaveAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();
};

#endif
