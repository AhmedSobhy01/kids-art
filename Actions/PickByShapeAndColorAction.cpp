#include "PickByShapeAndColorAction.h"

PickByShapeAndColorAction::PickByShapeAndColorAction(ApplicationManager* pApp) : PlayMode(pApp)
{
	Mode = PICK_BY_SHAPE_COLOR;
}

void PickByShapeAndColorAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	Target = pManager->CountFigure(RandomFigure);
	pOut->PrintMessage("Pick all the " + RandomFigure->GetFillClr().ReturnColor() +" " + RandomFigure->Type() + "s. " + to_string(Target) + " exist.");
}

bool PickByShapeAndColorAction::Execute() {
	return PlayMode::Execute();
}