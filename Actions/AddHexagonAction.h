#ifndef ADD_HEXAGON_ACTION_H
#define ADD_HEXAGON_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"

class AddHexagonAction : public UndoableFigureAction
{
private:
	Point Center;
	GfxInfo HexagonGfxInfo;

public:
	AddHexagonAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();
	virtual bool Execute();
	virtual void PlayRecord();
};

#endif