#include "UndoableFigureAction.h"

UndoableFigureAction::UndoableFigureAction(ApplicationManager* pApp) : UndoableAction(pApp)
{
	Figure = NULL;
}

void UndoableFigureAction::Undo()
{
	pManager->RemoveFigure(Figure);
}

void UndoableFigureAction::Redo()
{
	pManager->AddFigure(Figure);
}

UndoableFigureAction::~UndoableFigureAction()
{
	if (Figure != NULL) {
		if (Figure->CanBeDeleted())
			delete Figure;

		Figure->DecrementReference();
		Figure = NULL;
	}
}