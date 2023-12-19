#include "AddTriangleAction.h"

#include "..\Figures\CTriangle.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriangleAction::AddTriangleAction(ApplicationManager* pApp): UndoableFigureAction(pApp) {
	P1.x = 0;
	P1.y = 200;
	P2.x = 0;
	P2.y = 200;
	P3.x = 0;
	P3.y = 200;
}
bool AddTriangleAction::Validate() {
	bool cond1 = P1.y >= UI.ToolBarHeight && P1.y <= (UI.height - UI.StatusBarHeight);
	bool cond2 = P2.y >= UI.ToolBarHeight && P2.y <= (UI.height - UI.StatusBarHeight);
	bool cond3 = P3.y >= UI.ToolBarHeight && P3.y <= (UI.height - UI.StatusBarHeight);
	return cond1 && cond2 && cond3;

}

void AddTriangleAction::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Triangle: Click at the first corner");
	pIn->GetPointClicked(P1.x, P1.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->PrintMessage("New Triangle: Click at the second corner");
	pIn->GetPointClicked(P2.x, P2.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->PrintMessage("New Triangle: Click at the third corner");
	pIn->GetPointClicked(P3.x, P3.y);
	if (!Validate()) {
		int x, y;
		pOut->PrintMessage("ERROR: Invalid Point Location. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();
	TriangleGfxInfo.isFilled = (TriangleGfxInfo.FillClr != TRANSPARENT_COLOR);
	TriangleGfxInfo.BorderWidth = pOut->getCurrentPenWidth();
	pOut->ClearStatusBar();
}

bool AddTriangleAction::Execute() {
	ReadActionParameters();
	if (Validate()) {
		// Create a triangle with the parameters read from the user
		Figure = new CTriangle(P1, P2, P3, TriangleGfxInfo);
		Figure->IncrementReference();

		//Add the triangle to the list of figures
		pManager->AddFigure(Figure);

		return true;
	}

	return false;
}

void AddTriangleAction::PlayRecord()
{
	Output* pOut = pManager->GetOutput();
	pManager->AddFigure(Figure);
	Figure->Draw(pOut);
}
