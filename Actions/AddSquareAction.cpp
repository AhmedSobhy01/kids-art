#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddSquareAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Square: Click at the center");
	pIn->GetPointClicked(center.x, center.y);
	SquareGfxInfo.isFilled = false;
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();
	SquareGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

void AddSquareAction::Execute() {
	ReadActionParameters();

	//Create a square with the parameters read from the user
	CSquare* S = new CSquare(center, SquareGfxInfo);

	//Add the square to the list of figures
	pManager->AddFigure(S);
}