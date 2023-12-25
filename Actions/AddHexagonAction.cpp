#include "AddHexagonAction.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddHexagonAction::AddHexagonAction(ApplicationManager* pApp) : UndoableFigureAction(pApp)
{

}


void AddHexagonAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Getting Coordinates for the shape position
	pOut->PrintMessage("New Hexagon: Click at the center");
	pIn->GetPointClicked(Center.x, Center.y);

	//Get drawing, filling colors and pen width from the interface
	HexagonGfxInfo.DrawClr = pOut->GetCurrentDrawColor();
	HexagonGfxInfo.FillClr = pOut->GetCurrentFillColor();
	HexagonGfxInfo.IsFilled = (HexagonGfxInfo.FillClr != TRANSPARENT_COLOR);
	HexagonGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddHexagonAction::Execute() {
	ReadActionParameters();

	//Create a hexagon with the parameters read from the user
	Figure = new CHexagon(Center, HexagonGfxInfo);
	Figure->IncrementReference();

	//Add the hexagon to the list of figures
	pManager->AddFigure(Figure);
	return true;
}

void AddHexagonAction::PlayRecord()
{
	Figure->SetCenter(Center);
	Figure->ChangeFillColor(UI.FillColor);
	Figure->ChangeDrawColor(UI.DrawColor);
	pManager->AddFigure(Figure);
}