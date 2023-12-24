#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp) {}

void SaveAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Saving File: Enter File Name or Press esc to Cancel ");
	fName = pIn->GetString(pOut);
}

bool SaveAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	ofstream fout;
	fout.open("Saved Graphs/" + fName);
	if (fout.is_open())
	{
		pOut->PrintMessage("Created Save File Successfully");
		pManager->SaveAll(fout);
		fout.close();
		return 1;
	}	
	pOut->PrintMessage("Did not Create a File");
	return 0;
}

bool SaveAction::ShouldRecord() const
{
	return false;
}