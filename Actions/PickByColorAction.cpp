#include "PickByColorAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp) :Action(pApp) {

}

void PickByColorAction::ReadActionParameters() {												// Initializes the data members
	CorrectPicks = 0;
	Counter = 0;
	RandomColor = pManager->GetRandomColor();
	RandomColorNumber = pManager->CountColor(RandomColor);
}

string PickByColorAction::GetFigureColor(color FigColor) {
	string color;
	if (FigColor == BLACK) color = "Black";
	else if (FigColor == RED) color = "Red";
	else if (FigColor == BLUE) color = "Blue";
	else if (FigColor == GREEN) color = "Green";
	else if (FigColor == MAGENTA) color = "Magenta";
	else if (FigColor == ORANGE) color = "Orange";
	else if (FigColor == BROWN) color = "Brown";
	else if (FigColor == CYAN) color = "Cyan";
	else if (FigColor == YELLOW) color = "Yellow";
	else if (FigColor == GOLD) color = "Gold";
	else if (FigColor == TRANSPARENT_COLOR) color = "Transparent";
	return color;
}

void PickByColorAction::PrintMessage() {
	string ColorToPick = GetFigureColor(RandomColor);
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + ColorToPick + " figures. " + to_string(RandomColorNumber) + " exist.");
}
void PickByColorAction::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0) {
		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with them.");
		return;
	}
	ReadActionParameters();
	PrintMessage();

	///					Main Loop				///
	while (CorrectPicks < RandomColorNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);									// Get the clicked shape

		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;						// If theres not shape clicked or the shape is hidden
		else if (ClickedFigure->GetColor() == RandomColor) CorrectPicks++;						// Correct color is picked

		ClickedFigure->Hide();																	// Hiding every clicked shape
		pManager->UpdateInterface();
		Counter++;
	}
	if (Counter == CorrectPicks) pOut->PrintMessage("Congratulations! All your picks are correct!");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks");

	pManager->UnHideFigures();
	pManager->UpdateInterface();
}