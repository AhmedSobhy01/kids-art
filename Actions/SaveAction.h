#ifndef SAVE_ACTION_H
#define SAVE_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

class SaveAction : public Action
{
private:
	string fName;
public:
	SaveAction(ApplicationManager*);
	void ReadActionParameters();
	bool Execute();

	virtual bool ShouldRecord() const;
};

#endif
