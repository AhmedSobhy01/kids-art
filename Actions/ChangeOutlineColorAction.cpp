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
		pOut->PrintMessage("Error:Please select a shape to change it's color. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->CreateColorMenuWind(8 * 45, 0);
	pOut->DrawColorMenuItems(0);
	pOut->PrintMessage("Change Outline Color: Select a color.");
	pOut->ClearStatusBar();
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
		F->SetSelected(false);
		pManager->SetSelected(NULL);
	}
}
