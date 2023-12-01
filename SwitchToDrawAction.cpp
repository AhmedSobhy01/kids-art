#include "GUI\Output.h"
#include "ApplicationManager.h"

#include "SwitchToDrawAction.h"

SwitchToDrawAction::SwitchToDrawAction(ApplicationManager* pApp) :Action(pApp) 
{}

void SwitchToDrawAction::ReadActionParameters() {
	actType = TO_DRAW;
}

void SwitchToDrawAction::Execute() {
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	pOut->CreateDrawToolBar();
}