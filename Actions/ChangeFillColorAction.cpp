#include "ChangeFillColorAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeFillColorAction::ChangeFillColorAction(ApplicationManager* pApp): UndoableAction(pApp) {}

void ChangeFillColorAction::ReadActionParameters()
{
	Figure = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (Figure == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Please select a shape to change it's fill color. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->OpenColorMenuWind(8 * UI.ColorMenuItemWidth);
	pOut->PrintMessage("Change Fill Color: Select a color.");
}

bool ChangeFillColorAction::Execute()
{
	ReadActionParameters();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (Figure != NULL)
	{
		OldColor = Figure->GetFillColor();
		NewColor = pIn->GetSelectedColor(pOut);
		UI.FillColor = NewColor;
		Figure->ChangeFillColor(NewColor);
		UI.FillColor = NewColor;
		pOut->ClearStatusBar();
		Figure->SetSelected(false);
		pManager->SetSelected(NULL);

		return true;
	}

	return false;
}

void ChangeFillColorAction::PlayRecord()
{
	if (Figure)
	{
		Figure->ChangeFillColor(NewColor);
		UI.FillColor = NewColor;
	}
}

void ChangeFillColorAction::Undo()
{
	if (Figure)
	{
		Figure->ChangeFillColor(OldColor);
		UI.FillColor = OldColor;
	}
}

void ChangeFillColorAction::Redo()
{
	if (Figure)
	{
		Figure->ChangeFillColor(NewColor);
		UI.FillColor = NewColor;
	}
}