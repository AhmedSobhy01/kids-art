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
	{
		pOut->PrintMessage("Action sound turned on.");
		pOut->ToggleSound(0);
	}
	else
	{
		pOut->PrintMessage("Action sound turned off.");
		pOut->ToggleSound(1);
	}
	return true;
}

bool ToggleSoundAction::ShouldRecord() const {
	return false;
}