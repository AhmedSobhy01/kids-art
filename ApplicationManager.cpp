#include "ApplicationManager.h"
#include "Actions\UndoableAction.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddHexagonAction.h"
#include "Actions\SelectAction.h"
#include "Actions\MoveAction.h"
#include "Actions\SwitchToDrawAction.h"
#include "Actions\SwitchToPlayAction.h"
#include "Actions\UndoAction.h"
#include "Actions\RedoAction.h"
#include "Actions\ChangeFillColorAction.h"
#include "Actions\ChangeOutlineColorAction.h"
#include "Actions/PickByShapeAction.h"
#include "Actions/PickByColorAction.h"
#include "Actions/PickByShapeAndColorAction.h"
#include <iostream>

// Constructor
ApplicationManager::ApplicationManager() : FigList(MaxFigCount), UndoableActions(MaxUndoableActions), RedoableActions(MaxUndoableActions)
{
  // Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	SelectedFig = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action *pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case TO_PLAY:
		pAct = new SwitchToPlayAction(this);
		break;
	case TO_DRAW:
		pAct = new SwitchToDrawAction(this);
		break;
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;
	case DRAW_SQUARE:
		pAct = new AddSquareAction(this);
		break;
	case DRAW_TRIANGLE:
		pAct = new AddTriangleAction(this);
		break;
	case DRAW_CIRCLE:
		pAct = new AddCircleAction(this);
		break;
	case DRAW_HEXAGON:
		pAct = new AddHexagonAction(this);
		break;
	case SELECT:
		pAct = new SelectAction(this);
		break;
	case MOVE:
		pAct = new MoveAction(this);
		break;
	case UNDO:
		pAct = new UndoAction(this);
		break;
	case REDO:
		pAct = new RedoAction(this);
		break;
	case OUTLINE_COLOR:
		pAct = new ChangeOutlineColorAction(this);
		break;
	case FILL_COLOR:
		pAct = new ChangeFillColorAction(this);
		break;
	case PICK_BY_SHAPE:
		pAct = new PickByShapeAction(this);
		break;
	case PICK_BY_COLOR:
		pAct = new PickByColorAction(this);
		break;
	case PICK_BY_SHAPE_COLOR:
		pAct = new PickByShapeAndColorAction(this);
		break;
	case EXIT:
		/// create ExitAction here

		break;
	case STATUS: // a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		bool result = pAct->Execute(); // Execute

		if (ActType != UNDO && ActType != REDO)
			ClearRedoableActionsStack();

		if (dynamic_cast<UndoableAction *>(pAct) == NULL)
		{
			delete pAct;
		}
		else
			if (result)
				UndoableActions.push(dynamic_cast<UndoableAction *>(pAct));

		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

// Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure *pFig)
{
	FigList.push_back(pFig);
}
///////s/////////////////////////////////////////////////////////////////////////////
void ApplicationManager::RemoveFigure(CFigure *pFig)
{
	CFigure *f = FigList.remove(pFig);
}
CFigure* ApplicationManager::GetSelected() {
	return SelectedFig;
}
void ApplicationManager::SetSelected(CFigure* c) {
	SelectedFig = c;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	// If a figure is found return a pointer to it.
	// if this point (x,y) does not belong to any figure return NULL
	bool found = false;
	int i = FigList.size() - 1;
	while (i >= 0 && !found)
	{
		if (FigList[i]->CheckSelected(x, y))
		{
			found = true;
		}
		else
			i--;
	}

	if (found)
		return FigList[i];

	// Add your code here to search for a figure given a point x,y
	// Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}

CFigure* ApplicationManager::GetRandomFigure() {
	int j = rand() % FigList.size();
	return FigList[j];
}

color ApplicationManager::GetRandomColor() {
	return GetRandomFigure()->GetColor();
}

int ApplicationManager::CountRandomFigColor(CFigure* Fig)
{
	int counter = 0;
	for (int i = 0; i < FigList.size(); i++) {
		if (FigList[i]->Type() == Fig->Type() && FigList[i]->GetColor() == Fig->GetColor()) counter++;
	}
	return counter;
}

int ApplicationManager::CountFigure(CFigure* fig)
{
	int counter =0;
	for (int i = 0; i < FigList.size(); i++) {
		if (FigList[i]->Type() == fig->Type())counter++;
	}
	return counter;
}

int ApplicationManager::CountColor( color RandomColor)
{
	int counter = 0;
	for (int i = 0; i < FigList.size(); i++) {
		if (FigList[i]->GetColor() == RandomColor) counter++;

	}
	return counter;
}

int ApplicationManager::FiguresCount() {
	return FigList.size();
}

void ApplicationManager::UnHideFigures() {
	for (int i = 0; i < FigList.size(); i++)FigList[i]->UnHide();
}
UndoableActionStack &ApplicationManager::GetUndoableActionsStack()
{
	return UndoableActions;
}
UndoableActionStack &ApplicationManager::GetRedoableActionsStack()
{
	return RedoableActions;
}
void ApplicationManager::ClearRedoableActionsStack()
{
	for (int i = 0; i < RedoableActions.size(); i++)
	{
		delete RedoableActions.pop();
	}

	RedoableActions.clear();
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

// Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	for (int i = 0; i < FigList.size(); i++) {
		if(!FigList[i]->isHidden())FigList[i]->Draw(pOut); // Call Draw function (virtual member fn)
	}
}
////////////////////////////////////////////////////////////////////////////////////
// Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}
// Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////
// Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigList.size(); i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
}
