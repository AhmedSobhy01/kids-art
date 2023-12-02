#include "MoveAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

MoveAction::MoveAction(ApplicationManager* pApp):Action(pApp){}

void MoveAction::ReadActionParameters(){
	CFigure* F = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (F == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Select a shape before moving. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->PrintMessage("Move: Click on a new point to move.");
	pIn->GetPointClicked(P.x, P.y);
	if (F->Validate(P)) {
		pOut->ClearStatusBar();
	}
	else {
		int x, y;
		pOut->PrintMessage("Error:Invalid center position. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
}
void MoveAction::Execute(){
	ReadActionParameters();
	CFigure* F = pManager->GetSelected();
	
	if (F != NULL) {
		if (F->Validate(P)) {
			F->SetCenter(P);
		}
		F->SetSelected(false);
		pManager->GetSelected() = NULL;
	}
}