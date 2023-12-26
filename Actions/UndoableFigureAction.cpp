#include "UndoableFigureAction.h"

UndoableFigureAction::UndoableFigureAction(ApplicationManager *pApp) : UndoableAction(pApp)
{
	Figure = NULL; // Initialize figure pointer
}

void UndoableFigureAction::Undo()
{
	pManager->RemoveFigure(Figure); // Remove figure from list of figures

	if (Figure->IsSelected())
		pManager->GetOutput()->ClearStatusBar();
}

void UndoableFigureAction::Redo()
{
	pManager->AddFigure(Figure); // Add figure to list of figures

	if (Figure->IsSelected())
		Figure->PrintInfo(pManager->GetOutput());
}

UndoableFigureAction::~UndoableFigureAction()
{
	if (Figure != NULL)
	{
		Figure->DecrementReference(); // Decrement reference count

		if (Figure->CanBeDeleted()) // If reference count reaches 0, delete figure
			delete Figure;

		Figure = NULL;
	}
}