#ifndef LOAD_ACTION_H
#define LOAD_ACTION_H

#include "Action.h"
#include "..\ApplicationManager.h"

#include <iostream>
using namespace std;

class LoadAction : public Action
{
private:
	string FileName;
public:
	LoadAction(ApplicationManager*);
	void ReadActionParameters();
	bool Execute();
};

#endif
