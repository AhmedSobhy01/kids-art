#ifndef UNDOABLE_FIGURE_ACTION_H
#define UNDOABLE_FIGURE_ACTION_H

#include "UndoableAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

class UndoableFigureAction : public UndoableAction // Base class for all undoable actions that are related to a figure since they all add & remove a figure from the list of figures
{
protected:
	CFigure *Figure;

public:
	UndoableFigureAction(ApplicationManager *);

	virtual void Undo();
	virtual void Redo();

	virtual ~UndoableFigureAction();
};

#endif
