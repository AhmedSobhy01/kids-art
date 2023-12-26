#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "UndoableAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

class MoveAction : public UndoableAction
{
    Point NewCenter;
    Point OldCenter;
    CFigure *Figure;

public:
    MoveAction(ApplicationManager *);

    virtual void ReadActionParameters();
    virtual bool Execute();

    virtual void PlayRecord();

    virtual void Undo();
    virtual void Redo();

    virtual ~MoveAction();
};

#endif