#include "SwitchToPlayAction.h"
#include "..\GUI\Output.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager* pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void SwitchToPlayAction::ReadActionParameters()
{
}

bool SwitchToPlayAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->CreatePlayToolBar();
	pOut->ClearStatusBar();
	CFigure* SelectedFigure = pManager->GetSelected();
	if (SelectedFigure != NULL)
		SelectedFigure->SetSelected(false);					// Unselects the selected shape

	return true;
}