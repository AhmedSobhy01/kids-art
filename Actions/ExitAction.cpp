#include "ExitAction.h"

ExitAction::ExitAction(ApplicationManager* pApp) :Action(pApp) {
	clearAll = new ClearAllAction(pApp);

}
void ExitAction::ReadActionParameters() {};

bool ExitAction::Execute() {
	clearAll->Execute();
	delete clearAll;
	return true;
};