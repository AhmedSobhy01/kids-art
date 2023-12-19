#include "PlayRecordingAction.h"
#include "../GUI/Output.h"
#include "../Actions/ClearAllAction.h"
#include "../Actions/UndoableAction.h"


PlayRecordingAction::PlayRecordingAction(ApplicationManager* pApp) : Action(pApp) {}

void PlayRecordingAction::ReadActionParameters()
{
}

bool PlayRecordingAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	List<Action> RecordedActions = pManager->GetRecordedActionsList();

	//std::cout << *(pManager->GetRecordedActionsList()) << " " << *RecordedActions;

	if (RecordedActions.empty())
	{
		pOut->PrintMessage("No Recording to be Played");
		return false;
	}
	else
	{
		Action* clr = new ClearAllAction(pManager);
		clr->Execute();
		pOut->PrintMessage("Playing Recording");

		for (int i = 0; i < RecordedActions.size(); i++)
		{
			RecordedActions[i]->PlayRecord();
			pOut->PrintMessage("Replayed");
		}
		return true;
	}
}
