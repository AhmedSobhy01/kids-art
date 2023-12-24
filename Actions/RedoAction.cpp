#include "RedoAction.h"
#include "UndoableAction.h"
#include "../Containers/UndoableActionStack.h"

RedoAction::RedoAction(ApplicationManager* pApp) : Action(pApp)
{
}

void RedoAction::ReadActionParameters()
{
}

bool RedoAction::Execute()
{
	UndoableActionStack& redoableActions = pManager->GetRedoableActionsStack();

	if (redoableActions.empty()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		int x, y;

		pOut->PrintMessage("Nothing to redo ... click anywhere to continue");
		pIn->GetPointClicked(x, y);
		pOut->PrintMessage("");

		return false;
	}

	UndoableActionStack& undoableActions = pManager->GetUndoableActionsStack();

	UndoableAction* pAct = redoableActions.pop();

	pAct->Redo();
	undoableActions.push(pAct);

	return true;
}

void RedoAction::PlayRecord()
{
	UndoableActionStack& redoableActions = pManager->GetRedoableActionsStack();
	UndoableActionStack& undoableActions = pManager->GetUndoableActionsStack();

	UndoableAction* pAct = redoableActions.pop();

	pAct->Redo();
	undoableActions.push(pAct);
}
