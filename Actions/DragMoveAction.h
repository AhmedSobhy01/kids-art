#ifndef DRAG_MOVE_ACTION_H
#define DRAG_MOVE_ACTION_H

#include "UndoableAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"

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

    virtual ~DragMoveAction();
};

#endif
