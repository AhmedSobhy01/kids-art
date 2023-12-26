#ifndef EXIT_ACTION_H
#define EXIT_ACTION_H

#include "Action.h"
#include "../ApplicationManager.h"

class ExitAction : public Action
{
public:
    ExitAction(ApplicationManager *);

    virtual void ReadActionParameters();
    virtual bool Execute();
};

#endif