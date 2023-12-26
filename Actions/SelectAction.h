#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Action.h"

class SelectAction : public Action
{
    Point P;

public:
    SelectAction(ApplicationManager *);

    virtual void ReadActionParameters();
    virtual bool Execute();
};

#endif