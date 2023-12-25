#include "SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SelectAction::SelectAction(ApplicationManager* pApp): Action(pApp) {
	RecordEnabled = false;
}

void SelectAction::ReadActionParameters() {
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Select: Click on a shape to select.");
	pIn->GetPointClicked(P.x, P.y);
	pOut->ClearStatusBar();
}

bool SelectAction::Execute() {
	ReadActionParameters();

	CFigure* Figure = pManager->GetFigure(P.x, P.y);
	if (Figure == NULL)
		return false;

	CFigure* S = pManager->GetSelected();
	if (S != NULL) {
		S->SetSelected(false);
		cout << S->IsSelected();
	}

	pManager->SetSelected(NULL);
	if (Figure != S) {
		Figure->SetSelected(true);
		pManager->SetSelected(Figure);
		Figure->PrintInfo(pManager->GetOutput());
	}

	return true;
}