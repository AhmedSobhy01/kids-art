#include "SwitchToPlayAction.h"

#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToPlayAction::SwitchToPlayAction(ApplicationManager *pApp): Action(pApp)
{
}

void SwitchToPlayAction::ReadActionParameters() 
{}

bool SwitchToPlayAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreatePlayToolBar();

	return true;
}

bool SwitchToPlayAction::ShouldRecord() const {
	return false;
}