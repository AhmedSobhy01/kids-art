#include "MoveAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

MoveAction::MoveAction(ApplicationManager* pApp): UndoableAction(pApp) {}

void MoveAction::ReadActionParameters(){
	CFigure* F = pManager->GetSelected();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (F == NULL) {
		int x, y;
		pOut->PrintMessage("Error:Select a shape before moving. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	pOut->PrintMessage("Move: Click on a new point to move.");
	pIn->GetPointClicked(NewCenter.x, NewCenter.y);
	if (F->Validate(NewCenter)) {
		pOut->ClearStatusBar();
	}
	else {
		int x, y;
		pOut->PrintMessage("Error:Invalid center position. Click anywhere to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
}
bool MoveAction::Execute(){
	ReadActionParameters();
	Figure = pManager->GetSelected();
	
	if (Figure != NULL) {
		bool r = false;

		if (Figure->Validate(NewCenter)) {
			OldCenter = Figure->GetCenter();
			Figure->SetCenter(NewCenter);
			r = true;
		}
		Figure->SetSelected(false);
		pManager->SetSelected(NULL);

		return r;
	}

	return false;
}

void MoveAction::Undo()
{
	if (Figure)
		Figure->SetCenter(OldCenter);
}

void MoveAction::Redo()
{
	if (Figure)
		Figure->SetCenter(NewCenter);
}

MoveAction::~MoveAction()
{
	if (Figure)
		delete Figure;
}
