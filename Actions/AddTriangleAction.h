#ifndef ADD_TRIANGLE_ACTION_H
#define ADD_TRIANGLE_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"

class AddTriangleAction : public UndoableFigureAction
{
private:
	Point P1;
	Point P2;
	Point P3;
	GfxInfo TriangleGfxInfo;

public:
	AddTriangleAction(ApplicationManager *);

	virtual void ReadActionParameters();
	virtual bool Execute();
	virtual void PlayRecord();
};

#endif