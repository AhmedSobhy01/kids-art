#ifndef UNDOABLE_ACTION_STACK_H
#define UNDOABLE_ACTION_STACK_H

class UndoableAction;

class UndoableActionStack
{
	UndoableAction **items;
	int ItemsCount;
	int MaxSize;

public:
	UndoableActionStack(int);

	int Size() const;
	void push(UndoableAction *);
	UndoableAction *Pop();
	UndoableAction *Top() const;
	bool Empty() const;
	void Clear();

	~UndoableActionStack();
};

#endif