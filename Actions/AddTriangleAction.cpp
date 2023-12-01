#include "AddTriangleAction.h"

#include "..\Figures\CTriangle.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddTriangleAction::AddTriangleAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddTriangleAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Triangle: Click at the first corner");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->PrintMessage("New Triangle: Click at the second corner");
	pIn->GetPointClicked(P2.x, P2.y);
	pOut->PrintMessage("New Triangle: Click at the third corner");
	pIn->GetPointClicked(P3.x, P3.y);
	TriangleGfxInfo.isFilled = false;
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();
	TriangleGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

void AddTriangleAction::Execute() {
	ReadActionParameters();

	// Create a triangle with the parameters read from the user
	CTriangle* T = new CTriangle(P1,P2,P3, TriangleGfxInfo);

	//Add the triangle to the list of figures
	pManager->AddFigure(T);
}