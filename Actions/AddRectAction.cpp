#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager* pApp) : UndoableFigureAction(pApp)
{
}

void AddRectAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Getting Coordinates for the shape position
	pOut->PrintMessage("New Rectangle: Click at first corner");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->PrintMessage("New Rectangle: Click at second corner");
	pIn->GetPointClicked(P2.x, P2.y);

	//Get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.isFilled = (RectGfxInfo.FillClr != TRANSPARENT_COLOR);
	RectGfxInfo.BorderWidth = pOut->getCurrentPenWidth();

	pOut->ClearStatusBar();

}

bool AddRectAction::Execute()
{
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	Figure = new CRectangle(P1, P2, RectGfxInfo);
	Figure->IncrementReference();

	//Add the rectangle to the list of figures
	pManager->AddFigure(Figure);
	return true;
}

void AddRectAction::PlayRecord()
{
	Point center = { (P1.x + P2.x) / 2,(P1.y + P2.y) / 2 };
	Figure->SetCenter(center);
	Figure->ChngFillClr(UI.FillColor);
	Figure->ChngDrawClr(UI.DrawColor);
	pManager->AddFigure(Figure);
}
