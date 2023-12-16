#include "PickByShapeAction.h"
#include "SwitchToDrawAction.h"
#include "PickByColorAction.h"
#include "PickByShapeAndColorAction.h"
#include "ExitAction.h"

PickByShapeAction::PickByShapeAction(ApplicationManager* pApp) : Action(pApp)
{ }

void PickByShapeAction::ReadActionParameters() {				// Generates random figure and counts it
	CorrectPicks = 0;
	Counter = 0;
	ChangedAction = false;
	RandomFigure = pManager->GetRandomFigure();
	RandomFigureNumber = pManager->CountFigure(RandomFigure);
	RandomFigureType = RandomFigure->Type();
}

void PickByShapeAction::PrintMessage() {						// Prints a message according to the random asked shape
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomFigureType + "s. " + to_string(RandomFigureNumber) + " exist");
}

void PickByShapeAction::GetAction()
{
	SwitchToDrawAction* SwitchToDraw;
	PickByShapeAndColorAction* PickByShapeColor;
	PickByColorAction* PickByColor;
	ExitAction* Exit;
	Output* pOut;
	if (P.y >= 0 && P.y < UI.ToolBarHeight) {
		int clickeditem = P.x / UI.MenuItemWidth;
		switch (clickeditem) {
		case ITM_DRAW_MODE:
			SwitchToDraw = new SwitchToDrawAction(pManager);
			SwitchToDraw->Execute();
			pOut = pManager->GetOutput();
			pOut->PrintMessage("Game over. Switched to Draw Mode");
			ChangedAction = true;
			delete SwitchToDraw;
			return;
		case ITM_PICKBYSHAPE:
			this->Execute();
			ChangedAction = true;
			return;
		case ITM_PICKBYCOLOR:
			PickByColor = new PickByColorAction(pManager);
			PickByColor->Execute();
			ChangedAction = true;
			delete PickByColor;
			return;
		case ITM_PICKBYSHAPEANDCOLOR:
			PickByShapeColor = new PickByShapeAndColorAction(pManager);
			PickByShapeColor->Execute();
			ChangedAction = true;
			delete PickByShapeColor;
			return;
		}
	}
}

bool PickByShapeAction::Execute() {
	pManager->UnhideFigures();
	pManager->UpdateInterface();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0) {
		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with.");
		return false;
	}
	ReadActionParameters();
	PrintMessage();

	while (CorrectPicks < RandomFigureNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);

		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);								// Get the clicked shape
		GetAction();
		if (ChangedAction) return false;

		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;					// If there's no clicked shape or the clicked shape is already hidden
		else if (ClickedFigure->Type() == RandomFigureType) CorrectPicks++;					// Correct Shape picked

		ClickedFigure->Hide();																// Hiding any clicked shape
		pManager->UpdateInterface();
		Counter++;
	}

	if (Counter == CorrectPicks) pOut->PrintMessage("Congratulations! All your picks are correct! (" + to_string(CorrectPicks) + "/" + to_string(CorrectPicks) + ")");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");

	pManager->UnhideFigures();
	pManager->UpdateInterface();

	return true;
}