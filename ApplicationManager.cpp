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
#include "Actions\ChangeBorderWidthAction.h"

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
	case BORDER_WIDTH:
		pAct = new ChangeBorderWidthAction(this);
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
	FigList.PushBack(pFig);
}
void ApplicationManager::AddFigure(CFigure *pFig, int Index)
{
	FigList.PushBack(pFig, Index);
}
///////s/////////////////////////////////////////////////////////////////////////////
int ApplicationManager::RemoveFigure(CFigure *pFig)
{
	return FigList.Remove(pFig);
}
CFigure *ApplicationManager::GetSelected()
{
	return SelectedFig;
}
void ApplicationManager::SetSelected(CFigure *c)
{
	SelectedFig = c;
}

bool ApplicationManager::AddActionToRecordings(Action *pAct, bool Flag)
{
	if (IsCurrentlyRecording() && Flag && pAct->ShouldRecord())
	{
		RecordedActions.PushBack(pAct);

		if (RecordedActions.Size() == MaxRecordableActions)
		{
			SetRecordingState(false);

			pOut->PrintMessage("Recording stopped (operations: " + to_string(RecordedActions.Size()) + ").");
		}

		return true;
	}

	return false;
}

List<Action> &ApplicationManager::GetRecordedActionsList()
{
	return RecordedActions;
}

void ApplicationManager::ClearRecordedActionsList()
{
	int Size = RecordedActions.Size();

	for (int i = 0; i < Size; i++)
	{
		Action *pAct = RecordedActions.PopBack();

		if (pAct->CanBeDeleted())
			delete pAct;
	}
}
void ApplicationManager::SetRecordingState(bool State)
{
	IsRecording = State;
	pOut->SetRecordingState(State);
}
bool ApplicationManager::CanRecord() const
{
	return FigList.Empty() && UndoableActions.Empty() && RedoableActions.Empty();
}
bool ApplicationManager::IsCurrentlyRecording() const
{
	return IsRecording;
}
void ApplicationManager::SetPlayingRecordingState(bool State)
{
	IsPlayingRecording = State;
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
	Point P = {x, y};
	bool Found = false;
	int i = FigList.Size() - 1;
	while (i >= 0 && !Found)
	{
		if (FigList[i]->IsPointInside(P))
		{
			Found = true;
		}
		else
			i--;
	}

	if (Found)
		return FigList[i];

	// Add your code here to search for a figure given a point x,y
	// Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}

CFigure *ApplicationManager::GetRandomFigure()
{
	int j = rand() % FigList.Size();
	return FigList[j];
}

void ApplicationManager::ClearFigures()
{
	int Size = FigList.Size();

	for (int i = 0; i < Size; i++)
	{
		CFigure *pFig = FigList.PopBack();

		if (pFig->CanBeDeleted())
			delete pFig;
	}
}

void ApplicationManager::SaveAll(ofstream &FileOutputStream)
{
	FileOutputStream << UI.DrawColor << " " << UI.FillColor << " " << UI.BackgroundColor << endl;
	FileOutputStream << FiguresCount() << endl;
	for (int i = 0; i < FiguresCount(); i++)
		FigList[i]->Save(FileOutputStream);
}

int ApplicationManager::CountFigColor(CFigure *Fig)
{
	int Counter = 0;
	for (int i = 0; i < FigList.Size(); i++)
	{
		if (FigList[i]->Type() == Fig->Type() && FigList[i]->GetFillColor() == Fig->GetFillColor())
			Counter++;
	}
	return Counter;
}

void ApplicationManager::ResetColors()
{
	UI.DrawColor = BLUE;
	UI.BackgroundColor = BASE;
	UI.FillColor = TRANSPARENT_COLOR;
}

int ApplicationManager::CountFigure(CFigure *fig)
{
	int Counter = 0;
	for (int i = 0; i < FigList.Size(); i++)
	{
		if (FigList[i]->Type() == fig->Type())
			Counter++;
	}
	return Counter;
}

int ApplicationManager::CountColor(color RandomColor)
{
	int Counter = 0;
	for (int i = 0; i < FigList.Size(); i++)
	{
		if (FigList[i]->GetFillColor() == RandomColor)
			Counter++;
	}
	return Counter;
}

int ApplicationManager::FiguresCount()
{
	return FigList.Size();
}

void ApplicationManager::UnhideFigures()
{
	for (int i = 0; i < FigList.Size(); i++)
		FigList[i]->Unhide();
}

void ApplicationManager::PlayActionSound(ActionType ActType) const
{
	if (ShouldPlayActionSound())
	{
		char *Filename = NULL;

		switch (ActType)
		{
		case DRAW_RECT:
			Filename = "sounds\\Rectangle.wav";
			break;
		case DRAW_SQUARE:
			Filename = "sounds\\Square.wav";
			break;
		case DRAW_TRIANGLE:
			Filename = "sounds\\Triangle.wav";
			break;
		case DRAW_CIRCLE:
			Filename = "sounds\\Circle.wav";
			break;
		case DRAW_HEXAGON:
			Filename = "sounds\\Hexagon.wav";
			break;
		case OUTLINE_COLOR:
			Filename = "sounds\\OutlineColorChanged.wav";
			break;
		case FILL_COLOR:
			Filename = "sounds\\FillColorChanged.wav";
			break;
		case REMOVE:
			Filename = "sounds\\Deleted.wav";
			break;
		}

		if (Filename != NULL)
			PlaySound(Filename, NULL, SND_FILENAME | SND_ASYNC);
	}
}

bool ApplicationManager::ShouldPlayActionSound() const
{
	return PlayActionSoundEnabled;
}

void ApplicationManager::SetPlayActionSoundState(bool State)
{
	PlayActionSoundEnabled = State;
	pOut->SetPlayActionState(State);
}

bool ApplicationManager::AddActionToUndoables(Action *pAct, bool Flag)
{
	if (Flag && dynamic_cast<UndoableAction *>(pAct) != NULL)
	{
		UndoableActions.Push(dynamic_cast<UndoableAction *>(pAct));

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
	int Size = UndoableActions.Size();

	for (int i = 0; i < Size; i++)
	{
		UndoableAction *pAct = UndoableActions.Pop();

		if (pAct->CanBeDeleted())
			delete pAct;
	}
}
void ApplicationManager::ClearRedoableActionsStack()
{
	int Size = RedoableActions.Size();

	for (int i = 0; i < Size; i++)
	{
		UndoableAction *pAct = RedoableActions.Pop();

		if (pAct->CanBeDeleted())
			delete pAct;
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

// Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigList.Size(); i++)
	{
		if (!FigList[i]->IsHidden())
			FigList[i]->Draw(pOut); // Call Draw function (virtual member fn)
	}
	pOut->UpdateInterface();
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
	delete pIn;
	delete pOut;
}
