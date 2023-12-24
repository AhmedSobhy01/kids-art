#include "AddTriangleAction.h"

#include "..\Figures\CTriangle.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriangleAction::AddTriangleAction(ApplicationManager* pApp) : UndoableFigureAction(pApp) {
}


void AddTriangleAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Getting Coordinates for the shape position
	pOut->PrintMessage("New Triangle: Click at the first corner");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->PrintMessage("New Triangle: Click at the second corner");
	pIn->GetPointClicked(P2.x, P2.y);
	pOut->PrintMessage("New Triangle: Click at the third corner");
	pIn->GetPointClicked(P3.x, P3.y);

	//Get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pOut->GetCurrentDrawColor();
	TriangleGfxInfo.FillClr = pOut->GetCurrentFillColor();
	TriangleGfxInfo.isFilled = (TriangleGfxInfo.FillClr != TRANSPARENT_COLOR);
	TriangleGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddTriangleAction::Execute() {
	ReadActionParameters();
	// Create a triangle with the parameters read from the user
	Figure = new CTriangle(P1, P2, P3, TriangleGfxInfo);
	Figure->IncrementReference();

	//Add the triangle to the list of figures
	pManager->AddFigure(Figure);

	return true;

}

void AddTriangleAction::PlayRecord()
{
	Point center = { (P1.x + P2.x + P3.x) / 3,(P1.y + P2.y + P3.y) / 3 };
	Figure->SetCenter(center);
	Figure->ChngFillClr(UI.FillColor);
	Figure->ChngDrawClr(UI.DrawColor);
	Figure->ChngBorderWidth(UI.PenWidth);
	pManager->AddFigure(Figure);
}
