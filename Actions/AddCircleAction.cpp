#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include<windows.h>

AddCircleAction::AddCircleAction(ApplicationManager* pApp): UndoableFigureAction(pApp)
{
	center.x = 0;
	center.y = 200;
	radius.x = 0;
	radius.y = 200;
}
bool AddCircleAction::Validate() {
	int radius = sqrt(pow(center.x - this->radius.x, 2) + pow(center.y - this->radius.y, 2));

	return (center.y - radius) >= UI.ToolBarHeight && (center.y + radius) <= (UI.height - UI.StatusBarHeight);
}

void AddCircleAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Circle: Click at the center");
	pIn->GetPointClicked(center.x, center.y);
	pOut->PrintMessage("New Circle: //TODO: add a messege here :)");
	pIn->GetPointClicked(radius.x, radius.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();
	CircleGfxInfo.isFilled = (CircleGfxInfo.FillClr != TRANSPARENT_COLOR);
	CircleGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddCircleAction::Execute() {
	ReadActionParameters();
	if (Validate()) {
		//Create a circle with the parameters read from the user
		figure = new CCircle(center, radius, CircleGfxInfo);

		//Add the circle to the list of figures
		pManager->AddFigure(figure);

		PlayActionSound();

		return true;
	}

	return false;
}

void AddCircleAction::PlayActionSound() const
{
	if (pManager->ShouldPlayActionSound())
		PlaySound("sounds\\Circle.wav", NULL, SND_FILENAME | SND_ASYNC);
}
