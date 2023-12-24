#include "PlayRecordingAction.h"
#include "../GUI/Output.h"
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
		UI.PenWidth = 3;
		pOut->PrintMessage("Playing Recording");

		for (int i = 0; i < RecordedActionsList.size(); i++)
		{
				if (!dynamic_cast<UndoAction*>(RecordedActionsList[i]) && !dynamic_cast<RedoAction*>(RecordedActionsList[i]))
					pManager->ClearRedoableActionsStack();

				bool b = pManager->AddActionToUndoables(RecordedActionsList[i], 1);

			pManager->UpdateInterface();
			Pause(1000);
			RecordedActionsList[i]->PlayRecord();
		}
		Pause(1000);
		pOut->PrintMessage("Recording Finished");
		pManager->SetPlayingRecordingState(false);
		return true;
	}
}