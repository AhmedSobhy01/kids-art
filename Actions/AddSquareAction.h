#ifndef ADD_SQUARE_ACTION_H
#define ADD_SQUARE_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"
#include "..\ApplicationManager.h"

class AddSquareAction : public UndoableFigureAction
{
	Point Center;
	GfxInfo SquareGfxInfo;

public:
	AddSquareAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();

	virtual void PlayRecord();
};

#endif