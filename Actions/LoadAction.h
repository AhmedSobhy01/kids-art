#ifndef LOAD_ACTION_H
#define LOAD_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

class LoadAction : public Action
{
private:
	string FileName;
public:
	LoadAction(ApplicationManager*);
	void ReadActionParameters();
	bool Execute();

	virtual bool ShouldRecord() const;
};

#endif
