#include "ChangeBorderWidthAction.h"

ChangeBorderWidthAction::ChangeBorderWidthAction(ApplicationManager* pApp) : UndoableAction(pApp) {}

void ChangeBorderWidthAction::ReadActionParameters()
{
	Figure = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (Figure == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Please select a shape to change it's Border Width. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
}

bool ChangeBorderWidthAction::Execute()
{
	ReadActionParameters();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (Figure != NULL)
	{
		OldWidth = Figure->GetBorderWidth();
		if (UI.PenWidth < 4)
			UI.PenWidth++;
		else
			UI.PenWidth = 2;
		NewWidth = UI.PenWidth;
		Figure->ChngBorderWidth(NewWidth);
		pOut->CreateDrawToolBar(); // To update border width icon
		pOut->ClearStatusBar();
		Figure->SetSelected(false);
		pManager->SetSelected(NULL);

		return true;
	}

	return false;
}

void ChangeBorderWidthAction::PlayRecord()
{
	if (Figure)
	{
		Output* pOut = pManager->GetOutput();
		UI.PenWidth = NewWidth;
		Figure->ChngBorderWidth(NewWidth);
	}
}

void ChangeBorderWidthAction::Undo()
{
	if (Figure)
	{
		Output* pOut = pManager->GetOutput();
		UI.PenWidth = OldWidth;
		Figure->ChngBorderWidth(OldWidth);
	}
}

void ChangeBorderWidthAction::Redo()
{
	if (Figure)
	{
		Output* pOut = pManager->GetOutput();
		UI.PenWidth = NewWidth;
		Figure->ChngBorderWidth(NewWidth);
	}
}
