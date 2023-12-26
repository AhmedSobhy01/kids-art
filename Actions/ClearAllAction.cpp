#include "ClearAllAction.h"
#include "UndoableAction.h"
#include "..\Figures\CFigure.h"

ClearAllAction::ClearAllAction(ApplicationManager *pApp) : Action(pApp)
{
	RecordEnabled = false;
}

void ClearAllAction::ReadActionParameters()
{
}

bool ClearAllAction::Execute()
{
	CFigure* S = pManager->GetSelected();
	if (S != NULL)
		S->SetSelected(false);

	pManager->SetSelected(NULL);
	pManager->ClearUndoableActionsStack();
	pManager->ClearRedoableActionsStack();
	pManager->ResetColors();
	pManager->ClearFigures();
	pManager->SetPlayActionSoundState(true);
	pManager->SetRecordingState(false);
	pManager->GetOutput()->ClearStatusBar();
	CFigure::ResetID();

	if (!pManager->IsCurrentlyPlayingRecording())
		pManager->ClearRecordedActionsList();

	return true;
}