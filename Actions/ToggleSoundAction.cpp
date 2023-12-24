#include "ToggleSoundAction.h"

ToggleSoundAction::ToggleSoundAction(ApplicationManager* pApp): Action(pApp)
{
}

void ToggleSoundAction::ReadActionParameters()
{}

bool ToggleSoundAction::Execute() {
	Output* pOut = pManager->GetOutput();

	pManager->SetPlayActionSoundState(!pManager->ShouldPlayActionSound());

	pOut->PrintMessage(pManager->ShouldPlayActionSound() ? "Action sound turned on." : "Action sound turned off.");

	return true;
}

bool ToggleSoundAction::ShouldRecord() const {
	return false;
}