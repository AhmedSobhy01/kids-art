#include "UndoAction.h"
#include "UndoableAction.h"
#include "../Containers/UndoableActionStack.h"

UndoAction::UndoAction(ApplicationManager *pApp) : Action(pApp)
{
}

void UndoAction::ReadActionParameters()
{
}

bool UndoAction::Execute()
{
	UndoableActionStack &UndoableActions = pManager->GetUndoableActionsStack();

	if (UndoableActions.Empty()) // Nothing to undo
	{
		Output *pOut = pManager->GetOutput();
		Input *pIn = pManager->GetInput();

		pOut->PrintMessage("Nothing to undo.");

		return false;
	}

	UndoableActionStack &RedoableActions = pManager->GetRedoableActionsStack();

	UndoableAction *pAct = UndoableActions.Pop();

	pAct->Undo();

	RedoableActions.Push(pAct);

	return true;
}

void UndoAction::PlayRecord()
{
	UndoableActionStack &UndoableActions = pManager->GetUndoableActionsStack();
	UndoableActionStack &RedoableActions = pManager->GetRedoableActionsStack();

	UndoableAction *pAct = UndoableActions.Pop();

	pAct->Undo();

	RedoableActions.Push(pAct);
}
