#include "PickByShapeAndColorAction.h"
#include "SwitchToDrawAction.h"
#include "PickByColorAction.h"
#include "PickByShapeAction.h"

PickByShapeAndColorAction::PickByShapeAndColorAction(ApplicationManager* pApp) : Action(pApp)
{ }

void PickByShapeAndColorAction::ReadActionParameters() {
	CorrectPicks = 0;
	Counter = 0;
	ChangedAction = false;
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

void PickByShapeAndColorAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomColorName + " " + RandomFigureType + "s. " + to_string(RandomColorFigNumber) + " exist");
}

void PickByShapeAndColorAction::FinalMsg() {
	Output* pOut = pManager->GetOutput();
	if (Counter == CorrectPicks)pOut->PrintMessage("Congratulations! All your picks are correct! (" + to_string(CorrectPicks) + "/" + to_string(CorrectPicks) + ")");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");
}

void PickByShapeAndColorAction::GetAction() {
	Output* pOut;
	SwitchToDrawAction* SwitchToDraw;
	PickByShapeAction* PickByShape;
	PickByColorAction* PickByColor;
	if (P.y >= 0 && P.y < UI.ToolBarHeight) {
		int clickeditem = P.x / UI.MenuItemWidth;
		switch (clickeditem) {
		case ITM_DRAW_MODE:																// Switch to Draw mode
			SwitchToDraw = new SwitchToDrawAction(pManager);
			SwitchToDraw->Execute();
			pOut = pManager->GetOutput();
			pOut->PrintMessage("Game over. Switched to Draw Mode.");
			ChangedAction = true;
			delete SwitchToDraw;
			return;
		case ITM_PICKBYSHAPE:															// Switch to Pick By Shape mode
			PickByShape = new PickByShapeAction(pManager);
			PickByShape->Execute();
			ChangedAction = true;
			delete PickByShape;
			return;
		case ITM_PICKBYCOLOR:															// Switch to Pick By Color mode
			PickByColor = new PickByColorAction(pManager);
			PickByColor->Execute();
			ChangedAction = true;
			delete PickByColor;
			return;
		case ITM_PICKBYSHAPEANDCOLOR:													// Switch to Pick By Shape & Color mode
			this->Execute();
			ChangedAction = true;
			return;
		}
	}
}

bool PickByShapeAndColorAction::Execute() {
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
	StartingMessage();

	while (CorrectPicks < RandomColorFigNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);								// Gets the clicked shape
		GetAction();
		if (ChangedAction) return false;

		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;					// If there's no clicked shape or the clicked shape is already hidden
		bool SameType = ClickedFigure->Type() == RandomFigureType;
		bool SameColor = ClickedFigure->GetFillClr() == RandomFigureColor;
		if (SameType && SameColor) CorrectPicks++;											// Checks if the shapes of the same type & color

		ClickedFigure->Hide();																// Hiding any clicked shape
		pManager->UpdateInterface();
		Counter++;
	}
	FinalMsg();
	pManager->UnhideFigures();
	pManager->UpdateInterface();

	return true;
}