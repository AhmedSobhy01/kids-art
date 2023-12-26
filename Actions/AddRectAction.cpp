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

	// Getting Coordinates for the shape position
	pOut->PrintMessage("New Rectangle: Click at first corner");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->PrintMessage("New Rectangle: Click at second corner");
	pIn->GetPointClicked(P2.x, P2.y);

	// Get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	RectGfxInfo.FillColor = pOut->GetCurrentFillColor();
	RectGfxInfo.IsFilled = (RectGfxInfo.FillColor != TRANSPARENT_COLOR);
	RectGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();

	pOut->ClearStatusBar();
}

bool AddRectAction::Execute()
{
	ReadActionParameters();

	// Create a rectangle with the parameters read from the user
	Figure = new CRectangle(P1, P2, RectGfxInfo);
	Figure->IncrementReference();

	// Add the rectangle to the list of figures
	pManager->AddFigure(Figure);
	return true;
}

void AddRectAction::PlayRecord()
{

	//Note: Here we don't need to set the center of the rectangle
	//as the two corners is being set
	Figure->ChangeFillColor(UI.FillColor);	// Reset Position to initial position
	Figure->ChangeDrawColor(UI.DrawColor);	// Reset Fill color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth);	// Reset Outline color to initial color
	Figure->SetCorner(P1, 0);				// Reset Border Width to initial Width
	Figure->SetCorner(P2, 3);				// Reset Size to initial Size
	pManager->AddFigure(Figure);			// Add the rectangle to the figure list
}
