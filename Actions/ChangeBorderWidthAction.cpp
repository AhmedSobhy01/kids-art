#include "ChangeBorderWidthAction.h"

ChangeBorderWidthAction::ChangeBorderWidthAction(ApplicationManager* pApp) : UndoableAction(pApp) {}

void ChangeBorderWidthAction::ReadActionParameters()
{
	Figure = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
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
	if (Figure != NULL)
	{
		OldWidth = Figure->GetBorderWidth();
		if (UI.PenWidth < 4)					// if width == maximum -> width = minimum else width++
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
	UI.PenWidth = NewWidth;
	Figure->ChngBorderWidth(NewWidth);
	pOut->CreateDrawToolBar(); // To update border width icon
}

void ChangeBorderWidthAction::Undo()
{
	UI.PenWidth = OldWidth;
	Figure->ChngBorderWidth(OldWidth);
	pOut->CreateDrawToolBar(); // To update border width icon
}

void ChangeBorderWidthAction::Redo()	//we could just call PlayRecord() insted of writing the same code but for the sake of readability we left it as it is
{
	UI.PenWidth = NewWidth;
	Figure->ChngBorderWidth(NewWidth);
	pOut->CreateDrawToolBar(); // To update border width icon
}
