#ifndef DRAGMOVEACTION_H
#define DRAGMOVEACTION_H

#include "UndoableAction.h"
#include "../Figures/CFigure.h"

class DragMoveAction : public UndoableAction
{
    Point NewCenter;
    Point OldCenter;
    CFigure *Figure;

public:
    DragMoveAction(ApplicationManager *);
    virtual void ReadActionParameters();
    virtual bool Execute();
    virtual void PlayRecord();

    virtual void Undo();
    virtual void Redo();

    ~DragMoveAction();
};

#endif
