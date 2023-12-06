#include "PickByShapeAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Output.h"

PickByShapeAction::PickByShapeAction(ApplicationManager* pApp) : Action(pApp) {

}
void PickByShapeAction::ReadActionParameters() {
	FiguresNumber = pManager->FiguresCount();
	RandomFigure = pManager->GetRandomFigure();
	CorrectPicks = 0;
	Counter = 0;
}

string PickByShapeAction::GetFigureName(ShapeType stype) {							// Returns the shape type (to be used in PrintMessage function)
	switch (stype) {
	case CIRCLE:
		return "Circles, ";
	case SQUARE:
		return "Squares, ";
	case TRIANGLE:
		return "Triangles, ";
	case HEXAGON:
		return "Hexagons, ";
	case RECTANGLE:
		return "Rectangles, ";
	}
}
void PickByShapeAction::PrintMessage(CFigure* randomfigure) {						// Prints a message according to the random asked shape
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + GetFigureName(randomfigure->Type()) + to_string(pManager->CountFigure(randomfigure)) + " exist");
}
void PickByShapeAction::Execute() {

	///Generate random figure and count it///
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	RandomFigureNumber = pManager->CountFigure(RandomFigure);

	PrintMessage(RandomFigure);

	////				Main Loop				////
	while (CorrectPicks < RandomFigureNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);
		CFigure* ClickedShape = pManager->GetFigure(P.x, P.y);						// Get the clicked shape

		if (ClickedShape == NULL || ClickedShape->isHidden()) continue;				// If the there's no clicked shape or the clicked shape is already hidden
		else if (ClickedShape->Type() == RandomFigure->Type()) CorrectPicks++;		// Correct Shape picked

		ClickedShape->Hide();														// Hiding any clicked shape
		pManager->UpdateInterface();
		Counter++;
	}
	if (Counter == CorrectPicks)pOut->PrintMessage("You won and picked all the shapes correctly!");
		else pOut->PrintMessage("Game over. Correct picks are " + to_string(CorrectPicks) + " out of " + to_string(Counter) + " picks.");
		pManager->UnHideFigures();
		pManager->UpdateInterface();
}
