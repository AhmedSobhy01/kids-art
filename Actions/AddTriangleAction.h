#pragma once
#include "Action.h"
class AddTriangleAction :
	public Action
{
private:
	Point P1;
	Point P2;
	Point P3;
	GfxInfo TriangleGfxInfo;
public:
	AddTriangleAction(ApplicationManager* pApp);

	void ReadActionParameters();

	void Execute();
};

