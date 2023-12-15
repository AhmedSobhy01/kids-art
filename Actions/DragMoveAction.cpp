#include "DragMoveAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

DragMoveAction::DragMoveAction(ApplicationManager* pApp) :Action(pApp) {

}

void DragMoveAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("DragMove: Drag a shape to move");
}

bool DragMoveAction::Execute() {
	ReadActionParameters();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	bool buttonDown = false;
	CFigure* Fig;
	while (!buttonDown || Fig == NULL) {
		buttonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y);
		if (buttonDown) {
			Fig = pManager->GetFigure(NewCenter.x, NewCenter.y);
		}
	}

	OldCenter = Fig->GetCenter();
	int dx = OldCenter.x - NewCenter.x;
	int dy = OldCenter.y - NewCenter.y;
	int err = 0;
	while (buttonDown && Fig != NULL) {
		buttonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y);
		NewCenter.x += dx;
		NewCenter.y += dy;
		Fig->SetCenter(NewCenter);
		err = sqrt(pow(OldCenter.x - NewCenter.x,2) + pow(OldCenter.y - NewCenter.y,2));
		if(err){
			pManager->UpdateInterface();
		}
		OldCenter = NewCenter;
	}
	pOut->ClearStatusBar();

	return true;
}