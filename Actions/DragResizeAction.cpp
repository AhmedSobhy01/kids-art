#include "DragResizeAction.h"
#include "../ApplicationManager.h"

DragResizeAction::DragResizeAction(ApplicationManager* pApp) :UndoableAction(pApp) {

}

void DragResizeAction::ReadActionParameters() {

}

bool DragResizeAction::Execute() {
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

	pOut->PrintMessage("DragMove: Drag the selected shape to resize");

	bool buttonDown = false;
	while (!buttonDown || !Figure->GetCorner(NewCorner,PointIndex)) {
		buttonDown = pIn->GetLeftClickState(NewCorner.x, NewCorner.y);
	}
	OldCorner = NewCorner;
	Point CurrentCorner = OldCorner;
	int err;
	while (buttonDown) {
		buttonDown = pIn->GetLeftClickState(NewCorner.x, NewCorner.y);
		Figure->SetCorner(NewCorner,PointIndex);
		err = sqrt(pow(CurrentCorner.x - NewCorner.x, 2) + pow(CurrentCorner.y - NewCorner.y, 2));
		if (err) { // check if it moved by a pixel before updating interface
			pManager->UpdateInterface();
		}
		CurrentCorner = NewCorner;
	}
	Figure->SetSelected(false);
	pManager->SetSelected(NULL);
	pOut->ClearStatusBar();
	return true;
}


void DragResizeAction::PlayRecord()
{
	if (Figure != NULL)
		Figure->SetCorner(NewCorner,PointIndex);
}


void DragResizeAction::Undo()
{
	if (Figure != NULL)
		Figure->SetCorner(OldCorner, PointIndex);
}

void DragResizeAction::Redo()
{
	if (Figure != NULL)
		Figure->SetCorner(NewCorner, PointIndex);
}

DragResizeAction::~DragResizeAction()
{
	if (Figure != NULL) {
		Figure->DecrementReference();

		if (Figure->CanBeDeleted())
			delete Figure;

		Figure = NULL;
	}
}

