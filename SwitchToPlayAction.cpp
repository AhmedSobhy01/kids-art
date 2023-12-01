#include "SwitchToPlayAction.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include "ApplicationManager.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager *pApp): Action(pApp)
{}

void SwitchToPlayAction::ReadActionParameters() {
	Input* pIn = pManager->GetInput();
	actType = TO_PLAY;///actType = TO_PLAY
}

void SwitchToPlayAction::Execute() {
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	pOut->CreatePlayToolBar();
}