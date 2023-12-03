#ifndef UNDOABLE_FIGURE_ACTION_H
#define UNDOABLE_FIGURE_ACTION_H

#include "UndoableAction.h"
#include "../Figures/CFigure.h"
#include "../ApplicationManager.h"

class UndoableFigureAction : public UndoableAction
{
protected:
	CFigure* figure;

public:
	UndoableFigureAction(ApplicationManager* pApp);

	virtual void Undo();
	virtual void Redo();

	~UndoableFigureAction();
};

#endif
