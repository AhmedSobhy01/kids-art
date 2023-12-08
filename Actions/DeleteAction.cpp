#include "DeleteAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) :Action(pApp) {

}


void DeleteAction::ReadActionParameters() {
	CFigure* F = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (F == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Select a shape before deleting. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	return;
}

bool DeleteAction::Execute() {
	ReadActionParameters();
	CFigure* F = pManager->GetSelected();
	if (F != NULL) {
		pManager->RemoveFigure(F);
		pManager->SetSelected(NULL);
		return true;
	}
	return false;
}