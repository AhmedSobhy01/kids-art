#ifndef SAVE_ACTION_H
#define SAVE_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

#include <iostream>
using namespace std;

class SaveAction : public Action
{
private:
	string FileName;
public:
	SaveAction(ApplicationManager*);
	void ReadActionParameters();
	bool Execute();

	virtual bool ShouldRecord() const;
};

#endif
