#include "GUI\Output.h"
#include "ApplicationManager.h"

#include "SwitchToDrawAction.h"

SwitchToDrawAction::SwitchToDrawAction(ApplicationManager* pApp) :Action(pApp) 
{}

void SwitchToDrawAction::ReadActionParameters() 
{ }

void SwitchToDrawAction::Execute() {
	Output* pOut = pManager->GetOutput();
	pOut->CreateDrawToolBar();
}