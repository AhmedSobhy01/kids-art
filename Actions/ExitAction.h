#ifndef ExitAction_H
#define ExitAction_H

#include "Action.h"
#include "../ApplicationManager.h"
class ExitAction : public Action
{
public:
    ExitAction(ApplicationManager *);
    void ReadActionParameters();
    bool Execute();
};

#endif