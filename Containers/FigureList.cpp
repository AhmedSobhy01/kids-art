#include "FigureList.h"

FigureList::FigureList(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize)
{
	items = new CFigure *[MaxSize];

	for (int i = 0; i < MaxSize; i++)
		items[i] = NULL;
}

CFigure *FigureList::operator[](int index) const
{
	if (index < ItemsCount && index >= 0)
		return items[index];

	return NULL;
}

int FigureList::size() const
{
	return ItemsCount;
}

void FigureList::push_back(CFigure *item, int index)
{
	if (item && ItemsCount < MaxSize && items[index] == NULL)
	{
		items[index] = item;
		ItemsCount++;
	}
}

void FigureList::push_back(CFigure *item)
{
	push_back(item, ItemsCount);
}

CFigure *FigureList::pop_back()
{
	if (!empty())
		return remove(ItemsCount - 1);

	return NULL;
}

CFigure *FigureList::remove(int index)
{
	if (index < ItemsCount && index >= 0)
	{
		CFigure *item = items[index];

		items[index] = NULL;

		int i = index;
		while (items[i + 1] != NULL && i < ItemsCount)
		{
			items[i] = items[i + 1];
			items[i + 1] = NULL;
			i++;
		}

		ItemsCount--;

		return item;
	}

	return NULL;
}

int FigureList::remove(CFigure *item)
{
	if (item && !empty())
	{
		int index = -1;

		int i = 0;
		while (index == -1 && i < ItemsCount)
		{
			if (items[i] == item)
				index = i;
			i++;
		}

		if (index != -1)
		{
			remove(index);
			return index;
		}
	}

	return -1;
}

bool FigureList::contains(CFigure *item) const
{
	int i = 0;
	bool found = false;

	while (!found && i < size())
		if (items[i++] == item)
			found = true;

	return found;
}

bool FigureList::empty() const
{
	return ItemsCount == 0;
}

void FigureList::clear()
{
	for (int i = 0; i < ItemsCount; i++)
		items[i] = NULL;

	ItemsCount = 0;
}

FigureList::~FigureList()
{
	clear();

	delete items;
}