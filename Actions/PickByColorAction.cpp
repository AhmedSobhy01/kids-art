#include "PickByColorAction.h"
#include "SwitchToDrawAction.h"
#include "PickByShapeAction.h"
#include "PickByShapeAndColorAction.h"

PickByColorAction::PickByColorAction(ApplicationManager* pApp): Action(pApp)
{ }

void PickByColorAction::ReadActionParameters() {												// Initializes the data members
	CorrectPicks = 0;
	Counter = 0;
	ChangedAction = false;
	RandomFigure = pManager->GetRandomFigure();
	RandomColor = RandomFigure->GetFillClr();
	RandomColorNumber = pManager->CountColor(RandomColor);
	SetColorName();
}

void PickByColorAction::SetColorName() {
	if (RandomColor == BLACK) RandomColorName = "Black";
	else if (RandomColor == RED) RandomColorName = "Red";
	else if (RandomColor == BLUE) RandomColorName = "Blue";
	else if (RandomColor == GREEN) RandomColorName = "Green";
	else if (RandomColor == MAGENTA) RandomColorName = "Magenta";
	else if (RandomColor == ORANGE) RandomColorName = "Orange";
	else if (RandomColor == BROWN) RandomColorName = "Brown";
	else if (RandomColor == CYAN) RandomColorName = "Cyan";
	else if (RandomColor == YELLOW) RandomColorName = "Yellow";
	else if (RandomColor == GOLD) RandomColorName = "Gold";
	else if (RandomColor == TRANSPARENT_COLOR) RandomColorName = "Transparent";
}

void PickByColorAction::StartingMessage() {
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Pick all the " + RandomColorName + " figures. " + to_string(RandomColorNumber) + " exist.");
}

void PickByColorAction::FinalMsg() {
	Output* pOut = pManager->GetOutput();
	if (Counter == CorrectPicks) pOut->PrintMessage("Congratulations! All your picks are correct! (" + to_string(CorrectPicks) + "/" + to_string(CorrectPicks) + ")");
	else pOut->PrintMessage("Game over. You made " + to_string(CorrectPicks) + " correct picks out of " + to_string(Counter) + " picks");
}

void PickByColorAction::GetAction()
{
	Output* pOut;
	SwitchToDrawAction* SwitchToDraw;
	PickByShapeAction* PickByShape;
	PickByShapeAndColorAction* PickShapeColor;
	if (P.y >= 0 && P.y < UI.ToolBarHeight) {
		int clickeditem = P.x / UI.MenuItemWidth;
		switch (clickeditem) {
		case ITM_DRAW_MODE:															// Switch to Draw mode
			SwitchToDraw = new SwitchToDrawAction(pManager);
			SwitchToDraw->Execute();
			pOut = pManager->GetOutput();
			pOut->PrintMessage("Game over. Switched to Draw Mode.");
			ChangedAction = true;
			delete SwitchToDraw;
			return;
		case ITM_PICKBYSHAPE:														// Switch to Pick By Shape mode
			pManager->ExecuteAction(PICK_BY_SHAPE);
			return;
		case ITM_PICKBYCOLOR:														// Switch to Pick By Color mode
			this->Execute();
			ChangedAction = true;
			return;
		case ITM_PICKBYSHAPEANDCOLOR:												// Switch to Pick By Shape & Color mode
			PickShapeColor = new PickByShapeAndColorAction(pManager);
			PickShapeColor->Execute();
			ChangedAction = true;
			delete PickShapeColor;
			return;
		}
	}
}

bool PickByColorAction::Execute() {
	pManager->UnhideFigures();
	pManager->UpdateInterface();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	FiguresNumber = pManager->FiguresCount();
	if (FiguresNumber == 0) {
		pOut->PrintMessage("Switch to Draw Mode and draw some shapes to play with.");
		return false;
	}
	ReadActionParameters();
	StartingMessage();

	while (CorrectPicks < RandomColorNumber && Counter != FiguresNumber) {
		pIn->GetPointClicked(P.x, P.y);

		CFigure* ClickedFigure = pManager->GetFigure(P.x, P.y);									// Get the clicked shape
		GetAction();
		if (ChangedAction) return false;

		if (ClickedFigure == NULL || ClickedFigure->isHidden()) continue;						// If theres no shape clicked or the shape is hidden
		else if (ClickedFigure->GetFillClr() == RandomColor) CorrectPicks++;					// Correct color is picked

		ClickedFigure->Hide();																	// Hiding every clicked shape
		pManager->UpdateInterface();
		Counter++;
	}
	FinalMsg();
	pManager->UnhideFigures();
	pManager->UpdateInterface();
	return true;
}
