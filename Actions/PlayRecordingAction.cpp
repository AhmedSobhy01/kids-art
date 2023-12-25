#include "PlayRecordingAction.h"
#include "../Actions/ClearAllAction.h"
#include "../Actions/UndoableAction.h"
#include "../CMUgraphicsLib/auxil.h"
#include "UndoAction.h"
#include "RedoAction.h"

PlayRecordingAction::PlayRecordingAction(ApplicationManager *pApp) : Action(pApp) {}

void PlayRecordingAction::ReadActionParameters()
{
}

bool PlayRecordingAction::Execute()
{
	Output *pOut = pManager->GetOutput();
	List<Action> &RecordedActionsList = pManager->GetRecordedActionsList();

	if (RecordedActionsList.Empty())
	{
		pOut->PrintMessage("No Recording to be Played");
		return false;
	}
	else
	{
		pManager->SetPlayingRecordingState(true);

		Action *pClearAllAction = new ClearAllAction(pManager);
		pClearAllAction->Execute();
		delete pClearAllAction;

		pManager->UpdateInterface();
		UI.PenWidth = 3;									// Default border width
		pOut->PrintMessage("Playing Recording");

		for (int i = 0; i < RecordedActionsList.Size(); i++)
		{
			if (!dynamic_cast<UndoAction*>(RecordedActionsList[i]) && !dynamic_cast<RedoAction*>(RecordedActionsList[i]))		// handle undo & redo
				pManager->ClearRedoableActionsStack();

			pManager->AddActionToUndoables(RecordedActionsList[i], 1);

			RecordedActionsList[i]->PlayRecord();
			Pause(1000);
			pManager->UpdateInterface();
		}
		Pause(1000);
		pOut->PrintMessage("Recording Finished");
		pManager->SetPlayingRecordingState(false);
		return true;
	}
}