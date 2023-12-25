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
	RectGfxInfo.DrawClr = pOut->GetCurrentDrawColor();
	RectGfxInfo.FillClr = pOut->GetCurrentFillColor();
	RectGfxInfo.isFilled = (RectGfxInfo.FillClr != TRANSPARENT_COLOR);
	RectGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();

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
	Figure->ChngFillClr(UI.FillColor);
	Figure->ChngDrawClr(UI.DrawColor);
	Figure->ChngBorderWidth(UI.PenWidth);
	Figure->SetCorner(P1, 0);
	Figure->SetCorner(P2, 3);
	pManager->AddFigure(Figure);
}
