#include "PickByShapeAction.h"

PickByShapeAction::PickByShapeAction(ApplicationManager* pApp) : PlayMode(pApp)
{
	Mode = PICK_BY_SHAPE;
}

void PickByShapeAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	Target = pManager->CountFigure(RandomFigure);
	pOut->PrintMessage("Pick all the " + RandomFigure->Type() + "s. " + to_string(Target) + " exist.");
}

bool PickByShapeAction::Execute() {
	PlayMode::Execute();
	return true;
}