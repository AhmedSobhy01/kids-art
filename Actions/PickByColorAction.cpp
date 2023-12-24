#include "PickByColorAction.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp): PlayMode(pApp)
{
	Mode = PICK_BY_COLOR;
}

void PickByColorAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	Target = pManager->CountColor(RandomFigure->GetFillClr());
	pOut->PrintMessage("Pick all the " + RandomFigure->GetFillClr().ReturnColor() + " figures. " + to_string(Target) + " exist.");
}

bool PickByColorAction::Execute() {
	PlayMode::Execute();
	return true;
}