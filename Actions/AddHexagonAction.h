#pragma once
#include "Action.h"
class AddHexagonAction : public Action
{
private:
	Point center;
	GfxInfo HexagonGfxInfo;
public:
	AddHexagonAction(ApplicationManager* pApp);
	bool Validate();
	void ReadActionParameters();

	void Execute();
};

