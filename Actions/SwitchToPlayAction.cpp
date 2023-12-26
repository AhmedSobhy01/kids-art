#include "SwitchToPlayAction.h"
#include "..\GUI\Output.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager *pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void SwitchToPlayAction::ReadActionParameters()
{
}

bool SwitchToPlayAction::Execute()
{
	Output *pOut = pManager->GetOutput();
	pOut->CreatePlayToolBar();
	pOut->ClearStatusBar();

	return true;
}