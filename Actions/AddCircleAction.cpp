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

	pOut->PrintMessage("New Circle: Click at the center"); // Print a message to the user to get the center
	pIn->GetPointClicked(Center.x, Center.y);			   // Get center point of the circle

	pOut->PrintMessage("New Circle: Click at the radius"); // Print a message to the user to get the radius
	pIn->GetPointClicked(Radius.x, Radius.y);			   // Get radius point of the circle

	// Get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	CircleGfxInfo.FillColor = pOut->GetCurrentFillColor();
	CircleGfxInfo.IsFilled = (CircleGfxInfo.FillColor != TRANSPARENT_COLOR);
	CircleGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();

	pOut->ClearStatusBar(); // Clear the status bar
}

bool AddCircleAction::Execute()
{
	ReadActionParameters();

	Figure = new CCircle(Center, Radius, CircleGfxInfo); // Create a circle with the parameters read from the user
	Figure->IncrementReference();						 // Increment the reference count of the figure

	pManager->AddFigure(Figure); // Add the circle to the list of figures

	return true;
}

void AddCircleAction::PlayRecord()
{
	Figure->SetCenter(Center);				// Reset center to initial Center
	Figure->ChangeFillColor(UI.FillColor);	// Reset fill color to initial color
	Figure->ChangeDrawColor(UI.DrawColor);	// Reset draw color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth); // Reset border width to initial width
	Figure->SetCorner(Radius, 0);			// Reset radius to initial radius
	pManager->AddFigure(Figure);			// Add the figure to the list of figures
}