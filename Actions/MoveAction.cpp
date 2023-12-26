#include "MoveAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

MoveAction::MoveAction(ApplicationManager *pApp) : UndoableAction(pApp) {}

void MoveAction::ReadActionParameters()
{
	Figure = pManager->GetSelected();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	//Checks if no figure is selected
	if (Figure == NULL)
	{
		int x, y;
		pOut->PrintMessage("Error:Select a shape before moving. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->PrintMessage("Move: Click on a new point to move.");
	pIn->GetPointClicked(NewCenter.x, NewCenter.y);
	pOut->ClearStatusBar();
}

bool MoveAction::Execute()
{
	ReadActionParameters();

	if (Figure == NULL)
		return false;

	Figure->IncrementReference();
	OldCenter = Figure->GetCenter();	//Save old center for undo and redo
	Figure->SetCenter(NewCenter);		//Sets the new center
	return true;
}

void MoveAction::PlayRecord()
{
	if (Figure != NULL)
		Figure->SetCenter(NewCenter);
}

void MoveAction::Undo()
{
	if (Figure != NULL)
		Figure->SetCenter(OldCenter);
}

void MoveAction::Redo()
{
	if (Figure != NULL)
		Figure->SetCenter(NewCenter);
}

MoveAction::~MoveAction()
{
	if (Figure != NULL)
	{
		Figure->DecrementReference();

		if (Figure->CanBeDeleted())
			delete Figure;

		Figure = NULL;
	}
}