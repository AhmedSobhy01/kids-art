#ifndef DRAGMOVEACTION_H
#define DRAGMOVEACTION_H

#include "Action.h"
#include "../Figures/CFigure.h"

class DragMoveAction : public Action
{
    Point NewCenter;
    Point OldCenter;
    CFigure* Figure;

public:
    DragMoveAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual bool Execute();

};


#endif