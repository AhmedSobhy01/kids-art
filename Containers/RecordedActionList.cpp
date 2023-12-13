#include "RecordedActionList.h"

RecordedActionList::RecordedActionList(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize)
{
	items = new Action *[MaxSize];

	for (int i = 0; i < MaxSize; i++)
		items[i] = NULL;
}

Action *RecordedActionList::operator[](int index) const
{
	if (index < ItemsCount && index >= 0)
		return items[index];

	return NULL;
}

int RecordedActionList::size() const
{
	return ItemsCount;
}

void RecordedActionList::push_back(Action *item, int index)
{
	if (item && ItemsCount < MaxSize && items[index] == NULL)
	{
		items[index] = item;
		item->IncrementReference();

		ItemsCount++;
	}
}

void RecordedActionList::push_back(Action *item)
{
	push_back(item, ItemsCount);
}

Action *RecordedActionList::pop_back()
{
	if (!empty())
		return remove(ItemsCount - 1);

	return NULL;
}

Action *RecordedActionList::remove(int index)
{
	if (index < ItemsCount && index >= 0)
	{
		Action *item = items[index];

		items[index] = NULL;
		item->DecrementReference();

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

int RecordedActionList::remove(Action *item)
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

bool RecordedActionList::empty() const
{
	return ItemsCount == 0;
}

void RecordedActionList::clear()
{
	for (int i = 0; i < ItemsCount; i++)
		items[i] = NULL;

	ItemsCount = 0;
}

RecordedActionList::~RecordedActionList()
{
	clear();

	delete items;
}