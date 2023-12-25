#include "ChangeBackgroundColorAction.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"

ChangeBackgroundColorAction::ChangeBackgroundColorAction(ApplicationManager* pApp) :UndoableAction(pApp) {}

void ChangeBackgroundColorAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->OpenColorMenuWind(ITM_BACKGROUND_COLOR * UI.ColorMenuItemWidth, false);
	pOut->PrintMessage("Change Background Color: Select a color.");
}

bool ChangeBackgroundColorAction::Execute()
{
	ReadActionParameters();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	OldColor = UI.BkGrndColor;
	NewColor = pIn->GetSelectedColor(pOut);
	UI.BkGrndColor = NewColor;
	pOut->ClearStatusBar();

	return true;
}

void ChangeBackgroundColorAction::PlayRecord()
{
	UI.BkGrndColor = NewColor;
}

void ChangeBackgroundColorAction::Undo()
{
	UI.BkGrndColor = OldColor;
}

void ChangeBackgroundColorAction::Redo()
{
	UI.BkGrndColor = NewColor;
}