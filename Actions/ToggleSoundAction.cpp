#include "ToggleSoundAction.h"

ToggleSoundAction::ToggleSoundAction(ApplicationManager* pApp): Action(pApp)
{
}

void ToggleSoundAction::ReadActionParameters()
{}

bool ToggleSoundAction::Execute() {
	Output* pOut = pManager->GetOutput();

	pManager->SetPlayActionSoundState(!pManager->ShouldPlayActionSound());

	if (pManager->ShouldPlayActionSound())
		pOut->PrintMessage("Action sound turned on.");
	else
		pOut->PrintMessage("Action sound turned off.");

	return true;
}

bool ToggleSoundAction::ShouldRecord() const {
	return false;
}