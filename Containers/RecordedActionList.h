#ifndef RECORDED_ACTION_LIST_H
#define RECORDED_ACTION_LIST_H

#include "../Actions/Action.h"

class RecordedActionList
{
	Action** items;
	int ItemsCount;
	int MaxSize;

public:
	RecordedActionList(int);

	Action* operator[](int) const;

	int size() const;

	void push_back(Action*, int);

	void push_back(Action*);

	Action* pop_back();

	Action* remove(int);

	int remove(Action*);

	bool empty() const;

	void clear();

	~RecordedActionList();
};

#endif