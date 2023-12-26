#include "DragResizeAction.h"

DragResizeAction::DragResizeAction(ApplicationManager *pApp) : UndoableAction(pApp)
{
}

void DragResizeAction::ReadActionParameters()
{
}

bool DragResizeAction::Execute()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	Figure = pManager->GetSelected();
	if (Figure == NULL)
	{
		int x, y;
		pOut->PrintMessage("Error:Select a shape before moving. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return false;
	}
	Figure->IncrementReference();

	pOut->PrintMessage("Drag Resize: Drag the selected shape to resize");

	bool ButtonDown = false;
	while (!ButtonDown) //Waits till there is a button click
	{
		ButtonDown = pIn->GetLeftClickState(NewCorner.x, NewCorner.y);
	}

	//Check if the cursor is inside the figure
	if (!Figure->GetCorner(NewCorner, PointIndex))
	{
		pOut->ClearStatusBar();
		return false;
	}
	OldCorner = NewCorner; //Saves the original corner for undo and redo
	Point CurrentCorner = OldCorner;
	int Err = 0; //The distance between the current figure center and the new center
	while (ButtonDown)
	{
		ButtonDown = pIn->GetLeftClickState(NewCorner.x, NewCorner.y);
		Figure->SetCorner(NewCorner, PointIndex);
		Err = sqrt(pow(CurrentCorner.x - NewCorner.x, 2) + pow(CurrentCorner.y - NewCorner.y, 2));
		//Check if it moved by a pixel before updating interface
		//To prevent unnecessary interface update
		if (Err)
			pManager->UpdateInterface();
		
		CurrentCorner = NewCorner;
	}

	pOut->ClearStatusBar();

	return true;
}

void DragResizeAction::PlayRecord()
{
	if (Figure != NULL)
		Figure->SetCorner(NewCorner, PointIndex);
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
	if (Figure != NULL)
	{
		Figure->DecrementReference();

		if (Figure->CanBeDeleted())
			delete Figure;

		Figure = NULL;
	}
}
