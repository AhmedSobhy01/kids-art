#include "FigureList.h"

FigureList::FigureList(int _MaxSize): ItemsCount(0), MaxSize(_MaxSize)
{
	items = new CFigure * [MaxSize];

	for (int i = 0; i < MaxSize; i++)
		items[i] = nullptr;
}

CFigure* FigureList::operator[](int index) const
{
	if (index < ItemsCount && index >= 0)
		return items[index];

	return nullptr;
}

int FigureList::size() const
{
	return ItemsCount;
}

void FigureList::push_back(CFigure* item)
{
	items[ItemsCount++] = item;
}

CFigure* FigureList::pop_back()
{
	CFigure* item = items[ItemsCount - 1];

	items[--ItemsCount] = nullptr;

	return item;
}

CFigure* FigureList::remove(int index)
{
	if (index < ItemsCount && index >= 0) {
		CFigure* item = items[index];

		int i = index;
		while (items[i + 1] != nullptr && i < ItemsCount) {
			items[i] = items[i + 1];
			items[i + 1] = nullptr;
			i++;
		}
		
		return item;
	}

	return nullptr;
}

CFigure* FigureList::remove(CFigure* item)
{
	if (ItemsCount > 0) {
		int index = -1;

		int i = 0;
		while(i == -1 && i < ItemsCount)
			if (items[i] == item)
				index = i;

		if (index != -1)
			return remove(index);
	}

	return nullptr;
}

void FigureList::clear()
{
	for (int i = 0; i < ItemsCount; i++)
		items[i] = nullptr;

	ItemsCount = 0;
}

FigureList::~FigureList()
{
	clear();

	delete items;
}
