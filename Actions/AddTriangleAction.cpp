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
	//Note: Here we don't need to set the center of the triangle
	//as the three verticies is being set
	Figure->ChangeFillColor(UI.FillColor);	// Reset Fill color to initial color
	Figure->ChangeDrawColor(UI.DrawColor);	// Reset Outline color to initial color	
	Figure->ChangeBorderWidth(UI.PenWidth); // Reset Border Width to initial Width
	Figure->SetCorner(P1, 0);				//Sets the first vertex
	Figure->SetCorner(P2, 1);				//Sets the second vertex
	Figure->SetCorner(P3, 2);				//Sets the third vertex
	pManager->AddFigure(Figure);			//Add the triangle to the figure list
}
