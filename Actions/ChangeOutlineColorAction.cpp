#include "ChangeOutlineColorAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeOutlineColorAction::ChangeOutlineColorAction(ApplicationManager* pApp) :Action(pApp) {}

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

void ChangeOutlineColorAction::Execute()
{
	ReadActionParameters();
	CFigure* F = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (F != NULL)
	{
		F->ChngDrawClr(pIn->GetSelectedColor(pOut));
		pOut->ClearStatusBar();
		F->SetSelected(false);
		pManager->SetSelected(NULL);
	}
}