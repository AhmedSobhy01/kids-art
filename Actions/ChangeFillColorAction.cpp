#include "ChangeFillColorAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeFillColorAction::ChangeFillColorAction(ApplicationManager* pApp) :Action(pApp) {}

void ChangeFillColorAction::ReadActionParameters()
{
	CFigure* F = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (F == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Please select a shape to change it's fill color. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->CreateColorMenuWind(8 * 45, 1);
	pOut->DrawColorMenuItems(1);
	pOut->PrintMessage("Change Fill Color: Select a color.");
	pOut->ClearStatusBar();
}

void ChangeFillColorAction::Execute()
{
	ReadActionParameters();
	CFigure* F = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (F != NULL)
	{
		F->ChngFillClr(pIn->GetSelectedColor(pOut));
		F->SetSelected(false);
		pManager->SetSelected(NULL);
	}
}