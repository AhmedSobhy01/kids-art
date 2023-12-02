#include "SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectAction::SelectAction(ApplicationManager* pApp) :Action(pApp) {

}

void SelectAction::ReadActionParameters() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Select: Click on a shape to select.");
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}

void SelectAction::Execute() {
	ReadActionParameters();
	CFigure* F = pManager->GetFigure(P.x, P.y);
	CFigure* S = pManager->GetSelected();
	if (F != NULL) {
		F->SetSelected(S != F);
		pManager->GetSelected() = F != S ? F : NULL;
	}

}