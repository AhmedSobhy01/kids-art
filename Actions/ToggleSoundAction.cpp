#include "ToggleSoundAction.h"

ToggleSoundAction::ToggleSoundAction(ApplicationManager *pApp) : Action(pApp)
{
	RecordEnabled = false; // Disable recording for this action
}

void ToggleSoundAction::ReadActionParameters()
{
}

bool ToggleSoundAction::Execute()
{
	Output *pOut = pManager->GetOutput();

	pManager->SetPlayActionSoundState(!pManager->ShouldPlayActionSound()); // Toggle the state of the action sound

	pOut->PrintMessage(pManager->ShouldPlayActionSound() ? "Action sound turned on." : "Action sound turned off.");

	return true;
}