#ifndef FIGURE_STACK_H
#define FIGURE_STACK_H

#include "../Actions/Action.h"

class ActionStack
{
	Action** items;
	int ItemsCount;
	int MaxSize;

public:
	ActionStack(int);

	int size() const;
	void push(Action*);
	Action* pop();
	Action* top() const;
	bool empty() const;
	void clear();

	~ActionStack();
};

#endif