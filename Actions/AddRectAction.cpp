#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager* pApp): UndoableFigureAction(pApp)
{
	P1.x = 0;
	P1.y = 200;
	P2.x = 0;
	P2.y = 200;
}

bool AddRectAction::Validate() {
	return P1.y >= UI.ToolBarHeight && P2.y >= UI.ToolBarHeight && P1.y <= (UI.height - UI.StatusBarHeight) && P2.y <= (UI.height - UI.StatusBarHeight);
}

void AddRectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	};

	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	};


	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.isFilled = (RectGfxInfo.FillClr != TRANSPARENT_COLOR);
	RectGfxInfo.BorderWidth = pOut->getCurrentPenWidth();

	pOut->ClearStatusBar();

}

//Execute the action
bool AddRectAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	if (Validate()) {
		//Create a rectangle with the parameters read from the user
		Figure = new CRectangle(P1, P2, RectGfxInfo);
		Figure->IncrementReference();

		//Add the rectangle to the list of figures
		pManager->AddFigure(Figure);

		return true;
	}

	return false;
}

void AddRectAction::PlayRecord()
{
	Point center = { (P1.x + P2.x) / 2,(P1.y + P2.y) / 2 };
	Figure->SetCenter(center);
	Figure->ChngFillClr(UI.FillColor);
	Figure->ChngDrawClr(UI.DrawColor);
	pManager->AddFigure(Figure);
}
