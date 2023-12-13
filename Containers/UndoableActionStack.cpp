#include "UndoableActionStack.h"
#include "../Actions/UndoableFigureAction.h"

UndoableActionStack::UndoableActionStack(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize)
{
	items = new UndoableAction *[MaxSize];

	for (int i = 0; i < MaxSize; i++)
		items[i] = NULL;
}

int UndoableActionStack::size() const
{
	return ItemsCount;
}

void UndoableActionStack::push(UndoableAction *item)
{
	if (item)
	{
		if (ItemsCount >= MaxSize)
		{
			items[0]->DecrementReference();
			if (items[0]->CanBeDeleted())
				delete items[0];
			items[0] = NULL;

			for (int i = 1; i < ItemsCount; i++)
				items[i - 1] = items[i];

			ItemsCount--;
		}

		items[ItemsCount++] = item;
		item->IncrementReference();
	}
}

UndoableAction *UndoableActionStack::pop()
{
	if (!empty())
	{
		UndoableAction *item = items[ItemsCount - 1];

		items[ItemsCount - 1] = NULL;
		item->DecrementReference();

		ItemsCount--;
		return item;
	}

	return NULL;
}

UndoableAction *UndoableActionStack::top() const
{
	if (!empty())
		return items[ItemsCount - 1];

	return NULL;
}

bool UndoableActionStack::empty() const
{
	return ItemsCount == 0;
}

void UndoableActionStack::clear()
{
	for (int i = 0; i < ItemsCount; i++)
		items[i] = NULL;

	ItemsCount = 0;
}

UndoableActionStack::~UndoableActionStack()
{
	clear();

	delete items;
}