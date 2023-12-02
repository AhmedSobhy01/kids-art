#include "AddHexagonAction.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddHexagonAction::AddHexagonAction(ApplicationManager* pApp) :Action(pApp)
{
	center.x = 0;
	center.y = 200;
}
bool AddHexagonAction::Validate() {
	int hexagonSize = CHexagon::getHexagonSize();

	return (center.y - hexagonSize / 2 * sqrt(3)) > UI.ToolBarHeight && (center.y + hexagonSize / 2 * sqrt(3)) <= (UI.height - UI.StatusBarHeight);
}

void AddHexagonAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Hexagon: Click at the center");
	pIn->GetPointClicked(center.x, center.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	HexagonGfxInfo.isFilled = false;
	HexagonGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexagonGfxInfo.FillClr = pOut->getCrntFillColor();
	HexagonGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

void AddHexagonAction::Execute() {
	ReadActionParameters();
	if (Validate()) {
		//Create a hexagon with the parameters read from the user
		CHexagon* H = new CHexagon(center, HexagonGfxInfo);

		//Add the hexagon to the list of figures
		pManager->AddFigure(H);
	}
}