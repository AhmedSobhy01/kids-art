#include "SwitchToPlayAction.h"

#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToPlayAction::SwitchToPlayAction(ApplicationManager *pApp): Action(pApp)
{}

void SwitchToPlayAction::ReadActionParameters() 
{}

void SwitchToPlayAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreatePlayToolBar();
}