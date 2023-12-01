#pragma once
#include "Action.h"
class AddHexagonAction : public Action
{
private:
	Point center;
	GfxInfo HexagonGfxInfo;
public:
	AddHexagonAction(ApplicationManager* pApp);

	void ReadActionParameters();

	void Execute();
};

