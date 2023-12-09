#include "UndoableFigureAction.h"

UndoableFigureAction::UndoableFigureAction(ApplicationManager* pApp) : UndoableAction(pApp)
{
	figure = NULL;
}

void UndoableFigureAction::Undo()
{
	pManager->RemoveFigure(figure);
}

void UndoableFigureAction::Redo()
{
	pManager->AddFigure(figure);
}

UndoableFigureAction::~UndoableFigureAction()
{
	if (figure)
		delete figure;
}