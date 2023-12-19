#ifndef DRAGMOVEACTION_H
#define DRAGMOVEACTION_H

#include "UndoableAction.h"
#include "../Figures/CFigure.h"

class DragMoveAction : public UndoableAction
{
    Point NewCenter;
    Point OldCenter;
    CFigure* Figure;

public:
    DragMoveAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual bool Execute();


    virtual void Undo();
    virtual void Redo();
    virtual void PlayRecord();

    ~DragMoveAction();
};


#endif