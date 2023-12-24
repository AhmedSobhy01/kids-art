#include "PickColor.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp): PlayMode(pApp)
{ }

void PickByColorAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	Target = pManager->CountColor(RandomFigure->GetFillClr());
	pOut->PrintMessage("Pick all the " + RandomFigure->GetFillClr().ReturnColor() + " figures. " + to_string(Target) + " exist.");
}

void PickByColorAction::GetClickedAction() {
	ChangedAction = false;
	EmptyClick = false;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	ActionType Act = pIn->GetAction(P);
	if (Act == TO_DRAW || (Act >= PICK_BY_COLOR && Act <= PICK_BY_SHAPE_COLOR) || Act == EXIT)
		ChangedAction = true;
	else {
		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);
		if (ClickedFigure == NULL || ClickedFigure->isHidden()) {
			EmptyClick = true;
			return;
		}
		else if (ClickedFigure->GetFillClr() == RandomFigure->GetFillClr()) {
			CorrectPicks++;
			pOut->PrintMessage("Correct.");
		}
		else pOut->PrintMessage("Incorrect.");
		ClickedFigure->Hide();
	}
}

bool PickByColorAction::Execute() {
	PlayMode::Execute();
	return true;
}