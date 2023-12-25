#include "PlayRecordingAction.h"
#include "../GUI/Output.h"
#include "../Actions/ClearAllAction.h"
#include "../Actions/UndoableAction.h"
#include "../CMUgraphicsLib/auxil.h"

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

		pOut->PrintMessage("Playing Recording");

		for (int i = 0; i < RecordedActionsList.Size(); i++)
		{
			RecordedActionsList[i]->PlayRecord();
			pManager->UpdateInterface();
			Pause(1000);
		}
		pOut->PrintMessage("Recording Finished");
		pManager->SetPlayingRecordingState(false);
		return true;
	}
}