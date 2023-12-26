#include "SwitchToDrawAction.h"

#include "..\GUI\Output.h"

SwitchToDrawAction::SwitchToDrawAction(ApplicationManager *pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void SwitchToDrawAction::ReadActionParameters()
{
}

bool SwitchToDrawAction::Execute()
{
	Output *pOut = pManager->GetOutput();
	pOut->CreateDrawToolBar();
	pOut->ClearStatusBar();

	return true;
}