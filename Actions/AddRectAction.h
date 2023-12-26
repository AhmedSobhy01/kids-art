#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"
#include "..\ApplicationManager.h"

class AddRectAction : public UndoableFigureAction
{
	Point P1, P2;
	GfxInfo RectGfxInfo;

public:
	AddRectAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual void PlayRecord();

	virtual bool Execute();
};

#endif