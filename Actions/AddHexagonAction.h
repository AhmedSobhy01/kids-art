#ifndef ADD_HEXAGON_ACTION_H
#define ADD_HEXAGON_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"

class AddHexagonAction : public UndoableFigureAction
{
private:
	Point center;
	GfxInfo HexagonGfxInfo;
public:
	AddHexagonAction(ApplicationManager* pApp);
	bool Validate();

	virtual void ReadActionParameters();
	virtual bool Execute();
	virtual void PlayRecord();
};

#endif