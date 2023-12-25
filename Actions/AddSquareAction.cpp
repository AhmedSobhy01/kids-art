#include "AddSquareAction.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddSquareAction::AddSquareAction(ApplicationManager *pApp) : UndoableFigureAction(pApp)
{
}

void AddSquareAction::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();

	// Getting Coordinates for the shape position
	pOut->PrintMessage("New Square: Click at the center");
	pIn->GetPointClicked(Center.x, Center.y);

	// Get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->GetCurrentDrawColor();
	SquareGfxInfo.FillClr = pOut->GetCurrentFillColor();
	SquareGfxInfo.IsFilled = (SquareGfxInfo.FillClr != TRANSPARENT_COLOR);
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
	Figure->SetCenter(Center);
	Figure->ChangeFillColor(UI.FillColor);
	Figure->ChangeDrawColor(UI.DrawColor);
	pManager->AddFigure(Figure);
}