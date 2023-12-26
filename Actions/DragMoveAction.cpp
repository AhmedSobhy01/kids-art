#include "DragMoveAction.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

DragMoveAction::DragMoveAction(ApplicationManager *pApp) : UndoableAction(pApp)
{
}

void DragMoveAction::ReadActionParameters()
{
}

bool DragMoveAction::Execute()
{

	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	Figure = pManager->GetSelected();

	if (Figure == NULL) // Checks if no figure is selected
	{
		int x, y;
		pOut->PrintMessage("Error: Select a shape before moving. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();

		return false;
	}

	Figure->IncrementReference(); // Increment the reference count of the figure

	pOut->PrintMessage("Drag Move: Drag the selected shape to move");

	bool ButtonDown = false;
	while (!ButtonDown) // Waits till there is a button click
	{
		ButtonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y); // Gets the new center
	}

	if (!Figure->IsPointInside(NewCenter)) // Check if the cursor is inside the figure
	{
		pOut->ClearStatusBar();
		return false;
	}

	OldCenter = Figure->GetCenter(); // Saves the original center for undo and redo
	Point CurrentCenter = OldCenter;
	int dx = OldCenter.x - NewCenter.x; // The distance between the mouse and the center
	int dy = OldCenter.y - NewCenter.y;
	int Err = 0; // The distance between the current figure center and the new center

	while (ButtonDown)
	{
		ButtonDown = pIn->GetLeftClickState(NewCenter.x, NewCenter.y);
		NewCenter.x += dx;
		NewCenter.y += dy;
		Figure->SetCenter(NewCenter);
		Err = sqrt(pow(CurrentCenter.x - NewCenter.x, 2) + pow(CurrentCenter.y - NewCenter.y, 2));

		// Check if it moved by a pixel before updating interface
		// To prevent unnecessary interface update
		if (Err)
			pManager->UpdateInterface();

		CurrentCenter = NewCenter;
	}

	pOut->ClearStatusBar(); // Clear the status bar

	return true;
}

void DragMoveAction::PlayRecord()
{
	if (Figure != NULL)
		Figure->SetCenter(NewCenter);
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

DragMoveAction::~DragMoveAction()
{
	if (Figure != NULL)
	{
		Figure->DecrementReference();

		if (Figure->CanBeDeleted())
			delete Figure;

		Figure = NULL;
	}
}
