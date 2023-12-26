#include "AddTriangleAction.h"
#include "..\Figures\CTriangle.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

AddTriangleAction::AddTriangleAction(ApplicationManager *pApp) : UndoableFigureAction(pApp)
{
}

void AddTriangleAction::ReadActionParameters()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();

	// Getting Coordinates for the shape position
	pOut->PrintMessage("New Triangle: Click at the first point");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->PrintMessage("New Triangle: Click at the second point");
	pIn->GetPointClicked(P2.x, P2.y);
	pOut->PrintMessage("New Triangle: Click at the third point");
	pIn->GetPointClicked(P3.x, P3.y);

	// Get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawColor = pOut->GetCurrentDrawColor();
	TriangleGfxInfo.FillColor = pOut->GetCurrentFillColor();
	TriangleGfxInfo.IsFilled = (TriangleGfxInfo.FillColor != TRANSPARENT_COLOR);
	TriangleGfxInfo.BorderWidth = pOut->GetCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddTriangleAction::Execute()
{
	ReadActionParameters();
	// Create a triangle with the parameters read from the user
	Figure = new CTriangle(P1, P2, P3, TriangleGfxInfo);
	Figure->IncrementReference();

	// Add the triangle to the list of figures
	pManager->AddFigure(Figure);

	return true;
}

void AddTriangleAction::PlayRecord()
{
	Figure->ChangeFillColor(UI.FillColor);
	Figure->ChangeDrawColor(UI.DrawColor);
	Figure->ChangeBorderWidth(UI.PenWidth);
	Figure->SetCorner(P1, 0);
	Figure->SetCorner(P2, 1);
	Figure->SetCorner(P3, 2);
	pManager->AddFigure(Figure);
}
