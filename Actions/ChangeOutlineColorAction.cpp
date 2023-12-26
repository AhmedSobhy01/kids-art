#include "ChangeOutlineColorAction.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

ChangeOutlineColorAction::ChangeOutlineColorAction(ApplicationManager *pApp) : UndoableAction(pApp) {}

void ChangeOutlineColorAction::ReadActionParameters()
{
	Figure = pManager->GetSelected();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if (Figure == NULL)
	{

		int x, y;
		pOut->PrintMessage("Error:Please select a shape to change it's outline color. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->OpenColorMenuWind(8 * UI.ColorMenuItemWidth, false);
	pOut->PrintMessage("Change Outline Color: Select a color.");
}

bool ChangeOutlineColorAction::Execute()
{
	ReadActionParameters();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	if (Figure != NULL)
	{
		OldColor = Figure->GetDrawColor();
		NewColor = pIn->GetSelectedColor(pOut);
		UI.DrawColor = NewColor;
		Figure->ChangeDrawColor(NewColor);
		UI.DrawColor = NewColor;
		pOut->ClearStatusBar();

		return true;
	}

	return false;
}

void ChangeOutlineColorAction::PlayRecord()
{
	Figure->ChangeDrawColor(NewColor);
	UI.DrawColor = NewColor;
}

void ChangeOutlineColorAction::Undo()
{
	Figure->ChangeDrawColor(OldColor);
	UI.DrawColor = OldColor;
}

void ChangeOutlineColorAction::Redo() // we could just call PlayRecord() insted of writing the same code but for the sake of readability we left it as it is
{
	Figure->ChangeDrawColor(NewColor);
	UI.DrawColor = NewColor;
}