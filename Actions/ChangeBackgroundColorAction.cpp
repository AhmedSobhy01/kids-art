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

	OldColor = UI.BackgroundColor;
	NewColor = pIn->GetSelectedColor(pOut) - 5;
	UI.BackgroundColor = NewColor;
	pOut->ClearStatusBar();

	return true;
}

void ChangeBackgroundColorAction::PlayRecord()
{
	UI.BackgroundColor = NewColor;
}

void ChangeBackgroundColorAction::Undo()
{
	UI.BackgroundColor = OldColor;
}

void ChangeBackgroundColorAction::Redo()
{
	UI.BackgroundColor = NewColor;
}