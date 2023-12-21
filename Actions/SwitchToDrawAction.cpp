#include "SwitchToDrawAction.h"

#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToDrawAction::SwitchToDrawAction(ApplicationManager* pApp): Action(pApp) 
{
}

void SwitchToDrawAction::ReadActionParameters() 
{}

bool SwitchToDrawAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreateDrawToolBar();
	pOut->ClearStatusBar();
	return true;
}

bool SwitchToDrawAction::ShouldRecord() const {
	return false;
}