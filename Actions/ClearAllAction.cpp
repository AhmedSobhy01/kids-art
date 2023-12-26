#include "ClearAllAction.h"
#include "UndoableAction.h"
#include "..\Figures\CFigure.h"

ClearAllAction::ClearAllAction(ApplicationManager *pApp) : Action(pApp)
{
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

	if (!pManager->IsCurrentlyPlayingRecording() && !pManager->IsCurrentlyRecording())
	{
		pManager->SetPlayActionSoundState(true);
		pManager->SetRecordingState(false);
		pManager->ClearRecordedActionsList();
		CFigure::ResetID();
		pManager->GetOutput()->ClearStatusBar();
	}

	return true;
}

void ClearAllAction::PlayRecord()
{
	Execute();
}
