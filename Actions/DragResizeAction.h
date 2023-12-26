#ifndef DRAG_RESIZE_ACTION_H
#define DRAG_RESIZE_ACTION_H

#include "UndoableAction.h"
#include "../Figures/CFigure.h"

class DragResizeAction : public UndoableAction
{
    Point NewCorner;
    Point OldCorner;
    int PointIndex;
    CFigure *Figure;

public:
    DragResizeAction(ApplicationManager *);

    virtual void ReadActionParameters();
    virtual bool Execute();

    virtual void PlayRecord();

    virtual void Undo();
    virtual void Redo();

    virtual ~DragResizeAction();
};

#endif
