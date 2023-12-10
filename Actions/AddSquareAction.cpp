#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp): UndoableFigureAction(pApp)
{}
bool AddSquareAction::Validate() {
	int squareSize = CSquare::getSquareSize();
	return (center.y - squareSize / 2) > UI.ToolBarHeight && (center.y + squareSize / 2) <= (UI.height - UI.StatusBarHeight);
}

void AddSquareAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Square: Click at the center");
	pIn->GetPointClicked(center.x, center.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	SquareGfxInfo.isFilled = false;
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();
	SquareGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddSquareAction::Execute() {
	ReadActionParameters();
	if (Validate()) {
		//Create a square with the parameters read from the user
		figure = new CSquare(center, SquareGfxInfo);

		//Add the square to the list of figures
		pManager->AddFigure(figure);

		return true;
	}

	return false;
}