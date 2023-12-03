#include "UndoableActionStack.h"

UndoableActionStack::UndoableActionStack(int _MaxSize) : ItemsCount(0), MaxSize(_MaxSize)
{
	items = new UndoableAction * [MaxSize];

	for (int i = 0; i < MaxSize; i++)
		items[i] = nullptr;
}

int UndoableActionStack::size() const
{
	return ItemsCount;
}

void UndoableActionStack::push(UndoableAction* item)
{
	if (item) {
		if (ItemsCount >= MaxSize) {
			delete items[0];
			items[0] = nullptr;

			for (int i = 1; i < ItemsCount; i++)
				items[i - 1] = items[i];

			ItemsCount--;
		}

		items[ItemsCount++] = item;
	}
}

UndoableAction* UndoableActionStack::pop()
{
	if (!empty()) {
		UndoableAction* item = items[ItemsCount - 1];
		items[ItemsCount - 1] = nullptr;

		ItemsCount--;
		return item;
	}

	return nullptr;
}

UndoableAction* UndoableActionStack::top() const
{
	if (!empty())
		return items[ItemsCount - 1];

	return nullptr;
}

bool UndoableActionStack::empty() const
{
	return ItemsCount == 0;
}

void UndoableActionStack::clear()
{
	for (int i = 0; i < ItemsCount; i++)
		items[i] = nullptr;

	ItemsCount = 0;
}

UndoableActionStack::~UndoableActionStack()
{
	clear();

	delete items;
}