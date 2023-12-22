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

void PickByShapeAction::StartingMessage() {						// Prints a message according to the random asked shape
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomFigureType + "s. " + to_string(RandomFigureNumber) + " exist");
}

void PickByShapeAction::FinalMsg() {
	Output* pOut = pManager->GetOutput();
	if (Counter == CorrectPicks) pOut->PrintMessage("Congratulations! All your picks are correct! (" + to_string(CorrectPicks) + "/" + to_string(CorrectPicks) + ")");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");
}

void PickByShapeAction::GetAction()
{
	ChangedAction = false;
	EmptyClick = false;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (P.y >= 0 && P.y <= UI.StatusBarHeight) {
		ActionType Act = pIn->GetAction(P);
		if (Act == TO_DRAW || (Act >= PICK_BY_SHAPE && Act <= PICK_BY_SHAPE_COLOR)) {
			pManager->ExecuteAction(Act);
			ChangedAction = true;
			if (Act == TO_DRAW) pOut->PrintMessage("Game Over. Switch to Draw Mode.");
		}
		else EmptyClick = true;
	}
	else {
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);
		if (ClickedFigure == NULL || ClickedFigure->isHidden()) {
			EmptyClick = true;
			return;
		}
		else if (ClickedFigure->Type() == RandomFigure->Type()) {
			CorrectPicks++;
			pOut->PrintMessage("Correct.");
		}
		else pOut->PrintMessage("Incorrect.");
		ClickedFigure->Hide();
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
	StartingMessage();

	while (CorrectPicks < RandomFigureNumber && Counter != FiguresNumber) {
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

bool PickByShapeAction::ShouldRecord() const
{
	return false;
}
