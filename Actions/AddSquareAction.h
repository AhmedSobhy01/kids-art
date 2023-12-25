#ifndef ADD_SQUARE_ACTION_H
#define ADD_SQUARE_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"

class AddSquareAction : public UndoableFigureAction
{
private:
	Point Center;
	GfxInfo SquareGfxInfo;

public:
	AddSquareAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual bool Execute();
	virtual void PlayRecord();
};

#endif