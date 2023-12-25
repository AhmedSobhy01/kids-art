#include "ClearAllAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "UndoableAction.h"
#include "..\Figures\CFigure.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp): Action(pApp)
{
}

void ClearAllAction::ReadActionParameters() {

}

bool ClearAllAction::Execute() {
	pManager->ClearUndoableActionsStack();
	pManager->ClearRedoableActionsStack();
	pManager->ResetColors();
	pManager->ClearFigures();

	if (!pManager->IsCurrentlyPlayingRecording() && !pManager->IsCurrentlyRecording()) {
		pManager->SetRecordingState(false);
		pManager->ClearRecordedActionsList();
		CFigure::ResetID();
		pManager->GetOutput()->ClearStatusBar();
	}

	return true;
}

void ClearAllAction::PlayRecord() {
	Execute();
}
