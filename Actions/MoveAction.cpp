#include "MoveAction.h"
#include "..\ApplicationManager.h"
#include "..\Figures\CFigure.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

MoveAction::MoveAction(ApplicationManager* pApp) : UndoableAction(pApp) {}

void MoveAction::ReadActionParameters() {
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
	pOut->ClearStatusBar();
}
bool MoveAction::Execute() {
	ReadActionParameters();
	Figure = pManager->GetSelected();
	if (Figure == NULL)return false;
	Figure->IncrementReference();

	OldCenter = Figure->GetCenter();
	Figure->SetCenter(NewCenter);
	Figure->SetSelected(false);
	pManager->SetSelected(NULL);
	return true;
}

void MoveAction::PlayRecord()
{
	if (Figure != NULL)
		Figure->SetCenter(NewCenter);
}

void MoveAction::Undo()
{
	if (Figure != NULL)
		Figure->SetCenter(OldCenter);
}

void MoveAction::Redo()
{
	if (Figure != NULL)
		Figure->SetCenter(NewCenter);
}

MoveAction::~MoveAction()
{
	if (Figure != NULL) {
		Figure->DecrementReference();

		if (Figure->CanBeDeleted())
			delete Figure;

		Figure = NULL;
	}
}