#include "UndoAction.h"
#include "UndoableAction.h"
#include "../Containers/UndoableActionStack.h"

UndoAction::UndoAction(ApplicationManager* pApp): Action(pApp)
{
}

void UndoAction::ReadActionParameters()
{
}

bool UndoAction::Execute()
{
	UndoableActionStack& undoableActions = pManager->GetUndoableActionsStack();

	if (undoableActions.empty()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		int x, y;

		pOut->PrintMessage("Nothing to undo ... click anywhere to continue");
		pIn->GetPointClicked(x, y);
		pOut->PrintMessage("");

		return false;
	}

	UndoableActionStack& redoableActions = pManager->GetRedoableActionsStack();

	undoableActions.top()->Undo();
	redoableActions.push(undoableActions.pop());

	return true;
}
