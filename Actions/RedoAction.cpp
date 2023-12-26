#include "RedoAction.h"
#include "UndoableAction.h"
#include "../Containers/UndoableActionStack.h"

RedoAction::RedoAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RedoAction::ReadActionParameters()
{
}

bool RedoAction::Execute()
{
	UndoableActionStack &RedoableActions = pManager->GetRedoableActionsStack();

	if (RedoableActions.Empty()) // Nothing to redo
	{
		Output *pOut = pManager->GetOutput();

		pOut->PrintMessage("Nothing to redo.");

		return false;
	}

	UndoableActionStack &UndoableActions = pManager->GetUndoableActionsStack();

	UndoableAction *pAct = RedoableActions.Pop();

	pAct->Redo();
	UndoableActions.Push(pAct);

	return true;
}

void RedoAction::PlayRecord()
{
	UndoableActionStack &RedoableActions = pManager->GetRedoableActionsStack();
	UndoableActionStack &UndoableActions = pManager->GetUndoableActionsStack();

	UndoableAction *pAct = RedoableActions.Pop();

	pAct->Redo();
	UndoableActions.Push(pAct);
}