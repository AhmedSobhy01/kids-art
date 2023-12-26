#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CSquare.h"

AddSquareAction::AddSquareAction(ApplicationManager *pApp) : UndoableFigureAction(pApp)
{
}

void AddSquareAction::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();

	// Getting coordinates for the shape position
	pOut->PrintMessage("New Square: Click at the Center");
	pIn->GetPointClicked(Center.x, Center.y);

	// Get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	SquareGfxInfo.FillColor = pOut->GetCurrentFillColor();
	SquareGfxInfo.IsFilled = (SquareGfxInfo.FillColor != TRANSPARENT_COLOR);
	SquareGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();

	pOut->ClearStatusBar(); // Clear the status bar
}

bool AddSquareAction::Execute()
{
	ReadActionParameters();

	Figure = new CSquare(Center, SquareGfxInfo); // Create a square with the parameters read from the user
	Figure->IncrementReference();				 // Increment the reference count of the figure

	// Add the square to the list of figures
	pManager->AddFigure(Figure);

	return true;
}

void AddSquareAction::PlayRecord()
{
	Figure->SetCenter(Center);					// Reset position to initial position
	Figure->ChangeFillColor(UI.FillColor);		// Reset fill color to initial color
	Figure->ChangeDrawColor(UI.DrawColor);		// Reset outline color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth);		// Reset border width to initial Width
	int Size = CSquare::GetDefaultSquareSize(); // Get the default size of the square

	Point P1;
	P1.x = Center.x + Size / 2;	 // Calcuate the corner to set the size
	P1.y = Center.y + Size / 2;	 // Calcuate the corner to set the size
	Figure->SetCorner(P1, 0);	 // Sets the square to the default size
	pManager->AddFigure(Figure); // Add the square to the figure list
}