#include "ClearAllAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "UndoableAction.h"
#include "..\Figures\CFigure.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp) :Action(pApp) {

}

void ClearAllAction::ReadActionParameters() {

}

bool ClearAllAction::Execute() {
	pManager->ClearUndoableActionsStack();
	pManager->ClearRedoableActionsStack();
	pManager->ClearRecordedActionsList();
	pManager->SetRecordingState(false);
	pManager->ResetColors();
	pManager->ClearFigures();
	pManager->GetOutput()->ClearStatusBar();
	CFigure::ResetID();

	return true;
}

bool ClearAllAction::ShouldRecord() const
{
	return false;
}
