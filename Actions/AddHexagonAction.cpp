#include "AddHexagonAction.h"
#include "..\Figures\CHexagon.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Figures\CHexagon.h"

AddHexagonAction::AddHexagonAction(ApplicationManager *pApp) : UndoableFigureAction(pApp)
{
}

void AddHexagonAction::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click at the center"); // Print a message to the user to get the center
	pIn->GetPointClicked(Center.x, Center.y);				// Get coordinate of the center

	// Get drawing, filling colors and pen width from the interface
	HexagonGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	HexagonGfxInfo.FillColor = pOut->GetCurrentFillColor();
	HexagonGfxInfo.IsFilled = (HexagonGfxInfo.FillColor != TRANSPARENT_COLOR);
	HexagonGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddHexagonAction::Execute()
{
	ReadActionParameters();

	Figure = new CHexagon(Center, HexagonGfxInfo); // Create a hexagon with the parameters read from the user
	Figure->IncrementReference();				   // Increment the reference count of the figure

	pManager->AddFigure(Figure); // Add the hexagon to the list of figures

	return true;
}

void AddHexagonAction::PlayRecord()
{
	Figure->SetCenter(Center);					  // Reset position to initial position
	Figure->ChangeFillColor(UI.FillColor);		  // Reset fill color to initial color
	Figure->ChangeDrawColor(UI.DrawColor);		  // Reset outline color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth);		  // Reset border width to initial width
	int Size = CHexagon::GetDefaultHexagonSize(); // Get the default size of the hexagon

	Point P1;
	P1.x = Center.x + Size; // Calcuate the corner to set the size
	P1.y = Center.y;		// Calcuate the corner to set the size

	Figure->SetCorner(P1, 0);	 // Sets the hexagon to the default size
	pManager->AddFigure(Figure); // Add the hexagon to the figure list
}