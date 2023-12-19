#include "ClearAllAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "UndoableAction.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp) :Action(pApp) {

}

void ClearAllAction::ReadActionParameters() {

}

bool ClearAllAction::Execute() {
	//pManager->ClearUndoableActionsStack();
	//pManager->ClearRedoableActionsStack();
	pManager->SetRecordingState(false);
	pManager->ResetColors();
	//pManager->ClearFigures();
	pManager->GetOutput()->ClearStatusBar();

	return true;
}

bool ClearAllAction::ShouldRecord() const
{
	return false;
}
