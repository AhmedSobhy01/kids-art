#ifndef DELETE_ACTION_H
#define DELETE_ACTION_H

#include "UndoableAction.h"
#include "..\Figures\CFigure.h"

class DeleteAction : public UndoableAction
{
	CFigure *Figure;
	int RemovedFromIndex;

public:
	DeleteAction(ApplicationManager *);
	virtual void ReadActionParameters();
	virtual bool Execute();
	virtual void PlayRecord();

	virtual void Undo();
	virtual void Redo();

	~DeleteAction();
};

#endif
