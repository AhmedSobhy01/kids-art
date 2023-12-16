#include "ExitAction.h"
#include "ClearAllAction.h"

ExitAction::ExitAction(ApplicationManager* pApp) :Action(pApp) {
}
void ExitAction::ReadActionParameters() {};

bool ExitAction::Execute() {
	ClearAllAction* clearAll = new ClearAllAction(pManager);
	clearAll->Execute();
	delete clearAll;
	return true;
};