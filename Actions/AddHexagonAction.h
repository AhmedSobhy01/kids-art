#ifndef ADD_HEXAGON_ACTION_H
#define ADD_HEXAGON_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"
#include "..\ApplicationManager.h"

class AddHexagonAction : public UndoableFigureAction
{
	Point Center;
	GfxInfo HexagonGfxInfo;

public:
	AddHexagonAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();

	virtual void PlayRecord();
};

#endif