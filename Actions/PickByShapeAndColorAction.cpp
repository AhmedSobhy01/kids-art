#include "PickByShapeAndColorAction.h"
#include "PlayMode.h"

PickByShapeAndColorAction::PickByShapeAndColorAction(ApplicationManager *pApp) : PlayMode(pApp)
{
	RecordEnabled = false;
}

void PickByShapeAndColorAction::StartingMessage() // Displays the starting message
{
	Output *pOut = pManager->GetOutput();
	Target = pManager->CountFigure(RandomFigure);
	pOut->PrintMessage("Pick all the " + RandomFigure->GetFillColor().ReturnColor() + " " + RandomFigure->Type() + "s. " + to_string(Target) + " exist.");
}

bool PickByShapeAndColorAction::Execute()
{
	Mode = PICK_BY_SHAPE_COLOR;
	return PlayMode::Execute();
}