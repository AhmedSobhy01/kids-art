#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Action.h"
class SelectAction: public Action
{
private:
    Point P;
public:
    SelectAction(ApplicationManager* pApp);

    void ReadActionParameters();
    void Execute();
};

#endif