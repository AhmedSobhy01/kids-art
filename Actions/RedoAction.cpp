#include "RedoAction.h"
#include "UndoableAction.h"
#include "../Containers/UndoableActionStack.h"

RedoAction::RedoAction(ApplicationManager* pApp) : Action(pApp)
{
}

void RedoAction::ReadActionParameters()
{
}

void RedoAction::Execute()
{
	UndoableActionStack& redoableActions = pManager->GetRedoableActionsStack();

	if (redoableActions.empty()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		int x, y;

		pOut->PrintMessage("Nothing to redo ... click anywhere to continue");
		pIn->GetPointClicked(x, y);
		pOut->PrintMessage("");

		return;
	}

	UndoableActionStack& undoableActions = pManager->GetUndoableActionsStack();

	redoableActions.top()->Redo();
	undoableActions.push(redoableActions.pop());
}
