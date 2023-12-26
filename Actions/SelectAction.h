#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"

class SelectAction : public Action
{
    Point P;
    CFigure* Figure;

public:
    SelectAction(ApplicationManager *);

    virtual void ReadActionParameters();
    virtual bool Execute();
    virtual void PlayRecord();
};

#endif