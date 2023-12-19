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

bool ChangeBackgroundColorAction::Execute()
{
	ReadActionParameters();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	
	BkgndCol = pIn->GetSelectedColor(pOut);
	UI.BkGrndColor = BkgndCol;
	pOut->ClearStatusBar();

	return true;
}

void ChangeBackgroundColorAction::PlayRecord()
{
	UI.BkGrndColor = BkgndCol;
}
