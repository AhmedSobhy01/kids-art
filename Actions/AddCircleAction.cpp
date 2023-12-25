#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircleAction::AddCircleAction(ApplicationManager* pApp) : UndoableFigureAction(pApp)
{
}

void AddCircleAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Getting Coordinates for the shape position
	pOut->PrintMessage("New Circle: Click at the center");
	pIn->GetPointClicked(Center.x, Center.y);
	pOut->PrintMessage("New Circle: Click at the radius");
	pIn->GetPointClicked(Radius.x, Radius.y);

	//Get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pOut->GetCurrentDrawColor(); 
	CircleGfxInfo.FillClr = pOut->GetCurrentFillColor(); 
	CircleGfxInfo.IsFilled = (CircleGfxInfo.FillClr != TRANSPARENT_COLOR); 
	CircleGfxInfo.BorderWidth = pOut->GetCurrentPenWidth(); 
	pOut->ClearStatusBar();
}

bool AddCircleAction::Execute() {
	ReadActionParameters();

	//Create a circle with the parameters read from the user
	Figure = new CCircle(Center, Radius, CircleGfxInfo);
	Figure->IncrementReference();

	//Add the circle to the list of figures
	pManager->AddFigure(Figure);
	return true;
}

void AddCircleAction::PlayRecord()
{
	Figure->SetCenter(center);
	Figure->ChngFillClr(UI.FillColor);
	Figure->ChngDrawClr(UI.DrawColor);
	Figure->ChngBorderWidth(UI.PenWidth);
	Figure->SetCorner(radius, 0);
	pManager->AddFigure(Figure);
}