#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager *pApp) : UndoableFigureAction(pApp)
{
}

void AddRectAction::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner"); // Print a message to the user to get the first corner
	pIn->GetPointClicked(P1.x, P1.y);							// Get coordinate of the first corner

	pOut->PrintMessage("New Rectangle: Click at second corner"); // Print a message to the user to get the second corner
	pIn->GetPointClicked(P2.x, P2.y);							 // Get coordinate of the second corner

	// Get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	RectGfxInfo.FillColor = pOut->GetCurrentFillColor();
	RectGfxInfo.IsFilled = (RectGfxInfo.FillColor != TRANSPARENT_COLOR);
	RectGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();

	pOut->ClearStatusBar(); // Clear the status bar
}

bool AddRectAction::Execute()
{
	ReadActionParameters();

	Figure = new CRectangle(P1, P2, RectGfxInfo); // Create a rectangle with the parameters read from the user
	Figure->IncrementReference();				  // Increment the reference count of the figure

	pManager->AddFigure(Figure); // Add the rectangle to the list of figures
	return true;
}

void AddRectAction::PlayRecord()
{
	// Note: Here we don't need to set the center of the rectangle
	// as the two corners is being set
	Figure->ChangeFillColor(UI.FillColor);	// Reset position to initial position
	Figure->ChangeDrawColor(UI.DrawColor);	// Reset fill color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth); // Reset outline color to initial color
	Figure->SetCorner(P1, 0);				// Reset border width to initial Width
	Figure->SetCorner(P2, 3);				// Reset size to initial Size
	pManager->AddFigure(Figure);			// Add the rectangle to the figure list
}
