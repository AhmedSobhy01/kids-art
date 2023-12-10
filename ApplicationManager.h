#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Containers\List.h"
#include "Containers\UndoableActionStack.h"
#include "Actions/Action.h"

// Main class that manages everything in the application.
class ApplicationManager
{
	enum
	{
		MaxFigCount = 200,
		MaxRecordableActions = 20,
		MaxUndoableActions = 5,
	}; // Max no of figures

private:
	List<CFigure> FigList; // List of done figures

	List<Action> RecordedActions; // List of recorded actions
	bool IsRecording;

	UndoableActionStack UndoableActions; // Stack of actions that can be undone
	UndoableActionStack RedoableActions; // Stack of actions that can be redone

  CFigure *SelectedFig; // Pointer to the selected figure

	// Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:
	ApplicationManager();
	~ApplicationManager();

	// -- Action-Related Functions
	// Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType); // Creates an action and executes it

	// -- Figures Management Functions
	void AddFigure(CFigure*);			// Adds a new figure to the FigList
	void AddFigure(CFigure*, int);			// Adds a new figure to the FigList at specific index
	int RemoveFigure(CFigure*);		// Removes a figure from the FigList
	CFigure *GetFigure(int, int) const; // Search for a figure given a point inside the figure
	CFigure* GetRandomFigure();				// Creates a random index and returns its corresponding figure in the FigList
	int CountColor(color);
	int CountFigure(CFigure*);				// Counts how many instances of a passed figure
	int CountFigColor(CFigure*);
	int FiguresCount();						// Returns the number of figures in FigList
	void UnhideFigures();					// Reveals the hidden figures during the Play Mode 
	CFigure* GetSelected();
	void SetSelected(CFigure*);

	// -- Recorded Actions List
	bool AddActionToRecordings(Action*);
	List<Action>& GetRecordedActionsList();
	void ClearRecordedActionsList();
	void SetRecordingState(bool);

	// -- Undo & Redo Stacks
	bool AddActionToUndoables(Action*, bool);
	UndoableActionStack &GetUndoableActionsStack();
	UndoableActionStack &GetRedoableActionsStack();
	void ClearRedoableActionsStack();

	// -- Interface Management Functions
	Input *GetInput() const;	  // Return pointer to the input
	Output *GetOutput() const;	  // Return pointer to the output
	void UpdateInterface() const; // Redraws all the drawing window
};

#endif