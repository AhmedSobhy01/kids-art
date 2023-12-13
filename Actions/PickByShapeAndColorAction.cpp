#include "PickByShapeAndColorAction.h"
#include "SwitchToDrawAction.h"
#include <string>
using namespace std;
PickByShapeAndColorAction::PickByShapeAndColorAction(ApplicationManager* pApp) : Action(pApp), RandomFigureColor(TRANSPARENT_COLOR), P{ 0, 0 }, RandomFigureType(""), RandomColorName(""), CorrectPicks(0), Counter(0), FiguresNumber(0), RandomColorFigNumber(0)
{
	RandomFigure = NULL;
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
	pOut->PrintMessage("Pick all the " + RandomColorName + " " + RandomFigureType + "s. " + to_string(RandomColorFigNumber) + " exist");
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
	SwitchToDrawAction SwitchToDraw(pManager);

	while (CorrectPicks < RandomColorFigNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);								// Gets the clicked shape

		if (P.y >= 0 && P.y < UI.ToolBarHeight && P.x / UI.MenuItemWidth == 0) {			// If switched to Draw Mode
			SwitchToDraw.Execute();
			pOut->PrintMessage("Game over. Switched to Draw Mode");
			return false;
		}

		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;					// If there's no clicked shape or the clicked shape is already hidden

		bool SameType = ClickedFigure->Type() == RandomFigureType;
		bool SameColor = ClickedFigure->GetFillClr() == RandomFigureColor;
		if (SameType && SameColor) CorrectPicks++;											// Checks if the shapes of the same type & color

		ClickedFigure->Hide();																// Hiding any clicked shape
		pManager->UpdateInterface();
		Counter++;
	}
	if (Counter == CorrectPicks)pOut->PrintMessage("Congratulations! All your picks are correct!");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");

	pManager->UnhideFigures();
	pManager->UpdateInterface();

	return true;
}