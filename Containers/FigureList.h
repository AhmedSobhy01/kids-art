#ifndef FIGURE_LIST_H
#define FIGURE_LIST_H

#include "../Figures/CFigure.h"

class FigureList
{
	CFigure** items;
	int ItemsCount;
	int MaxSize;

public:
	FigureList(int);

	CFigure* operator[](int) const;
	int size() const;
	void push_back(CFigure*);
	CFigure* pop_back();
	CFigure* remove(int);
	CFigure* remove(CFigure*);
	void clear();

	~FigureList();
};

#endif