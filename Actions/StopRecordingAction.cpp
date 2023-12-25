#include "StopRecordingAction.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

StopRecordingAction::StopRecordingAction(ApplicationManager* pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void StopRecordingAction::ReadActionParameters()
{
}

bool StopRecordingAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (pManager->IsCurrentlyRecording()) {
		pManager->SetRecordingState(false);

		pOut->PrintMessage("Recording stopped (operations: " + to_string(pManager->GetRecordedActionsList().size()) + ").");

		return true;
	}

	pOut->PrintMessage("No running recording to stop.");

	return false;
}