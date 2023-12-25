#include "PickByColorAction.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void PickByColorAction::StartingMessage() {		// Displays the starting message
	Output* pOut = pManager->GetOutput();
	Target = pManager->CountColor(RandomFigure->GetFillClr());
	pOut->PrintMessage("Pick all the " + RandomFigure->GetFillClr().ReturnColor() + " figures. " + to_string(Target) + " exist.");
}

bool PickByColorAction::Execute() {
	Mode = PICK_BY_COLOR;
	return PlayMode::Execute();
}