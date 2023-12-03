#include "UndoableFigureAction.h"

UndoableFigureAction::UndoableFigureAction(ApplicationManager* pApp) : UndoableAction(pApp)
{
	figure = nullptr;
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
	delete figure;
}