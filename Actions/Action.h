#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"

class ApplicationManager; // forward class declaration

// Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager; // Actions needs AppMngr to do their job
	int ReferenceCount;			  // Used to make sure object is not referenced in another place before deleting (ex: when object is placed in UndoableActions & RecordedActions)

public:
	Action(ApplicationManager *pApp) : pManager(pApp), ReferenceCount(0) {} // constructor

	virtual bool Validate() { return true; };

	// Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() = 0;

	// Execute action (code depends on action type)
	virtual bool Execute() = 0;

	virtual bool ShouldRecord() const
	{
		return true; // By default, record action
	}

	// Reference
	void IncrementReference()
	{
		ReferenceCount++;
	}

	void DecrementReference()
	{
		if (ReferenceCount > 0)
			ReferenceCount--;
	}

	bool CanBeDeleted() const
	{
		return ReferenceCount == 0;
	}

	virtual ~Action() {};
};

#endif