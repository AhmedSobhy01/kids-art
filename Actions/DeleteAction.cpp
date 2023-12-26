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
	Figure->IncrementReference(); // Increment the reference count of the figure

	RemovedFromIndex = pManager->RemoveFigure(Figure); // Remove the figure from the list of figures

	Figure->SetSelected(false);	 // Unselect the deleted figure
	pManager->SetSelected(NULL); // Unselect from the application manager

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
