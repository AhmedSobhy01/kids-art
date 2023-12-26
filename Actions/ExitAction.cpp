#include "ExitAction.h"
#include "ClearAllAction.h"

ExitAction::ExitAction(ApplicationManager *pApp) : Action(pApp)
{
}

void ExitAction::ReadActionParameters(){};

bool ExitAction::Execute()
{
	pManager->SetRecordingState(false);

	ClearAllAction *pClearAllAct = new ClearAllAction(pManager);
	pClearAllAct->Execute();
	delete pClearAllAct;

	return true;
};