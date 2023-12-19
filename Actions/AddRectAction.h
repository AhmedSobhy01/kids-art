#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"

//Add Rectangle Action class
class AddRectAction: public UndoableFigureAction
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
public:
	AddRectAction(ApplicationManager *pApp);
	bool Validate();
	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual bool Execute();
	virtual void PlayRecord();
};

#endif