#include "PickByShapeAndColorAction.h"

PickByShapeAndColorAction::PickByShapeAndColorAction(ApplicationManager* pApp) : Action(pApp)
{

}

void PickByShapeAndColorAction::ReadActionParameters() {
	CorrectPicks = 0;
	Counter = 0;
	RandomFigure = pManager->GetRandomFigure();
	RandomFigureColor = RandomFigure->GetFillClr();
	RandomColorFigNumber = pManager->CountFigColor(RandomFigure);
	RandomFigureType = RandomFigure->Type();
	SetFigureStats();
}

void PickByShapeAndColorAction::SetFigureStats() {
	switch (RandomFigureType) {
	case CIRCLE:
		RandomFigureName =  "Circles";
		break;
	case SQUARE:
		RandomFigureName = "Squares";
		break;
	case TRIANGLE:
		RandomFigureName = "Triangles";
		break;
	case HEXAGON:
		RandomFigureName = "Hexagons";
		break;
	case RECTANGLE:
		RandomFigureName = "Rectangles";
		break;
	}
	if (RandomFigureColor == BLACK) RandomColorName = "Black";
	else if (RandomFigureColor == RED) RandomColorName = "Red";
	else if (RandomFigureColor == BLUE) RandomColorName = "Blue";
	else if (RandomFigureColor == GREEN) RandomColorName = "Green";
	else if (RandomFigureColor == MAGENTA) RandomColorName = "Magenta";
	else if (RandomFigureColor == ORANGE) RandomColorName = "Orange";
	else if (RandomFigureColor == BROWN) RandomColorName = "Brown";
	else if (RandomFigureColor == CYAN) RandomColorName = "Cyan";
	else if (RandomFigureColor == YELLOW) RandomColorName = "Yellow";
	else if (RandomFigureColor == GOLD) RandomColorName = "Gold";
	else if (RandomFigureColor == TRANSPARENT_COLOR) RandomColorName = "Transparent";
}

void PickByShapeAndColorAction::PrintMessage() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomColorName + " " + RandomFigureName + ". " + to_string(RandomColorFigNumber) + " exist");
}

bool PickByShapeAndColorAction::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0) {
		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with.");
		return false;
	}
	ReadActionParameters();
	PrintMessage();

	while (CorrectPicks < RandomColorFigNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);													// Gets the clicked shape
		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;										// If there's no clicked shape or the clicked shape is already hidden
		
		bool SameType = ClickedFigure->Type() == RandomFigureType;
		bool SameColor = ClickedFigure->GetFillClr() == RandomFigureColor;
		if (SameType && SameColor) CorrectPicks++;																// Checks if the shapes of the same type & color
		ClickedFigure->Hide();																					// Hiding any clicked shape
		pManager->UpdateInterface();
		Counter++;
	}
	if (Counter == CorrectPicks)pOut->PrintMessage("Congratulations! All your picks are correct!");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");

	pManager->UnHideFigures();
	pManager->UpdateInterface();

	return true;
}