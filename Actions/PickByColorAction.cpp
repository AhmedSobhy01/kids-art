#include "PickByColorAction.h"

PickByColorAction::PickByColorAction(ApplicationManager *pApp) : PlayMode(pApp)
{
	RecordEnabled = false;
}

void PickByColorAction::StartingMessage()
{ // Displays the starting message
	Output *pOut = pManager->GetOutput();
	Target = pManager->CountColor(RandomFigure->GetFillColor());
	pOut->PrintMessage("Pick all the " + RandomFigure->GetFillColor().ReturnColor() + " figures. " + to_string(Target) + " exist.");
}

bool PickByColorAction::Execute()
{
	Mode = PICK_BY_COLOR;
	return PlayMode::Execute();
}