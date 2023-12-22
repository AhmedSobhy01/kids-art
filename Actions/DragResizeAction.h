#ifndef DRAGRESIZEACTION_H
#define DRAGRESIZEACTION_H
#include "Action.h"
#include "../Figures/CFigure.h"
class DragResizeAction :
    public Action
{
    Point NewCorner;
    Point OldCorner;
    int PointIndex;
    CFigure* Figure;
public:
    DragResizeAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual bool Execute();
    virtual void PlayRecord();

    virtual void Undo();
    virtual void Redo();

    ~DragResizeAction();

};

#endif
