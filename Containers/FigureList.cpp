#include "FigureList.h"

FigureList::FigureList(int _MaxSize): ItemsCount(0), MaxSize(_MaxSize)
{
	items = new CFigure * [MaxSize];

	for (int i = 0; i < MaxSize; i++)
		items[i] = NULL;
}

CFigure* FigureList::operator[](int index) const
{
	if (index < ItemsCount && index >= 0)
		return items[index];

	return NULL;
}

int FigureList::size() const
{
	return ItemsCount;
}

void FigureList::push_back(CFigure* item)
{
	if (item && ItemsCount < MaxSize)
		items[ItemsCount++] = item;
}

CFigure* FigureList::pop_back()
{
	if (!empty()) {
		CFigure* item = items[ItemsCount - 1];

		items[--ItemsCount] = NULL;

		return item;
	}

	return NULL;
}

CFigure* FigureList::remove(int index)
{
	if (index < ItemsCount && index >= 0) {
		CFigure* item = items[index];

		items[index] = NULL;

		int i = index;
		while (items[i + 1] != NULL && i < ItemsCount) {
			items[i] = items[i + 1];
			items[i + 1] = NULL;
			i++;
		}

		ItemsCount--;
		
		return item;
	}

	return NULL;
}

CFigure* FigureList::remove(CFigure* item)
{
	if (item && !empty()) {
		int index = -1;

		int i = 0;
		while (index == -1 && i < ItemsCount) {
			if (items[i] == item)
				index = i;
			i++;
		}

		if (index != -1)
			return remove(index);
	}

	return NULL;
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
