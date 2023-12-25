#include "RedoAction.h"
#include "UndoableAction.h"
#include "../Containers/UndoableActionStack.h"

RedoAction::RedoAction(ApplicationManager* pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void RedoAction::ReadActionParameters()
{
}

bool RedoAction::Execute()
{
	UndoableActionStack& RedoableActions = pManager->GetRedoableActionsStack();

	if (RedoableActions.Empty()) {
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		int x, y;

		pOut->PrintMessage("Nothing to redo ... click anywhere to continue");
		pIn->GetPointClicked(x, y);
		pOut->PrintMessage("");

		return false;
	}

	UndoableActionStack& UndoableActions = pManager->GetUndoableActionsStack();

	UndoableAction* pAct = RedoableActions.Pop();

	pAct->Redo();
	UndoableActions.Push(pAct);

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