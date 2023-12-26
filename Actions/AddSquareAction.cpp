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

	// Getting Coordinates for the shape position
	pOut->PrintMessage("New Square: Click at the Center");
	pIn->GetPointClicked(Center.x, Center.y);

	// Get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	SquareGfxInfo.FillColor = pOut->GetCurrentFillColor();
	SquareGfxInfo.IsFilled = (SquareGfxInfo.FillColor != TRANSPARENT_COLOR);
	SquareGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddSquareAction::Execute()
{
	ReadActionParameters();

	// Create a square with the parameters read from the user
	Figure = new CSquare(Center, SquareGfxInfo);
	Figure->IncrementReference();

	// Add the square to the list of figures
	pManager->AddFigure(Figure);

	return true;
}

void AddSquareAction::PlayRecord()
{
	Figure->SetCenter(Center);					// Reset Position to initial position
	Figure->ChangeFillColor(UI.FillColor);		// Reset Fill color to initial color
	Figure->ChangeDrawColor(UI.DrawColor);		// Reset Outline color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth);		// Reset Border Width to initial Width
	int Size = CSquare::GetDefaultSquareSize();
	Point P1;
	P1.x = Center.x + Size / 2;
	P1.y = Center.y + Size / 2;					//Calcuate the corner to set the size
	Figure->SetCorner(P1, 0);					//Sets the square to the default size
	pManager->AddFigure(Figure);				//Add the square to the figure list
}