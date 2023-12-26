#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager *pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void SaveAction::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Saving File: Enter File Name or Press esc to Cancel ");
	FileName = pIn->GetString(pOut);
}

bool SaveAction::Execute()
{
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	ofstream FileOutputStream;
	FileOutputStream.open("Saved Graphs/" + FileName);
	if (FileOutputStream.is_open())
	{
		pOut->PrintMessage("Created Save File Successfully");
		pManager->SaveAll(FileOutputStream);
		FileOutputStream.close();
		return 1;
	}
	pOut->PrintMessage("Did not Create a File");
	return 0;
}