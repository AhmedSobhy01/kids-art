#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"

class ApplicationManager; // forward class declaration

// Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager; // Actions needs AppMngr to do their job
	bool RecordEnabled;			  // Flag to indicate whether actions should be recorded
	int ReferenceCount;			  // Used to make sure object is not referenced in another place before deleting (ex: when object is placed in UndoableActions & RecordedActions)

public:
	Action(ApplicationManager *pApp) : pManager(pApp), RecordEnabled(true), ReferenceCount(0) {}

	virtual void ReadActionParameters() = 0; // Reads parameters required for action to execute (code depends on action type)
	virtual bool Execute() = 0;				 // Execute action (code depends on action type)

	bool ShouldRecord() const // Returns whether action should be recorded or not
	{
		return RecordEnabled;
	}

	virtual void PlayRecord(){}; // Plays the action from the recorded actions stack (code depends on action type)

	// Reference counting functions
	void IncrementReference() // Increments reference count by 1
	{
		ReferenceCount++;
	}

	void DecrementReference() // Decrements reference count by 1
	{
		if (ReferenceCount > 0)
			ReferenceCount--;
	}

	bool CanBeDeleted() const // Returns whether object can be deleted or not
	{
		return ReferenceCount == 0;
	}

	virtual ~Action(){};
};

#endif