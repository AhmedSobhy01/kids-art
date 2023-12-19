#include "DragMoveAction.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

DragMoveAction::DragMoveAction(ApplicationManager* pApp): UndoableAction(pApp) {

}

void DragMoveAction::ReadActionParameters() {

}

bool DragMoveAction::Execute() {

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Figure = pManager->GetSelected();
	if (Figure == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Select a shape before moving. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return false;
	}

	Figure->IncrementReference();

	pOut->PrintMessage("DragMove: Drag the selected shape to move");

	bool buttonDown = false;
	while (!buttonDown || !Figure->CheckSelected(NewCenter.x, NewCenter.y)) {
		buttonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y);

	}

	OldCenter = Figure->GetCenter();
	Point CurrentCenter = OldCenter;
	int dx = OldCenter.x - NewCenter.x;
	int dy = OldCenter.y - NewCenter.y;
	int err = 0;
	while (buttonDown) {
		buttonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y);
		NewCenter.x += dx;
		NewCenter.y += dy;
		Figure->SetCenter(NewCenter);
		err = sqrt(pow(CurrentCenter.x - NewCenter.x, 2) + pow(CurrentCenter.y - NewCenter.y, 2));
		if (err) { // check if it moved by a pixel before updating interface
			pManager->UpdateInterface();
		}
		CurrentCenter = NewCenter;
	}
	Figure->SetSelected(false);
	pManager->SetSelected(NULL);
	pOut->ClearStatusBar();

	return true;
}


void DragMoveAction::Undo()
{
	if (Figure != NULL)
		Figure->SetCenter(OldCenter);
}

void DragMoveAction::Redo()
{
	if (Figure != NULL)
		Figure->SetCenter(NewCenter);
}

void DragMoveAction::PlayRecord()
{
	if (Figure != NULL)
		Figure->SetCenter(NewCenter);
}

DragMoveAction::~DragMoveAction()
{
	if (Figure != NULL) {
		Figure->DecrementReference();

		if (Figure->CanBeDeleted())
			delete Figure;

		Figure = NULL;
	}
}