#include <windows.h>
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
#include "Actions\StartRecordingAction.h"
#include "Actions\StopRecordingAction.h"
#include "Actions\PlayRecordingAction.h"
#include "Actions\UndoAction.h"
#include "Actions\RedoAction.h"
#include "Actions\ChangeFillColorAction.h"
#include "Actions\ChangeOutlineColorAction.h"
#include "Actions\ChangeBackgroundColorAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions\PickByShapeAction.h"
#include "Actions\PickByColorAction.h"
#include "Actions\PickByShapeAndColorAction.h"
#include "Actions\SaveAction.h"
#include "Actions\LoadAction.h"
#include "Actions\ToggleSoundAction.h"
#include "Actions\ExitAction.h"
#include "Actions\DragMoveAction.h"
#include "Actions\DragResizeAction.h"

// Constructor
ApplicationManager::ApplicationManager() : FigList(MaxFigCount), RecordedActions(MaxRecordableActions), IsRecording(false), IsPlayingRecording(false), UndoableActions(MaxUndoableActions), RedoableActions(MaxUndoableActions), PlayActionSoundEnabled(true)
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
	case START_RECORDING:
		pAct = new StartRecordingAction(this);
		break;
	case STOP_RECORDING:
		pAct = new StopRecordingAction(this);
		break;
	case PLAY_RECORDING:
		pAct = new PlayRecordingAction(this);
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
	case BACKGROUND_COLOR:
		pAct = new ChangeBackgroundColorAction(this);
		break;
	case REMOVE:
		pAct = new DeleteAction(this);
		break;
	case CLEAR_ALL:
		pAct = new ClearAllAction(this);
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
	case SAVE_GRAPH:
		pAct = new SaveAction(this);
		break;
	case OPEN_GRAPH:
		pAct = new LoadAction(this);
		break;
	case DRAG_MOVE:
		pAct = new DragMoveAction(this);
		break;
	case DRAG_RESIZE:
		pAct = new DragResizeAction(this);
		break;
	case TOGGLE_SOUND:
		pAct = new ToggleSoundAction(this);
		break;
	case EXIT:
		/// create ExitAction here
		pAct = new ExitAction(this);
		break;
	case STATUS: // a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		if (ActType != UNDO && ActType != REDO)
			ClearRedoableActionsStack();

		bool result = pAct->Execute(); // Execute
		
		if (result) // Play sound if action executed correctly
			PlayActionSound(ActType);

		bool a = AddActionToRecordings(pAct, result);
		bool b = AddActionToUndoables(pAct, result);

		if (!a && !b)
			delete pAct;

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
void ApplicationManager::AddFigure(CFigure *pFig, int index)
{
	FigList.push_back(pFig, index);
}
///////s/////////////////////////////////////////////////////////////////////////////
int ApplicationManager::RemoveFigure(CFigure *pFig)
{
	return FigList.remove(pFig);
}
CFigure *ApplicationManager::GetSelected()
{
	return SelectedFig;
}
void ApplicationManager::SetSelected(CFigure *c)
{
	SelectedFig = c;
}

bool ApplicationManager::AddActionToRecordings(Action *pAct, bool flag)
{
	if (IsCurrentlyRecording() && flag && pAct->ShouldRecord())
	{
		RecordedActions.push_back(pAct);

		if (RecordedActions.size() == MaxRecordableActions)
		{
			SetRecordingState(false);

			pOut->PrintMessage("Recording stopped (operations: " + to_string(RecordedActions.size()) + ").");
		}

		return true;
	}

	return false;
}

List<Action>& ApplicationManager::GetRecordedActionsList()
{
	return RecordedActions;
}

void ApplicationManager::ClearRecordedActionsList()
{
	int size = RecordedActions.size();

	for (int i = 0; i < size; i++) {
		Action* pAct = RecordedActions.pop_back();

		if (pAct->CanBeDeleted()) delete pAct;
	}
}
void ApplicationManager::SetRecordingState(bool state)
{
	IsRecording = state;
}
bool ApplicationManager::CanRecord() const
{
	return FigList.empty() && UndoableActions.empty() && RedoableActions.empty();
}
bool ApplicationManager::IsCurrentlyRecording() const
{
	return IsRecording;
}
void ApplicationManager::SetPlayingRecordingState(bool state)
{
	IsPlayingRecording = state;
}
bool ApplicationManager::IsCurrentlyPlayingRecording() const
{
	return IsPlayingRecording;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	// If a figure is found return a pointer to it.
	// if this point (x,y) does not belong to any figure return NULL
	Point P = { x,y };
	bool found = false;
	int i = FigList.size() - 1;
	while (i >= 0 && !found)
	{
		if (FigList[i]->IsPointInside(P))
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

CFigure *ApplicationManager::GetRandomFigure()
{
	int j = rand() % FigList.size();
	return FigList[j];
}

void ApplicationManager::ClearFigures()
{
	int size = FigList.size();

	for (int i = 0; i < size; i++) {
		CFigure* pFig = FigList.pop_back();

		if (pFig->CanBeDeleted()) delete pFig;
	}
}

void ApplicationManager::SaveAll(ofstream& fout)
{
	fout << UI.DrawColor << " " << UI.FillColor << " " << UI.BkGrndColor << endl;
	fout << FiguresCount() << endl;
	for (int i = 0; i < FiguresCount(); i++)
		FigList[i]->Save(fout);
}

int ApplicationManager::CountFigColor(CFigure *Fig)
{
	int counter = 0;
	for (int i = 0; i < FigList.size(); i++)
	{
		if (FigList[i]->Type() == Fig->Type() && FigList[i]->GetFillClr() == Fig->GetFillClr())
			counter++;
	}
	return counter;
}

void ApplicationManager::ResetColors()
{
	UI.DrawColor = BLUE;
	UI.BkGrndColor = BASE;
	UI.FillColor = TRANSPARENT_COLOR;
}

int ApplicationManager::CountFigure(CFigure *fig)
{
	int counter = 0;
	for (int i = 0; i < FigList.size(); i++)
	{
		if (FigList[i]->Type() == fig->Type())
			counter++;
	}
	return counter;
}

int ApplicationManager::CountColor(color RandomColor)
{
	int counter = 0;
	for (int i = 0; i < FigList.size(); i++)
	{
		if (FigList[i]->GetFillClr() == RandomColor)
			counter++;
	}
	return counter;
}

int ApplicationManager::FiguresCount()
{
	return FigList.size();
}

void ApplicationManager::UnhideFigures()
{
	for (int i = 0; i < FigList.size(); i++)
		FigList[i]->UnHide();
}

void ApplicationManager::PlayActionSound(ActionType ActType) const
{
	if (ShouldPlayActionSound()) {
		char* filename = NULL;

		switch (ActType) {
			case DRAW_RECT:
				filename = "sounds\\Rectangle.wav";
				break;
			case DRAW_SQUARE:
				filename = "sounds\\Square.wav";
				break;
			case DRAW_TRIANGLE:
				filename = "sounds\\Triangle.wav";
				break;
			case DRAW_CIRCLE:
				filename = "sounds\\Circle.wav";
				break;
			case DRAW_HEXAGON:
				filename = "sounds\\Hexagon.wav";
				break;
			case OUTLINE_COLOR:
				filename = "sounds\\OutlineColorChanged.wav";
				break;
			case FILL_COLOR:
				filename = "sounds\\FillColorChanged.wav";
				break;
			case REMOVE:
				filename = "sounds\\Deleted.wav";
				break;
		}

		if (filename != NULL)
			PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
	}
}

bool ApplicationManager::ShouldPlayActionSound() const
{
	return PlayActionSoundEnabled;
}

void ApplicationManager::SetPlayActionSoundState(bool state)
{
	PlayActionSoundEnabled = state;
}

bool ApplicationManager::AddActionToUndoables(Action *pAct, bool flag)
{
	if (flag && dynamic_cast<UndoableAction *>(pAct) != NULL)
	{
		UndoableActions.push(dynamic_cast<UndoableAction *>(pAct));

		return true;
	}

	return false;
}
UndoableActionStack &ApplicationManager::GetUndoableActionsStack()
{
	return UndoableActions;
}
UndoableActionStack &ApplicationManager::GetRedoableActionsStack()
{
	return RedoableActions;
}
void ApplicationManager::ClearUndoableActionsStack()
{
	int size = UndoableActions.size();

	for (int i = 0; i < size; i++) {
		UndoableAction* pAct = UndoableActions.pop();

		if (pAct->CanBeDeleted()) delete pAct;
	}
}
void ApplicationManager::ClearRedoableActionsStack()
{
	int size = RedoableActions.size();


	for (int i = 0; i < size; i++) {
		UndoableAction* pAct = RedoableActions.pop();

		if (pAct->CanBeDeleted()) delete pAct;
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

// Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigList.size(); i++)
	{
		if (!FigList[i]->isHidden())
			FigList[i]->Draw(pOut); // Call Draw function (virtual member fn)
	}
	pOut->updateBuffer();
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
