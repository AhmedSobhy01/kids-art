#include "UndoableFigureAction.h"

UndoableFigureAction::UndoableFigureAction(ApplicationManager *pApp) : UndoableAction(pApp)
{
	Figure = NULL; // Initialize figure pointer
}

void UndoableFigureAction::Undo()
{
	pManager->RemoveFigure(Figure); // Remove figure from list of figures
}

void UndoableFigureAction::Redo()
{
	pManager->AddFigure(Figure); // Add figure to list of figures
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