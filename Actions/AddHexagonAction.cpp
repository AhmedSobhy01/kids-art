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
	Figure->SetCenter(Center);
	Figure->ChangeFillColor(UI.FillColor);
	Figure->ChangeDrawColor(UI.DrawColor);
	Figure->ChangeBorderWidth(UI.PenWidth);
	int Size = CHexagon::GetDefaultHexagonSize();
	Point P1;
	P1.x = Center.x + Size;
	P1.y = Center.y;
	Figure->SetCorner(P1, 0);
	pManager->AddFigure(Figure);
}