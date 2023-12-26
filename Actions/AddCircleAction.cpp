#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

AddCircleAction::AddCircleAction(ApplicationManager *pApp) : UndoableFigureAction(pApp)
{
}

void AddCircleAction::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();

	// Getting Coordinates for the shape position
	pOut->PrintMessage("New Circle: Click at the center");
	pIn->GetPointClicked(Center.x, Center.y);
	pOut->PrintMessage("New Circle: Click at the radius");
	pIn->GetPointClicked(Radius.x, Radius.y);

	// Get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	CircleGfxInfo.FillColor = pOut->GetCurrentFillColor();
	CircleGfxInfo.IsFilled = (CircleGfxInfo.FillColor != TRANSPARENT_COLOR);
	CircleGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddCircleAction::Execute()
{
	ReadActionParameters();

	// Create a circle with the parameters read from the user
	Figure = new CCircle(Center, Radius, CircleGfxInfo);
	Figure->IncrementReference();

	// Add the circle to the list of figures
	pManager->AddFigure(Figure);
	return true;
}

void AddCircleAction::PlayRecord()
{
	Figure->SetCenter(Center);				// Reset Position to initial position
	Figure->ChangeFillColor(UI.FillColor);	// Reset Fill color to initial color
	Figure->ChangeDrawColor(UI.DrawColor);	// Reset Outline color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth);	// Reset Border Width to initial Width
	Figure->SetCorner(Radius, 0);			// Reset Size to initial Size
	pManager->AddFigure(Figure);			// Add the circle to the figure list
}