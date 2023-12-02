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
}

void SelectAction::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	CFigure* F = pManager->GetFigure(P.x, P.y);
	if (F != NULL) {
		F->SetSelected(true);
		pOut->ClearStatusBar();
		pManager->GetSelected() = F;
	}
	else {
		int x, y;
		pOut->PrintMessage("Clicked outside objects so none selected. Click anywhere to continue");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();

	}

}