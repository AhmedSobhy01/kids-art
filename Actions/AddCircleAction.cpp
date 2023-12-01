#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircleAction::AddCircleAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddCircleAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Circle: Click at the center");
	pIn->GetPointClicked(center.x, center.y);
	pOut->PrintMessage("New Circle: //TODO: add a messege here :)");
	pIn->GetPointClicked(radius.x, radius.y);
	CircleGfxInfo.isFilled = false;
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();
	CircleGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

void AddCircleAction::Execute() {
	ReadActionParameters();

	//Create a circle with the parameters read from the user
	CCircle* C = new CCircle(center, radius,CircleGfxInfo);

	//Add the circle to the list of figures
	pManager->AddFigure(C);
}