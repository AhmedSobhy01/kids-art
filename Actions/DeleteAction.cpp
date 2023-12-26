#include "DeleteAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

DeleteAction::DeleteAction(ApplicationManager *pApp) : UndoableAction(pApp), RemovedFromIndex(0)
{
	Figure = NULL;
}

void DeleteAction::ReadActionParameters()
{
	Figure = pManager->GetSelected();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (Figure == NULL)
	{
		int x, y;
		pOut->PrintMessage("Error: Select a shape before deleting. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
	}
	pOut->ClearStatusBar();
	return;
}

bool DeleteAction::Execute()
{
	ReadActionParameters();

	if (Figure == NULL)
		return false;
	Figure->IncrementReference();
	RemovedFromIndex = pManager->RemoveFigure(Figure);
	Figure->SetSelected(false);
	pManager->SetSelected(NULL);
	return true;
}

void DeleteAction::PlayRecord()
{
	if (Figure != NULL)
		RemovedFromIndex = pManager->RemoveFigure(Figure);
}

void DeleteAction::Undo()
{
	if (Figure != NULL)
		pManager->AddFigure(Figure, RemovedFromIndex);
}

void DeleteAction::Redo()
{
	if (Figure != NULL)
		RemovedFromIndex = pManager->RemoveFigure(Figure);
}

DeleteAction::~DeleteAction()
{
	if (Figure != NULL)
	{
		Figure->DecrementReference();

		if (Figure->CanBeDeleted())
			delete Figure;

		Figure = NULL;
	}
}
