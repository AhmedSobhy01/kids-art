#include "ClearAllAction.h"
#include "..\Figures\CFigure.h"
#include "..\ApplicationManager.h"
#include "UndoableAction.h"
#include "..\Figures\CFigure.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp): Action(pApp) {
	RecordEnabled = false;
}

void ClearAllAction::ReadActionParameters() {

}

bool ClearAllAction::Execute() {
	pManager->ClearUndoableActionsStack();
	pManager->ClearRedoableActionsStack();
	pManager->ResetColors();
	pManager->ClearFigures();
	pManager->GetOutput()->ClearStatusBar();

	if (!pManager->IsCurrentlyPlayingRecording()) {
		pManager->SetRecordingState(false);
		pManager->ClearRecordedActionsList();
		CFigure::ResetID();
	}

	return true;
}
