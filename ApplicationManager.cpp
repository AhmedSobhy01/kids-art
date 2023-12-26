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

ApplicationManager::ApplicationManager() : FigList(MaxFigCount), RecordedActions(MaxRecordableActions), IsRecording(false), IsPlayingRecording(false), UndoableActions(MaxUndoableActions), RedoableActions(MaxUndoableActions), PlayActionSoundEnabled(true)
{
	// Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	SelectedFig = NULL; // Initialize the selected figure by NULL
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action *pAct = NULL;

	// According to action type, create the corresponding action object and execute it
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
		pAct = new ExitAction(this);
		break;
	case STATUS: // a click on the status bar
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		if (ActType != UNDO && ActType != REDO) // If the action is not undo or redo, clear the redoable actions stack
			ClearRedoableActionsStack();

		bool result = pAct->Execute(); // Execute the action

		if (result) // Play sound if action executed correctly
			PlayActionSound(ActType);

		bool a = AddActionToRecordings(pAct, result); // Add the action to the recorded actions list
		bool b = AddActionToUndoables(pAct, result);  // Add the action to the undoable actions stack

		if (!a && !b) // If the action is not added to the recorded actions list or the undoable actions stack, delete it
			delete pAct;

		pAct = NULL; // Reset the pointer to the action
	}
}

//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//
void ApplicationManager::AddFigure(CFigure *pFig)
{
	FigList.PushBack(pFig); // Add the figure to the end of the list
}

void ApplicationManager::AddFigure(CFigure *pFig, int Index)
{
	FigList.PushBack(pFig, Index); // Add the figure to the end of the list at a specific index
}

int ApplicationManager::RemoveFigure(CFigure *pFig)
{
	return FigList.Remove(pFig); // Remove the figure from the list and return its index
}

CFigure *ApplicationManager::GetSelected()
{
	return SelectedFig; // Return the selected figure
}

void ApplicationManager::SetSelected(CFigure *c)
{
	SelectedFig = c; // Set the selected figure
}

//==================================================================================//
//						Recording Actions Functions									//
//==================================================================================//
bool ApplicationManager::AddActionToRecordings(Action *pAct, bool Flag)
{
	if (IsCurrentlyRecording() && Flag && pAct->ShouldRecord()) // If the user is currently recording and the action should be recorded, add the action to the recorded actions list
	{
		RecordedActions.PushBack(pAct); // Add the action to the end of the list

		if (RecordedActions.Size() == MaxRecordableActions) // If the number of recorded actions reaches the maximum number of recordable actions, stop recording
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
	int Size = RecordedActions.Size(); // Get the number of recorded actions

	for (int i = 0; i < Size; i++) // Delete all recorded actions
	{
		Action *pAct = RecordedActions.PopBack(); // Remove the last action from the list

		if (pAct->CanBeDeleted()) // If the action can be deleted, delete it
			delete pAct;
	}
}

void ApplicationManager::SetRecordingState(bool State)
{
	IsRecording = State;			// Set recording state
	pOut->SetRecordingState(State); // Set recording state in the output class as well (to change the color of the record button)
}

bool ApplicationManager::CanRecord() const
{
	return FigList.Empty() && UndoableActions.Empty() && RedoableActions.Empty(); // Return true if the FigList and the undoable and redoable actions stacks are empty
}

bool ApplicationManager::IsCurrentlyRecording() const
{
	return IsRecording; // Return true if the user is currently recording
}

void ApplicationManager::SetPlayingRecordingState(bool State)
{
	IsPlayingRecording = State; // Set playing recording state
}

bool ApplicationManager::IsCurrentlyPlayingRecording() const
{
	return IsPlayingRecording; // Return true if the user is currently playing a recording
}

//==================================================================================//
//						Figures Play Model Helper Functions							//
//==================================================================================//
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	Point P = {x, y}; // Create a point with the given coordinates

	bool Found = false;			// Flag to indicate whether a figure is found or not
	int i = FigList.Size() - 1; // Start searching from the last figure in the list

	while (i >= 0 && !Found) // Search for a figure until a figure is found or the end of the list is reached
	{
		if (FigList[i]->IsPointInside(P)) // If the point is inside the figure, set the flag to true and stop searching
		{
			Found = true;
		}
		else
			i--;
	}

	if (Found) // If a figure is found, return it
		return FigList[i];

	return NULL; // If no figure is found, return NULL
}

CFigure *ApplicationManager::GetRandomFigure()
{
	int j = rand() % FigList.Size(); // Generate a random number between 0 and the number of figures in the FigList

	return FigList[j];
}

void ApplicationManager::ClearFigures()
{
	int Size = FigList.Size(); // Get the number of figures in the FigList

	for (int i = 0; i < Size; i++) // Delete all figures
	{
		CFigure *pFig = FigList.PopBack(); // Remove the last figure from the list

		if (pFig->CanBeDeleted()) // If the figure can be deleted, delete it
			delete pFig;
	}
}

int ApplicationManager::CountFigColor(CFigure *Fig)
{
	int Counter = 0; // Counter to count the number of figures with the same color and type

	for (int i = 0; i < FigList.Size(); i++) // Loop on all figures in the FigList
	{
		if (*(FigList[i]) == *Fig) // If the figure has the same type and color, increment the counter
			Counter++;
	}

	return Counter;
}

void ApplicationManager::ResetColors()
{
	UI.DrawColor = BLUE;
	UI.BackgroundColor = BASE;
	UI.FillColor = TRANSPARENT_COLOR;
	UI.PenWidth = 3;
}

int ApplicationManager::CountFigure(CFigure *fig)
{
	int Counter = 0; // Counter to count the number of figures with the same type

	for (int i = 0; i < FigList.Size(); i++) // Loop on all figures in the FigList
	{
		if (FigList[i] == fig) // If the figure has the same type, increment the counter
			Counter++;
	}

	return Counter;
}

int ApplicationManager::CountColor(color RandomColor)
{
	int Counter = 0; // Counter to count the number of figures with the same color

	for (int i = 0; i < FigList.Size(); i++) // Loop on all figures in the FigList
	{
		if (FigList[i]->GetFillColor() == RandomColor) // If the figure has the same color, increment the counter
			Counter++;
	}

	return Counter;
}

int ApplicationManager::FiguresCount()
{
	return FigList.Size(); // Return the number of figures in the FigList
}

void ApplicationManager::UnhideFigures()
{
	for (int i = 0; i < FigList.Size(); i++) // Loop on all figures in the FigList and unhide them
		FigList[i]->Unhide();
}

//==================================================================================//
//						Save & Load Functions										//
//==================================================================================//
void ApplicationManager::SaveAll(ofstream &FileOutputStream)
{
	FileOutputStream << UI.DrawColor << " " << UI.FillColor << " " << UI.BackgroundColor << " " << UI.PenWidth << endl;
	FileOutputStream << FiguresCount() << endl;
	for (int i = 0; i < FiguresCount(); i++)
		FigList[i]->Save(FileOutputStream);
}

//==================================================================================//
//						Action Sound Functions										//
//==================================================================================//
void ApplicationManager::PlayActionSound(ActionType ActType) const
{
	if (ShouldPlayActionSound()) // If the user wants to play action sounds, play the corresponding sound
	{
		char *Filename = NULL; // Filename of the sound to be played

		switch (ActType) // Set the filename according to the action type
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
			PlaySound(Filename, NULL, SND_FILENAME | SND_ASYNC); // Play the sound
	}
}

bool ApplicationManager::ShouldPlayActionSound() const
{
	return PlayActionSoundEnabled;
}

void ApplicationManager::SetPlayActionSoundState(bool State)
{
	PlayActionSoundEnabled = State;		  // Set the flag to indicate whether the user wants to play action sounds or not
	pOut->SetPlayActionSoundState(State); // Set the flag in the output class as well (to change the color of the sound button)
}

//==================================================================================//
//						Undo & Redo Functions										//
//==================================================================================//
bool ApplicationManager::AddActionToUndoables(Action *pAct, bool Flag)
{
	if (Flag && dynamic_cast<UndoableAction *>(pAct) != NULL) // If the action is undoable and executed correctly, add it to the undoable actions stack
	{
		UndoableActions.Push(dynamic_cast<UndoableAction *>(pAct)); // Add the action to the end of the stack

		return true;
	}

	return false; // Return false if the action is not undoable or not executed correctly
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
	int Size = UndoableActions.Size(); // Get the number of actions in the stack

	for (int i = 0; i < Size; i++) // Delete all actions
	{
		UndoableAction *pAct = UndoableActions.Pop(); // Remove the last action from the stack

		if (pAct->CanBeDeleted()) // If the action can be deleted, delete it
			delete pAct;
	}
}

void ApplicationManager::ClearRedoableActionsStack()
{
	int Size = RedoableActions.Size(); // Get the number of actions in the stack

	for (int i = 0; i < Size; i++) // Delete all actions
	{
		UndoableAction *pAct = RedoableActions.Pop(); // Remove the last action from the stack

		if (pAct->CanBeDeleted()) // If the action can be deleted, delete it
			delete pAct;
	}
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea(); // Clear the drawing area

	for (int i = 0; i < FigList.Size(); i++) // Loop on all figures in the FigList
	{
		if (!FigList[i]->IsHidden()) // If the figure is not hidden, draw it
			FigList[i]->Draw(pOut);
	}

	pOut->UpdateInterface(); // Update the interface
}

Input *ApplicationManager::GetInput() const
{
	return pIn;
}

Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pIn;	 // Delete the input
	delete pOut; // Delete the output
}
