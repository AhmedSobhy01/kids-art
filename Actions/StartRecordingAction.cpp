#include "StartRecordingAction.h"
#include "../GUI/Output.h"

StartRecordingAction::StartRecordingAction(ApplicationManager* pApp): Action(pApp)
{
	RecordEnabled = false;
}

void StartRecordingAction::ReadActionParameters()
{
}

bool StartRecordingAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (pManager->IsCurrentlyRecording()) {
		pOut->PrintMessage("Already recording...");

		return false;
	}

	if (pManager->CanRecord()) {
		pManager->SetRecordingState(true);

		pOut->PrintMessage("Recording started...");

		return true;
	}

	pOut->PrintMessage("Can't start recording right now.");

	return false;
}