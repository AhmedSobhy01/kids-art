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

	// Getting Coordinates for the shape position
	pOut->PrintMessage("New Hexagon: Click at the center");
	pIn->GetPointClicked(Center.x, Center.y);

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

	// Create a hexagon with the parameters read from the user
	Figure = new CHexagon(Center, HexagonGfxInfo);
	Figure->IncrementReference();

	// Add the hexagon to the list of figures
	pManager->AddFigure(Figure);
	return true;
}

void AddHexagonAction::PlayRecord()
{
	Figure->SetCenter(Center);						// Reset Position to initial position
	Figure->ChangeFillColor(UI.FillColor);			// Reset Fill color to initial color
	Figure->ChangeDrawColor(UI.DrawColor);			// Reset Outline color to initial color
	Figure->ChangeBorderWidth(UI.PenWidth);			// Reset Border Width to initial Width
	int Size = CHexagon::GetDefaultHexagonSize();
	Point P1;			
	P1.x = Center.x + Size;
	P1.y = Center.y;								//Calcuate the corner to set the size
	Figure->SetCorner(P1, 0);						//Sets the hexagon to the default size
	pManager->AddFigure(Figure);					//Add the hexagon to the figure list
}