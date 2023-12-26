#ifndef ADD_CIRCLE_ACTION_H
#define ADD_CIRCLE_ACTION_H

#include "Action.h"
#include "UndoableFigureAction.h"
#include "..\ApplicationManager.h"

class AddCircleAction : public UndoableFigureAction
{
    Point Center;
    Point Radius;
    GfxInfo CircleGfxInfo;

public:
    AddCircleAction(ApplicationManager *);

    virtual void ReadActionParameters();
    virtual bool Execute();

    virtual void PlayRecord();
};

#endif