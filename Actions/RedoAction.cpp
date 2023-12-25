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
	UndoableActions.push(pAct);

	return true;
}

bool RedoAction::ShouldRecord() const
{
	return false;
}