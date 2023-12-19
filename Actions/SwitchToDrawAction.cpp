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
	pManager->UnhideFigures();
	pManager->UpdateInterface();
	return true;
}

bool SwitchToDrawAction::ShouldRecord() const {
	return false;
}