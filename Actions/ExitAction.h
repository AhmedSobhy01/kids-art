#ifndef ExitAction_H
#define ExitAction_H

#include "Action.h"
#include "../ApplicationManager.h"
#include "ClearAllAction.h"
class ExitAction :
    public Action
{
    ClearAllAction* clearAll;
public:
    ExitAction(ApplicationManager* pApp);
    void ReadActionParameters();
    bool Execute();
};

#endif