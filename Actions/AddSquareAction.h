#pragma once
#include "Action.h"
class AddSquareAction :
	public Action
{
private:
	Point center;
	GfxInfo SquareGfxInfo;
public:
	AddSquareAction(ApplicationManager* pApp);

	void ReadActionParameters();

	void Execute();
};

