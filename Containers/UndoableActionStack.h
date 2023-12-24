#ifndef UNDOABLE_ACTION_STACK_H
#define UNDOABLE_ACTION_STACK_H


class UndoableAction;

class UndoableActionStack
{
	UndoableAction** items;
	int ItemsCount;
	int MaxSize;

public:
	UndoableActionStack(int);

	int size() const;
	void push(UndoableAction*);
	UndoableAction* pop();
	UndoableAction* top() const;
	bool empty() const;
	void clear();

	~UndoableActionStack();
};

#endif