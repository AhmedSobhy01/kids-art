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
	if (figure && !pManager->FigListContains(figure)) // Checking if figure object exists in the figlist of app manager or not (if not then the figure will never be used anywhere again) (this will happen when deleting action object while referenced in redo stack)
		delete figure;
}