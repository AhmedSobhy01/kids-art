#include "PickByShapeAction.h"

PickByShapeAction::PickByShapeAction(ApplicationManager* pApp) : Action(pApp)
{ }

void PickByShapeAction::ReadActionParameters() {				// Initializes the data members
	CorrectPicks = 0;
	Counter = 0;
	RandomFigure = pManager->GetRandomFigure();
	RandomFigureNumber = pManager->CountFigure(RandomFigure);
}

void PickByShapeAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomFigure->Type() + "s. " + to_string(RandomFigureNumber) + " exist");
}

void PickByShapeAction::FinalMsg(bool& ChangedAction) {
	Output* pOut = pManager->GetOutput();
	if (Counter == CorrectPicks && !ChangedAction) 
		pOut->PrintMessage("Congratulations! All your picks are correct! (" + to_string(CorrectPicks) + "/" + to_string(CorrectPicks) + ")");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks.");
}

void PickByShapeAction::GetClickedAction(bool& ChangedAction, bool& EmptyClick) {
	ChangedAction = false;
	EmptyClick = false;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	ActionType Act = pIn->GetAction(P);
	if (Act == TO_DRAW || (Act >= PICK_BY_COLOR && Act <= PICK_BY_SHAPE_COLOR) || Act == EXIT)
		ChangedAction = true;
	else {
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);
		if (ClickedFigure == NULL || ClickedFigure->IsHidden()) {
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
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	bool ChangedAction, EmptyClick;

	int FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0) {
		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with.");
		return false;
	}
	ReadActionParameters();
	StartingMessage();

	while (CorrectPicks < RandomFigureNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		GetClickedAction(ChangedAction, EmptyClick);
		if (EmptyClick) continue;
		else if (ChangedAction) break;

		pManager->UpdateInterface();
		Counter++;
	}
	FinalMsg(ChangedAction);
	pManager->UnhideFigures();
	pManager->UpdateInterface();

	return true;
}

bool PickByShapeAction::ShouldRecord() const
{
	return false;
}
