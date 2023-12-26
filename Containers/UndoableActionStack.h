#ifndef UNDOABLE_ACTION_STACK_H
#define UNDOABLE_ACTION_STACK_H

class UndoableAction;

class UndoableActionStack
{
	UndoableAction **items; // Array of pointers to the items of the stack
	int ItemsCount;			// Number of items in the stack
	int MaxSize;			// Maximum number of items in the stack

public:
	UndoableActionStack(int);

	int Size() const;			 // Get the number of items in the stack
	void Push(UndoableAction *); // Add an item to the end of the stack (if the stack is full, the first item will be removed)
	UndoableAction *Pop();		 // Remove the last item in the stack and return it (if the stack is empty, NULL will be returned)
	UndoableAction *Top() const; // Get the last item in the stack (if the stack is empty, NULL will be returned)
	bool Empty() const;			 // Check whether the stack is empty or not
	void Clear();				 // Remove all items from the stack

	~UndoableActionStack();
};

#endif