#include "ChangeOutlineColorAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeOutlineColorAction::ChangeOutlineColorAction(ApplicationManager* pApp): UndoableAction(pApp) {}

void ChangeOutlineColorAction::ReadActionParameters()
{
	CFigure* F = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (F == NULL) {
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
	Figure = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	if (Figure != NULL)
	{
		OldColor = Figure->GetDrawClr();
		NewColor = pIn->GetSelectedColor(pOut);

		Figure->ChngDrawClr(NewColor);
		UI.DrawColor = NewColor;
		pOut->ClearStatusBar();
		Figure->SetSelected(false);
		pManager->SetSelected(NULL);

		return true;
	}

	return false;
}

void ChangeOutlineColorAction::Undo()
{
	if (Figure)
		Figure->ChngDrawClr(OldColor);
}

void ChangeOutlineColorAction::Redo()
{
	if (Figure)
		Figure->ChngDrawClr(NewColor);
}