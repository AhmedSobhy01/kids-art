#include "PickByColorAction.h"
#include "SwitchToDrawAction.h"
#include "PickByShapeAction.h"
#include "PickByShapeAndColorAction.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp): Action(pApp)
{ }

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

void PickByColorAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomColorName + " figures. " + to_string(RandomColorNumber) + " exist.");
}

void PickByColorAction::FinalMsg() {
	Output* pOut = pManager->GetOutput();
	if (Counter == CorrectPicks) pOut->PrintMessage("Congratulations! All your picks are correct! (" + to_string(CorrectPicks) + "/" + to_string(CorrectPicks) + ")");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks");
}

void PickByColorAction::GetAction(){
	ChangedAction = false;
	EmptyClick = false;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (P.y >= 0 && P.y <= UI.StatusBarHeight) {
		ActionType Act = pIn->GetAction(P);
		if (Act == TO_DRAW || (Act >= PICK_BY_COLOR && Act <= PICK_BY_SHAPE_COLOR)) {
			pManager->ExecuteAction(Act);
			ChangedAction = true;
			if (Act == TO_DRAW) pOut->PrintMessage("Game over. Switched to Draw Mode.");
		}
		else EmptyClick = true;
	}
	else {
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);
		if (ClickedFigure == NULL || ClickedFigure->isHidden()) {
			EmptyClick = true;
			return;
		}
		else if (ClickedFigure->GetFillClr() == RandomColor) {
			CorrectPicks++;
			pOut->PrintMessage("Correct.");
		}
		else pOut->PrintMessage("Incorrect.");
		ClickedFigure->Hide();
	}
}

bool PickByColorAction::Execute() {
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

	while (CorrectPicks < RandomColorNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		GetAction();

		if (EmptyClick) continue;
		else if (ChangedAction) return false;
		pManager->UpdateInterface();
		Counter++;
	}
	FinalMsg();
	pManager->UnhideFigures();
	pManager->UpdateInterface();
	return true;
}