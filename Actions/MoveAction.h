#pragma once
#include "Action.h"
class MoveAction :
    public Action
{
private:
    Point P;
public:
    MoveAction(ApplicationManager* pApp);
    void ReadActionParameters();
    void Execute();
};

