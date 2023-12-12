#ifndef ADD_SQUARE_ACTION_H
#define ADD_SQUARE_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"

class AddSquareAction : public UndoableFigureAction
{
private:
	Point center;
	GfxInfo SquareGfxInfo;
public:
	AddSquareAction(ApplicationManager* pApp);
	bool Validate();

	virtual void ReadActionParameters();
	virtual bool Execute();

	void PlayActionSound() const;
};

#endif