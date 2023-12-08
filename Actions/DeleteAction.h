#ifndef DELETEACTION_H
#define DELETEACTION_H
#include "Action.h"
class DeleteAction :public Action
{
	public:
		DeleteAction(ApplicationManager* pApp);
		virtual void ReadActionParameters();
		virtual bool Execute();
};

#endif

