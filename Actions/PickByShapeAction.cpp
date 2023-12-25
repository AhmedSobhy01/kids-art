#include "PickByShapeAction.h"

PickByShapeAction::PickByShapeAction(ApplicationManager* pApp) : PlayMode(pApp)
{
	RecordEnabled = false;
}

void PickByShapeAction::StartingMessage() {			// Displays the starting message
	Output* pOut = pManager->GetOutput();
	Target = pManager->CountFigure(RandomFigure);
	pOut->PrintMessage("Pick all the " + RandomFigure->Type() + "s. " + to_string(Target) + " exist.");
}

bool PickByShapeAction::Execute() {
	Mode = PICK_BY_SHAPE;
	return PlayMode::Execute();
}