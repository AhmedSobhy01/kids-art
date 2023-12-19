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
		else if (*ClickedFigure == *RandomFigure)CorrectPicks++;
		ClickedFigure->Hide();
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
		GetAction();

		if (EmptyClick)continue;
		else if (ChangedAction)return false;
		pManager->UpdateInterface();
		Counter++;
	}
	FinalMsg();
	pManager->UnhideFigures();
	pManager->UpdateInterface();

	return true;
}