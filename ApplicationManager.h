#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Containers\FigureList.h"
#include "Containers\UndoableActionStack.h"

// Main class that manages everything in the application.
class ApplicationManager
{
	enum
	{
		MaxFigCount = 200,
		MaxUndoableActions = 5
	}; // Max no of figures

private:
	FigureList FigList; // List of done figures

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
	void AddFigure(CFigure *pFig);			// Adds a new figure to the FigList
	void RemoveFigure(CFigure *pFig);		// Removes a figure from the FigList
	CFigure *GetFigure(int x, int y) const; // Search for a figure given a point inside the figure
	CFigure* GetRandomFigure();				// Creates a random index and returns its corresponding figure in the FigList
	int CountColor(color);
	int CountFigure(CFigure*);				// Counts how many instances of a passed figure
	int CountFigColor(CFigure*);
	int FiguresCount();						// Returns the number of figures in FigList
	void UnhideFigures();					// Reveals the hidden figures during the Play Mode 
	CFigure* GetSelected();
	void SetSelected(CFigure*);

	// -- Undo & Redo Stacks
	UndoableActionStack &GetUndoableActionsStack();
	UndoableActionStack &GetRedoableActionsStack();
	void ClearRedoableActionsStack();

	// -- Interface Management Functions
	Input *GetInput() const;	  // Return pointer to the input
	Output *GetOutput() const;	  // Return pointer to the output
	void UpdateInterface() const; // Redraws all the drawing window
};

#endif