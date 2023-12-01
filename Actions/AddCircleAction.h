#pragma once
#include "Action.h"
class AddCircleAction :
    public Action
{
private:
    Point center;
    Point radius;
    GfxInfo CircleGfxInfo;
public:
    AddCircleAction(ApplicationManager* pApp);
    bool Validate();
    void ReadActionParameters();

    void Execute();
};

