#include "ChangeBackgroundColorAction.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"

ChangeBackgroundColorAction::ChangeBackgroundColorAction(ApplicationManager* pApp) :Action(pApp) {}

void ChangeBackgroundColorAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->OpenColorMenuWind(ITM_BACKGROUND_COLOR * UI.ColorMenuItemWidth);
	pOut->PrintMessage("Change Background Color: Select a color.");
}

void ChangeBackgroundColorAction::Execute()
{
	ReadActionParameters();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	UI.BkGrndColor = pIn->GetSelectedColor(pOut);
	pOut->ClearStatusBar();
}