#include "SelectAction.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

SelectAction::SelectAction(ApplicationManager *pApp) : Action(pApp)
{
	RecordEnabled = true;
}

void SelectAction::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Select: Click on a shape to select.");
	pIn->GetPointClicked(P.x, P.y);
	Figure = pManager->GetFigure(P.x, P.y);
	pOut->ClearStatusBar();
}

bool SelectAction::Execute()
{
	ReadActionParameters();
	if (Figure == NULL)
		return false;

	// Checks if there is a selected figure and unselect it
	CFigure *S = pManager->GetSelected();
	if (S != NULL)
		S->SetSelected(false);

	// Unselect from the application manager
	pManager->SetSelected(NULL);

	// Checks if the current figure is not the previously selected one
	// And selects the new figure
	if (Figure != S)
	{
		Figure->SetSelected(true);
		pManager->SetSelected(Figure);
		Figure->PrintInfo(pManager->GetOutput());
	}
	else
		Figure = NULL; // To made the play record action simpler

	return true;
}

void SelectAction::PlayRecord()
{
	CFigure *S = pManager->GetSelected();
	if (S != NULL)
		S->SetSelected(false);
	pManager->SetSelected(Figure);
	if (Figure != NULL)
		Figure->SetSelected(true);
}
