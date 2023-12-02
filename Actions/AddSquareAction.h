#pragma once
#include "Action.h"
class AddSquareAction : public Action
{
private:
	Point center;
	GfxInfo SquareGfxInfo;
public:
	AddSquareAction(ApplicationManager* pApp);
	bool Validate();
	void ReadActionParameters();

	void Execute();
};

