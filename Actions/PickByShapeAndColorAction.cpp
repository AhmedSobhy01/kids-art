#include "PickByShapeAndColorAction.h"

PickByShapeAndColorAction::PickByShapeAndColorAction(ApplicationManager* pApp) : Action(pApp)
{

}

void PickByShapeAndColorAction::ReadActionParameters() {						// Generates random figure and counts it
	
	CorrectPicks = 0;
	Counter = 0;
	RandomFigure = pManager->GetRandomFigure();
	RandomColor = RandomFigure->GetColor();
	RandomColorFigNumber = pManager->CountRandomFigColor(RandomFigure);
}

void PickByShapeAndColorAction::GetFigureStats(CFigure* Fig) {
	ShapeType type = Fig->Type();
	switch (type) {
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
	if (Fig->GetColor() == BLACK) RandomColorName = "Black";
	else if (Fig->GetColor() == RED) RandomColorName = "Red";
	else if (Fig->GetColor() == BLUE) RandomColorName = "Blue";
	else if (Fig->GetColor() == GREEN) RandomColorName = "Green";
	else if (Fig->GetColor() == MAGENTA) RandomColorName = "Magenta";
	else if (Fig->GetColor() == ORANGE) RandomColorName = "Orange";
	else if (Fig->GetColor() == BROWN) RandomColorName = "Brown";
	else if (Fig->GetColor() == CYAN) RandomColorName = "Cyan";
	else if (Fig->GetColor() == YELLOW) RandomColorName = "Yellow";
	else if (Fig->GetColor() == GOLD) RandomColorName = "Gold";
	else if (Fig->GetColor() == TRANSPARENT_COLOR) RandomColorName = "Transparent";
}

void PickByShapeAndColorAction::PrintMessage() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomColorName + " " + RandomFigureName + ". " + to_string(RandomColorFigNumber) + " exist");
}

void PickByShapeAndColorAction::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0) {
		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with them.");
		return;
	}
	ReadActionParameters();
	GetFigureStats(RandomFigure);
	PrintMessage();

	///							Main Loop						///
	while (CorrectPicks < RandomColorFigNumber && Counter != FiguresNumber && FiguresNumber !=0) {
		pIn->GetPointClicked(P.x, P.y);
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);													// Gets the clicked shape
		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;										// If there's no clicked shape or the clicked shape is already hidden
		
		bool SameType = ClickedFigure->Type() == RandomFigure->Type();
		bool SameColor = ClickedFigure->GetColor() == RandomFigure->GetColor();
		if (SameType && SameColor) CorrectPicks++;																// Checks if the shapes of the same type & color
		ClickedFigure->Hide();																					// Hiding any clicked shape
		pManager->UpdateInterface();
		Counter++;
	}
	if (Counter == CorrectPicks)pOut->PrintMessage("Congratulations! All your picks are correct!");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");
	pManager->UnHideFigures();
	pManager->UpdateInterface();
}