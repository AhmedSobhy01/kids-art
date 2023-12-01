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
	pOut->PrintMessage("New Square: Click at center");
	pIn->GetPointClicked(center.x, center.y);
	SquareGfxInfo.isFilled = false;
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();
	SquareGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

void AddSquareAction::Execute() {
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	CSquare* R = new CSquare(center, SquareGfxInfo);

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
}