#include "SwitchToDrawAction.h"

#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


SwitchToDrawAction::SwitchToDrawAction(ApplicationManager* pApp): Action(pApp) 
{}

void SwitchToDrawAction::ReadActionParameters() 
{}

void SwitchToDrawAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreateDrawToolBar();
}