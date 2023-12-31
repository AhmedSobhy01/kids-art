#include "ChangeFillColorAction.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ChangeFillColorAction::ChangeFillColorAction(ApplicationManager *pApp) : UndoableAction(pApp) {}

void ChangeFillColorAction::ReadActionParameters()
{
	Figure = pManager->GetSelected();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (Figure == NULL)
	{
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
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (Figure != NULL)
	{
		OldColor = Figure->GetFillColor();
		NewColor = pIn->GetSelectedColor(pOut);
		UI.FillColor = NewColor;
		Figure->ChangeFillColor(NewColor);
		UI.FillColor = NewColor;
		pOut->ClearStatusBar();

		return true;
	}

	return false;
}

void ChangeFillColorAction::PlayRecord()
{
	Figure->ChangeFillColor(NewColor);
	UI.FillColor = NewColor;
}

void ChangeFillColorAction::Undo()
{
	Figure->ChangeFillColor(OldColor);
	UI.FillColor = OldColor;
}

void ChangeFillColorAction::Redo() // we could just call PlayRecord() insted of writing the same code but for the sake of readability we left it as it is
{
	Figure->ChangeFillColor(NewColor);
	UI.FillColor = NewColor;
}