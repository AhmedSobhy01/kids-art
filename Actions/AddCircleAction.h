#ifndef ADD_CIRCLE_ACTION_H
#define ADD_CIRCLE_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"

class AddCircleAction: public UndoableFigureAction
{
private:
    Point center;
    Point radius;
    GfxInfo CircleGfxInfo;
public:
    AddCircleAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual bool Execute();
    virtual void PlayRecord();
};

#endif