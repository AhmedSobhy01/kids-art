#include "DragMoveAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

DragMoveAction::DragMoveAction(ApplicationManager* pApp) :Action(pApp) {

}

void DragMoveAction::ReadActionParameters() {

}

bool DragMoveAction::Execute() {

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	CFigure* SelectedFig = pManager->GetSelected();
	if (SelectedFig == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Select a shape before moving. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return false;
	}
	pOut->PrintMessage("DragMove: Drag the selected shape to move");

	bool buttonDown = false;
	while (!buttonDown || !SelectedFig->CheckSelected(NewCenter.x, NewCenter.y)) {
		buttonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y);

	}

	OldCenter = SelectedFig->GetCenter();
	int dx = OldCenter.x - NewCenter.x;
	int dy = OldCenter.y - NewCenter.y;
	int err = 0;
	while (buttonDown) {
		buttonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y);
		NewCenter.x += dx;
		NewCenter.y += dy;
		SelectedFig->SetCenter(NewCenter);
		err = sqrt(pow(OldCenter.x - NewCenter.x, 2) + pow(OldCenter.y - NewCenter.y, 2));
		if (err) { // check if it moved by a pixel before updating interface
			pManager->UpdateInterface();
		}
		OldCenter = NewCenter;
	}
	SelectedFig->SetSelected(false);
	pManager->SetSelected(NULL);
	pOut->ClearStatusBar();

	return true;
}