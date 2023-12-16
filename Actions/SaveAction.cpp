#include "SaveAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp) {}

void SaveAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Saving File: Enter File Name");
	fName = pIn->GetString(pOut);
}

bool SaveAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	ofstream fout;
	fout.open(fName);
	if (fout.is_open())
	{
		pOut->PrintMessage("Created Save File Successfully");
		pManager->SaveAll(fName);
		fout.close();
		return 1;
	}
	return 0;
}
