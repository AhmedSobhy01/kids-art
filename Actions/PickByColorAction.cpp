#include "PickByColorAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"
#include "SwitchToDrawAction.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp): Action(pApp) {}

void PickByColorAction::ReadActionParameters() {												// Initializes the data members
	CorrectPicks = 0;
	Counter = 0;
	RandomFigure = pManager->GetRandomFigure();
	RandomColor = RandomFigure->GetFillClr();
	RandomColorNumber = pManager->CountColor(RandomColor);
	SetColorName();
}

void PickByColorAction::SetColorName() {
	if (RandomColor == BLACK) RandomColorName = "Black";
	else if (RandomColor == RED) RandomColorName = "Red";
	else if (RandomColor == BLUE) RandomColorName = "Blue";
	else if (RandomColor == GREEN) RandomColorName = "Green";
	else if (RandomColor == MAGENTA) RandomColorName = "Magenta";
	else if (RandomColor == ORANGE) RandomColorName = "Orange";
	else if (RandomColor == BROWN) RandomColorName = "Brown";
	else if (RandomColor == CYAN) RandomColorName = "Cyan";
	else if (RandomColor == YELLOW) RandomColorName = "Yellow";
	else if (RandomColor == GOLD) RandomColorName = "Gold";
	else if (RandomColor == TRANSPARENT_COLOR) RandomColorName = "Transparent";
}

void PickByColorAction::PrintMessage() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomColorName + " figures. " + to_string(RandomColorNumber) + " exist.");
}

bool PickByColorAction::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0) {

		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with.");
    
		return false;
	}
	ReadActionParameters();
	PrintMessage();
	SwitchToDrawAction SwitchToDraw(pManager);

	while (CorrectPicks < RandomColorNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);									// Get the clicked shape

		if (P.y >= 0 && P.y < UI.ToolBarHeight && P.x / UI.MenuItemWidth == 0) {				// If switched to Draw Mode
			SwitchToDraw.Execute();
			pOut->PrintMessage("Game over. Switched to Draw Mode");
			return false;
		}

		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;						// If theres not shape clicked or the shape is hidden
		else if (ClickedFigure->GetFillClr() == RandomColor) CorrectPicks++;					// Correct color is picked

		ClickedFigure->Hide();																	// Hiding every clicked shape
		pManager->UpdateInterface();
		Counter++;
	}

	if (Counter == CorrectPicks) pOut->PrintMessage("Congratulations! All your picks are correct!");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks");

	pManager->UnhideFigures();
	pManager->UpdateInterface();

	return true;
}