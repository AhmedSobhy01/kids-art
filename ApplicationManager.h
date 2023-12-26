#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Containers\List.h"
#include "Containers\UndoableActionStack.h"
#include "Actions\Action.h"
#include "Figures\CFigure.h"

// Main class that manages everything in the application.
class ApplicationManager
{
	enum
	{
		MaxFigCount = 200,		   // Max no of figures
		MaxRecordableActions = 20, // Max no of actions that can be recorded
		MaxUndoableActions = 5,	   // Max no of undoable actions
	};

	List<CFigure> FigList; // List of all figures (Array of pointers)

	List<Action> RecordedActions; // List of all recorded actions
	bool IsRecording;			  // Flag to indicate whether the user is recording or not
	bool IsPlayingRecording;	  // Flag to indicate whether the user is playing a recording or not

	UndoableActionStack UndoableActions; // Stack of actions that can be undone
	UndoableActionStack RedoableActions; // Stack of actions that can be redone

	bool PlayActionSoundEnabled; // Flag to indicate whether the user wants to play action sounds or not

	CFigure *SelectedFig; // Pointer to the selected figure

	Input *pIn;	  // Pointer to the Input object
	Output *pOut; // Pointer to the Output object

public:
	ApplicationManager();
	~ApplicationManager();

	ActionType GetUserAction() const; // Reads the input command from the user and returns the corresponding action type
	void ExecuteAction(ActionType);	  // Creates an action and executes it

	void AddFigure(CFigure *);			// Adds a new figure to the FigList
	void AddFigure(CFigure *, int);		// Adds a new figure to the FigList at a specific index
	int RemoveFigure(CFigure *);		// Removes a figure from the FigList
	CFigure *GetFigure(int, int) const; // Returns a pointer to the figure at a specific point
	void ClearFigures();				// Deletes all figures in the FigList
	void SaveAll(ofstream &);			// Saves all figures in the FigList to the file

	CFigure *GetRandomFigure();	  // Returns a pointer to a random figure in the FigList (used in Play Mode)
	int CountColor(color);		  // Counts how many figures of a specific color are in the FigList
	int CountFigure(CFigure *);	  // Counts how many figures of a specific type are in the FigList
	int CountFigColor(CFigure *); // Counts how many figures of a specific color and type are in the FigList
	void ResetColors();			  // Resets the colors of all figures in the FigList to their original colors
	int FiguresCount();			  // Returns the number of figures in the FigList
	void UnhideFigures();		  // Unhides all hidden figures in the FigList

	void PlayActionSound(ActionType) const; // Plays a sound when an action is executed
	bool ShouldPlayActionSound() const;		// Returns whether the user wants to play action sounds or not
	void SetPlayActionSoundState(bool);		// Sets whether the user wants to play action sounds or not

	CFigure *GetSelected();		 // Returns a pointer to the selected figure
	void SetSelected(CFigure *); // Sets the selected figure

	bool AddActionToRecordings(Action *, bool); // Adds an action to the recorded actions list
	List<Action> &GetRecordedActionsList();		// Returns a reference to the recorded actions list
	void ClearRecordedActionsList();			// Clears the recorded actions list

	void SetRecordingState(bool);			  // Sets the recording state
	bool CanRecord() const;					  // Returns whether the user can record or not
	bool IsCurrentlyRecording() const;		  // Returns whether the user is currently recording or not
	void SetPlayingRecordingState(bool);	  // Sets the playing recording state
	bool IsCurrentlyPlayingRecording() const; // Returns whether the user is currently playing a recording or not

	bool AddActionToUndoables(Action *, bool);		// Adds an action to the undoable actions stack
	UndoableActionStack &GetUndoableActionsStack(); // Returns a reference to the undoable actions stack
	UndoableActionStack &GetRedoableActionsStack(); // Returns a reference to the redoable actions stack
	void ClearUndoableActionsStack();				// Clears the undoable actions stack
	void ClearRedoableActionsStack();				// Clears the redoable actions stack

	Input *GetInput() const;	  // Return pointer to the input
	Output *GetOutput() const;	  // Return pointer to the output
	void UpdateInterface() const; // Redraws all the drawing area
};

#endif