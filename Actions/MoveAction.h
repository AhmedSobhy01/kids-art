#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "UndoableAction.h"
#include "../Figures/CFigure.h"

class MoveAction: public UndoableAction
{
    Point NewCenter;
    Point OldCenter;
    CFigure* Figure;

public:
    MoveAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual bool Execute();

    virtual void Undo();
    virtual void Redo();
    virtual void PlayRecord();

    ~MoveAction();
};

#endif