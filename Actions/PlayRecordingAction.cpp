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
	List<Action>& RecordedActionsList = pManager->GetRecordedActionsList();

	if (RecordedActionsList.empty())
	{
		pOut->PrintMessage("No Recording to be Played");
		return false;
	}
	else
	{
		pManager->SetPlayingRecordingState(true);

		Action* pClearAction = new ClearAllAction(pManager);
		pClearAction->Execute();
		delete pClearAction;

		pOut->PrintMessage("Playing Recording");

		for (int i = 0; i < RecordedActionsList.size(); i++)
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